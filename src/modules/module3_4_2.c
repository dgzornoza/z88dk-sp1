
#include "../z88dk_headers.h"
#include <intrinsic.h>
#include "./modules.h"
#include "../data/module3_4.h"

struct sp1_ss *player_sprite;
static unsigned char current_position_y = 0;

/**
 * Asignar atributos iniciales a las celdas del sprite
 * @count: número de celda dentro del sprite (0 a 28: 7cols x 4rows)
 * @cell: puntero a la estructura de la celda del sprite
 */
static void initialiseColour(unsigned int count, struct sp1_cs *cell)
{
    // celdas 2 y 3 corresponden a la antena + padding horizontal (4)
    if (count == 2 || count == 3 || count == 4)
    {
        cell->attr_mask = SP1_AMASK_INK; // alfa para la mascara
        cell->attr = INK_BLUE;           // tinta azul
    }
}

/**
 * cambiar el color de la antena en bucle pasando por todos los colores
 * @count: número de celda dentro del sprite (0 a 28: 7cols x 4rows)
 * @cell: puntero a la estructura de la celda del sprite
 */
static void changeAntennacolour(unsigned int count, struct sp1_cs *cell)
{
    // celdas 2 y 3 corresponden a la antena + padding horizontal (4)
    if (count == 2 || count == 3 || count == 4)
    {
        // incrementa el color (++cell) desde azul hasta blanco y cuando llega a blanco establece el color azul y vuelta a empezar
        // (esto es un bucle para pasar por todos los colores de tinta)
        if (++cell->attr == INK_WHITE)
        {
            cell->attr = INK_BLUE;
        }

        // obtener estructura de actualizacion.
        // si existe, es que ha sido modificado el sprite y requiere actualizacion (en este caso cell->attr ha sido modificado en las lineas anteriores).
        // Esto se requiere por que en el bucle principal el sprite baja hasta el final de la pantalla y se para,
        // de modo que si el esprite no se mueve, SP1 no invalida el sprite y no se redibuja,
        // mediante este codigo se invalida manualmente para que actualice los atributos y siga cambiando el color.
        unsigned int *update_struct = (unsigned int *)cell->update;
        // si existe estructura de actualicacion, invalidar la celda para que se redibuje con el nuevo color
        if (*update_struct)
        {
            // como es Big Endian los bytes del puntero 'update_struct',
            // deben convertirse a Little Endian (usado por el Z80) mediante la funcion 'intrinsic_swap_endian_16'
            unsigned int inv_update_struct = intrinsic_swap_endian_16((unsigned int)update_struct);
            sp1_InvUpdateStruct((void *)inv_update_struct);
        }
    }
}

static void init_player(void)
{
    // crear el sprite (con mascara), no se especifica el puntero al sprites,
    // sera especificada en la funcion 'sp1_MoveSprPix' del bucle principal.
    player_sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 4, 0, 0);
    // añadir 5 columnas usando offsets (resta entre la columna x y la columna 1)
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, sprite_mothership_column_2 - sprite_mothership_column_1, 0);
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, sprite_mothership_column_3 - sprite_mothership_column_1, 0);
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, sprite_mothership_column_4 - sprite_mothership_column_1, 0);
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, sprite_mothership_column_5 - sprite_mothership_column_1, 0);
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, sprite_mothership_column_6 - sprite_mothership_column_1, 0);
    // añadir columna con el limite derecho RB (RightBoundary)
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2RB, SP1_TYPE_2BYTE, 0, 0);

    // Aplicar atributos a cada celda del sprite
    sp1_IterateSprChar(player_sprite, initialiseColour);
}

static void main_loop(void)
{
    // iterar por cada celda del sprite y cambiar el color de la antena
    sp1_IterateSprChar(player_sprite, changeAntennacolour);

    // mover el sprite hacia abajo hasta que llegue al final de la pantalla (192 - altura del sprite)
    if (current_position_y <= 192 - 24)
    {
        // mover el sprite hacia abajo indicando el puntero al gráfico de la primera columna del sprite como 3 parametro.
        // (al no haberse especificado en la creacion del sprite, se especifica aqui, pero se podria haber especificado en la creacion del sprite))
        sp1_MoveSprPix(player_sprite, &game_area, sprite_mothership_column_1, 104, current_position_y++);
    }

    // retrasar para reducir la velocidad
    z80_delay_ms(10);

    // Fuerza el redibujado de las celdas invalidadas
    sp1_UpdateNow();
}

void run_module3_4_2(void)
{
    zx_border(PAPER_BLACK);

    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                   INK_WHITE | PAPER_BLACK, ' ');

    // Marcar área para el primer render
    sp1_Invalidate(&game_area);

    init_player();

    // ejecutar el bucle principal hasta que se presione INTRO
    wait_for_intro_key(main_loop);
}

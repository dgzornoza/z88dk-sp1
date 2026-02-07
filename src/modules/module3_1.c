
#include "../z88dk_headers.h"
#include "./modules.h"
#include "../data/module3_1.h"

// Estructura del sprite
static struct sp1_ss *player_sprite;

// Asignar atributos a las celdas del sprite
static void set_sprite_colour(unsigned int count, struct sp1_cs *c)
{
    (void)count; /* Suprimir warning del compilador por parametro no usado */
    c->attr_mask = SP1_AMASK_PAPER;
    c->attr = PAPER_RED;
}

static void init_player(void)
{
    // Crear sprite sin mascara
    player_sprite = sp1_CreateSpr(SP1_DRAW_LOAD1LB, SP1_TYPE_1BYTE, 2, (int)sprite_circle, 0);

    // Añadir columnas (una por cada 8px de ancho),
    // en este caso como solo es un sprite 8x8 (un caracter), en la columna se define con la etiqueta de fin con 'SP1_DRAW_LOAD1RB'
    // lo cual no requiere establecer el puntero al grafico
    sp1_AddColSpr(player_sprite, SP1_DRAW_LOAD1RB, SP1_TYPE_1BYTE, 0, 0);

    // Aplicar atributos a cada celda del sprite
    sp1_IterateSprChar(player_sprite, set_sprite_colour);

    // Posicionar el sprite (frame, Y, X, rotY, rotX)
    sp1_MoveSprAbs(player_sprite, &game_area, (void *)0, 10, 15, 0, 2);
}

static void main_loop(void)
{
    // Fuerza el redibujado de las celdas invalidadas
    sp1_UpdateNow();
}

void run_module3_1(void)
{
    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                   INK_WHITE | PAPER_BLACK, ' ');

    // Marcar área para el primer render
    sp1_Invalidate(&game_area);

    init_player();

    // ejecutar el bucle principal hasta que se presione INTRO
    wait_for_intro_key(main_loop);
}

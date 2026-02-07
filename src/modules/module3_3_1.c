
#include "../z88dk_headers.h"
#include "./modules.h"
#include "../data/module3_3.h"

static struct sp1_ss *player_sprite;
static int position_x = 0;
static int animation_offset = 0;

// Asignar atributos a las celdas del sprite
static void set_sprite_colour(unsigned int count, struct sp1_cs *c)
{
    (void)count; /* Suprimir warning del compilador por parametro no usado */
    c->attr_mask = SP1_AMASK_PAPER;
    c->attr = PAPER_RED;
}

static void init_player(void)
{
    // Crear sprite con el player (sin mascara)
    player_sprite = sp1_CreateSpr(SP1_DRAW_LOAD1LB, SP1_TYPE_1BYTE, 2, (int)sprite_player, 0);

    // Añadir columnas (una por cada 8px de ancho),
    // en este caso como solo es un sprite 8x8 (un caracter), en la columna se define con la etiqueta de fin con 'SP1_DRAW_LOAD1RB'
    // lo cual no requiere establecer el puntero al grafico
    sp1_AddColSpr(player_sprite, SP1_DRAW_LOAD1RB, SP1_TYPE_1BYTE, 0, 0);

    // Aplicar atributos a cada celda del sprite
    sp1_IterateSprChar(player_sprite, set_sprite_colour);
}

static void main_loop(void)
{
    // establecer el frame actual a mostrar en el sprite mediante su offset
    // como solo se establece el siguiente frame en la estructura
    // y el puntero a player_sprite es el mismo, es por esto por lo que
    // se puede rehusar el padding superior (el que esta 7 bytes antes de sprite_player)
    player_sprite->frame = (void *)animation_offset;

    // mover el sprite a la nueva posición (x)
    sp1_MoveSprPix(player_sprite, &game_area, 0, position_x++, 80);

    // incrementar el offset de los frames en 1 frame (8 bytes grafico + 8 bytes padding inferior)
    animation_offset += 16;
    // reestablecer el primer frame (8 frames * 16 = 128)
    if (animation_offset == 128)
    {
        animation_offset = 0;
    }

    // retrasar para reducir la velocidad
    z80_delay_ms(50);

    // Fuerza el redibujado de las celdas invalidadas
    sp1_UpdateNow();
}

void run_module3_3_1(void)
{
    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                   INK_WHITE | PAPER_BLACK, ' ');

    // Marcar área para el primer render
    sp1_Invalidate(&game_area);

    init_player();

    // ejecutar el bucle principal hasta que se presione INTRO
    wait_for_intro_key(main_loop);
}

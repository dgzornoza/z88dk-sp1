
#include "../z88dk_headers.h"
#include "./modules.h"
#include "../data/module3_4.h"

struct sp1_ss *player_sprite;
static unsigned char current_position_x = 0;

// Asignar atributos a las celdas del sprite
static void set_sprite_colour(unsigned int count, struct sp1_cs *c)
{
    (void)count; /* Suprimir warning del compilador por parametro no usado */
    c->attr_mask = SP1_AMASK_PAPER;
    c->attr = PAPER_RED;
}

static void init_player(void)
{
    // crear el sprite (con mascara)
    player_sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 4, (int)sprite_mothership_column_1, 0);
    // añadir 5 columnas
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, (int)sprite_mothership_column_2, 0);
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, (int)sprite_mothership_column_3, 0);
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, (int)sprite_mothership_column_4, 0);
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, (int)sprite_mothership_column_5, 0);
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, (int)sprite_mothership_column_6, 0);
    // añadir columna con el limite derecho RB (RightBoundary)
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2RB, SP1_TYPE_2BYTE, 0, 0);

    // Aplicar atributos a cada celda del sprite
    sp1_IterateSprChar(player_sprite, set_sprite_colour);
}

static void main_loop(void)
{
    sp1_MoveSprPix(player_sprite, &game_area, 0, current_position_x++, 0);

    // retrasar para reducir la velocidad
    z80_delay_ms(10);

    // Fuerza el redibujado de las celdas invalidadas
    sp1_UpdateNow();
}

void run_module3_4_2(void)
{
    zx_border(PAPER_BLACK);

    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                   INK_BLACK | PAPER_WHITE, 'Z');

    // Marcar área para el primer render
    sp1_Invalidate(&game_area);

    init_player();

    // ejecutar el bucle principal hasta que se presione INTRO
    wait_for_intro_key(main_loop);
}

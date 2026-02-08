
#include "../z88dk_headers.h"
#include "./modules.h"
#include "../data/module3_4.h"

static struct sp1_ss *player_sprite;
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
    // Crear sprite enmascarado de tipo LB (LeftBoundary): 2 bytes por línea (grafico+mascara).
    player_sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_bubble_column_1, 0);

    // segunda columna del sprite (es 16x16, de modo que tendra 2 filas de alto y 2 columnas de ancho)
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, (int)sprite_bubble_column_2, 0);

    // Añadir columna con el limite RB (RightBoundary) como en los ejemplos anteriores.
    sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2RB, SP1_TYPE_2BYTE, 0, 0);

    // Aplicar atributos a cada celda del sprite
    sp1_IterateSprChar(player_sprite, set_sprite_colour);
}

static void main_loop(void)
{
    sp1_MoveSprPix(player_sprite, &game_area, 0, current_position_x++, 80);

    // retrasar para reducir la velocidad
    z80_delay_ms(50);

    // Fuerza el redibujado de las celdas invalidadas
    sp1_UpdateNow();
}

void run_module3_4_1(void)
{
    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                   INK_WHITE | PAPER_BLACK, 'X');

    // Marcar área para el primer render
    sp1_Invalidate(&game_area);

    init_player();

    // ejecutar el bucle principal hasta que se presione INTRO
    wait_for_intro_key(main_loop);
}

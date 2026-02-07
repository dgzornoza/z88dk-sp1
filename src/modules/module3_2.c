
#include "../z88dk_headers.h"
#include "./modules.h"
#include "../data/module3_2.h"

// Estructura para manejar multiples sprites en movimiento
typedef struct
{
    struct sp1_ss *sprite;
    unsigned char x_pos;
    unsigned char y_pos;
} player_sprite;

// array con el numero de sprites a mostrar
#define NUM_SPRITES 15
player_sprite player_sprites[NUM_SPRITES];

// variable para iterar sobre los sprites en el bucle principal
unsigned char sprite_index;

// Asignar atributos a las celdas del sprite
static void set_sprite_colour(unsigned int count, struct sp1_cs *c)
{
    (void)count; /* Suprimir warning del compilador por parametro no usado */
    c->attr_mask = SP1_AMASK_PAPER;
    c->attr = PAPER_RED;
}

static void init_player(int player_index)
{
    // Crear sprite enmascarado: 2 bytes por línea (grafico+mascara).
    player_sprites[player_index].sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 2, (int)sprite_masked_circle, 0);

    // Añadir columna derecha (RB). Para este ejemplo no pasamos nueva
    // dirección de datos porque la segunda columna se compone del
    // desplazamiento del primero.
    sp1_AddColSpr(player_sprites[player_index].sprite, SP1_DRAW_MASK2RB, SP1_TYPE_2BYTE, 0, 0);

    // Aplicar atributos a cada celda del sprite
    sp1_IterateSprChar(player_sprites[player_index].sprite, set_sprite_colour);

    // Posicionar el sprite (frame, Y, X, rotY, rotX) (row=4,col=10) sin rotación
    // sp1_MoveSprAbs(player_sprites[player_index].sprite, &game_area, (void *)0, 4, 10, 0, 0);

    // almacenar posición inicial para cada sprite
    player_sprites[player_index].x_pos = player_index * 10;
    player_sprites[player_index].y_pos = player_index * 10;
}

static void main_loop(void)
{
    for (sprite_index = 0; sprite_index < NUM_SPRITES; sprite_index++)
    {
        sp1_MoveSprPix(player_sprites[sprite_index].sprite, &game_area, 0, player_sprites[sprite_index].x_pos++, player_sprites[sprite_index].y_pos);
    }

    // retrasar para reducir la velocidad
    // z80_delay_ms(50);

    // Fuerza el redibujado de las celdas invalidadas
    sp1_UpdateNow();
}

void run_module3_2(void)
{
    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                   INK_WHITE | PAPER_BLACK, 'Z');

    // Marcar área para el primer render
    sp1_Invalidate(&game_area);

    // Crear X sprites enmascarados y posicionarlos en pantalla
    for (sprite_index = 0; sprite_index < NUM_SPRITES; sprite_index++)
    {
        init_player(sprite_index);
    }

    // ejecutar el bucle principal hasta que se presione INTRO
    wait_for_intro_key(main_loop);
}

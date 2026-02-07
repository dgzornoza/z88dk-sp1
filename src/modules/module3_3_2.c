
#include <input.h>
#include "input/input_zx.h" // usada para vscode IN_KEY_SCANCODE_o y IN_KEY_SCANCODE_p

#include "../z88dk_headers.h"
#include "./modules.h"
#include "../data/module3_3.h"

// estructura con la maquina de estados para el movimiento del sprite,
// cada estado se corresponde con una tecla y define el gráfico a usar y el delta de movimiento
static struct
{
    unsigned int scan_code;
    unsigned char *graphic;
    signed char x_delta;
} arrow_state[] = {{IN_KEY_SCANCODE_o, arrow_left, -1},
                   {IN_KEY_SCANCODE_p, arrow_right, +1}};

static struct sp1_ss *arrow_sprite;

static unsigned char current_position_x = 128;
static unsigned char current_arrow_state = 0;

// Asignar atributos a las celdas del sprite
static void set_sprite_colour(unsigned int count, struct sp1_cs *c)
{
    (void)count; /* Suprimir warning del compilador por parametro no usado */
    c->attr_mask = SP1_AMASK_PAPER;
    c->attr = PAPER_RED;
}

static void init_sprite(void)
{
    // Crear sprite sin especificar grafico (sera especificado dinamicamente segun el estado)
    arrow_sprite = sp1_CreateSpr(SP1_DRAW_LOAD1LB, SP1_TYPE_1BYTE, 2, 0, 0);

    // Añadir columnas (una por cada 8px de ancho),
    // en este caso como solo es un sprite 8x8 (un caracter), en la columna se define con la etiqueta de fin con 'SP1_DRAW_LOAD1RB'
    // lo cual no requiere establecer el puntero al grafico
    sp1_AddColSpr(arrow_sprite, SP1_DRAW_LOAD1RB, SP1_TYPE_1BYTE, 0, 0);

    // Aplicar atributos a cada celda del sprite
    sp1_IterateSprChar(arrow_sprite, set_sprite_colour);
}

static void main_loop(void)
{
    // verificar estado segun la tecla 'O' 'P' pulsada
    for (uint8_t i = 0; i < 2; i++)
    {
        if (in_key_pressed(arrow_state[i].scan_code) == 0xFFFF)
        {
            current_arrow_state = i;
            break;
        }
    }

    // establecer la nueva posicion del sprite (delta es usada para mover el sprite a la izquierda o derecha segun el estado)
    current_position_x += arrow_state[current_arrow_state].x_delta;

    // Establecer el gráfico del sprite en la dirección correspondiente al estado actual
    sp1_MoveSprPix(arrow_sprite, &game_area, arrow_state[current_arrow_state].graphic, current_position_x, 80);

    // retrasar para reducir la velocidad
    z80_delay_ms(50);

    // Fuerza el redibujado de las celdas invalidadas
    sp1_UpdateNow();
}

void run_module3_3_2(void)
{
    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                   INK_WHITE | PAPER_BLACK, ' ');

    // Marcar área para el primer render
    sp1_Invalidate(&game_area);

    init_sprite();

    // ejecutar el bucle principal hasta que se presione INTRO
    wait_for_intro_key(main_loop);
}

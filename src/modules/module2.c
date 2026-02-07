
#include "../z88dk_headers.h"
#include "./modules.h"
#include "../data/module2.h"

static void main_loop(void)
{
    // Fuerza el redibujado de las celdas invalidadas
    sp1_UpdateNow();
}

void run_module2(void)
{
    // Inicializar el motor SP1 con tablas de rotacion y limpieza de pantalla
    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE, INK_WHITE | PAPER_BLACK, ' ');

    // Marcar toda la pantalla como "sucia" para el primer renderizado completo
    sp1_Invalidate(&game_area);

    // Registrar los graficos personalizados asociandolos a un codigo de caracter ASCII
    sp1_TileEntry('b', tile_brick);
    sp1_TileEntry('g', tile_grass);

    // Pintar una linea de suelo de hierba en la fila 22 mediante un bucle
    for (uint8_t x = 0; x < 32; x++)
    {
        sp1_PrintAt(22, x, INK_GREEN | PAPER_BLACK, 'g');
    }

    // Dibujar elementos decorativos en coordenadas especificas (Fila, Columna)
    sp1_PrintAt(21, 5, INK_RED | PAPER_BLACK, 'b');
    sp1_PrintAt(20, 5, INK_RED | PAPER_BLACK, 'b');

    // ejecutar el bucle principal hasta que se presione INTRO
    wait_for_intro_key(main_loop);
}

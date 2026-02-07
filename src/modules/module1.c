
#include "../z88dk_headers.h"
#include "./modules.h"

static void main_loop(void)
{
    // Fuerza el redibujado de las celdas invalidadas
    sp1_UpdateNow();
}

void run_module1(void)
{
    /*
       Inicialiar SP1:
       - SP1_IFLAG_MAKE_ROTTBL: Crea tablas de rotacion para los sprites.
       - SP1_IFLAG_OVERWRITE_TILES: Permite sobrescribir los tiles de fondo.
       - SP1_IFLAG_OVERWRITE_DFILE: Inicializa el area de pantalla de la libreria.
    */
    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE, INK_WHITE | PAPER_BLACK, ' ');

    // Marcar toda la pantalla como "sucia" para el primer renderizado
    sp1_Invalidate(&game_area);

    // ejecutar el bucle principal hasta que se presione INTRO
    wait_for_intro_key(main_loop);
}

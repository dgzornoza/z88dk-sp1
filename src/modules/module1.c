
#include "../z88dk_headers.h"
#include "./modules.h"

/* Definir un rectangulo que cubre toda la pantalla (32x24 celdas) */
struct sp1_Rect full_screen = {0, 0, 32, 24};

void example1_main_loop(void) {
    /* Fuerza el redibujado de las celdas invalidadas */
    sp1_UpdateNow();
}

void run_example1(void) {
    /* Establecer el borde en blanco */
    zx_border(INK_WHITE);

    /*
       Inicialiar SP1:
       - SP1_IFLAG_MAKE_ROTTBL: Crea tablas de rotacion para los sprites.
       - SP1_IFLAG_OVERWRITE_TILES: Permite sobrescribir los tiles de fondo.
       - SP1_IFLAG_OVERWRITE_DFILE: Inicializa el area de pantalla de la libreria.
    */
    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES |  SP1_IFLAG_OVERWRITE_DFILE, INK_WHITE | PAPER_BLACK, ' ');

    /* Marcar toda la pantalla como "sucia" para el primer renderizado */
    sp1_Invalidate(&full_screen);

    // ejecutar el bucle principal hasta que se presione INTRO
    wait_for_intro_key(example1_main_loop);
}




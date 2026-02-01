#include "z88dk_headers.h"
#include <stdio.h>
#include <input.h>
#include "modules/modules.h"
#include <input/input_zx.h>

static void print_menu(void) {
    // limpiar pantalla
    zx_cls(PAPER_WHITE);
    puts("\x16\x01\x01");

    printf("Tutorial SP1 - Menu\n");
    printf("==============================\n");
    printf("(Presiona INTRO para salir del ejemplo)\n\n");
    printf("1) Preparacion e Inicializacion\n");
    printf("2) Graficos de Fondo (UDGs)\n");
    printf("3) Sprites y Movimiento\n");
    printf("4) Logica de Juego y Sincronismo\n");
    printf("5) Gestion Avanzada y 128k\n");
    printf("6) Scroll y Parallax\n");
    printf("\nSelecciona un numero: ");
}

int main(void) {
    unsigned char key = 0;

    while (1) {
        print_menu();

        in_wait_key();
        key = in_inkey();
        in_wait_nokey();

        switch (key) {
            case '1':
                run_example1();
                break;
            // case '2':
            //     break;
            // case '3':
            //     break;
            // case '4':
            //     break;
            // case '5':
            //     break;
            // case '6':
            //     break;
            // default:
            //     printf("key = %d\n", key);
            //     printf("key = %c\n", key);
            //     break;
        }
    }
}



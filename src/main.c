#include "z88dk_headers.h"
#include <stdio.h>
#include <input.h>
#include "modules/modules.h"
#include <input/input_zx.h>

/** Cambiar por el numero de tutorial a ejecutar */
int module = 3;
int submodule = 4;
int sample = 2;

int main(void)
{
    // limpiar pantalla
    zx_border(PAPER_BLACK);
    zx_cls(PAPER_BLACK);

    switch (module)
    {
    case 1:
        run_module1();
        break;
    case 2:
        run_module2();
        break;
    case 3:
        switch (submodule)
        {
        case 1:
            run_module3_1();
            break;
        case 2:
            run_module3_2();
            break;
        case 3:
            switch (sample)
            {
            case 1:
                run_module3_3_1();
                break;
            case 2:
                run_module3_3_2();
                break;
            }
            break;
        case 4:
            switch (sample)
            {
            case 1:
                run_module3_4_1();
                break;
            case 2:
                run_module3_4_2();
                break;
            }
            break;
        }

        break;
    case 4:
        // run_module4();
        break;
    default:
        printf("Modulo no encontrado");
        break;
    }

    return 1;
}

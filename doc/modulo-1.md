# Módulo 1: Preparación e Inicialización

Este módulo cubre la configuración inicial del entorno de desarrollo y la puesta en marcha del motor gráfico **SP1**.

## 1. Introducción a SP1

La librería **SP1** es un motor de sprites por software que utiliza un sistema de **actualización diferencial**. En lugar de redibujar toda la pantalla en cada frame, divide la pantalla en celdas de 8x8 píxeles. Solo las celdas que cambian (porque un sprite pasa por ellas o el fondo se modifica) se marcan como "sucias" y se redibujan, lo que permite un alto rendimiento y una visualización **libre de parpadeos** (flicker-free) sin necesidad de sincronización compleja.

## 2. Configuración del Entorno (zx-ide)

Para estos tutoriales, será usada la extensión **zx-ide** para VSCode, la extensión hace uso de un **DevContainer** que ya incluye todas las herramientas necesarias para la compilación y desarrollo. El proyecto creado por la extensión utiliza un **Makefile** para la compilación incremental, por lo que no es necesario listar manualmente los archivos fuente, además contiene algunas funcionalidades útiles para la ejecución y depuración tanto del codigo C como ASM. Para la instalación de la extensión se puede seguir la guía, donde además se podrá encontrar información adicional sobre la extensión (ver [wiki de zx-ide](https://github.com/dgzornoza/zx-ide/wiki)).

## 3. Configuración de Memoria (`zpragma.inc`)

Para que el compilador organice correctamente la memoria del Spectrum y SP1 funcione, debemos crear el archivo `zpragma.inc` en la raíz del proyecto con los siguientes parámetros (recomendados para SP1):

```c
#pragma output CRT_ORG_CODE           = 25000      // Direccion de inicio del codigo
#pragma output REGISTER_SP            = 0xd000     // Ubicacion del stack para SP1

#pragma output CRT_ENABLE_CLOSE       = 0          // No cerrar archivos al salir
#pragma output CRT_ENABLE_EIDI        = 0x1        // Desactivar interrupciones al inicio
#pragma output CRT_ON_EXIT            = 0          // Salto a 0 al terminar

#pragma output CLIB_STDIO_HEAP_SIZE   = 0          // Sin heap para stdio
#pragma output CLIB_EXIT_STACK_SIZE   = 0          // Sin funciones atexit()
#pragma output CLIB_FOPEN_MAX         = -1         // Sin lista de archivos
#pragma output CLIB_OPEN_MAX          = -1         // Sin tabla de descriptores

// Crea un asignador de bloques de memoria necesario para los sprites de SP1
#pragma output CLIB_BALLOC_TABLE_SIZE = 1       

#pragma output CRT_STACK_SIZE         = 128     // Tamaño del stack principal
```

## 4. Código Base (main.c)

Este es el código mínimo para inicializar el motor. El flujo consiste en inicializar la librería, definir el área de juego e invalidar la pantalla para forzar el primer dibujo.

```c
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <z80.h>

/* Definir un rectangulo que cubre toda la pantalla (32x24 celdas) */
struct sp1_Rect full_screen = {0, 0, 32, 24};

int main(void) {
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

    while (1) {
        /* Fuerza el redibujado de las celdas invalidadas */
        sp1_UpdateNow();
    }
}
```
## 4. Funciones

- [`sp1_Initialize`](z88dk-sp1.md#sp1_initialize): Prepara las tablas internas y el estado inicial de la pantalla.
- [`sp1_Invalidate`](z88dk-sp1.md#sp1_invalidate): Marca un área de la pantalla para que el motor sepa que debe redibujarla en la próxima actualización.
- [`sp1_UpdateNow`](z88dk-sp1.md#sp1_updatenow): Es la función que realmente realiza el dibujo en la memoria de video procesando la lista de celdas modificadas.

## 5. Conceptos Clave

- **Gestión de Memoria:** SP1 realiza asignaciones dinámicas implícitas al crear sprites, por lo que el parámetro `CLIB_BALLOC_TABLE_SIZE = 1` en los pragmas es obligatorio.


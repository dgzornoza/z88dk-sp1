# Módulo 2: Gráficos de Fondo y Tiles con ZX Paintbrush

En este módulo aprenderemos a gestionar el fondo de nuestros juegos utilizando **UDGs** (User-Defined Graphics) diseñados con **ZX Paintbrush**. Esta técnica es fundamental para crear escenarios visualmente ricos sin agotar la memoria del ZX Spectrum.

## 1. El flujo de trabajo con ZX Paintbrush

A diferencia de los archivos de imagen genéricos, las imágenes creadas en **ZX Paintbrush** son ideales para el desarrollo en Spectrum porque conservan metadatos que el motor **SP1** puede aprovechar. 

### Ventajas de ZX Paintbrush:

- **Gestión de Atributos:** Permite definir explícitamente qué color es "paper" y cuál es "ink" dentro de cada celda de 8x8 píxeles.

- **Efectos Especiales:** Facilita la activación de los bits de **Brillo (Bright)** y **Flash** por cada carácter, algo que se pierde en una conversión de imagen estándar.

- **Ficheros de Proyecto:** El uso de archivos `.zxp` (como `tileset.zxp`) permite editar y regenerar los gráficos de forma sencilla durante el desarrollo.

## 2. Los Tiles (UDGs) en el motor SP1

La librería **SP1** entiende dos entidades gráficas principales: los **Sprites** y los **Tiles de fondo (UDGs)**. Los UDGs son "baratos" en consumo de RAM porque funcionan reemplazando un código de carácter ASCII (8x8 píxeles) por un dibujo personalizado.

### El sistema de Actualización Diferencial

El secreto de la velocidad de **SP1** es su motor de actualización diferencial:
1.  Divide la pantalla en celdas de 8x8, cada una descrita por una estructura `struct sp1_update`.
2.  Mantiene una lista de **celdas sucias** (dirtied character cells).
3.  Cuando modificamos el fondo o movemos un objeto, la celda afectada se añade a esta lista automáticamente.
4.  Al llamar a `sp1_UpdateNow()`, el motor recorre la lista y redibuja únicamente las celdas que han cambiado. Esto permite un funcionamiento **libre de parpadeos (flicker-free)** sin necesidad de sincronizar con el haz de luz del monitor.

## 3. Implementación en C

Una vez diseñados los tiles en **ZX Paintbrush** y exportados como arrays de bytes, utilizaremos las funciones de la API de **SP1** para registrarlos y pintarlos.

```c
#include <arch/zx.h>
#include <arch/zx/sp1.h>

/* Definir datos del tile: un ladrillo de 8x8 pixeles exportado de ZX Paintbrush */
const uint8_t tile_brick[] = {0xfe, 0x82, 0x82, 0xfe, 0x82, 0x82, 0x82, 0xfe};

/* Definir datos del tile: un bloque de hierba exportado de ZX Paintbrush */
const uint8_t tile_grass[] = {0x00, 0x00, 0x11, 0x22, 0x44, 0x11, 0xee, 0xff};

int main() {
    /* Inicializar el motor SP1 con tablas de rotacion y limpieza de pantalla */
    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE, 
                   INK_WHITE | PAPER_BLACK, ' ');

    /* Registrar los graficos personalizados asociandolos a un codigo de caracter ASCII */
    sp1_TileEntry('b', tile_brick);
    sp1_TileEntry('g', tile_grass);

    /* Pintar una linea de suelo de hierba en la fila 22 mediante un bucle */
    for (uint8_t x = 0; x < 32; x++) {
        sp1_PrintAt(22, x, INK_GREEN | PAPER_BLACK, 'g');
    }

    /* Dibujar elementos decorativos en coordenadas especificas (Fila, Columna) */
    sp1_PrintAt(21, 5, INK_RED | PAPER_BLACK, 'b');
    sp1_PrintAt(20, 5, INK_RED | PAPER_BLACK, 'b');

    /* Ejecutar el bucle principal de renderizado */
    while (1) {
        /* Procesar la lista de celdas sucias y volcar cambios a la memoria de video */
        sp1_UpdateNow();
    }
}
```

## 4. Consideraciones Técnicas Importantes

- Attribute Clash: El Spectrum gestiona el color en bloques de 8x8. Si dos elementos con diferentes colores de tinta (INK) coinciden en la misma celda, ocurrirá un choque de atributos. Por ello, es común diseñar héroes en blanco y negro sobre fondos de color.

- Invalidación Automática: Al usar sp1_PrintAt, SP1 marca la celda como "sucia" automáticamente. Si una celda se invalida varias veces en el mismo ciclo, el motor solo la redibuja una vez para ahorrar tiempo de CPU.

- Limitación de Scroll: Debido a su naturaleza diferencial, SP1 no está diseñado para scroll de píxeles, aunque permite realizar desplazamientos por celdas completas (8 píxeles).  

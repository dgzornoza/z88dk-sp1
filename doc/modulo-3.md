# Módulo 3: Sprites, Máscaras y Planos

En este módulo veremos cómo crear y gestionar sprites en **SP1**, asi como los conceptos basicos sobre máscaras de transparencia y las consideraciones relacionadas con los planos de profundidad y el "attribute clash" del ZX Spectrum.

Este modulo esta dividido en varias partes:
1. **Sprites basicos**: Codigo base: [src/modules/module3_1.c](../src/modules/module3_1.c)
2. **Sprites con mascara**: Codigo base: [src/modules/module3_2.c](../src/modules/module3_2.c)

## 1. Conceptos fundamentales

Los sprites son objetos gráficos que se dibujan "sobre" el fondo y pueden moverse independientemente de los **UDGs** (tiles). SP1 usa un sistema de **actualización diferencial** que sólo redibuja las celdas (8×8) afectadas por cambios, lo que permite animaciones fluidas y sin parpadeo.

### Planos

- SP1 soporta hasta **256 planos** de profundidad (0..255).
  - **Plano 0**: más cercano al observador (se dibuja por encima de los demás).
  - **Plano 255**: situado justo encima del fondo.
- Si dos sprites quedan en el mismo plano, no hay una garantía de orden de dibujo determinista.

### Máscaras y color

- El Attribute Clash (choque de atributos) ocurre siempre que dos sprites con diferentes colores de tinta (INK) coinciden en una misma celda de 8x8 píxeles. 
- Las máscaras permiten definir píxeles transparentes en el sprite para evitar el *attribute clash* cuando se superponen con el fondo.
- Las máscaras deben tener al menos un píxel de borde alrededor del sprite para una visualización correcta
- El tipo de dibujo SP1_DRAW_MASK2LB permite usar máscaras, aunque consume el doble de memoria al almacenar tanto la información del sprite como la de la máscara

### Definición de Columnas

- Un sprite se crea definiendo el alto del sprite (en caracteres) + 1, el puntero con el offset del primer frame de animación dentro del archivo de gráficos (mapa de sprites) y por ultimo el plano.
- Un sprite se construye añadiendo columnas de 8 píxeles de ancho mediante la función sp1_AddColSpr (Si un sprite mide 24 píxeles de ancho, se deben realizar tres llamadas a esta función)
- Es necesario especificar el desplazamiento (offset) de cada columna dentro del archivo de gráficos, calculando el espacio según el número de frames de animación disponibles.


## 2. Creacion de un sprite

Los pasos básicos son:

1. Crear el archivo de datos con el sprite (para generar el codigo .asm/.h del sprite).
2. Crear la estructura del sprite con `sp1_CreateSpr`.
3. Añadir las columnas que componen el sprite con `sp1_AddColSpr`.
4. Establecer atributos/color por celda con `sp1_IterateSprChar` si es necesario.
5. Posicionar el sprite con `sp1_MoveSprAbs` o `sp1_MoveSprPix` y llamar a `sp1_UpdateNow()` cada frame.

## 4. Notas técnicas y buenas prácticas

- **Memoria:** Los sprites sin máscara (SP1_DRAW_LOAD1LB) cargan un sprite de 8x8 píxeles en 8 bytes, mientras que los sprites con máscara (SP1_DRAW_MASK2LB) requieren 16 bytes por celda.
- **Rotación:** SP1 incluye rotadores por software opcionales para posicionamiento por píxel.
- **Clipping:** Los sprites se recortan automáticamente cuando exceden el rectángulo indicado en `sp1_MoveSprAbs`.
- **Gestión dinámica:** SP1 reserva memoria al crear sprites; asegúrate de configurar `CLIB_BALLOC_TABLE_SIZE` en `zpragma.inc`.
- **Diseño:** Para minimizar attribute clash, diseña sprites (especialmente héroes) en paletas reducidas o con máscara bien definida.


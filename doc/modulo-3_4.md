# Módulo 3.4 — Sprites grandes

Este módulo explica cómo crear sprites grande usando la biblioteca SP1 en Z88DK. Se asume que el lector entiende la inicialización básica de SP1 y las partes anteriores de este módulo.

## Objetivo

Entender la representación en memoria de sprites de mayor tamaño, cómo
componer varias columnas de datos (gráfico + máscara), y cómo inicializarlos y
dibujarlos con SP1, incluyendo el manejo del padding necesario para posicionar
por píxel vertical y horizontalmente.

## Concepto general

SP1 representa un sprite grande como una serie de "columnas" de 8 píxeles de
ancho. Cada columna puede contener N filas (si hay 2 filas, seria un sprite de 16×16). 
Cuando un sprite esta desplazado vertical, SP1 ajusta el puntero de lectura dentro del bloque de memoria del sprite, por lo que es necesario incluir bytes de relleno (padding) antes y después de los datos reales para evitar leer memoria aleatoria (como se indico en modulos anteriores).

Para sprites enmascarados cada línea de una columna suele almacenarse como:
`<mask_byte>, <data_byte>` (dos bytes por línea). Además se añaden filas
vacías (con máscara) antes y después de cada columna (padding) para permitir desplazamiento
vertical por píxel sin corromper las columnas adyacentes.

## Datos de un sprite 16×16 

Un sprite 16×16 se compone de 2 columnas de 8×16 cada una. 
Si está alineado en un grid de 8×8 ocupa 4 celdas, si está desplazado horizontal y 
verticalmente puede llegar a ocupar hasta 9 celdas. 
SP1 maneja estos detalles si le damos la estructura de columnas correcta y padding correcto (como se explico anteriormente).

El formato es el mismo que para sprites más pequeños, pero con más filas graficas por columna.

Ejemplo resumen del layout (ensamblador): guardar esto en
`bubble_masked_sprite.asm`:

```asm
SECTION rodata_user

PUBLIC _sprite_bubble_column_1
PUBLIC _sprite_bubble_column_2

		; padding (7 filas con máscara)
		defb @11111111, @00000000
		defb @11111111, @00000000
		; ... (5 filas más) ...

_sprite_bubble_column_1:
		; 16 filas: primero el byte de mascara y luego el sprite grafico
		defb @11111100, @00000000
		defb @11110000, @00000011
		; ... 14 filas (grafico) ...

		; padding (8 filas con máscara)
		defb @11111111, @00000000
		defb @11111111, @00000000
		; ... (6 filas más) ...

_sprite_bubble_column_2:
		defb @00111111, @00000000
		defb @00001111, @11000000
		; ... (resto de filas y padding)
```

En este formato el sprite esta formado por:
 - 7 filas vacías antes (padding)
 - 16 filas (gráfico columna 1: máscara + dato)
 - 8 filas vacías después (padding)
 - 16 filas (gráfico columna 2: máscara + dato)
 - 8 filas vacías después (padding)


## Inicialización y creación del sprite

Pasos: crear un sprite de 16x16 con dos columnas, cada una con su bloque de filas (gráfico + máscara) y el padding necesario.

> Codigo base: [src/modules/module3_4_1.c](../src/modules/module3_4_1.c)

Puntos clave:
- `SP1_DRAW_MASK2LB` / `SP1_DRAW_MASK2` / `SP1_DRAW_MASK2RB`: variantes de
	dibujo que indican uso de máscara y control de rotación en bordes izquierdo,
	interior y derecho.
- `SP1_TYPE_2BYTE`: indica que cada línea usa dos bytes (máscara + dato).
- El tercer argumento de `sp1_CreateSpr` indica la altura máxima en celdas de
	8×8 que ocupará la columna (por ejemplo `3` → 2 celdas = 16px de alto + 1 celda de padding).
- Crear el sprite con la primera columna, añadir una segunda columna con `sp1_AddColSpr` y por ultimo la columna con el borde derecho (RB) para completar el sprite con el limite derecho (RightBoundary).


### Método alternativo: inicializar sprite sin datos y pasar dirección al mover

Como se ha visto anteriormente, otra técnica es crear el sprite con punteros nulos y calcular offsets al añadir columnas. Esto permite usar la dirección absoluta del gráfico en `sp1_MoveSprPix()` y cambiar la apariencia en tiempo de ejecución:

```c
// crear sprite sin datos (punteros nulos)
player_sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, 0, 0);

// segunda columna del sprite especificando un offset respecto a la primera (distancia entre columnas)
int offset = sprite_bubble_column_2 - sprite_bubble_column_1;
sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, offset, 0);

// Añadir columna con el limite RB (RightBoundary) como en los ejemplos anteriores.
sp1_AddColSpr(player_sprite, SP1_DRAW_MASK2RB, SP1_TYPE_2BYTE, 0, 0);

/* dibujar con el puntero al sprite (si se cambia el punter puede cambiarse de sprite siempre y cuando coincidan las distancias de columnas y numero de columnas)  */
sp1_MoveSprPix(player_sprite, &full_screen, sprite_bubble_column_1, x, y);
```

Esto es útil cuando se tiene una tabla de gráficos (todos alineados con el mismo offset para columnas) y se desea cambiar el contenido del sprite simplemente pasando la dirección base al mover.

## Ejemplo más grande: nave/mothership

Para sprites más grandes (por ejemplo 48×24 = 6×3 celdas) se emplean más
columnas (3 o más). El patrón es el mismo: cada columna tiene su bloque de
filas (mask+data), padding antes/after y se añaden mediante `sp1_AddColSpr`.

> Codigo base: [src/modules/module3_4_2.c](../src/modules/module3_4_2.c)

## Buenas prácticas

- **Padding**: 7 filas vacías antes y 8 después de cada columna para permitir
	posicionamiento vertical por píxel.
- **Documentar offsets**: anotar el tamaño (filas útiles) y el espaciado entre
	bloques cuando se compone un sprite por columnas.
- **Máscaras para preservar fondo**: usar el formato mask+data para sprites
	que no deben borrar el fondo.
- **Datos en rodata**: mantener los datos gráficos en secciones `rodata_user`
	para ahorrar RAM y facilitar la compartición entre módulos.

## Referencias SP1 usadas en este módulo

- [`sp1_Initialize`](z88dk-sp1.md#sp1_initialize)
- [`sp1_Invalidate`](z88dk-sp1.md#sp1_invalidate)
- [`sp1_CreateSpr`](z88dk-sp1.md#sp1_createspr)
- [`sp1_AddColSpr`](z88dk-sp1.md#sp1_addcolspr)
- [`sp1_MoveSprPix`](z88dk-sp1.md#sp1_movesprpix)
- [`sp1_UpdateNow`](z88dk-sp1.md#sp1_updatenow)
- [`SP1_DRAW_MASK2LB` / `SP1_DRAW_MASK2RB`](z88dk-sp1.md#sp1_draw_mask2lb)

## Ejercicios propuestos



## Conclusión

SP1 maneja la complejidad del posicionamiento y rotación de columnas; nuestro
trabajo consiste en preparar los datos por columna (mask+data), añadir el
padding correcto y registrar las columnas con `sp1_AddColSpr`. Con estos
patrones podemos crear sprites grandes y coloreados reutilizando las técnicas
vistos en los módulos anteriores.



# Módulo 4 — Detección de colisiones

Este módulo explica técnicas prácticas para detectar colisiones en juegos
desarrollados con Z88DK y la librería SP1. Se asume conocimiento previo de la
inicialización básica de SP1 y del formato de sprites por columnas (mask+data).

## Objetivo

Proveer una guía clara y utilizable sobre técnicas de colisión en Spectrum:
- Hotspots y comprobación por atributos
- Intersección de cajas (bounding boxes)
- Múltiples cajas por sprite
- Detección pixel-perfect utilizando máscaras y datos por columna (SP1)

## Concepto general

La detección de colisiones equilibra precisión y coste CPU. En ZX Spectrum es
habitual aplicar una estrategia en capas: primero una comprobación rápida y
barata (coarse), y sólo cuando ésta indica posible colisión, ejecutar una
comprobación más precisa (fine). Esto reduce drásticamente el número de
operaciones costosas por fotograma.

## Métodos comunes

1) Hotspots y celdas de atributo

	- Definición: un píxel de interés dentro del sprite (por ejemplo punta de
		un proyectil). Calcular su coordenada pantalla (x,y) y consultar el byte
		de atributo con `zx_pxy2aaddr()` para decidir si ha tocado un elemento
		del fondo.
	- Uso típico: terreno estático o bloques con atributos distintivos.
	- Ventaja: muy rápido. Desventaja: impreciso para formas grandes/irregulares.

	Ejemplo (hotspot):

	```c
	hotspot_attribute = *(zx_pxy2aaddr(obj_x + gfx.hotspot_x, obj_y + gfx.hotspot_y));
	if( hotspot_attribute != PAPER_BLACK ) { /* colisión */ }
	```

2) Intersección de cajas (bounding boxes)

	- Envolver cada sprite en un rectángulo definido por `x1,y1,x2,y2` y comprobar
		si los rectángulos se solapan. Muy eficiente y flexible.
	- Para mayor precisión usar varias cajas por sprite (por ejemplo 2–3 cajas)
		que aproximen mejor la forma real.

	Código típico de comprobación de intersección:

	```c
	if( !(b2.x1 >= b1.x2 || b2.x2 <= b1.x1 || b2.y1 >= b1.y2 || b2.y2 <= b1.y1) ) {
		/* cajas se intersectan */
	}
	```

3) Pixel-perfect usando máscaras (cuando es necesario)

	- Aplicar sólo después de que las cajas hayan indicado posible colisión.
	- Si los sprites usan formato `mask+data` por columna (como SP1), se puede
		realizar una comprobación por columnas superpuestas: leer los bytes de
		máscara correspondientes a las filas donde hay solapamiento vertical y
		aplicar una operación AND bit a bit entre las máscaras de ambos sprites.
	- Si el resultado de AND es distinto de cero en alguna fila, existe
		superposición de píxeles visibles (colisión real).

	Pseudocódigo:

	```c
	for(each overlapping_column) {
		for(each overlapping_row_byte) {
			mask_a = read_mask_byte(sprite_a, col, row_offset_a);
			mask_b = read_mask_byte(sprite_b, col, row_offset_b);
			if( (mask_a & mask_b) != 0 ) return COLLISION;
		}
	}
	return NO_COLLISION;
	```

	- Nota: leer bytes de máscara requiere conocer la disposición de los datos
		(padding antes/después de cada columna). Mantener una estructura que
		documente offsets facilita esta lectura.

## Integración con SP1

- Renderiza sprites con `sp1_MoveSprPix()` y `sp1_UpdateNow()` como de
	costumbre. Para detección, documenta las direcciones de inicio de columnas (o usa una estructura que
	contenga los offsets).
- Flujo recomendado por frame:
	1. Actualizar posiciones lógicas de los objetos.
	2. Ejecutar comprobaciones de colisión: cajas y hotspots rápidos.
	3. Si se detecta posible colisión, ejecutar comprobación pixel-perfect
		 accediendo a las máscaras de columnas.
	4. Dibujar sprites con `sp1_MoveSprPix()` y llamar `sp1_UpdateNow()`.

## Estructuras de datos sugeridas

Ejemplo de estructura que guarda punteros y metadatos útiles:

```c
struct GfxData {
	unsigned char *col1;
	unsigned char *col2; /* etc */
	unsigned char hotspot_x;
	unsigned char hotspot_y;
	unsigned char bbox_w; /* ancho caja */
	unsigned char bbox_h; /* alto caja */
	unsigned char col_rows; /* filas útiles por columna (en bytes) */
};
```

Con esta información se calcula la caja en pantalla y se localizan los bytes
de máscara a consultar para comprobaciones pixel-perfect.

## Código base y ejemplo en este repo

El código ejemplo de este módulo se encuentra en:

- [src/modules/module4.c](src/modules/module4.c)

Allí verás ejemplos de:
- Hotspot usando `zx_pxy2aaddr()`
- Bounding boxes y comprobación de intersecciones
- Esqueleto para comprobación por columnas (comentado y con referencias a
	dónde colocar los offsets de máscara)

## Buenas prácticas

- Siempre hacer primero un filtro barato (hotspot o cajas) antes del pixel-perfect.
- Documentar offsets y padding de columnas cuando uses máscaras intercaladas
	(mask+data). Un error en el padding provoca lecturas fuera de la memoria.
- Para sprites muy usados, precomputar la caja y/o una máscara compacta para
	acelerar la comparación.
- Hacer las cajas algo más pequeñas o más grandes según convenga al
	balance jugabilidad/justicia (p. ej. bombas con cajas más pequeñas).

## Referencias SP1 y z88dk usadas en este módulo

- [`sp1_MoveSprPix`](z88dk-sp1.md#sp1_movesprpix)
- [`sp1_UpdateNow`](z88dk-sp1.md#sp1_updatenow)
- [`sp1_CreateSpr`](z88dk-sp1.md#sp1_createspr)
- `zx_pxy2aaddr()` (Z88DK helper para obtener dirección de atributo por píxel)

## Ejercicios propuestos

- Implementa un sistema de 2 fases: cajas + máscaras; mide ciclos por frame.
- Añade soporte para múltiples cajas por sprite y compara precisión vs coste.
- Implementa una tabla de máscaras simplificadas para colisiones y compárala
	con el método pixel-perfect usando máscaras SP1.

## Conclusión

En Spectrum la clave está en combinar rapidez y precisión selectivamente: usa
hotspots y bounding boxes para la mayoría de comprobaciones y reserva las
operaciones bit a bit para los casos necesarios. Documentar offsets y 
mantener un flujo de actualización claro hará las colisiones manejables incluso en el limitado Z80.

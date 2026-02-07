# Módulo 3.2 — Sprites con máscara

Este módulo explica cómo crear y usar sprites con máscara usando la
biblioteca SP1 en Z88DK. Se asume que el lector entiende la inicialización básica de SP1 y las partes anteriores de este módulo.

## Objetivo

Mostrar un ejemplo mínimo que define los datos del sprite y su
máscara en ensamblador, y un programa C que inicializa SP1, crea varios
sprites con máscara (tipo 2 bytes), los dibuja y los mueve en pantalla.

## Concepto general

Los sprites con máscara permiten dibujar gráficos que preservan el fondo donde la máscara lo indique. Esto se logra usando dos bytes por línea: uno para el gráfico y otro para la máscara. La máscara define qué bits del byte gráfico se transferirán a la pantalla, permitiendo dibujos no destructivos.

De la misma forma que los sprites sin máscara, los sprites con máscara también requieren padding (bytes de relleno) antes y después del bloque gráfico para garantizar que las rotaciones verticales (desplazamientos pixel a pixel) copien datos válidos en pantalla, no obstante, al usar máscara el sprite, el padding debera tener 2 bytes por cada linea (equivalente a la mascara y al grafico) la mascara sera to 1 y el padding grafico sera 0.

## Datos del sprite (ensamblador)

Para los sprites enmascarados SP1 requiere por cada línea dos bytes:
el byte de mascara y el byte grafico. 
Ejemplo simplificado de 8x8 con máscara sin padding:

*NOTA: el archivo `module3_2.asm` contiene el codigo completo*

```asm
    ; padding (7 filas con máscara)
    defb @11111111, @00000000
    defb @11111111, @00000000
    ; ... (5 filas más) ...

    ; Pares: primero el byte mascara, luego su gráfico
    defb @00111100, @00111100
    defb @01000010, @01000010
    defb @10000001, @10000001
    defb @10000001, @10000001
    defb @10000001, @10000001
    defb @10000001, @10000001
    defb @01000010, @01000010
    defb @00111100, @00111100

    ; padding (8 filas con máscara)
    defb @11111111, @00000000
    defb @11111111, @00000000
    ; ... (6 filas más) ...
```

Notas rápidas:
- Los pares `mascara, grafico` son bytes por cada línea de pantalla.
- La máscara tiene '1' donde queremos preservar/activar el pixel del
	sprite según el algoritmo de dibujo usado por SP1.

## 4. Referencias SP1 usadas en el ejemplo

- [`sp1_Initialize`](z88dk-sp1.md#sp1_initialize): Inicializa el motor SP1 con opciones de configuración.
- ['sp1_Invalidate`](z88dk-sp1.md#sp1_invalidate): Marca una region de pantalla como "sucia", forzando su redibujado en la próxima actualización.
- [`sp1_CreateSpr`](z88dk-sp1.md#sp1_createspr): Crea un sprite básico, reservando espacio para el padding vertical.
- [`sp1_AddColSpr`](z88dk-sp1.md#sp1_addcolspr): Agrega una columna de datos al sprite
- [`sp1_MoveSprAbs`](z88dk-sp1.md#sp1_movesprabs): Mueve un sprite a coordenadas (de caracter) absolutas en pantalla
- [`sp1_MoveSprPix`](z88dk-sp1.md#sp1_movesprpix): Mueve un sprite a coordenadas (de pixeles) absolutas en pantalla.
- [`sp1_UpdateNow`](z88dk-sp1.md#sp1_updatenow): Ejecuta el motor de actualización diferencial, redibujando solo las celdas marcadas como "sucias".
- [`SP1_DRAW_MASK2LB` / `SP1_DRAW_MASK2RB`](z88dk-sp1.md#sp1_draw_mask2lb): Funciones de dibujo que usan dos bytes por línea (gráfico y máscara) con control de bordes izquierdo/derecho.


## 4. Notas técnicas y buenas prácticas

- **Padding arriba y abajo**: como en el ejemplo sin máscara, necesitas
	bytes extra antes y después del bloque gráfico para que las rotaciones
	verticales (pixel offsets) copien datos válidos en pantalla.
- **mascaras**: Planifica las máscaras para preservar el fondo donde corresponda, la máscara define qué bits del byte gráfico se transferirán. 
    Las máscaras permiten dibujos no destructivos: el fondo queda visible donde la máscara lo indique.
- **Sprites anchos**: Para sprites más anchos, SP1 permite combinar columnas con distintos
	métodos de dibujo (carga directa, AND/OR con máscara, etc.).
    *NOTA: en lugar de `SP1_DRAW_MASK2`, puede usarse `SP1_DRAW_LOAD2` para ver el efecto sin máscara (carga directa con 2 bytes), lo que puede ser útil para depurar la máscara*

## Ejercicios prácticos
- elimina la mascara del padding superior e inferior (quitando los bytes o dejandolos a @00000000), añade un color PAPER al sprite diferente del fondo y observa el efecto al rotar el sprite verticalmente (desplazamiento pixel a pixel).
- establece la mascara del grafico a @00000000 (sin mascara) y observa el efecto al mover el sprite por la pantalla.

## Conclusión


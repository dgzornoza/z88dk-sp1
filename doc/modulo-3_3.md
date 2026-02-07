# Módulo 3.3 — Animación de sprites

Este módulo explica cómo animar sprites usando la biblioteca SP1 en Z88DK. Se asume que el lector entiende la inicialización básica de SP1 y las partes anteriores de este módulo.

## Objetivo

Mostrar dos enfoques prácticos para animar sprites con SP1: la animación secuencial (frames contiguos con offset) y la animación por estados (direcciones o acciones enlazadas a direcciones de datos). 

## Concepto general

Para la animación secuencial/estados los frames se almacenan uno tras otro en memoria. Cada frame de 8×8 ocupa 8 bytes de datos (con máscara serán 16 bytes) y es buena práctica dejar 8 bytes de ceros como "padding" antes/después segun se explico anteriormente para facilitar desplazamientos por píxel verticales.

Los sprites secuenciales/estados, se definen de la misma forma, la unica diferencia es que por convencion los secuenciales se usa el sufijo `_f1` (puede usarse cualquier otro si se desea) y los estados se nombran segun su accion o direccion (ej: `arrow_left`, `arrow_right`).

*NOTA: en los sprites secuencial/estados, solo hace falta definir un padding superior para todos los frames, ya que todos tienen la misma alineacion vertical y puede rehusarse, no obstante, se requiere un padding inferior entre cada frame para permitir desplazamientos verticales sin corromper el siguiente frame. Ej: el puntero al sprite comienza en `sprite_player:` , de modo que ese puntero se usa como base al sprite y el codigo anterior (padding) se rehusa para todos los frames que se van especificando mediante el offset*

## Datos del sprite

Ejemplo simplificado (formato 1 byte por línea):

*NOTA: los archivos `module3_3_1.asm` y `module3_3_2.asm` contienen el codigo completo*

```asm
// module3_3_1.asm
PUBLIC _player

    // padding superior
    defb @00000000
    defb @00000000
    defb @00000000
    defb @00000000
    defb @00000000
    defb @00000000
    defb @00000000

_player_f1:
    defb @00010000
    defb @00100000
    ; ... 8 bytes (grafico) + padding ...

_player_f2:
    defb @00001000
    defb @00000100
    ; ... 8 bytes (grafico) + padding ...

; ... repetir frames f2..f8, siguiendo la misma estructura ...
```

```asm
// module3_3_2.asm
PUBLIC _arrow_left
PUBLIC _arrow_right

    ; padding inicial
    defb @00000000
    defb @00000000
    ...

_arrow_left:
    defb @00010000
    defb @00100000
    ; ... 8 bytes (grafico) + padding ...

_arrow_right:
    defb @00001000
    defb @00000100
    ; ... 8 bytes (grafico) + padding ...
```

Notas: cada frame siguiente estará a +16 bytes del anterior (8 bytes del frame + 8 bytes de padding inferior).

## Animación secuencial (offset)

Pasos: crear un sprite cuyo puntero base apunte al primer frame y cambiar el offset de frame para mostrar el siguiente.

Codigo base: [src/modules/module3_3_1.c](../src/modules/module3_3_1.c)

Puntos clave:
- `player_sprite->frame`: Establecer el frame actual a mostrar en el sprite mediante su offset 
como solo se establece el siguiente frame en la estructura y el puntero a player_sprite es el mismo, 
es por esto por lo que se puede rehusar el padding superior (el que esta 7 bytes antes de sprite_player)

*NOTA*: el offset se incrementa en 16 bytes para pasar al siguiente frame (8 bytes de gráfico + 8 bytes de padding inferior).

## Animación por estados (direcciones absolutas)

Pasos: almacenar direcciones absolutas de cada gráfico (por ejemplo `arrow_left`, `arrow_right`) y pasar la dirección al mover el sprite, útil para sprites con múltiples estados no secuenciales.

Codigo base: [src/modules/module3_3_2.c](../src/modules/module3_3_2.c)


Notas:
- En este enfoque `sp1_CreateSpr` no requiere inicializarlo con los datos del sprite, ya que seran especificados en la funcion `sp1_MoveSprPix()`, que recibe la dirección absoluta del gráfico en su tercer argumento.

- Es más flexible para máquinas de estados complejas.

## Referencias SP1 usadas en el ejemplo

- [`sp1_Initialize`](z88dk-sp1.md#sp1_initialize): Inicializa el motor SP1 con opciones de configuración.
- ['sp1_Invalidate`](z88dk-sp1.md#sp1_invalidate): Marca una region de pantalla como "sucia", forzando su redibujado en la próxima actualización.
- [`sp1_CreateSpr`](z88dk-sp1.md#sp1_createspr): Crea un sprite básico, reservando espacio para el padding vertical.
- [`sp1_AddColSpr`](z88dk-sp1.md#sp1_addcolspr): Agrega una columna de datos al sprite
- [`sp1_MoveSprAbs`](z88dk-sp1.md#sp1_movesprabs): Mueve un sprite a coordenadas (de caracter) absolutas en pantalla
- [`sp1_MoveSprPix`](z88dk-sp1.md#sp1_movesprpix): Mueve un sprite a coordenadas (de pixeles) absolutas en pantalla.
- [`sp1_UpdateNow`](z88dk-sp1.md#sp1_updatenow): Ejecuta el motor de actualización diferencial, redibujando solo las celdas marcadas como "sucias".
- [`SP1_DRAW_MASK2LB` / `SP1_DRAW_MASK2RB`](z88dk-sp1.md#sp1_draw_mask2lb): Funciones de dibujo que usan dos bytes por línea (gráfico y máscara) con control de bordes izquierdo/derecho.

## Notas técnicas y buenas prácticas

- **Padding**: conservar 7 bytes antes y 8 bytes después del bloque gráfico para permitir desplazamientos verticales.
- **Offsets**: documentar el espaciado de frames al diseñar los datos (ej. +16 bytes entre frames en el ejemplo).
- **Máscara vs carga directa**: para sprites que deben preservar fondo, usar máscaras.
- **Memoria**: mantener bajo uso de RAM; preferir datos en rodata y referencias por dirección.

## Ejercicios propuestos


## Conclusión

Hemos presentado dos patrones de animación con SP1: el método secuencial (offsets) y el método por estados (direcciones absolutas). Ambos son útiles dependiendo del tipo de sprite y lógica del juego, el segundo es más flexible para personajes con múltiples acciones.



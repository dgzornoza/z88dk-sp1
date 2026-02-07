# Módulo 3.1: Sprites basicos

En esta sección veremos cómo crear y gestionar sprites básicos en **SP1**, sin usar máscaras de transparencia. Aprenderemos a definir un sprite, asignarle atributos de color y posicionarlo en la pantalla.

Codigo base: [src/modules/module3_1.c](../src/modules/module3_1.c)

## 1. Conceptos fundamentales

Como se indicó anteriormente, los sprites son objetos gráficos que se dibujan "sobre" el fondo y pueden moverse independientemente de los **UDGs** (tiles). SP1 usa un sistema de **actualización diferencial** que sólo redibuja las celdas (8×8) afectadas por cambios, lo que permite animaciones fluidas y sin parpadeo.

La naturaleza de SP1 es usar bloques de 8x8 (caracter) para la gestion grafica (para optimizar la velocidad), de modo que SP1 no desplaza bits para posicionar un sprite por píxel, en su lugar ajusta el puntero de lectura dentro del bloque de memoria del sprite.
Para que este mecanismo funcione sin leer basura, cada sprite debe incluir bytes de relleno (padding) antes y después de los datos reales.

### Padding superior (7 bytes)

SP1 puede necesitar empezar a leer el sprite hasta 7 bytes antes del primer byte real cuando el sprite está desplazado verticalmente dentro de una celda de 8×8 (Si esos bytes no existen, SP1 leería memoria aleatoria).

*NOTA: son 7 por que un desplazamiento de 8 seria de un caracter, que es lo mismo que no tener desplazamiento, por lo que para ahorrar ese ultimo byte, tiene sentido un máximo desplazamiento de 7 píxeles.*

> Regla: Añadir 7 bytes con valor 0 antes de los datos del sprite.

### Padding inferior (8 bytes)

Cuando un sprite cae parcialmente en la celda inferior por un desplazamiento verticl, SP1 copia 8 líneas completas para esa celda, aunque el sprite real no las ocupe todas.
Esto obliga a que existan bytes válidos inmediatamente después del gráfico.

> Regla: Añadir 8 bytes con valor 0 después de los datos del sprite.

### Estructura final del bloque de datos

Para cualquier sprite, independientemente de su altura:

Código
[ 7 bytes de cero ]
[ datos del sprite ]
[ 8 bytes de cero ]

> Notas:
> - Este padding es obligatorio tanto para sprites sin máscara como para sprites con máscara (SP1_DRAW_MASK2LB).
> - Cada sprite debe tener su propio bloque contiguo con padding, no se puede compartir entre sprites distintos.

El contenido del padding siempre es cero, pero su presencia es lo que garantiza que SP1 pueda desplazar el sprite verticalmente. Es por esto que la funcion `sp1_CreateSpr` requiere establecer un alto del sprite + 1, para reservar espacio para el padding superior/inferior utilizado.

**Ejemplo**: tenemos un sprite de 8x8 y lo desplazamos verticamente 3 pixels, entonces el sprite quedara en pantalla como un sprite de 8X16, con 3 bytes de padding superior, 8 bytes de datos del sprite y 5 bytes de padding inferior, total 16 bytes (3+8+5=16 que equivale al alto del sprite + 1 usado en `sp1_CreateSpr`)
(Esto se puede verificar modificando los paddings con algunos 1 para ver su efecto en pantalla)

### Padding en columnas

Como se ha comentado, un sprite se construye añadiendo columnas de 8 píxeles de ancho mediante la función sp1_AddColSpr, del mismo modo que el padding usado para el desplazamiento vertical, el padding horizontal se gestiona añadiendo columnas, esto significa, que aunque solo existe un caracter para el sprite, hace falta especificar una columna (ademas de la creacion con `sp1_CreateSpr`) indicando las funciones de dibujo con sufijo LB y RB para indicar con los limites izquierdo y derecho que seran usados, esto permite a SP1 controlar el padding horizontal. De no añadirse esta columna, el sprite se dibujaria sin padding horizontal, lo que provocaria que el sprite se recorte por la derecha al desplazarse horizontalmente (ademas sin desplazamiento, no seria visualizado).


## 4. Referencias SP1 usadas en el ejemplo

- [`sp1_Initialize`](z88dk-sp1.md#sp1_initialize): Inicializa el motor SP1 con opciones de configuración.
- ['sp1_Invalidate`](z88dk-sp1.md#sp1_invalidate): Marca una region de pantalla como "sucia", forzando su redibujado en la próxima actualización.
- [`sp1_CreateSpr`](z88dk-sp1.md#sp1_createspr): Crea un sprite básico, reservando espacio para el padding vertical.
- [`sp1_AddColSpr`](z88dk-sp1.md#sp1_addcolspr): Agrega una columna de datos al sprite
- [`sp1_MoveSprAbs`](z88dk-sp1.md#sp1_movesprabs): Mueve un sprite a coordenadas absolutas en pantalla
- [`sp1_UpdateNow`](z88dk-sp1.md#sp1_updatenow): Ejecuta el motor de actualización diferencial, redibujando solo las celdas marcadas como "sucias".
- [`SP1_DRAW_LOAD1LB` / `SP1_DRAW_LOAD1RB`](z88dk-sp1.md#sp1_draw_load1lb--sp1_draw_load1rb): Funciones de dibujo que usa un byte con control de bordes izquierdo/derecho.

Véase [Indice.md](Indice.md) para más información sobre la documentación general del proyecto.

## Ejercicios prácticos
## Conclusión

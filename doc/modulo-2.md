# Módulo 2: Gráficos de Fondo y Tiles con ZX Paintbrush

En este módulo aprenderemos a gestionar el fondo de nuestros juegos utilizando **UDGs** (User-Defined Graphics), pueden diseñarse con cualquier herramienta de dibujo y exportar en png, desde zx-ide se podran generar los datos del dibujo con el comando 'attach-image-data'. 
La tecnica de tiles, es fundamental para crear escenarios visualmente ricos sin agotar la memoria del ZX Spectrum.

Codigo base: [src/modules/module2.c](../src/modules/module2.c)

## 1. El flujo de trabajo con ZX Paintbrush

A diferencia de los archivos de imagen genéricos, las imágenes creadas en **ZX Paintbrush** son ideales para el desarrollo en Spectrum porque conservan metadatos que el motor **SP1** puede aprovechar.

### Ventajas de ZX Paintbrush

TODO: falta revisar e implementar cuando se termine la herremienta de zxide

- **Gestión de Atributos:** Permite definir explícitamente qué color es "paper" y cuál es "ink" dentro de cada celda de 8x8 píxeles.

- **Efectos Especiales:** Facilita la activación de los bits de **Brillo (Bright)** y **Flash** por cada carácter, algo que se pierde en una conversión de imagen estándar.

- **Ficheros de Proyecto:** El uso de archivos `.zxp` usando la extension zxide permite editar y regenerar los gráficos de forma sencilla durante el desarrollo.

### Crear Tiles en ZX Paintbrush

TODO: falta revisar e implementar cuando se termine la herremienta de zxide

1. Crea un nuevo archivo de tipo "ZxPaintBrush" con extension `.zxp` en ZX Paintbrush con una resolución necesaria para contener los tiles necesarios (para este ejemplo sera de 16x8 píxeles que contendra 2 tiles de 8x8 píxeles). Este ejemplo tiene el archivo en assets/module1.zxp que se puede modificar.
2. Diseña tus tiles asegurándote de definir correctamente los colores "paper" e "ink".
3. Selecciona los tiles que deseas exportar y utiliza la opción "Export File/Selection as..." y selecciona
 el tipo de archivo 'Assembler data file (*.asm)'.
4. Guarda el archivo exportado (ej: `tileset.asm`) en la carpeta 'src/assets/module1' (sera compilado junto con el resto del codigo fuente).
5. para este ejemplo las opciones seran las siguientes:
   - Include attributes in output: **desactivado** (no se requieren atributos en este ejemplo).
   - Settings for pixel data: **hexadecimal output**

## 2. Los Tiles (UDGs) en el motor SP1

La librería **SP1** entiende dos entidades gráficas principales: los **Sprites** y los **Tiles de fondo (UDGs)**. Los UDGs son "baratos" en consumo de RAM porque funcionan reemplazando un código de carácter ASCII (8x8 píxeles) por un dibujo personalizado.

### El sistema de Actualización Diferencial

El secreto de la velocidad de **SP1** es su motor de actualización diferencial:

1. Divide la pantalla en celdas de 8x8, cada una descrita por una estructura `struct sp1_update`.
2. Mantiene una lista de **celdas sucias** (dirtied character cells).
3. Cuando modificamos el fondo o movemos un objeto, la celda afectada se añade a esta lista automáticamente.
4. Al llamar a `sp1_UpdateNow()`, el motor recorre la lista y redibuja únicamente las celdas que han cambiado. Esto permite un funcionamiento **libre de parpadeos (flicker-free)** sin necesidad de sincronizar con el haz de luz del monitor.


## 3. Conceptos clave

- **Attribute Clash**: El Spectrum gestiona el color en bloques de 8x8. Si dos elementos con diferentes colores de tinta (INK) coinciden en la misma celda, ocurrirá un choque de atributos. Por ello, es común diseñar héroes en blanco y negro sobre fondos de color.

- **Invalidación Automática**: Al usar sp1_PrintAt, SP1 marca la celda como "sucia" automáticamente. Si una celda se invalida varias veces en el mismo ciclo, el motor solo la redibuja una vez para ahorrar tiempo de CPU.

- **Limitación de Scroll**: Debido a su naturaleza diferencial, SP1 no está diseñado para scroll de píxeles, aunque permite realizar desplazamientos por celdas completas (8 píxeles).  

## Ejercicios prácticos
## Conclusión

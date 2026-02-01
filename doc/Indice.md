# Índice del Tutorial: Desarrollo de Juegos con SP1 en ZX Spectrum


## 1. Módulo 1: Preparación e Inicialización

*   **Introducción a SP1:** El motor de actualización diferencial y el concepto de celdas sucias.
*   **Entorno zx-ide:** Uso del DevContainer para evitar la instalación de dependencias.
*   **Configuración Técnica:** Ajuste del archivo `zpragma.inc` y gestión del bloque de memoria (`CLIB_BALLOC_TABLE_SIZE`).
*   **Código Base:** Inicialización de la pantalla y forzado del primer renderizado con `sp1_UpdateNow`.

## 2. Módulo 2: Gráficos de Fondo y Tiles con ZX Paintbrush

*   **Diseño Visual:** Ventajas de usar **ZX Paintbrush** para controlar Atributos, Brillo y Flash por cada celda.
*   **UDGs vs Sprites:** Entender por qué los Tiles de fondo son más eficientes en memoria.
*   **Registro de Tiles:** Uso de `sp1_TileEntry` para vincular datos exportados de ZX Paintbrush con caracteres ASCII.
*   **Construcción del Escenario:** Pintado de fondos mediante coordenadas con `sp1_PrintAt`.

## 3. Módulo 3: Sprites, Máscaras y Planos

*   **Creación con ZX Paintbrush:** Diseño de sprites y gestión de la máscara para evitar el choque de atributos.
*   **Arquitectura de Sprites:** Definición de columnas y planos de profundidad (0 a 255).
*   **Movimiento en Pantalla:** Implementación de `sp1_MoveSprAbs` para el desplazamiento con precisión de píxel.

## 4. Módulo 4: Lógica de Juego y Sincronismo (VSYNC)

*   **Control de Usuario:** Lectura de teclado y joystick mediante punteros a funciones.
*   **Sistema de Ticks (IM2):** Configuración de interrupciones de Modo 2 para una velocidad de juego constante a 50Hz.
*   **Colisiones por Burbuja:** Cálculo de distancias entre coordenadas para detectar impactos entre entidades.

## 5. Módulo 5: Gestión de Memoria y Paginación (128k)

*   **Optimización de RAM:** Estrategias para ahorrar memoria (evitar `malloc`, uso de variables globales y funciones `inline`).
*   **Paginación de Memoria:** Creación de un cargador BASIC para gestionar bancos de memoria en modelos 128k.
*   **Carga de Pantallas:** Uso de `sp1_IterateUpdateRect` para actualizar fondos completos desde datos comprimidos.

## 6. Módulo 6: Scroll de Background y Parallax

*   **Scroll por Caracteres:** Técnicas de desplazamiento de fondo mediante la actualización de tiles en bloques de 8 píxeles.
*   **Efecto Parallax:** Simulación de profundidad moviendo diferentes capas de tiles a distintas velocidades.
*   **Invalidación Selectiva:** Manipulación manual de la lista de actualización para optimizar el rendimiento en movimientos de cámara.

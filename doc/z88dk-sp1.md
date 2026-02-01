# Z88dk SP1 (Sprite Pack v3.0) – Documentación

Documentación práctica de las funciones principales de la libreria SP1 para ZX Spectrum. Incluye descripción y ejemplo mínimo por función. Las funciones están agrupadas por funcionalidad para facilitar la búsqueda.

> Nota: Los ejemplos son fragmentos ilustrativos. Ajustar tipos, tiles y gráficos según se requiera.

---

## Tabla de contenidos (TOC)

- [Estructuras de datos](#estructuras-de-datos)
  - [sp1_Rect](#sp1_rect)
  - [sp1_update](#sp1_update)
  - [sp1_ss](#sp1_ss)
  - [sp1_cs](#sp1_cs)
  - [sp1_ap](#sp1_ap)
  - [sp1_tp](#sp1_tp)
  - [sp1_pss](#sp1_pss)
- [Constantes y flags](#constantes-y-flags)
  - [Tipos y atributos de sprites](#tipos-y-atributos-de-sprites)
  - [Flags de rectángulo y printing](#flags-de-rectángulo-y-printing)
  - [Flags de inicialización (updater)](#flags-de-inicialización-updater)
- [Flujo de inicialización recomendado](#flujo-de-inicialización-recomendado)
- [Sprites: creación y configuración](#sprites-creación-y-configuración)
  - [sp1_CreateSpr](#sp1_createspr)
  - [sp1_AddColSpr](#sp1_addcolspr)
  - [sp1_ChangeSprType](#sp1_changesprtype)
  - [sp1_DeleteSpr](#sp1_deletespr)
- [Sprites: movimiento](#sprites-movimiento)
  - [sp1_MoveSprAbs](#sp1_movesprabs)
  - [sp1_MoveSprRel](#sp1_movesprrel)
  - [sp1_MoveSprPix](#sp1_movesprpix)
- [Sprites: iteración y utilidades](#sprites-iteración-y-utilidades)
  - [sp1_IterateSprChar](#sp1_iteratesprchar)
  - [sp1_IterateUpdateSpr](#sp1_iterateupdatespr)
  - [sp1_GetSprClrAddr](#sp1_getsprclraddr)
  - [sp1_PutSprClr](#sp1_putsprclr)
  - [sp1_GetSprClr](#sp1_getsprclr)
  - [sp1_PreShiftSpr](#sp1_preshiftspr)
- [Char structs independientes](#char-structs-independientes)
  - [sp1_InitCharStruct](#sp1_initcharstruct)
  - [sp1_InsertCharStruct](#sp1_insertcharstruct)
  - [sp1_RemoveCharStruct](#sp1_removecharstruct)
- [Tiles y texto](#tiles-y-texto)
  - [sp1_TileEntry](#sp1_tileentry)
  - [sp1_PrintAt](#sp1_printat)
  - [sp1_PrintAtInv](#sp1_printatinv)
  - [sp1_ScreenStr](#sp1_screenstr)
  - [sp1_ScreenAttr](#sp1_screenattr)
  - [sp1_PrintString](#sp1_printstring)
  - [sp1_SetPrintPos](#sp1_setprintpos)
  - [sp1_GetTiles](#sp1_gettiles)
  - [sp1_PutTiles](#sp1_puttiles)
  - [sp1_PutTilesInv](#sp1_puttilesinv)
  - [sp1_ClearRect](#sp1_clearrect)
  - [sp1_ClearRectInv](#sp1_clearrectinv)
- [Updater (actualización de pantalla)](#updater-actualización-de-pantalla)
  - [sp1_Initialize](#sp1_initialize)
  - [sp1_UpdateNow](#sp1_updatenow)
  - [sp1_GetUpdateStruct](#sp1_getupdatestruct)
  - [sp1_IterateUpdateArr](#sp1_iterateupdatearr)
  - [sp1_IterateUpdateRect](#sp1_iterateupdaterect)
  - [sp1_InvUpdateStruct](#sp1_invupdatestruct)
  - [sp1_ValUpdateStruct](#sp1_valupdatestruct)
  - [sp1_DrawUpdateStructIfInv](#sp1_drawupdatestructifinv)
  - [sp1_DrawUpdateStructIfVal](#sp1_drawupdatestructifval)
  - [sp1_DrawUpdateStructIfNotRem](#sp1_drawupdatestructifnotrem)
  - [sp1_DrawUpdateStructAlways](#sp1_drawupdatestructalways)
  - [sp1_RemoveUpdateStruct](#sp1_removeupdatestruct)
  - [sp1_RestoreUpdateStruct](#sp1_restoreupdatestruct)
  - [sp1_Invalidate](#sp1_invalidate)
  - [sp1_Validate](#sp1_validate)
- [Funciones de dibujo (draw functions)](#funciones-de-dibujo-draw-functions)
  - [SP1_DRAW_MASK2](#sp1_draw_mask2)
  - [SP1_DRAW_MASK2NR](#sp1_draw_mask2nr)
  - [SP1_DRAW_MASK2LB](#sp1_draw_mask2lb)
  - [SP1_DRAW_MASK2RB](#sp1_draw_mask2rb)
  - [SP1_DRAW_LOAD2](#sp1_draw_load2)
  - [SP1_DRAW_LOAD2NR](#sp1_draw_load2nr)
  - [SP1_DRAW_LOAD2LB](#sp1_draw_load2lb)
  - [SP1_DRAW_LOAD2RB](#sp1_draw_load2rb)
  - [SP1_DRAW_OR2](#sp1_draw_or2)
  - [SP1_DRAW_OR2NR](#sp1_draw_or2nr)
  - [SP1_DRAW_OR2LB](#sp1_draw_or2lb)
  - [SP1_DRAW_OR2RB](#sp1_draw_or2rb)
  - [SP1_DRAW_XOR2](#sp1_draw_xor2)
  - [SP1_DRAW_XOR2NR](#sp1_draw_xor2nr)
  - [SP1_DRAW_XOR2LB](#sp1_draw_xor2lb)
  - [SP1_DRAW_XOR2RB](#sp1_draw_xor2rb)
  - [SP1_DRAW_LOAD2LBIM](#sp1_draw_load2lbim)
  - [SP1_DRAW_LOAD2RBIM](#sp1_draw_load2rbim)
  - [SP1_DRAW_LOAD1](#sp1_draw_load1)
  - [SP1_DRAW_LOAD1NR](#sp1_draw_load1nr)
  - [SP1_DRAW_LOAD1LB](#sp1_draw_load1lb)
  - [SP1_DRAW_LOAD1RB](#sp1_draw_load1rb)
  - [SP1_DRAW_OR1](#sp1_draw_or1)
  - [SP1_DRAW_OR1NR](#sp1_draw_or1nr)
  - [SP1_DRAW_OR1LB](#sp1_draw_or1lb)
  - [SP1_DRAW_OR1RB](#sp1_draw_or1rb)
  - [SP1_DRAW_XOR1](#sp1_draw_xor1)
  - [SP1_DRAW_XOR1NR](#sp1_draw_xor1nr)
  - [SP1_DRAW_XOR1LB](#sp1_draw_xor1lb)
  - [SP1_DRAW_XOR1RB](#sp1_draw_xor1rb)
  - [SP1_DRAW_LOAD1LBIM](#sp1_draw_load1lbim)
  - [SP1_DRAW_LOAD1RBIM](#sp1_draw_load1rbim)
  - [SP1_DRAW_ATTR](#sp1_draw_attr)

---

## Estructuras de datos

### sp1_Rect
Rectángulo en coordenadas de tiles (fila, columna, ancho, alto). Se usa para límites de impresión, invalidación y operaciones en tiles.

**Ejemplo:**
```c
struct sp1_Rect clip = { .row = 4, .col = 6, .width = 12, .height = 8 };
```

### sp1_update
Describe cada tile gestionado por SP1. Contiene estado de invalidación, color de fondo, tile, lista de sprites y puntero al área de pantalla.

**Ejemplo:**
```c
struct sp1_update *u = sp1_GetUpdateStruct(10, 10);
u->colour = 0x47;
```

### sp1_ss
Estructura principal del sprite. Guarda posición en tiles, tamaño, rotación, frame actual y lista de `sp1_cs`.

**Ejemplo:**
```c
struct sp1_ss *spr = sp1_CreateSpr(SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
spr->xthresh = 1;
```

### sp1_cs
“Sprite char” (pieza del sprite que cabe en un tile). Incluye atributos, plano, punteros a funciones de dibujo y enlaces en listas.

**Ejemplo:**
```c
struct sp1_cs cs;
sp1_InitCharStruct(&cs, SP1_DRAW_OR1, SP1_TYPE_1BYTE, gfx_tile, 0);
```

### sp1_ap
Par atributo/máscara para colores de sprite.

**Ejemplo:**
```c
struct sp1_ap ap = { .attr_mask = 0xFF, .attr = 0x47 };
```

### sp1_tp
Par tile/atributo para operaciones con fondo.

**Ejemplo:**
```c
struct sp1_tp tp = { .attr = 0x47, .tile = 'A' };
```

### sp1_pss
Estado de impresión de texto: límites, posición de cursor y atributos.

**Ejemplo:**
```c
struct sp1_pss ps = { &clip, SP1_PSSFLAG_INVALIDATE, 0, 0, 0xFF, 0x47, 0, 0 };
```

---

## Constantes y flags

### Tipos y atributos de sprites
- `SP1_TYPE_OCCLUDE`: el sprite oculta fondo y sprites debajo.
- `SP1_TYPE_BGNDCLR`: para sprites occlusivos, limpia con tile de fondo.
- `SP1_TYPE_2BYTE` / `SP1_TYPE_1BYTE`: formato de gráfico (con máscara o sin máscara).
- Máscaras de atributo: `SP1_AMASK_TRANS`, `SP1_AMASK_INK`, `SP1_AMASK_PAPER`, `SP1_AMASK_NOFLASH`, `SP1_AMASK_NOBRIGHT`.
- Atributo transparente: `SP1_ATTR_TRANS`.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_MASK2, SP1_TYPE_2BYTE | SP1_TYPE_OCCLUDE, 2, (int)gfx, 0);
```

### Flags de rectángulo y printing
- `SP1_RFLAG_TILE`, `SP1_RFLAG_COLOUR`, `SP1_RFLAG_SPRITE`: controlan qué se limpia o actualiza en rectángulos.
- `SP1_PSSFLAG_INVALIDATE`, `SP1_PSSFLAG_XWRAP`, `SP1_PSSFLAG_YINC`, `SP1_PSSFLAG_YWRAP`: control del comportamiento de impresión.

**Ejemplo:**
```c
sp1_ClearRect(&clip, 0x00, 0, SP1_RFLAG_TILE | SP1_RFLAG_COLOUR);
```

### Flags de inicialización (updater)
- `SP1_IFLAG_MAKE_ROTTBL`: genera tabla de rotaciones software.
- `SP1_IFLAG_OVERWRITE_TILES`: sobrescribe tabla de tiles.
- `SP1_IFLAG_OVERWRITE_DFILE`: sobrescribe pantalla durante inicialización.

**Ejemplo:**
```c
sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL, 0x00, 0);
```

---

## Flujo de inicialización recomendado
Flujo típico para arrancar SP1 en un proyecto:

1) Inicializar la librería con flags y fondo.
2) Definir tiles básicos con `sp1_TileEntry` si usas tabla de tiles.
3) Crear sprites y asignar frames.
4) Posicionar sprites con `sp1_MoveSprAbs` o `sp1_MoveSprPix`.
5) En el bucle principal, invalidar áreas y llamar a `sp1_UpdateNow`.

**Ejemplo:**
```c
sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL, 0x00, 0);
sp1_TileEntry('A', tileA);
struct sp1_ss *spr = sp1_CreateSpr(SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
sp1_MoveSprAbs(spr, &clip, frame0, 8, 12, 0, 0);
// loop:
// sp1_UpdateNow();
```

---

## Sprites: creación y configuración

### sp1_CreateSpr
Crea un sprite principal y devuelve un puntero a `struct sp1_ss`. Define tipo de gráficos (1 o 2 bytes), altura en tiles y plano.

**Ejemplo:**
```c
struct sp1_ss *spr = sp1_CreateSpr(SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### sp1_AddColSpr
Añade una columna (tile column) al sprite ya creado. Útil para sprites más anchos que 1 tile.

**Ejemplo:**
```c
sp1_AddColSpr(spr, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, (int)gfx_col2, 0);
```

### sp1_ChangeSprType
Cambia la función de dibujo de un `struct sp1_cs` (sprite char) existente.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_XOR2);
```

### sp1_DeleteSpr
Libera y elimina un sprite creado con `sp1_CreateSpr`.

**Ejemplo:**
```c
sp1_DeleteSpr(spr);
```

---

## Sprites: movimiento

### sp1_MoveSprAbs
Mueve el sprite a coordenadas absolutas (tile + rotación). Requiere que el sprite no esté en pantalla.

**Ejemplo:**
```c
sp1_MoveSprAbs(spr, &clip, frame0, 8, 12, 0, 0);
```

### sp1_MoveSprRel
Mueve el sprite en relativo (delta en tiles y rotaciones).

**Ejemplo:**
```c
sp1_MoveSprRel(spr, &clip, frame0, 0, 1, 0, 0); // mover 1 tile a la derecha
```

### sp1_MoveSprPix
Mueve el sprite por píxeles (x,y). Internamente ajusta tile y rotaciones.

**Ejemplo:**
```c
sp1_MoveSprPix(spr, &clip, frame0, 96, 40);
```

---

## Sprites: iteración y utilidades

### sp1_IterateSprChar
Recorre los `struct sp1_cs` de un sprite y llama a un hook por cada uno. Hook típico: `void hook(uint count, struct sp1_cs *c)`.

**Ejemplo:**
```c
void my_hook(uint count, struct sp1_cs *c) {
    (void)count; c->attr = 0x47;
}
sp1_IterateSprChar(spr, (void*)my_hook);
```

### sp1_IterateUpdateSpr
Itera las celdas del sprite que están en pantalla y llama a un hook por `sp1_update`. Hook típico: `void hook(uint count, struct sp1_update *u)`.

**Ejemplo:**
```c
void my_upd_hook(uint count, struct sp1_update *u) {
    (void)count; u->colour = 0x1F;
}
sp1_IterateUpdateSpr(spr, (void*)my_upd_hook);
```

### sp1_GetSprClrAddr
Obtiene la dirección interna donde están los atributos (colores) del sprite.

**Ejemplo:**
```c
uint8_t *sprclr;
sp1_GetSprClrAddr(spr, &sprclr);
```

### sp1_PutSprClr
Escribe pares atributo/máscara (`struct sp1_ap`) sobre el buffer de colores del sprite.

**Ejemplo:**
```c
struct sp1_ap colors[2] = {{0xFF, 0x47}, {0xFF, 0x43}};
uint8_t *sprclr;
sp1_GetSprClrAddr(spr, &sprclr);
sp1_PutSprClr(&sprclr, colors, 2);
```

### sp1_GetSprClr
Lee pares atributo/máscara desde el buffer de colores del sprite.

**Ejemplo:**
```c
struct sp1_ap out[2];
uint8_t *sprclr;
sp1_GetSprClrAddr(spr, &sprclr);
sp1_GetSprClr(&sprclr, out, 2);
```

### sp1_PreShiftSpr
Precalcula versiones desplazadas de un frame para acelerar rotaciones por software.

**Ejemplo:**
```c
void *shifted = sp1_PreShiftSpr(0, 2, 2, srcframe, dstframe, 3);
```

---

## Char structs independientes

### sp1_InitCharStruct
Inicializa un `struct sp1_cs` para usarlo de forma independiente (no conectado a un sprite).

**Ejemplo:**
```c
sp1_InitCharStruct(&cs, SP1_DRAW_OR1, SP1_TYPE_1BYTE, gfx_tile, 0);
```

### sp1_InsertCharStruct
Inserta el `struct sp1_cs` en un `struct sp1_update` para que se dibuje en pantalla.

**Ejemplo:**
```c
struct sp1_update *u = sp1_GetUpdateStruct(10, 10);
sp1_InsertCharStruct(u, &cs);
```

### sp1_RemoveCharStruct
Elimina el `struct sp1_cs` de la pantalla.

**Ejemplo:**
```c
sp1_RemoveCharStruct(&cs);
```

---

## Tiles y texto

### sp1_TileEntry
Define o asigna un tile en la tabla de tiles.

**Ejemplo:**
```c
sp1_TileEntry('A', tileA);
```

### sp1_PrintAt
Imprime un tile con atributo en una posición de pantalla.

**Ejemplo:**
```c
sp1_PrintAt(5, 10, 0x47, 'A');
```

### sp1_PrintAtInv
Igual que `sp1_PrintAt` pero invalidando el área para refresco inmediato.

**Ejemplo:**
```c
sp1_PrintAtInv(5, 11, 0x47, 'B');
```

### sp1_ScreenStr
Devuelve el tile actual en una posición (como código de pantalla).

**Ejemplo:**
```c
uint16_t t = sp1_ScreenStr(5, 10);
```

### sp1_ScreenAttr
Devuelve el atributo de color actual en una posición.

**Ejemplo:**
```c
uint16_t a = sp1_ScreenAttr(5, 10);
```

### sp1_PrintString
Imprime una cadena dentro de los límites definidos en `sp1_pss`.

**Ejemplo:**
```c
struct sp1_pss ps = { &clip, SP1_PSSFLAG_INVALIDATE, 0, 0, 0xFF, 0x47, 0, 0 };
sp1_PrintString(&ps, (uint8_t*)"HOLA");
```

### sp1_SetPrintPos
Mueve el cursor de impresión dentro de un `sp1_pss`.

**Ejemplo:**
```c
sp1_SetPrintPos(&ps, 2, 4);
```

### sp1_GetTiles
Copia tiles y atributos de un rectángulo a un buffer (`sp1_tp`).

**Ejemplo:**
```c
struct sp1_tp saved[16];
sp1_GetTiles(&clip, saved);
```

### sp1_PutTiles
Restaura tiles y atributos desde un buffer (`sp1_tp`).

**Ejemplo:**
```c
sp1_PutTiles(&clip, saved);
```

### sp1_PutTilesInv
Restaura tiles y atributos e invalida el rectángulo para redibujado.

**Ejemplo:**
```c
sp1_PutTilesInv(&clip, saved);
```

### sp1_ClearRect
Rellena un rectángulo con color/tile opcional y flags de qué limpiar.

**Ejemplo:**
```c
sp1_ClearRect(&clip, 0x00, 0, SP1_RFLAG_TILE | SP1_RFLAG_COLOUR);
```

### sp1_ClearRectInv
Igual que `sp1_ClearRect` pero invalidando el rectángulo.

**Ejemplo:**
```c
sp1_ClearRectInv(&clip, 0x00, 0, SP1_RFLAG_TILE | SP1_RFLAG_COLOUR);
```

---

## Updater (actualización de pantalla)

### sp1_Initialize
Inicializa SP1, configurando flags y tile/color de fondo.

**Ejemplo:**
```c
sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL, 0x00, 0);
```

### sp1_UpdateNow
Fuerza el refresco inmediato de las áreas invalidadas.

**Ejemplo:**
```c
sp1_UpdateNow();
```

### sp1_GetUpdateStruct
Obtiene el `sp1_update` asociado a una coordenada tile.

**Ejemplo:**
```c
struct sp1_update *u = sp1_GetUpdateStruct(10, 5);
```

### sp1_IterateUpdateArr
Itera un array de `sp1_update*` terminado en 0 y llama un hook.

**Ejemplo:**
```c
struct sp1_update *list[] = { u, 0 };
sp1_IterateUpdateArr(list, (void*)my_upd_hook);
```

### sp1_IterateUpdateRect
Itera todos los `sp1_update` dentro de un rectángulo.

**Ejemplo:**
```c
sp1_IterateUpdateRect(&clip, (void*)my_upd_hook);
```

### sp1_InvUpdateStruct
Marca un `sp1_update` como inválido (necesita redibujo).

**Ejemplo:**
```c
sp1_InvUpdateStruct(u);
```

### sp1_ValUpdateStruct
Marca un `sp1_update` como válido (no necesita redibujo).

**Ejemplo:**
```c
sp1_ValUpdateStruct(u);
```

### sp1_DrawUpdateStructIfInv
Dibuja el `sp1_update` solo si está inválido.

**Ejemplo:**
```c
sp1_DrawUpdateStructIfInv(u);
```

### sp1_DrawUpdateStructIfVal
Dibuja el `sp1_update` solo si está válido.

**Ejemplo:**
```c
sp1_DrawUpdateStructIfVal(u);
```

### sp1_DrawUpdateStructIfNotRem
Dibuja el `sp1_update` solo si no está marcado como eliminado.

**Ejemplo:**
```c
sp1_DrawUpdateStructIfNotRem(u);
```

### sp1_DrawUpdateStructAlways
Dibuja el `sp1_update` siempre, sin condiciones.

**Ejemplo:**
```c
sp1_DrawUpdateStructAlways(u);
```

### sp1_RemoveUpdateStruct
Marca un `sp1_update` como removido para que no se dibuje.

**Ejemplo:**
```c
sp1_RemoveUpdateStruct(u);
```

### sp1_RestoreUpdateStruct
Restaura un `sp1_update` previamente removido.

**Ejemplo:**
```c
sp1_RestoreUpdateStruct(u);
```

### sp1_Invalidate
Invalida todos los `sp1_update` en un rectángulo.

**Ejemplo:**
```c
sp1_Invalidate(&clip);
```

### sp1_Validate
Valida todos los `sp1_update` en un rectángulo.

**Ejemplo:**
```c
sp1_Validate(&clip);
```

---

## Funciones de dibujo (draw functions)

Estas funciones se pasan como puntero al crear sprites o inicializar `sp1_cs`.

### SP1_DRAW_MASK2
Dibujo con máscara y gráfico (2 bytes por columna). Rotación software.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_MASK2NR
Como `SP1_DRAW_MASK2` pero sin rotación (tile boundary exacto).

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_MASK2NR, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_MASK2LB
Como `SP1_DRAW_MASK2` pero para el borde izquierdo del sprite.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_MASK2LB);
```

### SP1_DRAW_MASK2RB
Como `SP1_DRAW_MASK2` pero para el borde derecho del sprite.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_MASK2RB);
```

### SP1_DRAW_LOAD2
Carga gráfico (2 bytes), ignora máscara. Rotación software.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_LOAD2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_LOAD2NR
Como `SP1_DRAW_LOAD2` sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_LOAD2NR, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_LOAD2LB
Como `SP1_DRAW_LOAD2` para borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD2LB);
```

### SP1_DRAW_LOAD2RB
Como `SP1_DRAW_LOAD2` para borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD2RB);
```

### SP1_DRAW_OR2
Combina gráfico por OR (2 bytes). Rotación software.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_OR2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_OR2NR
OR 2 bytes sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_OR2NR, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_OR2LB
OR 2 bytes borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_OR2LB);
```

### SP1_DRAW_OR2RB
OR 2 bytes borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_OR2RB);
```

### SP1_DRAW_XOR2
XOR 2 bytes con rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_XOR2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_XOR2NR
XOR 2 bytes sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_XOR2NR, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_XOR2LB
XOR 2 bytes borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_XOR2LB);
```

### SP1_DRAW_XOR2RB
XOR 2 bytes borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_XOR2RB);
```

### SP1_DRAW_LOAD2LBIM
LOAD 2 bytes borde izquierdo con máscara implícita.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD2LBIM);
```

### SP1_DRAW_LOAD2RBIM
LOAD 2 bytes borde derecho con máscara implícita.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD2RBIM);
```

### SP1_DRAW_LOAD1
Carga gráfico de 1 byte (sin máscara). Rotación software.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_LOAD1, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_LOAD1NR
LOAD 1 byte sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_LOAD1NR, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_LOAD1LB
LOAD 1 byte borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD1LB);
```

### SP1_DRAW_LOAD1RB
LOAD 1 byte borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD1RB);
```

### SP1_DRAW_OR1
OR 1 byte con rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_OR1, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_OR1NR
OR 1 byte sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_OR1NR, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_OR1LB
OR 1 byte borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_OR1LB);
```

### SP1_DRAW_OR1RB
OR 1 byte borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_OR1RB);
```

### SP1_DRAW_XOR1
XOR 1 byte con rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_XOR1, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_XOR1NR
XOR 1 byte sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_XOR1NR, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_XOR1LB
XOR 1 byte borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_XOR1LB);
```

### SP1_DRAW_XOR1RB
XOR 1 byte borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_XOR1RB);
```

### SP1_DRAW_LOAD1LBIM
LOAD 1 byte borde izquierdo con máscara implícita.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD1LBIM);
```

### SP1_DRAW_LOAD1RBIM
LOAD 1 byte borde derecho con máscara implícita.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD1RBIM);
```

### SP1_DRAW_ATTR
Dibuja solo atributos (sin píxeles).

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_ATTR, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

---

Si necesitas ampliar la documentación con más detalles (p. ej. tablas de rotación o gestión de clipping), dímelo y lo añado.# SP1 (Sprite Pack v3.0) – Documentación de la cabecera sp1.h

Documentación práctica de las funciones expuestas en la cabecera SP1 para ZX Spectrum. Incluye descripción y ejemplo mínimo por función. Las funciones están agrupadas por funcionalidad para facilitar la búsqueda.

> Nota: Los ejemplos son fragmentos ilustrativos. Ajusta tipos, tiles y gráficos según tu proyecto.

---

## Tabla de contenidos (TOC)

- [Sprites: creación y configuración](#sprites-creación-y-configuración)
  - [sp1_CreateSpr](#sp1_createspr)
  - [sp1_AddColSpr](#sp1_addcolspr)
  - [sp1_ChangeSprType](#sp1_changesprtype)
  - [sp1_DeleteSpr](#sp1_deletespr)
- [Sprites: movimiento](#sprites-movimiento)
  - [sp1_MoveSprAbs](#sp1_movesprabs)
  - [sp1_MoveSprRel](#sp1_movesprrel)
  - [sp1_MoveSprPix](#sp1_movesprpix)
- [Sprites: iteración y utilidades](#sprites-iteración-y-utilidades)
  - [sp1_IterateSprChar](#sp1_iteratesprchar)
  - [sp1_IterateUpdateSpr](#sp1_iterateupdatespr)
  - [sp1_GetSprClrAddr](#sp1_getsprclraddr)
  - [sp1_PutSprClr](#sp1_putsprclr)
  - [sp1_GetSprClr](#sp1_getsprclr)
  - [sp1_PreShiftSpr](#sp1_preshiftspr)
- [Char structs independientes](#char-structs-independientes)
  - [sp1_InitCharStruct](#sp1_initcharstruct)
  - [sp1_InsertCharStruct](#sp1_insertcharstruct)
  - [sp1_RemoveCharStruct](#sp1_removecharstruct)
- [Tiles y texto](#tiles-y-texto)
  - [sp1_TileEntry](#sp1_tileentry)
  - [sp1_PrintAt](#sp1_printat)
  - [sp1_PrintAtInv](#sp1_printatinv)
  - [sp1_ScreenStr](#sp1_screenstr)
  - [sp1_ScreenAttr](#sp1_screenattr)
  - [sp1_PrintString](#sp1_printstring)
  - [sp1_SetPrintPos](#sp1_setprintpos)
  - [sp1_GetTiles](#sp1_gettiles)
  - [sp1_PutTiles](#sp1_puttiles)
  - [sp1_PutTilesInv](#sp1_puttilesinv)
  - [sp1_ClearRect](#sp1_clearrect)
  - [sp1_ClearRectInv](#sp1_clearrectinv)
- [Updater (actualización de pantalla)](#updater-actualización-de-pantalla)
  - [sp1_Initialize](#sp1_initialize)
  - [sp1_UpdateNow](#sp1_updatenow)
  - [sp1_GetUpdateStruct](#sp1_getupdatestruct)
  - [sp1_IterateUpdateArr](#sp1_iterateupdatearr)
  - [sp1_IterateUpdateRect](#sp1_iterateupdaterect)
  - [sp1_InvUpdateStruct](#sp1_invupdatestruct)
  - [sp1_ValUpdateStruct](#sp1_valupdatestruct)
  - [sp1_DrawUpdateStructIfInv](#sp1_drawupdatestructifinv)
  - [sp1_DrawUpdateStructIfVal](#sp1_drawupdatestructifval)
  - [sp1_DrawUpdateStructIfNotRem](#sp1_drawupdatestructifnotrem)
  - [sp1_DrawUpdateStructAlways](#sp1_drawupdatestructalways)
  - [sp1_RemoveUpdateStruct](#sp1_removeupdatestruct)
  - [sp1_RestoreUpdateStruct](#sp1_restoreupdatestruct)
  - [sp1_Invalidate](#sp1_invalidate)
  - [sp1_Validate](#sp1_validate)
- [Funciones de dibujo (draw functions)](#funciones-de-dibujo-draw-functions)
  - [SP1_DRAW_MASK2](#sp1_draw_mask2)
  - [SP1_DRAW_MASK2NR](#sp1_draw_mask2nr)
  - [SP1_DRAW_MASK2LB](#sp1_draw_mask2lb)
  - [SP1_DRAW_MASK2RB](#sp1_draw_mask2rb)
  - [SP1_DRAW_LOAD2](#sp1_draw_load2)
  - [SP1_DRAW_LOAD2NR](#sp1_draw_load2nr)
  - [SP1_DRAW_LOAD2LB](#sp1_draw_load2lb)
  - [SP1_DRAW_LOAD2RB](#sp1_draw_load2rb)
  - [SP1_DRAW_OR2](#sp1_draw_or2)
  - [SP1_DRAW_OR2NR](#sp1_draw_or2nr)
  - [SP1_DRAW_OR2LB](#sp1_draw_or2lb)
  - [SP1_DRAW_OR2RB](#sp1_draw_or2rb)
  - [SP1_DRAW_XOR2](#sp1_draw_xor2)
  - [SP1_DRAW_XOR2NR](#sp1_draw_xor2nr)
  - [SP1_DRAW_XOR2LB](#sp1_draw_xor2lb)
  - [SP1_DRAW_XOR2RB](#sp1_draw_xor2rb)
  - [SP1_DRAW_LOAD2LBIM](#sp1_draw_load2lbim)
  - [SP1_DRAW_LOAD2RBIM](#sp1_draw_load2rbim)
  - [SP1_DRAW_LOAD1NR](#sp1_draw_load1nr)
  - [SP1_DRAW_LOAD1LB](#sp1_draw_load1lb)
  - [SP1_DRAW_LOAD1RB](#sp1_draw_load1rb)
  - [SP1_DRAW_OR1](#sp1_draw_or1)
  - [SP1_DRAW_OR1LB](#sp1_draw_or1lb)
  - [SP1_DRAW_OR1RB](#sp1_draw_or1rb)
  - [SP1_DRAW_XOR1](#sp1_draw_xor1)
  - [SP1_DRAW_XOR1LB](#sp1_draw_xor1lb)
  - [SP1_DRAW_XOR1RB](#sp1_draw_xor1rb)
  - [SP1_DRAW_LOAD1LBIM](#sp1_draw_load1lbim)
  - [SP1_DRAW_LOAD1RBIM](#sp1_draw_load1rbim)
  - [SP1_DRAW_ATTR](#sp1_draw_attr)


## Sprites: creación y configuración

Crea un sprite principal y devuelve un puntero a `struct sp1_ss`. Define tipo de gráficos (1 o 2 bytes), altura en tiles y plano.

**Ejemplo:**
```c
struct sp1_ss *spr = sp1_CreateSpr(SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### sp1_AddColSpr
Añade una columna (tile column) al sprite ya creado. Útil para sprites más anchos que 1 tile.

**Ejemplo:**
```c
```

### sp1_ChangeSprType
Cambia la función de dibujo de un `struct sp1_cs` (sprite char) existente.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_XOR2);
```

### sp1_DeleteSpr
Libera y elimina un sprite creado con `sp1_CreateSpr`.

**Ejemplo:**
```c
```

---

## Sprites: movimiento

### sp1_MoveSprAbs
Mueve el sprite a coordenadas absolutas (tile + rotación). Requiere que el sprite no esté en pantalla.

**Ejemplo:**
```c
sp1_MoveSprAbs(spr, &clip, frame0, 8, 12, 0, 0);
```

### sp1_MoveSprRel
Mueve el sprite en relativo (delta en tiles y rotaciones).

**Ejemplo:**
```c
sp1_MoveSprRel(spr, &clip, frame0, 0, 1, 0, 0); // mover 1 tile a la derecha
```

### sp1_MoveSprPix
Mueve el sprite por píxeles (x,y). Internamente ajusta tile y rotaciones.

**Ejemplo:**
```c
sp1_MoveSprPix(spr, &clip, frame0, 96, 40);
```

---

## Sprites: iteración y utilidades


  ## Estructuras de datos

Recorre los `struct sp1_cs` de un sprite y llama a un hook por cada uno.


**Ejemplo:**
  ```c
  struct sp1_Rect clip = { .row = 4, .col = 6, .width = 12, .height = 8 };
  ```

```c
void my_hook(uint count, struct sp1_cs *c) {

    (void)count; c->attr = 0x47;
  ```c
  struct sp1_update *u = sp1_GetUpdateStruct(10, 10);
  u->colour = 0x47;
  ```

}
sp1_IterateSprChar(spr, (void*)my_hook);

```
  ```c
  struct sp1_ss *spr = sp1_CreateSpr(SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
  spr->xthresh = 1;
  ```


### sp1_IterateUpdateSpr
Itera las celdas del sprite que están en pantalla y llama a un hook por `sp1_update`.

  ```c
  struct sp1_cs cs;
  sp1_InitCharStruct(&cs, SP1_DRAW_OR1, SP1_TYPE_1BYTE, gfx_tile, 0);
  ```

**Ejemplo:**
```c

void my_upd_hook(uint count, struct sp1_update *u) {
  ```c
  struct sp1_ap ap = { .attr_mask = 0xFF, .attr = 0x47 };
  ```

    (void)count; u->colour = 0x1F;
}

sp1_IterateUpdateSpr(spr, (void*)my_upd_hook);
  ```c
  struct sp1_tp tp = { .attr = 0x47, .tile = 'A' };
  ```

```


### sp1_GetSprClrAddr
  ```c
  struct sp1_pss ps = { &clip, SP1_PSSFLAG_INVALIDATE, 0, 0, 0xFF, 0x47, 0, 0 };
  ```


  ## Constantes y flags


  - `SP1_TYPE_OCCLUDE`: el sprite oculta fondo y sprites debajo.
  - `SP1_TYPE_BGNDCLR`: para sprites occlusivos, limpia con tile de fondo.
  - `SP1_TYPE_2BYTE` / `SP1_TYPE_1BYTE`: formato de gráfico (con máscara o sin máscara).
  - Máscaras de atributo: `SP1_AMASK_TRANS`, `SP1_AMASK_INK`, `SP1_AMASK_PAPER`, `SP1_AMASK_NOFLASH`, `SP1_AMASK_NOBRIGHT`.
  - Atributo transparente: `SP1_ATTR_TRANS`.

**Ejemplo:**
  ```c
  sp1_CreateSpr(SP1_DRAW_MASK2, SP1_TYPE_2BYTE | SP1_TYPE_OCCLUDE, 2, (int)gfx, 0);
  ```

```c
  - `SP1_RFLAG_TILE`, `SP1_RFLAG_COLOUR`, `SP1_RFLAG_SPRITE`: controlan qué se limpia o actualiza en rectángulos.
  - `SP1_PSSFLAG_INVALIDATE`, `SP1_PSSFLAG_XWRAP`, `SP1_PSSFLAG_YINC`, `SP1_PSSFLAG_YWRAP`: control del comportamiento de impresión.

uint8_t *sprclr;
  ```c
  sp1_ClearRect(&clip, 0x00, 0, SP1_RFLAG_TILE | SP1_RFLAG_COLOUR);
  ```

sp1_GetSprClrAddr(spr, &sprclr);
  - `SP1_IFLAG_MAKE_ROTTBL`: genera tabla de rotaciones software.
  - `SP1_IFLAG_OVERWRITE_TILES`: sobrescribe tabla de tiles.
  - `SP1_IFLAG_OVERWRITE_DFILE`: sobrescribe pantalla durante inicialización.

```
  ```c
  sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL, 0x00, 0);
  ```


  ## Flujo de inicialización recomendado
  Flujo típico para arrancar SP1 en un proyecto:

### sp1_PutSprClr
  2) Definir tiles básicos con `sp1_TileEntry` si usas tabla de tiles.
  3) Crear sprites y asignar frames.
  4) Posicionar sprites con `sp1_MoveSprAbs` o `sp1_MoveSprPix`.
  5) En el bucle principal, invalidar áreas y llamar a `sp1_UpdateNow`.

Escribe pares atributo/máscara (`struct sp1_ap`) sobre el buffer de colores del sprite.
  ```c
  sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL, 0x00, 0);
  sp1_TileEntry('A', tileA);
  struct sp1_ss *spr = sp1_CreateSpr(SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
  sp1_MoveSprAbs(spr, &clip, frame0, 8, 12, 0, 0);
  // loop:
  // sp1_UpdateNow();
  ```

  ---

**Ejemplo:**
```c
struct sp1_ap colors[2] = {{0xFF, 0x47}, {0xFF, 0x43}};
uint8_t *sprclr;
sp1_GetSprClrAddr(spr, &sprclr);
sp1_PutSprClr(&sprclr, colors, 2);
```

### sp1_GetSprClr
Lee pares atributo/máscara desde el buffer de colores del sprite.

**Ejemplo:**
```c
struct sp1_ap out[2];
uint8_t *sprclr;
sp1_GetSprClrAddr(spr, &sprclr);
sp1_GetSprClr(&sprclr, out, 2);
```

### sp1_PreShiftSpr
Precalcula versiones desplazadas de un frame para acelerar rotaciones por software.

**Ejemplo:**
```c
void *shifted = sp1_PreShiftSpr(0, 2, 2, srcframe, dstframe, 3);
```

---

## Char structs independientes

### sp1_InitCharStruct
Inicializa un `struct sp1_cs` para usarlo de forma independiente (no conectado a un sprite).

**Ejemplo:**
```c
sp1_InitCharStruct(&cs, SP1_DRAW_OR1, SP1_TYPE_1BYTE, gfx_tile, 0);
```

### sp1_InsertCharStruct
Inserta el `struct sp1_cs` en un `struct sp1_update` para que se dibuje en pantalla.

**Ejemplo:**
```c
struct sp1_update *u = sp1_GetUpdateStruct(10, 10);
sp1_InsertCharStruct(u, &cs);
```

### sp1_RemoveCharStruct
Elimina el `struct sp1_cs` de la pantalla.

**Ejemplo:**
```c
sp1_RemoveCharStruct(&cs);
```

---

## Tiles y texto

### sp1_TileEntry
Define o asigna un tile en la tabla de tiles.

**Ejemplo:**
```c
sp1_TileEntry('A', tileA);
```

### sp1_PrintAt
Imprime un tile con atributo en una posición de pantalla.

**Ejemplo:**
```c
sp1_PrintAt(5, 10, 0x47, 'A');
```

### sp1_PrintAtInv
Igual que `sp1_PrintAt` pero invalidando el área para refresco inmediato.

**Ejemplo:**
```c
sp1_PrintAtInv(5, 11, 0x47, 'B');
```

### sp1_ScreenStr
Devuelve el tile actual en una posición (como código de pantalla).

**Ejemplo:**
```c
uint16_t t = sp1_ScreenStr(5, 10);
```

### sp1_ScreenAttr
Devuelve el atributo de color actual en una posición.

**Ejemplo:**
```c
uint16_t a = sp1_ScreenAttr(5, 10);
```

### sp1_PrintString
Imprime una cadena dentro de los límites definidos en `sp1_pss`.

**Ejemplo:**
```c
struct sp1_pss ps = { &clip, SP1_PSSFLAG_INVALIDATE, 0, 0, 0xFF, 0x47, 0, 0 };
sp1_PrintString(&ps, (uint8_t*)"HOLA");
```

### sp1_SetPrintPos
Mueve el cursor de impresión dentro de un `sp1_pss`.

**Ejemplo:**
```c
sp1_SetPrintPos(&ps, 2, 4);
```

### sp1_GetTiles
Copia tiles y atributos de un rectángulo a un buffer (`sp1_tp`).

**Ejemplo:**
```c
struct sp1_tp saved[16];
sp1_GetTiles(&clip, saved);
```

### sp1_PutTiles
Restaura tiles y atributos desde un buffer (`sp1_tp`).

**Ejemplo:**
```c
sp1_PutTiles(&clip, saved);
```

### sp1_PutTilesInv
Restaura tiles y atributos e invalida el rectángulo para redibujado.

**Ejemplo:**
```c
sp1_PutTilesInv(&clip, saved);
```

### sp1_ClearRect
Rellena un rectángulo con color/tile opcional y flags de qué limpiar.

**Ejemplo:**
```c
sp1_ClearRect(&clip, 0x00, 0, SP1_RFLAG_TILE | SP1_RFLAG_COLOUR);
```

### sp1_ClearRectInv
Igual que `sp1_ClearRect` pero invalidando el rectángulo.

**Ejemplo:**
```c
sp1_ClearRectInv(&clip, 0x00, 0, SP1_RFLAG_TILE | SP1_RFLAG_COLOUR);
```

---

## Updater (actualización de pantalla)

### sp1_Initialize
Inicializa SP1, configurando flags y tile/color de fondo.

**Ejemplo:**
```c
sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL, 0x00, 0);
```

### sp1_UpdateNow
Fuerza el refresco inmediato de las áreas invalidadas.

**Ejemplo:**
```c
sp1_UpdateNow();
```

### sp1_GetUpdateStruct
Obtiene el `sp1_update` asociado a una coordenada tile.

**Ejemplo:**
```c
struct sp1_update *u = sp1_GetUpdateStruct(10, 5);
```

### sp1_IterateUpdateArr
Itera un array de `sp1_update*` terminado en 0 y llama un hook.

**Ejemplo:**
```c
struct sp1_update *list[] = { u, 0 };
sp1_IterateUpdateArr(list, (void*)my_upd_hook);
```

### sp1_IterateUpdateRect
Itera todos los `sp1_update` dentro de un rectángulo.

**Ejemplo:**
```c
sp1_IterateUpdateRect(&clip, (void*)my_upd_hook);
```

### sp1_InvUpdateStruct
Marca un `sp1_update` como inválido (necesita redibujo).

**Ejemplo:**
```c
sp1_InvUpdateStruct(u);
```

### sp1_ValUpdateStruct
Marca un `sp1_update` como válido (no necesita redibujo).

**Ejemplo:**
```c
sp1_ValUpdateStruct(u);
```

### sp1_DrawUpdateStructIfInv
Dibuja el `sp1_update` solo si está inválido.

**Ejemplo:**
```c
sp1_DrawUpdateStructIfInv(u);
```

### sp1_DrawUpdateStructIfVal
Dibuja el `sp1_update` solo si está válido.

**Ejemplo:**
```c
sp1_DrawUpdateStructIfVal(u);
```

### sp1_DrawUpdateStructIfNotRem
Dibuja el `sp1_update` solo si no está marcado como eliminado.

**Ejemplo:**
```c
sp1_DrawUpdateStructIfNotRem(u);
```

### sp1_DrawUpdateStructAlways
Dibuja el `sp1_update` siempre, sin condiciones.

**Ejemplo:**
```c
sp1_DrawUpdateStructAlways(u);
```

### sp1_RemoveUpdateStruct
Marca un `sp1_update` como removido para que no se dibuje.

**Ejemplo:**
```c
sp1_RemoveUpdateStruct(u);
```

### sp1_RestoreUpdateStruct
Restaura un `sp1_update` previamente removido.

**Ejemplo:**
```c
sp1_RestoreUpdateStruct(u);
```

### sp1_Invalidate
Invalida todos los `sp1_update` en un rectángulo.

**Ejemplo:**
```c
sp1_Invalidate(&clip);
```

### sp1_Validate
Valida todos los `sp1_update` en un rectángulo.

**Ejemplo:**
```c
sp1_Validate(&clip);
```

---

## Funciones de dibujo (draw functions)

Estas funciones se pasan como puntero al crear sprites o inicializar `sp1_cs`.

### SP1_DRAW_MASK2
Dibujo con máscara y gráfico (2 bytes por columna). Rotación software.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_MASK2NR
Como `SP1_DRAW_MASK2` pero sin rotación (tile boundary exacto).

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_MASK2NR, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_MASK2LB
Como `SP1_DRAW_MASK2` pero para el borde izquierdo del sprite.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_MASK2LB);
```

### SP1_DRAW_MASK2RB
Como `SP1_DRAW_MASK2` pero para el borde derecho del sprite.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_MASK2RB);
```

### SP1_DRAW_LOAD2
Carga gráfico (2 bytes), ignora máscara. Rotación software.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_LOAD2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_LOAD2NR
Como `SP1_DRAW_LOAD2` sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_LOAD2NR, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_LOAD2LB
Como `SP1_DRAW_LOAD2` para borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD2LB);
```

### SP1_DRAW_LOAD2RB
Como `SP1_DRAW_LOAD2` para borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD2RB);
```

### SP1_DRAW_OR2
Combina gráfico por OR (2 bytes). Rotación software.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_OR2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_OR2NR
OR 2 bytes sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_OR2NR, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_OR2LB
OR 2 bytes borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_OR2LB);
```

### SP1_DRAW_OR2RB
OR 2 bytes borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_OR2RB);
```

### SP1_DRAW_XOR2
XOR 2 bytes con rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_XOR2, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_XOR2NR
XOR 2 bytes sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_XOR2NR, SP1_TYPE_2BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_XOR2LB
XOR 2 bytes borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_XOR2LB);
```

### SP1_DRAW_XOR2RB
XOR 2 bytes borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_XOR2RB);
```

### SP1_DRAW_LOAD2LBIM
LOAD 2 bytes borde izquierdo con máscara implícita.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD2LBIM);
```

### SP1_DRAW_LOAD2RBIM
LOAD 2 bytes borde derecho con máscara implícita.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD2RBIM);
```

### SP1_DRAW_LOAD1
Carga gráfico de 1 byte (sin máscara). Rotación software.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_LOAD1, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_LOAD1NR
LOAD 1 byte sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_LOAD1NR, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_LOAD1LB
LOAD 1 byte borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD1LB);
```

### SP1_DRAW_LOAD1RB
LOAD 1 byte borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD1RB);
```

### SP1_DRAW_OR1
OR 1 byte con rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_OR1, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_OR1NR
OR 1 byte sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_OR1NR, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_OR1LB
OR 1 byte borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_OR1LB);
```

### SP1_DRAW_OR1RB
OR 1 byte borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_OR1RB);
```

### SP1_DRAW_XOR1
XOR 1 byte con rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_XOR1, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_XOR1NR
XOR 1 byte sin rotación.

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_XOR1NR, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

### SP1_DRAW_XOR1LB
XOR 1 byte borde izquierdo.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_XOR1LB);
```

### SP1_DRAW_XOR1RB
XOR 1 byte borde derecho.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_XOR1RB);
```

### SP1_DRAW_LOAD1LBIM
LOAD 1 byte borde izquierdo con máscara implícita.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD1LBIM);
```

### SP1_DRAW_LOAD1RBIM
LOAD 1 byte borde derecho con máscara implícita.

**Ejemplo:**
```c
sp1_ChangeSprType(cs, SP1_DRAW_LOAD1RBIM);
```

### SP1_DRAW_ATTR
Dibuja solo atributos (sin píxeles).

**Ejemplo:**
```c
sp1_CreateSpr(SP1_DRAW_ATTR, SP1_TYPE_1BYTE, 2, (int)gfx, 0);
```

---

Si necesitas ampliar la documentación con estructuras, macros o flujo de inicialización recomendado, indícalo y lo añado.

// Read-Only Data Section for User Module
SECTION rodata_user

PUBLIC _tile_brick
_tile_brick:
    defb @11111110
    defb @10000010
    defb @10000010
    defb @11111110
    defb @10000010
    defb @10000010
    defb @10000010
    defb @11111110

PUBLIC _tile_grass
_tile_grass:
    defb @00000000
    defb @00000000
    defb @00010001
    defb @00100010
    defb @01000100
    defb @00010001
    defb @11101110
    defb @11111111

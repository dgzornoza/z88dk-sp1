SECTION rodata_user

PUBLIC _sprite_masked_circle

; 7 bytes arriba (padding) para rotación vertical segura
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000
_sprite_masked_circle:
; Pares: primero el byte de mascara y luego el sprite grafico
    defb @11000011, @00111100
    defb @10000001, @01000010
    defb @00000000, @10000001
    defb @00000000, @10000001
    defb @00000000, @10000001
    defb @00000000, @10000001
    defb @10000001, @01000010
    defb @11000011, @00111100

    ; 8 bytes abajo (padding) para rotación vertical segura
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000
	defb @11111111, @00000000

SECTION rodata_user

PUBLIC _sprite_player

    ; 7 bytes arriba (padding) para rotación vertical segura
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000

_sprite_player:
    ; sprite grafico frame 1
	defb @00011000
	defb @00011110
	defb @00000000
	defb @00010000
	defb @00010000
	defb @00000000
	defb @00100000
	defb @00011000

; 8 bytes abajo (padding) para rotación vertical segura
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000

_sprite_player_f2:
; sprite grafico frame 2
	defb @00011000
	defb @00011110
	defb @00000000
	defb @00100000
	defb @00100000
	defb @00000010
	defb @00000100
	defb @00110000

; 8 bytes abajo (padding) para rotación vertical segura
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000

_sprite_player_f3:
; sprite grafico frame 3
	defb @00000000
	defb @00011000
	defb @00011110
	defb @00000000
	defb @00100000
	defb @01000000
	defb @00000000
	defb @01100110

; 8 bytes abajo (padding) para rotación vertical segura
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000

_sprite_player_f4:
; sprite grafico frame 4
	defb @00011000
	defb @00011110
	defb @00000000
	defb @00010000
	defb @00100000
	defb @00000000
	defb @01000000
	defb @01001100

; 8 bytes abajo (padding) para rotación vertical segura
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000

_sprite_player_f5:
; sprite grafico frame 5
	defb @00011000
	defb @00011110
	defb @00000000
	defb @00001000
	defb @00010000
	defb @00000000
	defb @00100000
	defb @00011000

; 8 bytes abajo (padding) para rotación vertical segura
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000

_sprite_player_f6:
; sprite grafico frame 6
	defb @00011000
	defb @00011110
	defb @00000000
	defb @00001000
	defb @00001000
	defb @00000010
	defb @00000100
	defb @00110000

; 8 bytes abajo (padding) para rotación vertical segura
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000

_sprite_player_f7:
; sprite grafico frame 7
	defb @00000000
	defb @00011000
	defb @00011110
	defb @00000000
	defb @00001000
	defb @00000100
	defb @00000000
	defb @01100110

; 8 bytes abajo (padding) para rotación vertical segura
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000

_sprite_player_f8:
; sprite grafico frame 8
	defb @00011000
	defb @00011110
	defb @00000000
	defb @00010000
	defb @00001000
	defb @00000000
	defb @01000000
	defb @01001100

; 8 bytes abajo (padding) para rotación vertical segura
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000
	defb @00000000

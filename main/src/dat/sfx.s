.area				_DATA

FLAG_NOISE			= 0x01
FLAG_ENV			= 0x02
FLAG_VIB			= 0x04 


; Note Count first, then

; Note format for each note (9 bytes):
; .dw period
; .db duration
; .db volume
; .db flags (noise, envelope, vibrato)
; .db noise period
; .db envelope
; .db vibrato depth
; .db vibrato speed

.globl				_sfx_footstep
.globl				_sfx_get_item
.globl				_sfx_spawn
.globl				_sfx_show_hint
.globl				_sfx_open_door
.globl				_sfx_use_bomb
.globl				_sfx_splat
.globl				_sfx_shoot

_sfx_footstep:

	.db				2 

	.dw 			0x0200 
	.db				4 
	.db				10 
	.db				FLAG_ENV | FLAG_NOISE
	.db				14
	.db				0x0D
	.db				0
	.db				0

	.dw				0x0000
	.db				4
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0


_sfx_get_item:

	.db				5 

	.dw				0x0200
	.db				2
	.db				12
	.db				FLAG_ENV
	.db				0
	.db				0x0F
	.db				0
	.db				0

	.dw				0x0180
	.db				1
	.db				15
	.db				FLAG_ENV 
	.db				0
	.db				0x0F
	.db				0
	.db				0 

	.dw				0x0140
	.db				4
	.db				12
	.db				FLAG_ENV
	.db				0
	.db				0x0F
	.db				0
	.db				0

	.dw				0x0200
	.db				6
	.db				8
	.db				FLAG_ENV
	.db				0
	.db				0x0F
	.db				0
	.db				0

	.dw				0x0000
	.db				10
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0


_sfx_spawn:

	.db				2 

	.dw 			0x00BE
	.db				12
	.db				15
	.db				FLAG_ENV
	.db				0
	.db				0x09
	.db				0
	.db				0

	.dw				0x0000
	.db				6
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0


_sfx_show_hint:

	.db				4

	.dw				0x0094 
	.db				6
	.db				15
	.db				FLAG_ENV
	.db				0
	.db				0x09
	.db				0
	.db				0

	.dw				0x0078
	.db				6
	.db				15
	.db				FLAG_ENV
	.db				0
	.db				0x09
	.db				0
	.db				0

	.dw				0x0064
	.db				8
	.db				20
	.db				FLAG_ENV
	.db				0
	.db				0x09
	.db				0
	.db				0

	.dw				0x0000
	.db				6
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0


_sfx_open_door:

	.db				7 

	.dw				0x0240
	.db				3
	.db				15
	.db				FLAG_ENV
	.db				0
	.db				0x09
	.db				0
	.db				0

	.dw				0x0200
	.db				3
	.db				15
	.db				FLAG_ENV
	.db				0
	.db				0x09
	.db				0
	.db				0

	.dw				0x01C0
	.db				4
	.db				15
	.db				FLAG_ENV | FLAG_NOISE
	.db				28
	.db				0x09
	.db				0
	.db				0

	.dw				0x0180
	.db				5
	.db				15
	.db				FLAG_ENV | FLAG_NOISE
	.db				24
	.db				0x09
	.db				0
	.db				0

	.dw				0x0140
	.db				6
	.db				15
	.db				FLAG_ENV | FLAG_NOISE
	.db				18
	.db				0x09
	.db				0
	.db				0

	.dw				0x0001
	.db				5
	.db				15
	.db				FLAG_ENV | FLAG_NOISE
	.db				10
	.db				0x09
	.db				0
	.db				0

	.dw				0x0000
	.db				10
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0


_sfx_use_bomb:

	.db				3

	.dw				0x00E3
	.db				24
	.db				12
	.db				FLAG_VIB | FLAG_ENV
	.db				0
	.db				0x09
	.db				2
	.db				3

	.dw				0x00BE
	.db				16
	.db				11
	.db				FLAG_VIB | FLAG_ENV
	.db				0
	.db				0x09
	.db				2
	.db				3

	.dw				0x0000
	.db				10
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0


_sfx_splat:

	.db				4 

	.dw				0x0300
	.db				3
	.db				15
	.db				FLAG_NOISE | FLAG_ENV
	.db				4
	.db				0x09
	.db				0
	.db				0

	.dw				0x0280
	.db				6
	.db				12
	.db				FLAG_NOISE
	.db				10
	.db				0
	.db				0
	.db				0

	.dw				0x0200
	.db				8
	.db				8
	.db				FLAG_NOISE
	.db				18
	.db				0
	.db				0
	.db				0

	.dw				0x0000
	.db				6
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0


_sfx_shoot:

	.db				2

	.dw				0x0060
	.db				2
	.db				12
	.db				FLAG_NOISE
	.db				3
	.db				0
	.db				0
	.db				0

	.dw				0x0000
	.db				2
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0
	.db				0

.module sfx_engine

; ===============================
; CONSTANTS
; ===============================

FLAG_NOISE			= 0x01
FLAG_ENV 			= 0x02
FLAG_VIB			= 0x04
NOTE_SIZE			= 9

; ===============================
; DATA
; ===============================
.area				_DATA

sfx_active:			.db 0
sfx_note_count: 	.db 0
sfx_table_ptr:		.dw 0

note_pos:			.db 0
note_hold:			.db 0
note_flags:			.db 0
note_noise_per:		.db 0
note_env_shape:		.db 0
note_vib_depth:		.db 0
note_vib_speed:		.db 0
vib_phase:			.db 0

vib_table:
					.db  0, -1, -2, -1, 0, 1, 2, 1

; ===============================
; CODE
; ===============================
.area				_CODE

.globl				_sfx_start
.globl				_sfx_update
.globl				_sfx_stop

; ==============================================================================
; PSG write (C = register, E = value)
; ==============================================================================
psg_write:

	di
	ld				b,#0xF4
	out				(c),c

	ld				b,#0xF6
	ld				a,#0xC0
	out				(c),a

	xor				a
	out				(c),a

	ld				b,#0xF4
	out				(c),e

	ld				b,#0xF6
	ld				a,#0x80
	out				(c),a

	xor				a
	out				(c),a
	ei
	ret

; ==============================================================================
; Write tone period to channel A (HL = period)
; ==============================================================================
psg_tone_A:

	ld				c,#0
	ld				e,l
	call			psg_write

	ld				c,#1
	ld				e,h
	call			psg_write
	ret

; ==============================================================================
; SFX START (HL = pointer to SFX table)
; ==============================================================================
_sfx_start::

	ld				a,(sfx_active)
	or				a
	ret				nz					; already playing

	ld				(sfx_table_ptr),hl
	ld 				a,(hl)				; first byte = note count
	ld (sfx_note_count),a

	xor				a
	ld				(note_pos),a
	ld				(note_hold),a
	ld				(note_flags),a
	ld				(vib_phase),a

	ld				c,#8				; Hard reset channel A state
	ld				e,#0
	call			psg_write

	ld				c,#0x0D
	ld				e,#0xFF
	call			psg_write

	ld				a,#1
	ld				(sfx_active),a
	ret

; ==============================================================================
; SFX STOP
; ==============================================================================
_sfx_stop::

	xor				a
	ld				(sfx_active),a

	ld				c,#8
	ld				e,#0
	call			psg_write
	ret

; ==============================================================================
; SFX UPDATE (NOTE_SIZE = 9)
; ==============================================================================
_sfx_update::

	ld				a,(sfx_active)
	or				a
	ret				z

	
	ld				hl,(sfx_table_ptr)	; HL = table + 1 + note_pos * 9
	inc				hl

	ld				a,(note_pos)
	ld				e,a
	ld				d,#0

	
	add				hl,de				; ×9
	add				hl,de
	add				hl,de
	add				hl,de
	add				hl,de
	add				hl,de
	add				hl,de
	add				hl,de
	add				hl,de

	push			hl					; Read note data (9 bytes)
	inc				hl
	inc				hl
	ld				b,(hl)				; duration
	inc				hl
	ld				d,(hl)				; volume
	inc				hl
	ld				a,(hl)				; flags
	inc				hl
	ld				c,(hl)				; noise period
	inc				hl
	ld				e,(hl)				; envelope shape
	inc				hl
	ld				l,(hl)				; vibrato depth
	inc				hl
	ld				h,(hl)				; vibrato speed
	pop				hl

	ld				(note_flags),a

	ld				a,c
	ld				(note_noise_per),a

	ld				a,e
	ld				(note_env_shape),a

	ld				a,l
	ld				(note_vib_depth),a

	ld				a,h
	ld				(note_vib_speed),a

	ld				a,(note_hold)		; Hold logic
	cp				b
	jr				c,hold_note

	xor				a
	ld				(note_hold),a

	ld				a,(note_pos)
	inc				a
	ld				b,a
	ld				a,(sfx_note_count)
	cp				b
	jr				nz,store_pos

	call			_sfx_stop
	ret

store_pos:
	ld				a,b
	ld				(note_pos),a
	xor				a
	ld				(vib_phase),a 		; reset vibrato per note
	jr				play_note

hold_note:
	inc				a
	ld				(note_hold),a

play_note:
	ld				e,(hl)				; Read tone period
	inc				hl
	ld				h,(hl)
	ld 				l,e

	ld				a,d					; Rest if volume = 0
	or				a
	jr				z,rest_note

	ld				a,(note_flags)		; Vibrato
	and				#FLAG_VIB
	jr				z,no_vibrato

	ld				a,(note_vib_speed)
	ld				b,a
	ld				a,(note_hold)
	and				b
	jr				nz,no_vibrato

	ld				a,(vib_phase)
	inc				a
	and				#7
	ld				(vib_phase),a

	ld				hl,#vib_table
	ld				e,a
	ld				d,#0
	add				hl,de
	ld				a,(hl)

	ld				e,a
	ld				a,l
	add				a,e
	ld				l,a
	jr				nc,no_vib_carry
	inc				h

no_vib_carry:
no_vibrato:

	ld				a,(note_flags)		; Mixer (noise optional)
	and				#FLAG_NOISE
	jr				z,tone_only

	ld				c,#7
	ld				e,#0x36
	call				psg_write

	ld				a,(note_noise_per)
	ld				c,#6
	ld				e,a
	call				psg_write
	jr				mixer_done

tone_only:
	ld				c,#7
	ld				e,#0x3E
	call				psg_write

mixer_done:
	ld				a,(note_flags)		; Volume / Envelope
	and				#FLAG_ENV
	jr				z,fixed_volume

	ld				a,(note_hold)
	or				a
	jr				nz,env_volume_only

	ld				c,#0x0B
	ld				e,l
	call				psg_write

	ld				c,#0x0C
	ld				e,h
	call				psg_write

	ld				a,(note_env_shape)
	ld				c,#0x0D
	ld				e,a
	call				psg_write

env_volume_only:
	ld				c,#8
	ld				e,#0x10
	call				psg_write
	jr				play_tone

fixed_volume:
	ld				a,d
	ld				c,#8
	ld				e,a
	call				psg_write

play_tone:
	call				psg_tone_A
	ret

rest_note:
	ld				c,#8
	ld				e,#0
	call				psg_write
	ret

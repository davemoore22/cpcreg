    .area _DATA

    .globl _g_level_fg
    .globl _g_screen_bg

    ; Export CPCTelera constants for ASM
LEVEL_SCRS      .equ 12
LEVEL_U_W       .equ 16
LEVEL_U_H       .equ 9

_g_level_fg:
    .ds LEVEL_SCRS * LEVEL_U_W * LEVEL_U_H

_g_screen_bg:
    .ds LEVEL_U_W * LEVEL_U_H


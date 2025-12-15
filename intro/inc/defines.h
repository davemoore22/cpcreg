/*
 * Reginald and the She Vampires for the Amstrad CPC
 * Copyright (C) 2026 Dave Moore
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cpctelera.h>

/* C-standard used for Compilation */
#define C99
#undef C11

/* For Image Decompression */
#define VIDEO_MEM_END ((void *)0xffff)
#define VIDEO_MEM_START ((void *)0xC000)

#define MASK_TABLE_LOC 0x6000 /* 0x0100 bytes long */
#define DISK_TABLE_LOC 0x6100 /* 0x0100 bytes long */
#define MENU_MUSIC_LOC 0x5000 /* 0x0C00 bytes long */
#define CODE_ENTRY_POINT 0x1400

/* Size of Character Font in Bytes/Lines (8x8 pixels) */
#define LINE_P_W 2
#define LINE_P_W_SHIFT 1
#define LINE_P_H 8
#define LINE_P_H_SHIFT 3

/* String Indexes */
#define SCROLLING_TITLE_TEXT 0

/* Length of Scroller Text (g_strings [0]) */
#define SCROLLER_TEXT_LEN 310

/* Pens */
#define PEN_0 0
#define PEN_1 1
#define PEN_2 2
#define PEN_3 3

/* Timings */
#define FC_MAX 50
#define FC_TICK 5

/* WinAPE Breakpoint Macro */
#define WinwApe_Brk __asm__(".dw #0xFFED");

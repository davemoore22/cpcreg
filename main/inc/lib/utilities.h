/*
 * Reginald and the She Vampires for the Amstrad CPC
 * Copyright (C) 2025 Dave Moore
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

#include "main.h"

/* Global Variables */
extern bool g_clock_on; /* Enable Global Timer */
extern clock_t g_clock; /* Realtime Clock */
extern const key_t u_key_mapping[KEY_MAPPING_REDEFINE_SZ];

extern void __divulong(void);

/* Public Functions */
void utils_wait_for_key(cpct_keyID key);
void utils_wait(const u16 n);
cpct_keyID utils_map_ascii_to_key(const u8 ascii);
u8 utils_map_key_to_ascii(const cpct_keyID key);
u8 utils_get_str_width(const u32 score);
void utils_clock_interrupt(void);
void utils_reset_clock(void);
void utils_clear_input(void);
cpct_keyID utils_wait_for_keys(const cpct_keyID *keys, u8 num_keys);
cpct_keyID utils_wait_for_extended_key(void);

/* Game Data Functions */
inline void utils_get_delta(const dir_t dir, i8 *dx, i8 *dy);
u16 utils_get_screen_x_y(const u8 zone_index, const u8 x, const u8 y);

/* Replacement Standard Library Functions */
char *utils_strcpy(char *dest, const char *src);
u8 utils_strlen(const char *str);
u32 utils_abs(i32 x);
i8 utils_sign(u8 uval);
void utils_itoa_2(char *buf, u8 num);
void utils_itoa_4(char *buf, u16 num);
void utils_itoa_6(char *buf, u32 num);
void utils_sort_hiscores(void);
u8 utils_rand_0_8(void);
void utils_clock_tick(void);

/* Load data from Disc without using Firmware */
void utils_load(char file_name[12], u8 *loc);

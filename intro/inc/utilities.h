/*
 * Reginald and the She Vampires for the Amstrad CPC
 * Copyright (C) 2026 davy moore
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

/* Public Functions */
void utils_clock_interrupt(void);
void utils_reset_clock(void);

/* Replacement Standard Library Functions */
char *utils_str_cpy(char *dest, const char *src);
void utils_str_cpy_n(char *dest, const char *src, u16 n);
u8 utils_str_len(const char *str);
void utils_rotate_str_fixed(char *str, u16 n, u16 len);
void utils_load(char file_name[12], u8 *loc);
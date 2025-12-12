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

/* Interrupt Indexes */
extern u8 v_int_idx;
extern u8 v_pal_idx;
extern u8 v_frame_c;

/* Public Functions */
void video_init(void);
void video_blk_scr(void);
void video_reset_pal(void);
void video_reset_pal_presents(void);
void video_reset_pal_guide(void);
void video_wait_VSYNC(u8 n);
void video_clr_scr(void);
void video_wipe_scr(bool dir);
void video_reset_timers(void);
inline u8 *video_get_pos(const u8 x, const u8 y);
void video_print_c(const char *str, const u8 y);
void video_print(const char *str, const u8 x, const u8 y);

/*
 * Reginald and the Sex Vampires for the Amstrad CPC
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
extern u8 v_pen;
extern u8 v_flash_index;
extern u8 v_flash_active;

/* Public Functions */
void video_init(void);
void video_blank_screen(void);
void video_full_clear(void);
void video_reset_palette(void);
void video_clear_screen(void);
void video_wipe_screen(bool dir);
void video_reset_timers(void);
void video_print_centred_text(const char *str, const u8 y);
void video_print_text(const char *str, const u8 x, const u8 y);
void video_clear_centre(void);
void video_draw_GUI(void);
void video_draw_title(const u8 y);
void video_draw_HUD(void);
void video_clear_HUD(void);
void video_draw_player(void);
void video_draw_hint(const u8 hint_id);
void video_draw_dirty_tiles(void);
void video_clear_dirty_list(void);
void video_mark_dirty_tile(const u8 x, const u8 y);
void video_draw_rect(u8 tx, u8 ty, u8 tw, u8 th);
void video_draw_bullet(void);
void video_monster_draw_all(void);
void video_draw_xor_sprite(const u8 *spr, u8 x, u8 y);
void video_flash_border(u8 c0, u8 c1, u8 c2);
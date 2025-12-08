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

/* Global variables */
extern cpct_keyID g_controls[CONTROLS_SZ];
extern score_t g_hiscores[HISCORES_SZ];
extern u8 g_options;

extern u8 g_int_idx;
extern u8 g_frame_c;

extern player_t g_player;
extern game_t g_game;
extern bullet_t g_bullet;

extern u8 g_screen_bg[SCREEN_U_W * SCREEN_U_H];
extern u8 g_level_fg[LEVEL_SCRS * SCREEN_U_W * SCREEN_U_H];

extern bool g_has_bullet;

/* Public functions */
void game_setup(void);
u32 game_start(void);
void game_stop(void);
void game_update_health_string(void);
inline void game_take_damage(u16 amount);
void game_update_player_facing(dir_t newdir);
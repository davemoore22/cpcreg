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

extern u8 g_monmap[MONMAP_BYTES];
extern monster_t g_monsters[MAX_MONSTERS];

/* Spawn timers */
extern u8 g_bat_spawn_timer;
extern u8 g_zombie_spawn_timer;
extern u8 g_ghost_spawn_timer;

/* Movement helpers */
extern const i8 mon_step_bx[4];
extern const i8 mon_step_by[4];
void monster_init_all(void);

/* Monster map */
void monmap_clear_all(void);
u8 monmap_get(u8 gx, u8 gy);
void monmap_set(u8 gx, u8 gy, u8 type);

/* Spawning */
monster_t *monster_spawn(u8 type, u8 screen, u8 gx, u8 gy);
void monster_update_spawn_timers(void);
void monster_try_spawns(void);
void monster_try_spawn_bat(u8 screen);
void monster_try_spawn_zombie(u8 screen);
void monster_try_spawn_ghost(u8 screen);

/* Animation */
void monster_tick_animation(void);

/* Movement */
void monster_update_moves(void);
void monster_step_all_pixels(events_t *events);

/* Despawning when player leaves screen */
void monster_despawn_offscreen(void);

/* Collisions */
void monster_player_collisions(events_t *events);
monster_t *monster_find_at(u8 screen, u8 gx, u8 gy);
void monster_kill(monster_t *m, events_t *events);

u16 monmap_idx(u8 gx, u8 gy);
u8 monmap_get(u8 gx, u8 gy);
void monmap_set(u8 gx, u8 gy, u8 type);

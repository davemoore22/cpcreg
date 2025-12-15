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

#pragma codeseg CODE

#include "monster.h"

u8 g_monmap[MONMAP_BYTES];
monster_t g_monsters[MAX_MONSTERS];

u8 g_bat_spawn_timer;
u8 g_zombie_spawn_timer;
u8 g_ghost_spawn_timer;

/* Movement helpers (unaltered) */
const i8 mon_step_bx[4] = {0, 0, 2, -2};
const i8 mon_step_by[4] = {-8, 8, 0, 0};

const u8 monster_base_hp[] = {
	[MON_BAT] = 1,
	[MON_ZOMBIE] = 2,
	[MON_GHOST] = 3,
};

static dir_t monster_pick_move_dir(monster_t *m);
static bool monster_can_enter_tile(monster_t *m, u8 gx, u8 gy);
static void monster_start_move(monster_t *m, dir_t dir);
static void monster_finish_move(monster_t *m, events_t *events);
static void monster_step_pixel(monster_t *m, events_t *events);
static u8 monster_any_sarcophagus(u8 screen);
static dir_t monster_random_dir(void);

/* Clear the current screen of monsters */
void monmap_clear_all(void) {

	cpct_memset(g_monmap, 0, MONMAP_BYTES);
}

u8 monmap_get(u8 gx, u8 gy) {

	u16 t;
	u8 byte, shift;

	if (gx >= SCREEN_U_W || gy >= 9)
		return MON_NONE;

	t = gy * SCREEN_U_W + gx;
	byte = g_monmap[t >> 2];
	shift = (t & 3) * 2;

	return (byte >> shift) & 3;
}

void monmap_set(u8 gx, u8 gy, u8 type) {

	u16 t;
	u8 idx, shift, mask;

	if (gx >= SCREEN_U_W || gy >= 9)
		return;
	t = gy * SCREEN_U_W + gx;
	idx = t >> 2;
	shift = (t & 3) * 2;

	mask = ~(3 << shift);
	g_monmap[idx] = (g_monmap[idx] & mask) | ((type & 3) << shift);
}

/* Initialise all monsters! */
void monster_init_all(void) {

	monmap_clear_all();

	for (u8 i = 0; i < MAX_MONSTERS; i++) {

		monster_t *m = &g_monsters[i];
		m->active = 0;
		m->type = MON_NONE;

		m->screen = 0;
		m->grid_x = m->grid_y = 0;
		m->byte_x = m->byte_y = 0;

		m->step_bx = m->step_by = 0;
		m->step_left = 0;

		m->dir = DIR_SOUTH;

		m->anim_frame = 0;
		m->anim_counter = 0;

		m->speed_delay = 0;
		m->delay_count = 0;

		m->despawn_timer = 0;
		m->v_pos = 0;
		m->hp = 0;
	}

	/* Spawn timers start maxed so no instant spawns */
	g_bat_spawn_timer = 50;
	g_zombie_spawn_timer = 150;
	g_ghost_spawn_timer = 200;
}

/* Monster spawning */
monster_t *monster_spawn(u8 type, u8 screen, u8 gx, u8 gy) {

	monster_t *m;
	u16 idx = utils_get_screen_x_y(screen, gx, gy);
	u8 fg = g_level_fg[idx];
	u8 bg = g_screen_bg[gy * SCREEN_U_W + gx];

	/* Validate coordinates */
	if (gx >= SCREEN_U_W || gy >= 9)
		return 0;

	/* Cannot spawn on player */
	if (screen == g_player.screen && gx == (u8)g_player.grid_x &&
		gy == (u8)g_player.grid_y)
		return 0;

	/* Cannot spawn onto monster */
	if (monmap_get(gx, gy) != MON_NONE)
		return 0;

	/* Spawn rules */
	switch (type) {

	case MON_BAT:
		if (!(IS_JAR(fg)))
			return 0;
		break;

	case MON_ZOMBIE:
		if (!IS_WALKABLE(bg))
			return 0;
		if (fg != 0)
			return 0;
		break;

	case MON_GHOST:
		break;

	default:
		return 0;
	}

	/* Find free slot */
	m = 0;
	for (u8 i = 0; i < MAX_MONSTERS; i++) {
		if (!g_monsters[i].active) {
			m = &g_monsters[i];
			break;
		}
	}
	if (!m)
		return 0;

	/* Bat spawns destroy jar */
	if (type == MON_BAT) {

		g_level_fg[idx] = 0;
		video_mark_dirty_tile(gx, gy);
	}

	/* Initialise monster */
	m->active = 1;
	m->type = type;
	m->screen = screen;

	m->grid_x = gx;
	m->grid_y = gy;
	m->byte_x = gx << 2;
	m->byte_y = gy << 4;

	m->step_left = 0;
	m->step_bx = m->step_by = 0;

	m->dir = DIR_SOUTH;

	m->anim_frame = 0;
	m->anim_counter = 0;

	m->hp = monster_base_hp[m->type];

	/* Speed settings */
	if (type == MON_BAT)
		m->speed_delay = 30;
	else if (type == MON_ZOMBIE)
		m->speed_delay = 80;
	else
		m->speed_delay = 20;

	m->delay_count = m->speed_delay;
	m->despawn_timer = 0;

	m->v_pos = cpct_getScreenPtr(CPCT_VMEM_START, GAME_WINDOW_X + m->byte_x,
		GAME_WINDOW_Y + m->byte_y);

	monmap_set(gx, gy, type);

	sfx_stop();
	sfx_start((void *)sfx_spawn);

	return m;
}

void monster_update_spawn_timers(void) {

	if (g_bat_spawn_timer)
		g_bat_spawn_timer--;
	if (g_zombie_spawn_timer)
		g_zombie_spawn_timer--;
	if (g_ghost_spawn_timer)
		g_ghost_spawn_timer--;
}

void monster_try_spawns(void) {

	u8 screen = g_player.screen;

	if (g_bat_spawn_timer == 0) {
		monster_try_spawn_bat(screen);
		g_bat_spawn_timer = BAT_SPAWN_INTERVAL;
	}

	if (g_zombie_spawn_timer == 0) {
		monster_try_spawn_zombie(screen);
		g_zombie_spawn_timer = ZOMBIE_SPAWN_INTERVAL;
	}

	if (g_ghost_spawn_timer == 0) {
		monster_try_spawn_ghost(screen);
		g_ghost_spawn_timer = GHOST_SPAWN_INTERVAL;
	}
}

void monster_try_spawn_bat(u8 screen) {

	u8 count = 0;
	u8 choice;
	u8 gx, gy;

	/* First count eligible jars */
	for (gy = 0; gy < 9; gy++)
		for (gx = 0; gx < 16; gx++) {
			u8 fg = g_level_fg[utils_get_screen_x_y(
				screen, gx, gy)];

			if (!(IS_JAR(fg)))
				continue;
			if (monmap_get(gx, gy) != MON_NONE)
				continue;
			if (gx == (u8)g_player.grid_x &&
				gy == (u8)g_player.grid_y)
				continue;

			count++;
		}

	if (!count)
		return;

	/* Pick a random jar index uniformly */
	choice = cpct_getRandom_lcg_u8(0);
	while (choice >= count)
		choice -= count;

	/* Second pass: find the chosen jar */
	for (gy = 0; gy < 9; gy++)
		for (gx = 0; gx < 16; gx++) {
			u8 fg = g_level_fg[utils_get_screen_x_y(
				screen, gx, gy)];

			if (!(IS_JAR(fg)))
				continue;
			if (monmap_get(gx, gy) != MON_NONE)
				continue;
			if (gx == (u8)g_player.grid_x &&
				gy == (u8)g_player.grid_y)
				continue;

			if (choice-- == 0) {
				monster_spawn(MON_BAT, screen, gx, gy);
				return;
			}
		}
}

void monster_try_spawn_zombie(u8 screen) {

	static const i8 dxs[4] = {0, 0, 1, -1};
	static const i8 dys[4] = {-1, 1, 0, 0};

	if (!monster_any_sarcophagus(screen))
		return;

	for (u8 gy = 0; gy < 9; gy++)
		for (u8 gx = 0; gx < 16; gx++) {

			u8 fg = g_level_fg[utils_get_screen_x_y(
				screen, gx, gy)];

			if (!IS_SARCOGRAPHUS(fg))
				continue;

			for (u8 i = 0; i < 4; i++) {

				u8 sx = gx + dxs[i];
				u8 sy = gy + dys[i];
				u8 bg;

				if (sx >= 16 || sy >= 9)
					continue;

				bg = g_screen_bg[sy * 16 + sx];
				if (!IS_WALKABLE(bg))
					continue;

				if (monmap_get(sx, sy) != MON_NONE)
					continue;

				if (sx == (u8)g_player.grid_x &&
					sy == (u8)g_player.grid_y)
					continue;

				if (monster_spawn(MON_ZOMBIE, screen, sx, sy))
					return;
			}
		}
}

void monster_try_spawn_ghost(u8 screen) {

	if (!monster_any_sarcophagus(screen))
		return;

	u8 attempts = 20;
	while (attempts--) {

		u8 gx = cpct_getRandom_lcg_u8(0) & 15;
		u8 gy = utils_rand_0_8();

		if (gx == (u8)g_player.grid_x && gy == (u8)g_player.grid_y)
			continue;

		if (monmap_get(gx, gy) != MON_NONE)
			continue;

		if (monster_spawn(MON_GHOST, screen, gx, gy))
			return;
	}
}

void monster_tick_animation(void) {

	for (u8 i = 0; i < MAX_MONSTERS; i++) {

		monster_t *m = &g_monsters[i];
		if (!m->active)
			continue;

		if (m->type == MON_BAT)
			continue;

		if (++m->anim_counter >= 8) {
			m->anim_counter = 0;

			if (++m->anim_frame == 3)
				m->anim_frame = 0;
		}
	}
}

static dir_t monster_pick_move_dir(monster_t *m) {

	i8 dx = (i8)g_player.grid_x - (i8)m->grid_x;
	i8 dy = (i8)g_player.grid_y - (i8)m->grid_y;

	if (utils_abs(dx) > utils_abs(dy))
		return (dx > 0) ? DIR_EAST : DIR_WEST;

	return (dy > 0) ? DIR_SOUTH : DIR_NORTH;
}

static bool monster_can_enter_tile(monster_t *m, u8 gx, u8 gy) {

	if (gx >= SCREEN_U_W || gy >= 9)
		return false;

	if (monmap_get(gx, gy) != MON_NONE)
		return false;

	u16 idx = utils_get_screen_x_y(m->screen, gx, gy);
	u8 fg = g_level_fg[idx];
	u8 bg = g_screen_bg[gy * SCREEN_U_W + gx];

	switch (m->type) {

	case MON_GHOST:
		return true;

	case MON_BAT:
		if (!IS_WALKABLE(bg))
			return false;
		if (IS_DOOR(fg))
			return false;
		return true;

	case MON_ZOMBIE:
		if (!IS_WALKABLE(bg))
			return false;
		if (fg != 0 && !IS_WALKABLE_FG(fg))
			return false;
		return true;
	}

	return false;
}

static void monster_start_move(monster_t *m, dir_t dir) {

	i8 dx, dy;

	m->dir = dir;

	utils_get_delta(dir, &dx, &dy);

	m->step_left = 2;
	m->step_bx = (dx < 0) ? -2 : (dx > 0 ? 2 : 0);
	m->step_by = (dy < 0) ? -8 : (dy > 0 ? 8 : 0);

	m->anim_frame++;
	if (m->anim_frame == 3)
		m->anim_frame = 0;
}

static void monster_finish_move(monster_t *m, events_t *events) {

	i8 dx = (m->step_bx > 0) ? 1 : (m->step_bx < 0 ? -1 : 0);
	i8 dy = (m->step_by > 0) ? 1 : (m->step_by < 0 ? -1 : 0);

	u8 old_x = m->grid_x;
	u8 old_y = m->grid_y;

	m->grid_x += dx;
	m->grid_y += dy;
	m->byte_x = m->grid_x << 2;
	m->byte_y = m->grid_y << 4;

	m->v_pos = cpct_getScreenPtr(CPCT_VMEM_START, GAME_WINDOW_X + m->byte_x,
		GAME_WINDOW_Y + m->byte_y);

	monmap_set(old_x, old_y, MON_NONE);
	monmap_set(m->grid_x, m->grid_y, m->type);

	/* Dirty tiles if visible */
	if (m->screen == g_player.screen) {

		video_mark_dirty_tile(old_x, old_y);
		video_mark_dirty_tile(m->grid_x, m->grid_y);

		events->dirtied_tiles = true;
	}
}

static void monster_step_pixel(monster_t *m, events_t *events) {

	if (!m->active || m->step_left == 0)
		return;

	m->byte_x += m->step_bx;
	m->byte_y += m->step_by;

	m->v_pos = cpct_getScreenPtr(CPCT_VMEM_START, GAME_WINDOW_X + m->byte_x,
		GAME_WINDOW_Y + m->byte_y);

	if (--m->step_left == 0)
		monster_finish_move(m, events);
}

void monster_step_all_pixels(events_t *events) {

	for (u8 i = 0; i < MAX_MONSTERS; i++) {

		if (g_monsters[i].active)
			monster_step_pixel(&g_monsters[i], events);
	}
}

void monster_update_moves(void) {

	for (u8 i = 0; i < MAX_MONSTERS; i++) {

		dir_t dir;
		monster_t *m = &g_monsters[i];
		i8 dx, dy;
		u8 nx, ny;

		if (!m->active)
			continue;

		/* Despawn logic if not on same screen */
		if (m->screen != g_player.screen) {

			if (++m->despawn_timer > 180) {
				monmap_set(m->grid_x, m->grid_y, MON_NONE);
				m->active = 0;
			}
			continue;
		}

		m->despawn_timer = 0;

		/* Still walking? */
		if (m->step_left > 0)
			continue;

		/* Delay between steps */
		if (m->delay_count > 0) {
			m->delay_count--;
			continue;
		}

		m->delay_count = m->speed_delay;

		/* Primary movement direction: chase player */
		dir = monster_pick_move_dir(m);

		utils_get_delta(dir, &dx, &dy);
		nx = m->grid_x + dx;
		ny = m->grid_y + dy;

		/* Try primary move */
		if (!monster_can_enter_tile(m, nx, ny)) {

			/* Fallback only for bats and zombies */
			if (m->type == MON_BAT || m->type == MON_ZOMBIE) {

				for (u8 tries = 0; tries < 4; tries++) {

					/* Random direction */
					dir = (dir_t)(cpct_getRandom_lcg_u8(0) &
						      3);

					utils_get_delta(dir, &dx, &dy);
					nx = m->grid_x + dx;
					ny = m->grid_y + dy;

					if (monster_can_enter_tile(m, nx, ny)) {
						monster_start_move(m, dir);
						goto did_move;
					}
				}
			}

			/* cannot move */
			continue;
		}

		/* direct path is valid */
		monster_start_move(m, dir);

	did_move:;
	}
}

void monster_player_collisions(events_t *events) {

	for (u8 i = 0; i < MAX_MONSTERS; i++) {

		monster_t *m = &g_monsters[i];
		if (!m->active)
			continue;

		if (m->screen != g_player.screen)
			continue;

		if (m->grid_x == (u8)g_player.grid_x &&
			m->grid_y == (u8)g_player.grid_y) {

			if (m->type == MON_BAT)
				game_take_damage(100);
			else if (m->type == MON_ZOMBIE)
				game_take_damage(200);
			else if (m->type == MON_GHOST)
				game_take_damage(300);
			game_update_health_string();
			events->health_updated = true;
			events->redraw_hud = true;

			monmap_set(m->grid_x, m->grid_y, MON_NONE);
			m->active = 0;

			video_mark_dirty_tile(m->grid_x, m->grid_y);

			video_flash_border(TRIPLET_RED);
		}
	}
}

monster_t *monster_find_at(u8 screen, u8 gx, u8 gy) {

	for (u8 i = 0; i < MAX_MONSTERS; i++) {

		monster_t *m = &g_monsters[i];
		if (!m->active)
			continue;
		if (m->screen == screen && m->grid_x == gx && m->grid_y == gy)
			return m;
	}

	return 0;
}

void monster_kill(monster_t *m, events_t *events) {

	if (!m || !m->active)
		return;

	monmap_set(m->grid_x, m->grid_y, MON_NONE);

	video_mark_dirty_tile(m->grid_x, m->grid_y);
	events->dirtied_tiles = true;

	g_game.score += 250;
	m->active = 0;

	sfx_stop();
	sfx_start((void *)sfx_splat);
}

static u8 monster_any_sarcophagus(u8 screen) {

	for (u8 gy = 0; gy < SCREEN_U_H; gy++)
		for (u8 gx = 0; gx < SCREEN_U_W; gx++) {

			u8 fg = g_level_fg[utils_get_screen_x_y(
				screen, gx, gy)];
			if (IS_SARCOGRAPHUS(fg))
				return true;
		}

	return false;
}

static dir_t monster_random_dir(void) {

	return (dir_t)(cpct_getRandom_lcg_u8(0) & 3);
}

void monster_take_damage(monster_t *m, u8 dmg, events_t *events) {

	if (m->hp > dmg)
		m->hp -= dmg;
	else {
		m->hp = 0;
		monster_kill(m, events);
	}
}
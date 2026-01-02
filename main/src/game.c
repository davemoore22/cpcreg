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

#include "game.h"

/* Keyboard Controls */
cpct_keyID g_controls[CONTROLS_SZ];

/* Hi-Score Table */
score_t g_hiscores[HISCORES_SZ];

/* Game Options */
u8 g_options;

/* Interrupt Indexes and Counters */
u8 g_int_idx = 0;
u8 g_frame_c = 0;

/* Player */
player_t g_player;

/* Game */
game_t g_game;

/* Bullet */
bullet_t g_bullet;

static const u8 (*g_palette)[4];

bool g_sprite_flipped = false;
bool g_completed = false;

/* Working screens are all in firmware area once it has been disabled */

/* Private Functions */
static void game_draw_all(void);
static void game_reset_game(void);
static void game_update_hud_strings(void);
static void game_reset_player(
	const u8 screen, const dir_t dir, const u8 grid_x, const u8 grid_y);
static void game_read_input(input_t *input);
static bool game_get_dir(const input_t *input, dir_t *out_dir);
static void game_do_player(const input_t *input, events_t *events);
static void game_try_player_move(dir_t dir, events_t *events);
static void game_do_player_move(i8 dx, i8 dy, dir_t dir, events_t *events);
static void game_smash_sarcophagus(const i8 dx, const i8 dy);
static bool game_play_level(void);
static void game_load_level(void);
static bool game_can_move_screen(const dir_t dir);
static bool game_check_move_screen(
	const dir_t new_dir, const i8 dx, const i8 dy);
static inline void game_get_new_screen_pos(dir_t dir, i8 *gx, i8 *gy);
static bool game_try_move_screen(dir_t dir, events_t *events);
static void game_show_hint(const u8 idx);
static void game_interrupt(void);
static void game_reset_timers(void);
static void game_open_door(const i8 dx, const i8 dy);
static void game_step_player_pixel(events_t *events);
static void game_fire_bullet(void);
static void game_step_bullet(events_t *events);
static bool game_bullet_check_collision(events_t *events);
static void game_open_horizontal_door(u8 x, u8 y);
static void game_open_vertical_door(u8 x, u8 y);
static bool game_handle_tile_on_entry(
	u8 gx, u8 gy, i8 dx, i8 dy, events_t *events);
static bool game_check_landing_tile(u8 fg, u8 bg);
static void game_load_bg_for_screen(u8 screen_id);
static inline u16 game_get_screen_xy(u8 x, u8 y);
static void game_use_holy_water_bomb(events_t *events);
static void game_smash_all_sarcophagi_on_screen(u8 screen);
static void game_destroy_all_jars_on_screen(u8 screen, events_t *events);
static void game_update_artifact_string(void);
static void game_update_bomb_string(void);
static void game_update_keys_string(void);
static void game_do_pause(void);
inline void game_maybe_hint(u8 h);
static void game_draw_pause(void);
static void game_undraw_pause(void);

static inline u16 game_get_screen_xy(u8 x, u8 y) {

	return (y << 4) + x;
}

/* Set up Game */
void game_setup(void) {

	g_options = OPT_CHARACTER | OPT_TEXT | OPT_SFX;

	/* Default Keyboard Controls */
	g_controls[KEY_UP] = Key_Q;
	g_controls[KEY_DOWN] = Key_A;
	g_controls[KEY_LEFT] = Key_O;
	g_controls[KEY_RIGHT] = Key_P;
	g_controls[KEY_PAUSE] = Key_Control;
	g_controls[KEY_SHOOT] = Key_Space;
	g_controls[KEY_BOMB] = Key_B;
	g_controls[JOY_UP] = Joy0_Up;
	g_controls[JOY_DOWN] = Joy0_Down;
	g_controls[JOY_LEFT] = Joy0_Left;
	g_controls[JOY_RIGHT] = Joy0_Right;
	g_controls[JOY_SHOOT] = Joy0_Fire1;
	g_controls[JOY_BOMB] = Joy0_Fire2;

	/* Populate Hi-Score table */
	entry_insert("dsm", 10000, 0);
	entry_insert("waz", 100, 1);
	entry_insert("chn", 50, 2);
	entry_insert("lfb", 40, 3);
	entry_insert("osr", 30, 4);
	entry_insert("dad", 20, 5);
	entry_insert("psb", 10, 6);
}

u32 game_start(void) {

	const u8 MAX_LEVEL = 6;
	bool game_over = false;
	bool lvl_complete;

	game_reset_game();

	while (!game_over) {

		/* Between Screen */
		between_start();
		between_stop();

		video_full_clear();

		/* Load the Level */
		game_load_level();

		/* Setup Interrupts and Clock */
		game_reset_timers();
		utils_reset_clock();
		g_clock_on = true;

		/* Play Level */
		lvl_complete = game_play_level();

		/* Stop clock every loop */
		g_clock_on = false;

		/* Level Success */
		if (lvl_complete) {

			welldone_start();
			welldone_stop();

			video_full_clear();

			u8 next = g_game.level + 1;

			if (next > MAX_LEVEL) {

				/* No more level go to end game for now */
				victory_start();
				victory_stop();

				game_over = true;
			} else {

				/* Advance to next level */
				g_game.level = next;
			}

			continue;
		}

		/* Level Failed */
		game_stop();

		defeat_start();
		defeat_stop();

		/* If cheating, don't allow hiscores */
		if (g_game.score >= g_hiscores[HISCORES_SZ - 1].score) {
			if (!(g_options & OPT_CHEAT)) {
				entry_start();
				entry_stop();
			}
		}

		game_over = true;
	}

	return g_game.score;
}

/* Stop Game */
void game_stop(void) {

	video_wipe_screen(true);
	video_blank_screen();
	video_clear_screen();
}

/* Reset Interrupt Timers */
void game_reset_timers(void) {

	g_int_idx = 0;
	g_frame_c = 0;
}

/* Interrupt for Main Game */
void game_interrupt(void) {

	static const u8 palette_mn[4] = {
		HW_BLACK,
		HW_SKY_BLUE,
		HW_PASTEL_MAGENTA,
		HW_BRIGHT_WHITE,
	};

	if (g_int_idx == 0) {
		if (++g_frame_c == FC_MAX)
			g_frame_c = 0;
	}

	if (g_int_idx == 1)
		cpct_scanKeyboard_if();

	if (g_int_idx == 4)
		utils_wait(54);

	if (g_int_idx == 2 && (g_options & OPT_SFX))
		sfx_update();

	if (g_options & OPT_GREEN_SCREEN)
		cpct_setPalette(palette_mn, sizeof(palette_mn));
	else
		cpct_setPalette(g_palette[g_int_idx], 4);

	if (++g_int_idx == 6)
		g_int_idx = 0;

	/* Call the real time clock whilst in game */
	utils_clock_interrupt();
}

/* Note this does not load the GUI from disk - use v_draw_GUI() for that */
static void game_draw_all(void) {

	video_draw_HUD();
	video_draw_rect(0, 0, SCREEN_U_W, SCREEN_U_H);
	video_monster_draw_all();
	video_draw_player();
}

static void game_reset_game(void) {

	/* Initial values */
	g_game.level = 1; /* Starting level - not 0-indexed */
	g_game.score = 0;
	g_game.max_hp = 2000;
	g_game.health = g_game.max_hp;
	g_game.artifacts = 0;
	if (g_options & OPT_CHEAT) {
		g_game.bombs = 64;
		g_game.keys = 64;
	} else {
		g_game.bombs = 0;
		g_game.keys = 0;
	}

	/* Update string equivalents */
	game_update_hud_strings();

	/* Reset hints */
	bool options_text = g_options & OPT_TEXT;
	cpct_memset(g_game.hints, options_text, HINTS_SZ);

	/* Reset monsters */
	monster_init_all();
}

static void game_update_hud_strings(void) {

	game_update_artifact_string();
	game_update_health_string();
	game_update_bomb_string();
	game_update_keys_string();
}

static void game_update_artifact_string(void) {

	utils_itoa_2(g_game.artifacts_str, g_game.artifacts);
}

static void game_update_bomb_string(void) {

	utils_itoa_2(g_game.bombs_str, g_game.bombs);
}

void game_update_health_string(void) {

	utils_itoa_4(g_game.health_str, g_game.health);
}

static void game_update_keys_string(void) {

	utils_itoa_2(g_game.keys_str, g_game.keys);
}

static void game_reset_player(
	const u8 screen, const dir_t dir, const u8 grid_x, const u8 grid_y) {

	/* Set game screen */
	g_player.screen = screen;

	/* Logical tile position */
	g_player.grid_x = grid_x;
	g_player.grid_y = grid_y;

	/* Byte position relative to GAME_WINDOW (aligned to tile) */
	g_player.byte_x = grid_x << 2; /* 4 bytes per 16px tile */
	g_player.byte_y = grid_y << 4; /* 16 bytes per 16px tile */

	/* Orientation & animation */
	g_player.dir = dir;
	g_player.frame = 0;
	g_player.facing_right = (g_sprite_flipped ? false : true);
	// game_update_player_facing(dir);

	/* No movement in progress */
	g_player.moving = false;
	g_player.step_left = 0;
	g_player.step_bx = 0;
	g_player.step_by = 0;

	/* Compute v_pos from byte coords */
	g_player.v_pos = cpct_getScreenPtr(CPCT_VMEM_START,
		GAME_WINDOW_X + g_player.byte_x,
		GAME_WINDOW_Y + g_player.byte_y);

	/* 0 = N, 3 = S, 6 = E, W = 6 (since West are flipepd East frames) */
	static const u8 dir_to_start_frame[4] = {0, 3, 6, 6};
	g_player.s_idx = dir_to_start_frame[g_player.dir] + g_player.frame;
}

static void game_read_input(input_t *input) {

	input->up = cpct_isKeyPressed(g_controls[KEY_UP]) ||
		    cpct_isKeyPressed(g_controls[JOY_UP]);
	input->down = cpct_isKeyPressed(g_controls[KEY_DOWN]) ||
		      cpct_isKeyPressed(g_controls[JOY_DOWN]);
	input->left = cpct_isKeyPressed(g_controls[KEY_LEFT]) ||
		      cpct_isKeyPressed(g_controls[JOY_LEFT]);
	input->right = cpct_isKeyPressed(g_controls[KEY_RIGHT]) ||
		       cpct_isKeyPressed(g_controls[JOY_RIGHT]);
	input->fire = cpct_isKeyPressed(g_controls[KEY_SHOOT]) ||
		      cpct_isKeyPressed(g_controls[JOY_SHOOT]);
	input->bomb = cpct_isKeyPressed(g_controls[KEY_BOMB]);

	input->pause = cpct_isKeyPressed(g_controls[KEY_PAUSE]);
	input->quit = cpct_isKeyPressed(Key_Esc);
	input->skip = cpct_isKeyPressed(Key_Tab);
}

static bool game_get_dir(const input_t *input, dir_t *out_dir) {

	if (input->left) {
		*out_dir = DIR_WEST;
		return true;
	}
	if (input->right) {
		*out_dir = DIR_EAST;
		return true;
	}
	if (input->up) {
		*out_dir = DIR_NORTH;
		return true;
	}
	if (input->down) {
		*out_dir = DIR_SOUTH;
		return true;
	}
	return false;
}

/* Handle player and their interactions (again ChatGPT was helpful here) */
static void game_do_player(const input_t *input, events_t *events) {

	dir_t dir;

	if (g_player.move_cooldown > 0) {
		g_player.move_cooldown--;
		return; /* Block new movement until cooldown expires */
	}

	/* If already moving, continue tween, but still allow fire */
	if (g_player.moving) {
		game_step_player_pixel(events);

		if (input->fire && !g_bullet.active)
			game_fire_bullet();

		if (input->bomb)
			game_use_holy_water_bomb(events);

		return;
	}

	/* Fire works even when standing still */
	if (input->fire && !g_bullet.active) {
		game_fire_bullet();
	}

	if (input->bomb) {
		game_use_holy_water_bomb(events);
	}

	/* Now process movement */
	if (!game_get_dir(input, &dir))
		return;

	game_try_player_move(dir, events);

	if (g_player.moving)
		game_step_player_pixel(events);
}

/* Note, tweening is a right sod to get right, I had to use ChatGPT here */
static void game_try_player_move(dir_t dir, events_t *events) {

	i8 dx, dy;
	utils_get_delta(dir, &dx, &dy);

	u8 new_gx, new_gy;
	new_gx = g_player.grid_x + dx;
	new_gy = g_player.grid_y + dy;

	/* Always rotate, even if otherwise blocked  */
	if (g_player.dir != dir) {
		g_player.dir = dir;
		g_player.frame = 0;
		events->rotated = true;
		game_update_player_facing(dir);
	}

	/* 1. Check for screen transition */
	bool can_transition;
	can_transition = game_can_move_screen(dir);

	if (can_transition) {

		/* This attempts transition; success returns true */
		if (game_try_move_screen(dir, events)) {
			return; /* screen moved successfully */
		}

		/*
		 * Transition *should* happen but was blocked (jar, grave,
		 * door without key)
		 *
		 * So do not move player, do not change grid coords
		 *
		 * We have already rotated, so we just stop here.
		 */
		g_player.moving = false;
		g_player.step_left = 0;
		g_player.step_bx = 0;
		g_player.step_by = 0;
		return;
	}

	/* 2 Check tile entry */
	if (!game_handle_tile_on_entry(new_gx, new_gy, dx, dy, events)) {

		/* We are blocked so ensure no leftover tweening continues */
		g_player.moving = false;
		g_player.step_left = 0;
		g_player.step_bx = 0;
		g_player.step_by = 0;

		return;
	}

	/*  3. Finally allow Movement */
	game_do_player_move(dx, dy, dir, events);
}

static void game_do_player_move(i8 dx, i8 dy, dir_t dir, events_t *events) {

	u8 target_byte_x;
	u8 target_byte_y;

	/* Save tile we are leaving before grid_x/grid_y are updated */
	g_player.last_grid_x = g_player.grid_x;
	g_player.last_grid_y = g_player.grid_y;

	/* Handle rotation and animation advance (unchanged) */
	if (g_player.dir != dir) {
		g_player.dir = dir;
		g_player.frame = 0;
		events->rotated = true;
		game_update_player_facing(dir);
	} else {
		if (++g_player.frame == 3)
			g_player.frame = 0;
	}

	/* Old grid position already used in checks before we get here */
	g_player.grid_x += dx;
	g_player.grid_y += dy;

	/* Target byte coordinates for the new tile */
	target_byte_x = g_player.grid_x << 2; /* 4 bytes/tile */
	target_byte_y = g_player.grid_y << 4; /* 16 bytes/tile */

	/* Starting byte position, if not moving, this is aligned to old tile */

	/*
	 * Compute per-frame byte deltas:
	 * - 16px horizontally  = 4 bytes: we do it in 2 steps => 2 bytes/step
	 * - 16px vertically    = 16 bytes: we do it in 2 steps => 8 byte/step
	 */
	g_player.step_bx = 0;
	g_player.step_by = 0;
	g_player.step_left = 2; /* 2 frames of tween = half-tile steps */
	g_player.moving = true;

	/* Movement cooldown (slows movement) */
	g_player.move_cooldown = 1;

	if (dx < 0)
		g_player.step_bx = -1;
	else if (dx > 0)
		g_player.step_bx = +1;

	if (dy < 0)
		g_player.step_by = -4;
	else if (dy > 0)
		g_player.step_by = +4;

	/* Movement event (logical move has happened) */
	events->moved = true;

	sfx_stop();
	sfx_start((void *)sfx_footstep);
}

/* Main game loop (input → simulate → render) */
static bool game_play_level(void) {

	u16 status = 0;
	input_t input;
	events_t events;
	render_t rq;

	/* Reset player */
	if (g_game.level == 1) {
		game_reset_player(0, DIR_EAST, 5, 7);
		game_load_bg_for_screen(0);
	} else if (g_game.level == 2) {
		game_reset_player(9, DIR_EAST, 2, 7);
		game_load_bg_for_screen(9);
	} else if (g_game.level == 3) {
		game_reset_player(10, DIR_EAST, 4, 5);
		game_load_bg_for_screen(10);
	} else if (g_game.level == 4) {
		game_reset_player(2, DIR_EAST, 7, 3);
		game_load_bg_for_screen(2);
	} else if (g_game.level == 5) {
		game_reset_player(0, DIR_EAST, 2, 3);
		game_load_bg_for_screen(0);
	} else if (g_game.level == 6) {
		game_reset_player(3, DIR_EAST, 10, 2);
		game_load_bg_for_screen(3);
	}

	g_completed = false;

	/* Load GUI from disk */
	video_draw_GUI();

	/* Initial draw while screen is blanked */
	video_clear_HUD();
	game_draw_all();

	/* Setup interrupts (makes screen visible) */
	cpct_waitVSYNCStart();
	cpct_setInterruptHandler(game_interrupt);

	if (g_options & OPT_CHARACTER)
		game_show_hint(HINT_GET_READY_REGINALD);
	else
		game_show_hint(HINT_GET_READY_REGINA);

	/* Main Game Loop */
	while (!(status & BIT_QUIT) && !(status & BIT_SUCCESS)) {

		/* Read controls */
		game_read_input(&input);

		/* Meta-input */
		if (input.pause)
			status |= BIT_PAUSE;
		if (input.quit)
			status |= BIT_QUIT;
		if (input.skip && g_options & OPT_CHEAT) {
			status |= BIT_SUCCESS;
			continue;
		}

		/* Pause */
		if (status & BIT_PAUSE) {
			cpct_setBorder(HW_WHITE);
			g_game.hints[PAUSE_HINT_IDX] = true;
			game_do_pause();
			cpct_setBorder(HW_BLACK);
			status &= ~BIT_PAUSE;
			continue;
		}

		/* Reset render queue and the events struct */
		rq = RQ_NONE;
		cpct_memset(&events, 0, sizeof(events_t));

		/* The simulation phase - where we do stuff! */

		/* Player movement & doors & firing */
		game_do_player(&input, &events);
		if (g_completed)
			status |= BIT_SUCCESS;

		/* Bullet movement */
		if (g_bullet.active)
			game_step_bullet(&events);

		/* Spawn logic */
		monster_update_spawn_timers();
		monster_try_spawns();
		monster_tick_animation();

		if (events.health_updated)
			game_update_health_string();

		if (events.level_complete)
			status |= BIT_SUCCESS;

		/*
		 * Urgh. This is the order we do this:
		 *
		 * 1) Decide movement
		 * 2) Perform pixel-tweening
		 * 3) Finalise tile positions
		 * 4) Apply collisions using final positions
		 */
		monster_update_moves(); /* Pick directions, start tweens */
		monster_step_all_pixels(&events);   /* Advance pixel movement */
		monster_player_collisions(&events); /* With updated grid_x/y */

		/* Now decide what to render (a fancy queue!) */
		if (events.moved_screen)
			rq |= RQ_SCREEN | RQ_PLAYER | RQ_ITEMS | RQ_HUD;
		else {

			if (events.moved || events.rotated)
				rq |= RQ_PLAYER;

			if (events.redraw_hud || events.picked_item)
				rq |= RQ_HUD;

			if (events.opened_door || events.destroyed_grave)
				rq |= RQ_ITEMS;

			if (events.dirtied_tiles)
				rq |= RQ_DIRTY;
		}

		/* Health check */
		if (!(g_options & OPT_CHEAT))
			if (g_game.health == 0) {
				status |= BIT_QUIT;
				continue;
			}

		/* Finally draw stuff! */
		cpct_waitVSYNC();

		/* Full-screen redraw */
		if (rq & RQ_SCREEN) {
			video_draw_rect(0, 0, SCREEN_U_W, SCREEN_U_H);
		}

		/* Dirty tiles */
		if (rq & RQ_DIRTY) {
			video_draw_dirty_tiles();
			video_clear_dirty_list();
		}

		/* Draw monsters once */
		video_monster_draw_all();

		/* Draw player */
		video_draw_player();

		/* HUD */
		if (rq & RQ_HUD)
			video_draw_HUD();

		/* Bullet */
		if (g_bullet.active)
			video_draw_bullet();
	}

	/* End of level */
	return (status & BIT_SUCCESS) != 0;
}

/* Screen transitions */
static bool game_can_move_screen(const dir_t dir) {
	i8 grid_dx, grid_dy;

	/* Get new direction and thus offset */
	utils_get_delta(dir, &grid_dx, &grid_dy);

	return game_check_move_screen(dir, grid_dx, grid_dy);
}

static bool game_check_move_screen(
	const dir_t new_dir, const i8 dx, const i8 dy) {

	i8 new_x = g_player.grid_x + dx;
	i8 new_y = g_player.grid_y + dy;

	/* Check we are on the edge of the screen, if not return */
	switch (new_dir) {
	case DIR_SOUTH:
		if (new_y < SCREEN_U_H)
			return false;
		break;
	case DIR_NORTH:
		if (new_y >= 0)
			return false;
		break;
	case DIR_WEST:
		if (new_x >= 0)
			return false;
		break;
	case DIR_EAST:
		if (new_x < SCREEN_U_W)
			return false;
		break;
	default:
		return false;
	}

	/* If we reach here, we have a screen move */
	return true;
}

static inline void game_get_new_screen_pos(dir_t dir, i8 *gx, i8 *gy) {

	switch (dir) {
	case DIR_NORTH:
		*gy = SCREEN_U_H - 1;
		break;
	case DIR_SOUTH:
		*gy = 0;
		break;
	case DIR_WEST:
		*gx = SCREEN_U_W - 1;
		break;
	case DIR_EAST:
		*gx = 0;
		break;
	default:
		break;
	}
}

/* This is another hideous complicated piece of code */
static bool game_try_move_screen(dir_t dir, events_t *events) {

	if (!game_can_move_screen(dir))
		return false;

	/* Clear any dirty tiles */
	video_clear_dirty_list();

	u8 new_screen = l_next_screen[g_game.level - 1][dir][g_player.screen];
	if (new_screen == NO_LINK)
		return false;

	i8 gx = g_player.grid_x;
	i8 gy = g_player.grid_y;
	game_get_new_screen_pos(dir, &gx, &gy);

	/* 1. Precheck the landing tile on target screen */

	/* Decompress the target screen's BG temporarily */
	cpct_zx7b_decrunch_s(g_temp_bg + g_temp_bg_sz - 1,
		level_bgs[g_game.level - 1][new_screen].data_end);

	u16 idx = utils_get_screen_x_y(new_screen, gx, gy);

	i8 fg = g_level_fg[idx];
	i8 bg = g_temp_bg[game_get_screen_xy(gx, gy)];

	if (!game_check_landing_tile(fg, bg))
		return false;

	/* 2. Apply transition */
	events->rotated = false; /* Don't flip player sprites on move screen */
	game_reset_player(new_screen, dir, gx, gy);
	game_load_bg_for_screen(new_screen);

	/* 3. Apply entry effects after moving */
	game_handle_tile_on_entry(gx, gy, 0, 0, events);

	/* Reset spawns */
	g_bat_spawn_timer = 16;
	g_zombie_spawn_timer = 128;
	g_ghost_spawn_timer = 255;

	events->moved_screen = true;
	return true;
}

static void game_draw_pause(void) {

	utils_clear_input();
	video_draw_hint(PAUSE_HINT_IDX);
}

static void game_undraw_pause(void) {

	video_draw_rect(0, 0, 16, 9);
	video_draw_player();
}

static void game_show_hint(const u8 idx) {

	bool kp = false;

	if (!g_game.hints[idx])
		return;

	utils_clear_input();

	video_draw_hint(idx);

	sfx_stop();
	sfx_start((void *)sfx_show_hint);

	utils_reset_clock();
	g_clock_on = true;

	/* Display for a number of seconds or until a keypress */
	while (g_clock.s < HINT_DURATION) {

		/* Check for a keypress */
		kp = cpct_isAnyKeyPressed();
	}

	/* Stop Clock */
	g_clock_on = false;

	/* And disable hint */
	g_game.hints[idx] = false;

	/* Redraw as needed */
	video_draw_rect(1, 1, HINT_FRAME_WIDTH, HINT_FRAME_HEIGHT + 2);
	video_draw_player();
}

/* Load Level */
static void game_load_level(void) {

	/* Clear working memory */
	cpct_memset(g_level_fg, FLOOR_GFX, g_level_fg_sz);

	/* Decompress level data */
	switch (g_game.level) {
	case 1:
		cpct_zx7b_decrunch_s(
			g_level_fg + g_level_fg_sz - 1, l_level_1_fg_end);
		g_palette = palette_level_1;
		break;
	case 2:
		cpct_zx7b_decrunch_s(
			g_level_fg + g_level_fg_sz - 1, l_level_2_fg_end);
		g_palette = palette_level_2;
		break;
	case 3:
		cpct_zx7b_decrunch_s(
			g_level_fg + g_level_fg_sz - 1, l_level_3_fg_end);
		g_palette = palette_level_3;
		break;
	case 4:
		cpct_zx7b_decrunch_s(
			g_level_fg + g_level_fg_sz - 1, l_level_4_fg_end);
		g_palette = palette_level_4;
		break;
	case 5:
		cpct_zx7b_decrunch_s(
			g_level_fg + g_level_fg_sz - 1, l_level_5_fg_end);
		g_palette = palette_level_5;
		break;
	case 6:
		cpct_zx7b_decrunch_s(
			g_level_fg + g_level_fg_sz - 1, l_level_6_fg_end);
		g_palette = palette_level_6;
		break;
	}
}

/* Open a door (i.e. remove it from the working map) */
static void game_open_door(const i8 dx, const i8 dy) {

	i8 new_x = g_player.grid_x + dx;
	i8 new_y = g_player.grid_y + dy;
	u16 index = utils_get_screen_x_y(g_player.screen, new_x, new_y);
	u8 tile = g_level_fg[index];

	/* Not a door tile → nothing to do */
	if (!IS_HDOOR(tile) && !IS_VDOOR(tile))
		return;

	if (IS_HDOOR(tile)) {
		game_open_horizontal_door(new_x, new_y);
		sfx_stop();
		sfx_start((void *)sfx_open_door);
		return;
	}

	if (IS_VDOOR(tile)) {
		game_open_vertical_door(new_x, new_y);
		sfx_stop();
		sfx_start((void *)sfx_open_door);
		return;
	}
}

static void game_smash_sarcophagus(const i8 dx, const i8 dy) {

	u8 gx = g_player.grid_x + dx;
	u8 gy = g_player.grid_y + dy;
	grave_t gi;
	u8 sx, sy;
	u16 sec_index;

	u16 index = utils_get_screen_x_y(g_player.screen, gx, gy);
	u8 tile = g_level_fg[index];

	if (gx >= SCREEN_U_W || gy >= SCREEN_U_H)
		return;

	/* Only handle sarcophagus tiles */
	if (!IS_SARCOGRAPHUS(tile))
		return;

	/* Lookup: dx,dy,partner for each sarcophagus tile */
	static const grave_t grave_lookup[64] = {
		[SARC_1_TOP - 32] = {0, 1, SARC_1_BOTTOM},
		[SARC_1_BOTTOM - 32] = {0, -1, SARC_1_TOP},
		[SARC_2_LEFT - 32] = {1, 0, SARC_2_RIGHT},
		[SARC_2_RIGHT - 32] = {-1, 0, SARC_2_LEFT},
		[SARC_3_TOP - 32] = {0, 1, SARC_3_BOTTOM},
		[SARC_3_BOTTOM - 32] = {0, -1, SARC_3_TOP},
	};
	gi.dx = grave_lookup[tile - 32].dx;
	gi.dy = grave_lookup[tile - 32].dy;
	gi.partner = grave_lookup[tile - 32].partner;

	/* Safety check, treat zeroed entry as invalid */
	if (gi.dx == 0 && gi.dy == 0)
		return;

	/* Smash primary tile */
	g_level_fg[index] = tile + 2;

	/* Partner tile coordinates */
	sx = gx + gi.dx;
	sy = gy + gi.dy;

	if (sx >= SCREEN_U_W || sy >= SCREEN_U_H)
		return;

	sec_index = utils_get_screen_x_y(g_player.screen, sx, sy);

	/* Smash partner */
	g_level_fg[sec_index] = gi.partner + 2;

	/* Mark tiles dirty */
	video_mark_dirty_tile(gx, gy);
	video_mark_dirty_tile(sx, sy);
}

/* Step current tweening movement by one frame (8px) */
static void game_step_player_pixel(events_t *events) {

	u8 old_byte_x = g_player.byte_x;
	u8 old_byte_y = g_player.byte_y;

	if (!g_player.moving || g_player.step_left == 0)
		return;

	/* Mark the old tile dirty (note this is tile aligned) */
	u8 gx = g_player.last_grid_x;
	u8 gy = g_player.last_grid_y;

	video_mark_dirty_tile(gx, gy);

	events->dirtied_tiles = true;

	/* Apply byte movemenT */
	g_player.byte_x += g_player.step_bx;
	g_player.byte_y += g_player.step_by;

	--g_player.step_left;

	if (g_player.step_left == 0) {

		/* Tween finished: snap to tile position */
		g_player.byte_x = g_player.grid_x << 2;
		g_player.byte_y = g_player.grid_y << 4;
		g_player.moving = false;

		/* Update "last tile" for next movement */
		g_player.last_grid_x = g_player.grid_x;
		g_player.last_grid_y = g_player.grid_y;
	}

	/* Update player v_pos from byte coords */
	g_player.v_pos = cpct_getScreenPtr(CPCT_VMEM_START,
		GAME_WINDOW_X + g_player.byte_x,
		GAME_WINDOW_Y + g_player.byte_y);

	/* Mark new tile dirty (again, tile-aligned) */
	{
		u8 gx = g_player.grid_x;
		u8 gy = g_player.grid_y;

		video_mark_dirty_tile(gx, gy);
	}

	/* Work out new sprite frames */
	static const u8 dir_to_start_frame[4] = {0, 3, 6, 6};

	/* 0 = N, 3 = S, 6 = E, W = 6 (since West are flipepd East frames) */
	g_player.s_idx = dir_to_start_frame[g_player.dir] + g_player.frame;

	events->moved = true;
}

static void game_fire_bullet(void) {

	g_bullet.active = true;
	g_bullet.screen = g_player.screen;
	g_bullet.dir = g_player.dir;
	g_bullet.grid_x = g_player.grid_x;
	g_bullet.grid_y = g_player.grid_y;
	g_bullet.byte_x = g_player.byte_x;
	g_bullet.byte_y = g_player.byte_y;

	// Apply bullet offset only if NOT on the screen edge
	// if (g_player.dir == DIR_EAST) {
	//	if (g_player.grid_x <
	//		SCREEN_U_W - 1) // ensure not rightmost tile
	//		g_bullet.byte_x += 1;
	//} else if (g_player.dir == DIR_WEST) {
	////	if (g_player.grid_x > 0) // ensure not leftmost tile
	//		g_bullet.byte_x -= 1;
	//}

	g_bullet.last_grid_x = g_bullet.grid_x;
	g_bullet.last_grid_y = g_bullet.grid_y;

	g_bullet.step_left = 2;

	/* Optimised out a switch here */
	static const i8 bullet_step_x[4] = {0, 0, 2, -2};
	static const i8 bullet_step_y[4] = {-8, 8, 0, 0};
	g_bullet.step_bx = bullet_step_x[g_player.dir];
	g_bullet.step_by = bullet_step_y[g_player.dir];

	/* Bullet moves every frame */
	g_bullet.speed_delay = 0;
	g_bullet.delay_counter = g_bullet.speed_delay;

	g_bullet.v_pos = cpct_getScreenPtr(CPCT_VMEM_START,
		GAME_WINDOW_X + g_bullet.byte_x,
		GAME_WINDOW_Y + g_bullet.byte_y);

	sfx_stop();
	sfx_start((void *)sfx_shoot);
}

/* Again, needed ChatGPT here to iron out so many bugs */
static void game_step_bullet(events_t *events) {

	i16 next_bx, next_by;
	u16 max_bx, max_by;
	i16 screen_bx, screen_by;
	i16 min_x, min_y, max_x, max_y;

	if (!g_bullet.active)
		return;

	/* Mark old tile dirty (unless its the player tile)  */
	u8 lx = g_bullet.last_grid_x;
	u8 ly = g_bullet.last_grid_y;

	video_mark_dirty_tile(lx, ly);
	events->dirtied_tiles = true;

	/* Speed control for bullet */
	if (g_bullet.delay_counter > 0) {
		g_bullet.delay_counter--;
		return;
	}
	g_bullet.delay_counter = g_bullet.speed_delay;

	/* Compute pixel-level next position  */
	next_bx = g_bullet.byte_x + g_bullet.step_bx;
	next_by = g_bullet.byte_y + g_bullet.step_by;

	max_bx = (SCREEN_U_W << 2) - 16;
	max_by = (SCREEN_U_H << 4) - 16;

	screen_bx = GAME_WINDOW_X + next_bx;
	screen_by = GAME_WINDOW_Y + next_by;

	min_x = GAME_WINDOW_X;
	max_x = GAME_WINDOW_X + ((SCREEN_U_W << 2) - 4);
	min_y = GAME_WINDOW_Y;
	max_y = GAME_WINDOW_Y + ((SCREEN_U_H << 4) - 16);

	/* Kill bullet if it reaches the edge of the screen */
	if (screen_bx < min_x || screen_bx > max_x || screen_by < min_y ||
		screen_by > max_y) {

		if (!(g_bullet.grid_x == (u8)g_player.grid_x &&
			    g_bullet.grid_y == (u8)g_player.grid_y)) {

			video_mark_dirty_tile(g_bullet.grid_x, g_bullet.grid_y);
			events->dirtied_tiles = true;
		}

		g_bullet.active = false;
		return;
	}

	/* Apply byte movement */
	g_bullet.byte_x = next_bx;
	g_bullet.byte_y = next_by;
	g_bullet.step_left--;

	/* Finished tween, then do tile movement */
	if (g_bullet.step_left == 0) {

		i8 dx, dy;
		i8 next_x, next_y;

		g_bullet.step_left = 2;

		dx = (g_bullet.step_bx > 0) ? 1
					    : (g_bullet.step_bx < 0 ? -1 : 0);
		dy = (g_bullet.step_by > 0) ? 1
					    : (g_bullet.step_by < 0 ? -1 : 0);

		next_x = g_bullet.grid_x + dx;
		next_y = g_bullet.grid_y + dy;

		g_bullet.last_grid_x = g_bullet.grid_x;
		g_bullet.last_grid_y = g_bullet.grid_y;

		g_bullet.grid_x = next_x;
		g_bullet.grid_y = next_y;

		/* Do FG/BG collision first */
		if (game_bullet_check_collision(events)) {

			video_mark_dirty_tile(g_bullet.grid_x, g_bullet.grid_y);
			events->dirtied_tiles = true;

			u8 lx = g_bullet.last_grid_x;
			u8 ly = g_bullet.last_grid_y;

			if (!(lx == (u8)g_player.grid_x &&
				    ly == (u8)g_player.grid_y)) {

				video_mark_dirty_tile(lx, ly);
				events->dirtied_tiles = true;
			}

			g_bullet.active = false;
			return;
		}

		/* Do the monster collision after tile movement */
		u8 mt = monmap_get(g_bullet.grid_x, g_bullet.grid_y);
		if (mt != MON_NONE) {

			monster_t *m = monster_find_at(g_bullet.screen,
				g_bullet.grid_x, g_bullet.grid_y);

			if (m) {
				monster_take_damage(m, 1, events);

				g_bullet.active = false;
				return;
			}
		}
	}

	/* Mark new tile dirty (unless player's tile) */
	u8 gx = g_bullet.grid_x;
	u8 gy = g_bullet.grid_y;

	// if (!(gx == (u8)g_player.grid_x && gy == (u8)g_player.grid_y))
	video_mark_dirty_tile(gx, gy);

	g_bullet.v_pos = cpct_getScreenPtr(CPCT_VMEM_START,
		GAME_WINDOW_X + g_bullet.byte_x,
		GAME_WINDOW_Y + g_bullet.byte_y);

	events->dirtied_tiles = true;
}

static bool game_bullet_check_collision(events_t *events) {

	u16 index = utils_get_screen_x_y(
		g_bullet.screen, g_bullet.grid_x, g_bullet.grid_y);

	u8 bg = g_screen_bg[game_get_screen_xy(
		g_bullet.grid_x, g_bullet.grid_y)];
	u8 fg = g_level_fg[index];

	/* Background collision — bullet dies */
	if (!IS_WALKABLE(bg))
		return true;

	/* Foreground collision: Jar needs special handling */
	if (fg != 0) {

		if (IS_JAR(fg)) {

			/* Destroy jar */
			g_level_fg[index] = 0;

			g_game.score = g_game.score + 50;

			/* Redraw area */
			video_mark_dirty_tile(g_bullet.grid_x, g_bullet.grid_y);
			events->dirtied_tiles = true;
		}

		/* Any foreground stops bullet */
		return true;
	}

	return false; /* No collision */
}

static void game_open_horizontal_door(u8 x, u8 y) {

	u16 index = utils_get_screen_x_y(g_player.screen, x, y);
	u8 *p_tile = &g_level_fg[index];

	while (x > 0 && IS_HDOOR(p_tile[-1])) {
		p_tile--;
		x--;
	}

	while (IS_HDOOR(*p_tile)) {

		*p_tile = 0;
		video_mark_dirty_tile(x, y);
		p_tile++;
		x++;
	}
}

static void game_open_vertical_door(u8 x, u8 y) {

	u16 index = utils_get_screen_x_y(g_player.screen, x, y);
	u8 *p_tile = &g_level_fg[index];

	while (y > 0 && IS_VDOOR(p_tile[-TILE_ARRAY_W])) {
		p_tile -= TILE_ARRAY_W;
		y--;
	}

	while (IS_VDOOR(*p_tile)) {

		*p_tile = 0;
		video_mark_dirty_tile(x, y);
		p_tile += TILE_ARRAY_W;
		y++;
	}
}

static bool game_handle_tile_on_entry(
	u8 gx, u8 gy, i8 dx, i8 dy, events_t *events) {

	u16 idx = utils_get_screen_x_y(g_player.screen, gx, gy);
	u8 fg = g_level_fg[idx];
	u8 bg = g_screen_bg[game_get_screen_xy(gx, gy)];

	/* First handle special cases such as damage tiles and next level */
	if (IS_STATUE(bg)) {
		game_maybe_hint(HINT_BUMP_STATUE);
		game_take_damage(50);
		game_update_health_string();
		events->health_updated = true;
		events->redraw_hud = true;

		return false; /* Still blocks movement */
	}

	/* Boss! */
	if (IS_BOSS(fg)) {

		/* Fixed Position on Screen */
		video_flash_border(TRIPLET_RED);

		for (u8 gy = 0; gy < SCREEN_U_H; gy++) {
			for (u8 gx = 0; gx < SCREEN_U_W; gx++) {

				u16 idx = utils_get_screen_x_y(
					g_player.screen, gx, gy);
				u8 tile = g_level_fg[idx];

				if (IS_BOSS(tile)) {

					g_level_fg[idx] =
						tile + 3; /* Turn into body */

					video_mark_dirty_tile(gx, gy);
				}
			}

			video_draw_dirty_tiles();

			bool kp = false;
			while ((!kp) && (g_clock.s < 10)) {

				cpct_waitVSYNC();
				utils_clock_tick();
				if (cpct_isAnyKeyPressed())
					kp = true;
			}

			cpct_setBorder(HW_BLACK);

			g_completed = true;
		}
	}

	if (IS_PHYLACTERY(fg)) {
		if (g_game.artifacts == 0) {
			video_flash_border(TRIPLET_RED);
			game_maybe_hint(HINT_PHLACTERY_NO_ARTEFACT);
			game_take_damage(250);
			game_update_health_string();
			events->health_updated = true;
			events->redraw_hud = true;
		} else {
			video_flash_border(TRIPLET_GREEN);
			game_maybe_hint(HINT_PHLACTERY_DESTROY);
			events->health_updated = true;
			events->redraw_hud = true;
			game_update_health_string();
			--g_game.artifacts;
			events->level_complete = true;
		}

		events->redraw_hud = true;
		return false;
	}

	/* Blocked by background */
	if (!IS_WALKABLE(bg))
		return false;

	/* Check for foreground objects */

	/* Jar: now walkable but breaks, causes minor damage */
	if (IS_JAR(fg)) {

		video_flash_border(TRIPLET_RED);
		game_maybe_hint(HINT_BUMP_JAR);

		/* Apply damage */
		game_take_damage(100);
		g_game.score += 50;
		game_update_health_string();
		events->health_updated = true;
		events->redraw_hud = true;

		/* Remove jar tile */
		g_level_fg[idx] = 0;

		/* Mark for redraw */
		video_mark_dirty_tile(gx, gy);
		events->dirtied_tiles = true;

		/* Movement is allowed */
		return true;
	}

	/* Doors */
	if (IS_DOOR(fg)) {
		if (g_game.keys == 0) {
			game_maybe_hint(HINT_NEED_KEY);
			return false;
		}

		/* Open door */
		--g_game.keys;
		game_update_hud_strings();
		game_open_door(dx, dy);

		events->opened_door = true;
		events->redraw_hud = true;
		events->dirtied_tiles = true;
	}

	/* Sarcophagus (smash both halves) */
	if (IS_SARCOGRAPHUS(fg)) {
		game_maybe_hint(HINT_FOUND_SARCOGRAPHUS);

		g_game.score += 100;
		game_smash_sarcophagus(dx, dy);

		events->destroyed_grave = true;
		events->redraw_hud = true;

		/* Movement allowed after smashing */
		return true;
	}

	/* Open Grave — solid (cannot enter) */
	if (IS_GRAVE(fg)) {
		game_maybe_hint(HINT_FOUND_GRAVE);
		return false;
	}

	/* And handle items */
	if (fg == ITEM_KEY || fg == ITEM_HEALTH || fg == ITEM_BOMB ||
		fg == ITEM_ARTIFACT) {
		switch (fg) {
		case ITEM_KEY:
			video_flash_border(TRIPLET_MAGENTA);
			game_maybe_hint(HINT_FOUND_KEY);
			++g_game.keys;
			sfx_stop();
			sfx_start((void *)sfx_get_item);
			game_update_hud_strings();
			break;

		case ITEM_HEALTH:
			video_flash_border(TRIPLET_GREEN);
			game_maybe_hint(HINT_FOUND_HEALTH);
			g_game.health += 100;
			if (g_game.health > 2000)
				g_game.health = 2000;
			events->health_updated = true;
			events->redraw_hud = true;
			sfx_stop();
			sfx_start((void *)sfx_get_item);
			game_update_health_string();
			break;

		case ITEM_BOMB:
			video_flash_border(TRIPLET_YELLOW);
			++g_game.bombs;
			sfx_stop();
			sfx_start((void *)sfx_get_item);
			game_update_hud_strings();
			break;

		case ITEM_ARTIFACT:
			video_flash_border(TRIPLET_ORANGE);
			game_maybe_hint(HINT_FOUND_ARTIFACT);
			++g_game.artifacts;
			sfx_start((void *)sfx_get_item);
			game_update_hud_strings();
			break;
		}

		/* Remove item tile (not sarcophagus, and not grave) */
		g_level_fg[idx] = 0;

		/* Dirty tile so redraw happens */
		video_mark_dirty_tile(gx, gy);
		events->picked_item = true;
		events->dirtied_tiles = true;
		events->redraw_hud = true;
	}

	/* Movement allowed */
	return true;
}

static bool game_check_landing_tile(u8 fg, u8 bg) {

	if (!IS_WALKABLE(bg))
		return false;

	// if (IS_JAR(fg))
	//	return false;

	if (IS_GRAVE(fg))
		return false;

	if (IS_SARCOGRAPHUS(fg))
		return false;

	if (IS_DOOR(fg) && g_game.keys == 0)
		return false;

	return true;
}

static void game_load_bg_for_screen(u8 screen_id) {

	const u8 *src_end = level_bgs[g_game.level - 1][screen_id].data_end;

	/* Destination end = last byte of g_screen_bg */
	u8 *dst_end = g_screen_bg + g_screen_bg_sz - 1;

	cpct_zx7b_decrunch_s(dst_end, src_end);

	/* No forward decrunch implemented yet in CPCTelera! */
}

void game_use_holy_water_bomb(events_t *events) {

	u8 screen = g_player.screen;

	/* Open door */
	if (g_game.bombs == 0)
		return;

	video_flash_border(TRIPLET_YELLOW);

	/* 1. Kill monsters */
	for (u8 i = 0; i < MAX_MONSTERS; i++) {
		monster_t *m = &g_monsters[i];
		if (m->active && m->screen == screen)
			monster_kill(m, events);
	}

	sfx_stop();
	sfx_start((void *)sfx_use_bomb);

	/* 2. Destroy jars */
	game_destroy_all_jars_on_screen(screen, events);

	/* 3. Smash sarcophagi into ruins */
	game_smash_all_sarcophagi_on_screen(screen);

	--g_game.bombs;
	game_update_hud_strings();
	events->redraw_hud = true;

	video_flash_border(TRIPLET_YELLOW);
}

static void game_destroy_all_jars_on_screen(u8 screen, events_t *events) {

	for (u8 gy = 0; gy < SCREEN_U_H; gy++) {
		for (u8 gx = 0; gx < SCREEN_U_W; gx++) {

			u16 idx = utils_get_screen_x_y(screen, gx, gy);
			u8 fg = g_level_fg[idx];

			if (IS_JAR(fg)) {

				g_level_fg[idx] = 0; /* Remove jar */

				video_mark_dirty_tile(gx, gy);
				events->dirtied_tiles = true;
			}
		}
	}
}

static void game_smash_all_sarcophagi_on_screen(u8 screen) {

	for (u8 gy = 0; gy < SCREEN_U_H; gy++) {
		for (u8 gx = 0; gx < SCREEN_U_W; gx++) {

			u16 idx = utils_get_screen_x_y(screen, gx, gy);
			u8 tile = g_level_fg[idx];

			if (IS_SARCOGRAPHUS(tile)) {

				g_level_fg[idx] =
					tile + 2; /* Turn into ruins */

				video_mark_dirty_tile(gx, gy);
			}
		}
	}
}

void game_update_player_facing(dir_t newdir) {

	/* Only East and West need flipping */
	if (newdir != DIR_EAST && newdir != DIR_WEST)
		return;

	/* Determine desired sheet state */
	bool want_flipped = (newdir == DIR_WEST);

	/* If already in correct orientation → no flip needed */
	if (g_sprite_flipped == want_flipped)
		return;

	/* Base sprite sheet pointer */
	u8 *base = (u8 *)(g_options & OPT_CHARACTER ? reginald_m_16x16_00
						    : regina_m_16x16_00);

	/* Flip East-frame block (6,7,8) */
	cpct_hflipSpriteM1(4, 16, base + (6 << 6));
	cpct_hflipSpriteM1(4, 16, base + (7 << 6));
	cpct_hflipSpriteM1(4, 16, base + (8 << 6));

	/* Update sprite-sheet orientation flag */
	g_sprite_flipped = !g_sprite_flipped;
}

static void game_do_pause(void) {

	game_draw_pause();

	utils_wait_for_key(g_controls[KEY_PAUSE]);

	game_undraw_pause();
}

inline void game_maybe_hint(u8 idx) {

	if (g_game.hints[idx])
		game_show_hint(idx);
}

inline void game_take_damage(u16 amount) {

	if (!(g_options & OPT_CHEAT))
		g_game.health =
			(g_game.health > amount) ? g_game.health - amount : 0;
}

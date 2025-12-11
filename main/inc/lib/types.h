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

#include <cpctelera.h>

/* Hiscore object */
typedef struct {
		char initials[4]; /* scorer (user-entered, length 3 chars) */
		u32 score;	  /* score */
		u8 width;	  /* width in digits of score as string */
} score_t;

/* Screen Coordinate */
typedef struct {
		u8 x; /* x coordinate (0 is top-left) */
		u8 y; /* y coordinate (0 is top-left) */
} pos_t;

/* Rectangle */
typedef struct {
		i8 x0;
		i8 y0;
		i8 x1;
		i8 y1;
} rect_t;

/* Realtime clock */
typedef struct {

		u16 ms; /* Milliseconds*/
		u16 s;	/* Seconds */
} clock_t;

/* Keyboard Mapping */
typedef struct {
		cpct_keyID key;
		u8 ascii;
} key_t;

/* Game Events */
typedef struct {
		bool moved;
		bool moved_screen;
		bool rotated;
		bool opened_door;
		bool destroyed_grave;
		bool picked_item;
		bool fired;
		bool redraw_hud;
		bool dirtied_tiles;
		bool level_complete;
		bool health_updated;
} events_t;

/* Controls */
typedef struct {
		bool up;
		bool down;
		bool left;
		bool right;
		bool fire;
		bool bomb;
		bool pause;
		bool quit;
		bool skip;
} input_t;

/* Rendering Queue */
typedef enum {
	RQ_NONE = 0,
	RQ_PLAYER = 1,
	RQ_SCREEN = 2,
	RQ_HUD = 4,
	RQ_ITEMS = 8,
	RQ_DIRTY = 16
} render_t;

/* Player Data*/
typedef struct {
		i8 grid_x, grid_y; /* Current Grid Position (Grid Units) */
		i8 old_x, old_y;   /* Previous Grid Position (Grid Units) */
		u8 byte_x, byte_y; /* Byte Position (from GAME_WINDOW_X/Y) */
		dir_t dir;	   /* Current Direction */
		u8 frame;	   /* Current Animation Frame */
		u8 s_idx;	   /* Sprite Index */
		u8 *v_pos;	   /* Screen Position Pointer */
		u8 screen;	   /* Current Screen */

		u8 last_grid_x;
		u8 last_grid_y;
		bool moving;  /* currently tweening between tiles? */
		u8 step_left; /* how many 8px steps are left (0,1,2) */
		i8 step_bx;   /* per-frame byte delta on X */
		i8 step_by;   /*  per-frame byte delta on Y */

		bool facing_right; /* For Sprite Flipping */
		u8 move_cooldown;

} player_t;

/* Smashable Gravestone */
typedef struct {
		i8 dx, dy;
		u8 partner;
} grave_t;

/* Dirty Tile */
typedef struct {
		i8 x, y; /* Current Grid Position (Grid Units)  */
} dirty_t;

/* Game Data*/
typedef struct {
		u32 score;	      /* Current Score */
		u16 max_hp;	      /* Maximum Health */
		u16 health;	      /* Current Health */
		u8 level;	      /* Current Level */
		u8 keys;	      /* Current Number of Keys */
		u8 bombs;	      /* Current Number of Bombs */
		u8 artifacts;	      /* Current Number of Artefacts */
		bool hints[HINTS_SZ]; /* Tutorial Flags */
		char health_str[5];   /* String Representations */
		char keys_str[3];
		char bombs_str[3];
		char artifacts_str[3];

} game_t;

typedef struct {
		bool active;
		u8 screen; /* which screen the bullet is on */
		u8 byte_x; /* byte coordinates (relative to GAME_WINDOW_X) */
		u8 byte_y;
		u8 grid_x; /* tile coordinates */
		u8 grid_y;
		i8 step_bx; /* per-frame byte movement */
		i8 step_by;
		u8 step_left; /* 2 steps per tile */
		u8 dir;	      /* matches player DIR_N/E/S/W */
		u8 *v_pos;    /* cached VRAM pointer */

		u8 speed_delay;	  /* frames between movements */
		u8 delay_counter; /* countdown */
		u8 last_grid_x;
		u8 last_grid_y;
} bullet_t;

/* Screen Connections */
typedef struct {
		dir_t direction;
		u8 from;
		u8 to;
} connect_t;

typedef struct {
		u8 key_index;
		u8 joy_index;
		u8 direction;
} control_mapping_t;

typedef struct {
		const u8 *data;
		const u8 *data_end;
} screen_bg_t;

typedef struct {

		u8 active; /* 0 = dead, 1 = alive */
		u8 type;   /* MON_* */
		u8 screen; /* screen where monster belongs */

		/* tile coordinates */
		u8 grid_x;
		u8 grid_y;

		/* pixel byte coordinates (VRAM offsets) */
		u8 byte_x;
		u8 byte_y;

		/* tween movement */
		i8 step_bx;
		i8 step_by;
		u8 step_left;

		/* direction facing */
		dir_t dir;

		/* animation */
		u8 anim_frame;
		u8 anim_counter;

		/* movement delay */
		u8 speed_delay;
		u8 delay_count;

		/* despawn after time offscreen */
		u16 despawn_timer;

		/* vram pointer for drawing */
		u8 *v_pos;

} monster_t;

typedef struct {
		u8 y;		 /* byte Y position */
		bool going_down; /* direction flag */
		u8 frame;	 /* 0–2 cycle */
		bool drawn;	 /* Drawn initially */
		u8 anim_delay;
		u8 anim_phase;
} walker_t;

/* Border flashing triplets */
typedef struct {

		u8 c0, c1, c2;
} triplet_t;

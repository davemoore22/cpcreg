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

/* Hiscore object */
typedef struct {
  char initials[4]; /* scorer (user-entered, length 3 chars) */
  u32 score;        /* score */
  u8 width;         /* width in digits of score as string */
} score_t;

/* Screen Coordinate */
typedef struct {
  u8 x; /* x coordinate (0 is top-left) */
  u8 y; /* y coordinate (0 is top-left) */
} pos_t;

/* Realtime clock */
typedef struct {
  u16 ms; /* Milliseconds*/
  u16 s;  /* Seconds */
} clock_t;

/* Cardinal direction */
typedef enum { DIR_SOUTH = 0, DIR_EAST = 1, DIR_NORTH = 2, DIR_WEST = 3 } dir_t;

/* Screen */
typedef enum {
  SCREEN_TL = 0,
  SCREEN_TM = 1,
  SCREEN_TR = 2,
  SCREEN_ML = 3,
  SCREEN_M = 4,
  SCREEN_MR = 5,
  SCREEN_BL = 6,
  SCREEN_BM = 7,
  SCREEN_BR = 8
} screen_t;

/* Player Data*/
typedef struct {
  u8 x, y;    /* Current Location (Pixels) */
  u8 px, py;  /* Previous Location (Pixels) */
  u8 sx, sy;  /* Clipping Location (Grid)  */
  dir_t dir;  /* Current Direction */
  u8 frame;   /* Current Animation Frame */
  u8 *bb_pos; /* Screen Address of Player Sprite on Back Buffer */
  u8 s_idx;   /* Sprite Index */
} player_t;

/* Game Data*/
typedef struct {
  screen_t screen; /* Current Screen */
  u32 score;       /* Current Score */
  u16 max_hp;      /* Maximum Health */
  u16 hp;          /* Current Health */
  u8 level;        /* Current Level */
  u8 keys;         /* Current Number of Keys */
  u8 bombs;        /* Current Number of Bombs */
  u8 artefacts;    /* Current Number of Artefacts */
} game_t;

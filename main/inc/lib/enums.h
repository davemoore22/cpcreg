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

#include <cpctelera.h>

/* Controls */
typedef enum {
	KEY_UP = 0,
	KEY_DOWN = 1,
	KEY_LEFT = 2,
	KEY_RIGHT = 3,
	KEY_SHOOT = 4,
	KEY_BOMB = 5,
	KEY_PAUSE = 6,
	JOY_UP = 7,
	JOY_DOWN = 8,
	JOY_LEFT = 9,
	JOY_RIGHT = 10,
	JOY_SHOOT = 11,
	JOY_BOMB = 12,
} control_t;

/* Cardinal direction */
typedef enum {
	DIR_NORTH = 0,
	DIR_SOUTH = 1,
	DIR_EAST = 2,
	DIR_WEST = 3,
	DIR_NONE = 4
} dir_t;

enum {
	FT_TL,
	FT_TM,
	FT_TR,
	FT_ML,
	FT_MR,
	FT_BL,
	FT_BM,
	FT_BR
};
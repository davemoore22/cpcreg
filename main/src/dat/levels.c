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

#pragma constseg DATA

#include "dat/levels.h"

/* Level Palettes */

const u8 palette_level_1[6][4] = {
	{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PASTEL_YELLOW},
	{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PASTEL_YELLOW},
	{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PASTEL_YELLOW},
	{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PASTEL_YELLOW},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
};

const u8 palette_level_2[6][4] = {
	{HW_BLACK, HW_GREEN, HW_BRIGHT_GREEN, HW_BRIGHT_YELLOW},
	{HW_BLACK, HW_GREEN, HW_BRIGHT_GREEN, HW_BRIGHT_YELLOW},
	{HW_BLACK, HW_GREEN, HW_BRIGHT_GREEN, HW_BRIGHT_YELLOW},
	{HW_BLACK, HW_GREEN, HW_BRIGHT_GREEN, HW_BRIGHT_YELLOW},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
};

const u8 palette_level_3[6][4] = {
	{HW_BLACK, HW_MAGENTA, HW_PASTEL_MAGENTA, HW_PASTEL_YELLOW},
	{HW_BLACK, HW_MAGENTA, HW_PASTEL_MAGENTA, HW_PASTEL_YELLOW},
	{HW_BLACK, HW_MAGENTA, HW_PASTEL_MAGENTA, HW_PASTEL_YELLOW},
	{HW_BLACK, HW_MAGENTA, HW_PASTEL_MAGENTA, HW_PASTEL_YELLOW},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
};

const u8 palette_level_4[6][4] = {
	{HW_BLACK, HW_WHITE, HW_BRIGHT_CYAN, HW_BRIGHT_WHITE},
	{HW_BLACK, HW_WHITE, HW_BRIGHT_CYAN, HW_BRIGHT_WHITE},
	{HW_BLACK, HW_WHITE, HW_BRIGHT_CYAN, HW_BRIGHT_WHITE},
	{HW_BLACK, HW_WHITE, HW_BRIGHT_CYAN, HW_BRIGHT_WHITE},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
};

const u8 palette_level_5[6][4] = {
	{HW_BLACK, HW_RED, HW_ORANGE, HW_BRIGHT_YELLOW},
	{HW_BLACK, HW_RED, HW_ORANGE, HW_BRIGHT_YELLOW},
	{HW_BLACK, HW_RED, HW_ORANGE, HW_BRIGHT_YELLOW},
	{HW_BLACK, HW_RED, HW_ORANGE, HW_BRIGHT_YELLOW},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
};

const u8 palette_level_6[6][4] = {
	{HW_BLACK, HW_BLUE, HW_PURPLE, HW_ORANGE},
	{HW_BLACK, HW_BLUE, HW_PURPLE, HW_ORANGE},
	{HW_BLACK, HW_BLUE, HW_PURPLE, HW_ORANGE},
	{HW_BLACK, HW_BLUE, HW_PURPLE, HW_ORANGE},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
	{HW_BLACK, HW_BLUE, HW_PASTEL_BLUE, HW_PASTEL_CYAN},
};

const screen_bg_t level_bgs[6][LEVELS_SZ] = {
	{
		{level_1_0_bg, level_1_0_bg_end},
		{level_1_1_bg, level_1_1_bg_end},
		{level_1_2_bg, level_1_2_bg_end},
		{level_1_3_bg, level_1_3_bg_end},
		{level_1_4_bg, level_1_4_bg_end},
		{level_1_5_bg, level_1_5_bg_end},
		{level_1_6_bg, level_1_6_bg_end},
		{level_1_7_bg, level_1_7_bg_end},
		{level_1_8_bg, level_1_8_bg_end},
		{level_1_9_bg, level_1_9_bg_end},
		{level_1_10_bg, level_1_10_bg_end},
		{level_1_11_bg, level_1_11_bg_end},
	},
	{
		{level_2_0_bg, level_2_0_bg_end},
		{level_2_1_bg, level_2_1_bg_end},
		{level_2_2_bg, level_2_2_bg_end},
		{level_2_3_bg, level_2_3_bg_end},
		{level_2_4_bg, level_2_4_bg_end},
		{level_2_5_bg, level_2_5_bg_end},
		{level_2_6_bg, level_2_6_bg_end},
		{level_2_7_bg, level_2_7_bg_end},
		{level_2_8_bg, level_2_8_bg_end},
		{level_2_9_bg, level_2_9_bg_end},
		{level_2_10_bg, level_2_10_bg_end},
		{level_2_11_bg, level_2_11_bg_end},
	},
	{
		{level_3_0_bg, level_3_0_bg_end},
		{level_3_1_bg, level_3_1_bg_end},
		{level_3_2_bg, level_3_2_bg_end},
		{level_3_3_bg, level_3_3_bg_end},
		{level_3_4_bg, level_3_4_bg_end},
		{level_3_5_bg, level_3_5_bg_end},
		{level_3_6_bg, level_3_6_bg_end},
		{level_3_7_bg, level_3_7_bg_end},
		{level_3_8_bg, level_3_8_bg_end},
		{level_3_9_bg, level_3_9_bg_end},
		{level_3_10_bg, level_3_10_bg_end},
		{level_3_11_bg, level_3_11_bg_end},
	},
	{
		{level_4_0_bg, level_4_0_bg_end},
		{level_4_1_bg, level_4_1_bg_end},
		{level_4_2_bg, level_4_2_bg_end},
		{level_4_3_bg, level_4_3_bg_end},
		{level_4_4_bg, level_4_4_bg_end},
		{level_4_5_bg, level_4_5_bg_end},
		{level_4_6_bg, level_4_6_bg_end},
		{level_4_7_bg, level_4_7_bg_end},
		{level_4_8_bg, level_4_8_bg_end},
		{level_4_9_bg, level_4_9_bg_end},
		{level_4_10_bg, level_4_10_bg_end},
		{level_4_11_bg, level_4_11_bg_end},
	},
	{
		{level_5_0_bg, level_5_0_bg_end},
		{level_5_1_bg, level_5_1_bg_end},
		{level_5_2_bg, level_5_2_bg_end},
		{level_5_3_bg, level_5_3_bg_end},
		{level_5_4_bg, level_5_4_bg_end},
		{level_5_5_bg, level_5_5_bg_end},
		{level_5_6_bg, level_5_6_bg_end},
		{level_5_7_bg, level_5_7_bg_end},
		{level_5_8_bg, level_5_8_bg_end},
		{level_5_9_bg, level_5_9_bg_end},
		{level_5_10_bg, level_5_10_bg_end},
		{level_5_11_bg, level_5_11_bg_end},
	},
	{
		{level_6_0_bg, level_6_0_bg_end},
		{level_6_1_bg, level_6_1_bg_end},
		{level_6_2_bg, level_6_2_bg_end},
		{level_6_3_bg, level_6_3_bg_end},
		{level_6_4_bg, level_6_4_bg_end},
		{level_6_0_bg, level_6_0_bg_end},
		{level_6_0_bg, level_6_0_bg_end},
		{level_6_0_bg, level_6_0_bg_end},
		{level_6_0_bg, level_6_0_bg_end},
		{level_6_0_bg, level_6_0_bg_end},
		{level_6_0_bg, level_6_0_bg_end},
		{level_6_0_bg, level_6_0_bg_end},
	}};

/* Screen Connections (format is N, S, E, W then Screens 0 to 11) */
const u8 l_next_screen[6][4][12] = {
	{
		{1, 2, 3, 4, 5, 8, NO_LINK, NO_LINK, 9, NO_LINK, NO_LINK,
			NO_LINK},
		{NO_LINK, 0, 1, 2, 3, 4, NO_LINK, NO_LINK, 5, 8, NO_LINK,
			NO_LINK},
		{NO_LINK, 2, NO_LINK, NO_LINK, NO_LINK, 10, 5, 6, NO_LINK,
			NO_LINK, 11, NO_LINK},
		{NO_LINK, NO_LINK, NO_LINK, NO_LINK, NO_LINK, 6, 7, 6, NO_LINK,
			NO_LINK, 5, 10},
	},
	{
		{NO_LINK, NO_LINK, NO_LINK, 0, 1, 2, 3, 4, 5, 6, 7, 8},
		{3, 4, 5, 6, 7, 8, 9, 10, 11, NO_LINK, NO_LINK, NO_LINK},
		{1, 2, NO_LINK, 4, 5, NO_LINK, 7, 8, NO_LINK, 10, 11, NO_LINK},
		{NO_LINK, 0, 1, NO_LINK, 3, 4, NO_LINK, 6, 7, NO_LINK, 9, 10},
	},
	{
		{NO_LINK, NO_LINK, 9, 0, 1, 2, NO_LINK, 4, 10, 6, 7, 8},
		{3, 4, 5, NO_LINK, 7, 11, 9, 10, 11, 2, 8, NO_LINK},
		{1, 0, 8, 4, 3, 11, 7, 6, 2, 10, 9, 5},
		{1, 0, 8, 4, 3, 11, 7, 6, 2, 10, 9, 5},
	},
	{
		{NO_LINK, NO_LINK, 9, 0, 1, 10, 3, 4, NO_LINK, 6, 7, NO_LINK},
		{3, 4, NO_LINK, 6, 7, NO_LINK, 9, 10, NO_LINK, 2, 5, NO_LINK},
		{1, NO_LINK, 5, NO_LINK, NO_LINK, NO_LINK, NO_LINK, NO_LINK, 11,
			NO_LINK, NO_LINK, 7},
		{NO_LINK, 0, NO_LINK, NO_LINK, NO_LINK, 2, NO_LINK, 11, NO_LINK,
			NO_LINK, NO_LINK, 8},
	},
	{
		{9, 9, 9, 9, 9, 10, 9, NO_LINK, 0, NO_LINK, 11, 0},
		{8, 8, 8, 8, 8, 8, 8, NO_LINK, NO_LINK, 0, 5, 10},
		{1, 2, 3, 4, 5, 6, 7, NO_LINK, NO_LINK, NO_LINK, NO_LINK,
			NO_LINK},
		{NO_LINK, 0, 0, 0, 0, 0, 5, 6, NO_LINK, NO_LINK, 5, 10},
	},
	{
		{NO_LINK, NO_LINK, NO_LINK, NO_LINK, 1, NO_LINK, NO_LINK,
			NO_LINK, NO_LINK, NO_LINK, NO_LINK, NO_LINK},
		{NO_LINK, 4, NO_LINK, NO_LINK, NO_LINK, NO_LINK, NO_LINK,
			NO_LINK, NO_LINK, NO_LINK, NO_LINK, NO_LINK},
		{NO_LINK, 2, NO_LINK, 4, NO_LINK, NO_LINK, NO_LINK, NO_LINK,
			NO_LINK, NO_LINK, NO_LINK},
		{NO_LINK, NO_LINK, 1, NO_LINK, 3, NO_LINK, NO_LINK, NO_LINK,
			NO_LINK, NO_LINK, NO_LINK, NO_LINK},

	}};
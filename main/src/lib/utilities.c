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

#include "lib/utilities.h"

static void utils_set_page(u8 bank);
static void utils_swap_scores(score_t *a, score_t *b);

/* Enable Global Timer */
bool g_clock_on;

/* Realtime Clock */
clock_t g_clock = {.ms = 0, .s = 0};

/* Key Mapping */
const key_t u_key_mapping[KEY_MAPPING_REDEFINE_SZ] = {{Key_A, 'A'},
	{Key_B, 'B'}, {Key_C, 'C'}, {Key_D, 'D'}, {Key_E, 'E'}, {Key_F, 'F'},
	{Key_G, 'G'}, {Key_H, 'H'}, {Key_I, 'I'}, {Key_J, 'J'}, {Key_K, 'K'},
	{Key_L, 'L'}, {Key_M, 'M'}, {Key_N, 'N'}, {Key_O, 'O'}, {Key_P, 'P'},
	{Key_Q, 'Q'}, {Key_R, 'R'}, {Key_S, 'S'}, {Key_T, 'T'}, {Key_U, 'U'},
	{Key_V, 'V'}, {Key_W, 'W'}, {Key_X, 'X'}, {Key_Y, 'Y'}, {Key_Z, 'Z'},
	{Key_Space, ' '}, {Key_CursorUp, 0x81}, {Key_CursorDown, 0x82},
	{Key_CursorLeft, 0x83}, {Key_CursorRight, 0x84}, {Key_Enter, 0x85}};

cpct_keyID utils_wait_for_keys(const cpct_keyID *keys, u8 num_keys) {

	u8 count = 0;

	while (true) {
		if (++count == 200) {
			count = 0;
			for (u8 i = 0; i < num_keys; ++i)
				if (cpct_isKeyPressed(keys[i]))
					return keys[i];
		}
	}
}

cpct_keyID utils_wait_for_extended_key(void) {

	while (true) {

		/* Search mapping table */
		for (u8 i = 0; i < KEY_MAPPING_REDEFINE_SZ; ++i) {
			if (cpct_isKeyPressed(u_key_mapping[i].key))
				return u_key_mapping[i].key;
		}

		/* ESC cancels */
		if (cpct_isKeyPressed(Key_Esc))
			return Key_Esc;
	}
}

/* Wait for a Key */
void utils_wait_for_key(cpct_keyID key) {

	do
		cpct_scanKeyboard_f();
	while (!cpct_isKeyPressed(key));

	do
		cpct_scanKeyboard_f();
	while (cpct_isKeyPressed(key));
}

/* Wait for a certain number of cycles in a do nothing loop */
void utils_wait(const u16 n) {

	for (u16 i = 0; i < n; ++i)
		__asm__("NOP");
}

/* Map a keycode to Uppercase ASCII character */
u8 utils_map_key_to_ascii(const cpct_keyID key) {

	for (u8 i = 0; i < KEY_MAPPING_SZ; ++i) {
		if (u_key_mapping[i].key == key)
			return u_key_mapping[i].ascii;
	}

	return '.';
}

/* Map a character to keycode */
cpct_keyID utils_map_ascii_to_key(const u8 ascii) {

	for (u8 i = 0; i < KEY_MAPPING_SZ; ++i) {
		if (u_key_mapping[i].ascii == ascii)
			return u_key_mapping[i].key;
	}

	return Key_Dot;
}

/* Sort the Hiscore table */
void utils_sort_hiscores(void) {

	for (u8 i = 0; i < HISCORES_SZ - 1; ++i) {
		for (u8 j = i + 1; j < HISCORES_SZ; ++j) {

			if (g_hiscores[j].score > g_hiscores[i].score)
				utils_swap_scores(
					&g_hiscores[i], &g_hiscores[j]);
		}
	}
}

/* String Length (without using strlen) */
u8 utils_strlen(const char *str) {

	u8 length = 0;

	while (*str != '\0') {
		++length;
		++str;
	}

	return length;
}

/* Copy a string (without using strcpy) */
char *utils_strcpy(char *dest, const char *src) {

	char *original_dest = dest;

	while (*src != '\0') {
		*dest = *src;
		++dest;
		++src;
	}

	/* Null-terminate the destination string */
	*dest = '\0';

	return original_dest;
}

/* Get the Width (in digits, i.e. characters) of ths score (from 1 to 6) */
u8 utils_get_str_width(const u32 score) {

	/* Do it this way to avoid a division since we know the max length */
	if (score >= 100000UL)
		return 6;
	else if (score >= 10000UL)
		return 5;
	else if (score >= 1000UL)
		return 4;
	else if (score >= 100UL)
		return 3;
	else if (score >= 10UL)
		return 2;
	else
		return 1;
}

/* Interrupt function used by Realtime Clock */
void utils_clock_interrupt(void) {

	static u8 count = 0;

	/* Skip if the Realtime Clock is not enabled */
	if (g_clock_on) {

		/*
		 * On a CPC, interrupts are called every 1/300 of a second,
		 * therefore we throttle this function down to only do a tick
		 * every 1/50 of a second (20 microseconds)
		 */
		if (++count == 6)
			count = 0;
		if (count == 5) {
			g_clock.ms += 20;
			if (g_clock.ms == 1000) {
				++g_clock.s;
				g_clock.ms = 0;
			}
		}

		/*
		 * Note that this will cause an error once g_timer_s > 65535,
		 * or just over 18 hours; for efficiency purposes we do not
		 * check for this overlow!
		 */
	}
}

/* Reset Clock */
void utils_reset_clock(void) {

	g_clock.ms = g_clock.s = 0;
}

/* Clear Input Queue */
void utils_clear_input(void) {

	cpct_scanKeyboard_f();
	while (cpct_isAnyKeyPressed_f())
		cpct_scanKeyboard_f();
}

/* Get a delta for a cardinal direction (in grid units) */
inline void utils_get_delta(const dir_t dir, i8 *dx, i8 *dy) {

	/* North, South, East, West */
	const static i8 offsets_grid[4][2] = {
		{0, -PLAYER_DELTA_G_Y},
		{0, PLAYER_DELTA_G_Y},
		{PLAYER_DELTA_G_X, 0},
		{-PLAYER_DELTA_G_X, 0},
	};

	*dx = (offsets_grid[dir][0]);
	*dy = (offsets_grid[dir][1]);
}

/* Load and display a file (e.g. screen from disc) */
void utils_load(char file_name[12], u8 *loc) {

	asm_fdc_on();
	asm_load_file(file_name, loc, g_disk_table);
	asm_fdc_off();
}

u32 utils_abs(i32 x) {

	return (x < 0) ? -x : x;
}

i8 utils_sign(u8 uval) {
	if (uval <= 127)
		return (i8)uval;
	else
		return (i8)(uval - 256);
}

/* Assume 16x9 screens */
u16 utils_get_screen_x_y(u8 screen, u8 x, u8 y) {

	static const u8 row_lookup[12] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
	static const u8 col_lookup[12] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2};
	u8 row, col, abs_x, abs_y, screen_x, screen_y;
	u16 offset;

	/* Determine the row and column of the zone */
	row = row_lookup[screen];
	col = col_lookup[screen];

	/* Work out start x and y of screen */
	screen_x = col << 4;
	screen_y = (row << 3) + row;

	/* Compute the absolute x and y positions within the full array */
	abs_x = screen_x + x;
	abs_y = screen_y + y;

	/* Return linear offset (this is equvalent to abs_y * 48 + abs_x) */
	offset = (u16)((abs_y << 5) + (abs_y << 4)) + abs_x;

	return offset;
}

void utils_itoa_2(char *buf, u8 num) {

	u8 tens = 0;

	if (num > 99)
		num = 99;

	while (num >= 10) {
		num -= 10;
		tens++;
	}

	/* Tens */
	buf[0] = '0' + tens;

	/* Ones */
	buf[1] = '0' + num;

	/* Null terminator */
	buf[2] = '\0';
}

void utils_itoa_4(char *buf, u16 num) {

	u8 digit;

	/* Clamp to 9999 if needed */
	if (num > 9999)
		num = 9999;

	/* Thousands */
	digit = 0;
	while (num >= 1000) {
		num -= 1000;
		digit++;
	}
	buf[0] = '0' + digit;

	/* Hundreds */
	digit = 0;
	while (num >= 100) {
		num -= 100;
		digit++;
	}
	buf[1] = '0' + digit;

	/* Tens */
	digit = 0;
	while (num >= 10) {
		num -= 10;
		digit++;
	}
	buf[2] = '0' + digit;

	/* Ones */
	buf[3] = '0' + num;

	/* Null terminator */
	buf[4] = '\0';
}

void utils_itoa_6(char *buf, u32 num) {

	u8 i = 0;
	u8 started = 0; /* Have we printed any non-zero digit yet? */
	u8 digit;

	if (num == 0) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	/* 100000s */
	if (num >= 100000UL) {
		digit = 0;
		while (num >= 100000UL) {
			num -= 100000UL;
			++digit;
		}
		buf[i++] = '0' + digit;
		started = 1;
	}

	/* 10000s */
	if (started || num >= 10000UL) {
		digit = 0;
		while (num >= 10000UL) {
			num -= 10000UL;
			++digit;
		}
		buf[i++] = '0' + digit;
		started = 1;
	}

	/* 1000s */
	if (started || num >= 1000UL) {
		digit = 0;
		while (num >= 1000UL) {
			num -= 1000UL;
			++digit;
		}
		buf[i++] = '0' + digit;
		started = 1;
	}

	/* 100s */
	if (started || num >= 100UL) {
		digit = 0;
		while (num >= 100UL) {
			num -= 100UL;
			++digit;
		}
		buf[i++] = '0' + digit;
		started = 1;
	}

	/* 10s */
	if (started || num >= 10UL) {
		digit = 0;
		while (num >= 10UL) {
			num -= 10UL;
			++digit;
		}
		buf[i++] = '0' + digit;
		started = 1;
	}

	/* 1s (whatever’s left) */
	buf[i++] = '0' + (u8)num;

	buf[i] = '\0';
}

u8 utils_rand_0_8(void) {

	u8 r;
	do {
		r = cpct_getRandom_lcg_u8(0);
	} while (r >= 252);
	/* r < 252 ; 252 = 9*28 */
	/* Convert 0..251 → 0..8 using repeated subtraction */
	if (r >= 224)
		return 8;
	if (r >= 196)
		return 7;
	if (r >= 168)
		return 6;
	if (r >= 140)
		return 5;
	if (r >= 112)
		return 4;
	if (r >= 84)
		return 3;
	if (r >= 56)
		return 2;
	if (r >= 28)
		return 1;
	return 0;
}

static void utils_swap_scores(score_t *a, score_t *b) {

	score_t t;

	/* copy a → t */
	t.score = a->score;
	t.width = a->width;
	t.initials[0] = a->initials[0];
	t.initials[1] = a->initials[1];
	t.initials[2] = a->initials[2];
	t.initials[3] = a->initials[3];

	/* copy b → a */
	a->score = b->score;
	a->width = b->width;
	a->initials[0] = b->initials[0];
	a->initials[1] = b->initials[1];
	a->initials[2] = b->initials[2];
	a->initials[3] = b->initials[3];

	/* copy t → b */
	b->score = t.score;
	b->width = t.width;
	b->initials[0] = t.initials[0];
	b->initials[1] = t.initials[1];
	b->initials[2] = t.initials[2];
	b->initials[3] = t.initials[3];
}

void utils_clock_tick(void) {

	g_clock.ms += 20;
	if (g_clock.ms >= 1000) {
		g_clock.ms = 0;
		++g_clock.s;
	}
}
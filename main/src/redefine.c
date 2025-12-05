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

#pragma codeseg CODE

#include "redefine.h"

/* Temporary Buffer for Redefinding Controls */
cpct_keyID controls[13];

/* Private Functions */
static void redefine_draw(const control_t current);
static bool redefine_is_control_used(control_t current, cpct_keyID candidate);

/* Start Redefine Screen */
void redefine_start(void) {

	/* Get the current controls */
	for (u8 i = 0; i < CONTROLS_SZ; i++)
		controls[i] = g_controls[i];

	/* Draw the Screen */
	control_t current = KEY_UP;
	video_clear_centre();
	redefine_draw(current);

	/* Wait for a keypress for a selected control */
	while (current < KEY_PAUSE) {

		cpct_keyID key = utils_wait_for_extended_key();

		if (key == Key_Esc)
			return;

		/* First figure out if key is already used */
		i16 used_index = -1;
		for (u8 i = KEY_UP; i < KEY_PAUSE; i++) {
			if (controls[i] == key) {
				used_index = i;
				break;
			}
		}

		/* Doing redefining of keys is tricky! */
		if (used_index == -1) {

			/* If the key isn't yet used at all, accept it */
			controls[current] = key;
			++current;
		} else if (used_index == current) {

			/* Same key as before, accept it */
			++current;
		} else if (used_index < current) {

			/* Don't allow use of a previously redefined key */
			continue;
		} else if (used_index > current) {

			/* If it us used by a "later" control,  swap it */
			cpct_keyID tmp = controls[current];
			controls[current] = key;
			controls[used_index] = tmp;
			++current;
		}

		cpct_waitVSYNC();
		redefine_draw(current);
		utils_wait(1000);
	}

	utils_wait(1000);

	for (u8 i = 0; i < CONTROLS_SZ; i++)
		g_controls[i] = controls[i];
}

/* Stop Redefine Screen */
void redefine_stop(void) {

	m_menu_input_enabled = true;
}

/* Draw Redefine Keys */
static void redefine_draw(const control_t current) {

	char key[2] = "";
	u16 x, y, z;

	static const cpct_keyID special_keys[6] = {Key_CursorUp, Key_CursorDown,
		Key_CursorLeft, Key_CursorRight, Key_Space, Key_Enter};

	static const u8 special_strs[6] = {
		NON_ASCII_KEYS_START + 0,
		NON_ASCII_KEYS_START + 1,
		NON_ASCII_KEYS_START + 2,
		NON_ASCII_KEYS_START + 3,
		NON_ASCII_KEYS_START + 4,
		NON_ASCII_KEYS_START + 5,
	};

	/* Draw the Redefine Controls subtitle */
	y = TITLE_Y << LINE_P_H_SHIFT;
	v_pen = PEN_NO_RECOLOUR;
	video_print_centred_text(g_strings[REDEFINE_SUBTITLE], y);

	/* And each control in turn */
	x = KEYS_X << LINE_P_W_SHIFT;
	z = (KEYS_X + KEYS_GAP_X) << LINE_P_W_SHIFT;
	y = KEYS_Y << LINE_P_H_SHIFT;
	for (u8 i = KEY_UP; i < KEY_PAUSE; i++) {

		const char *str;
		bool printed = false;

		/* Draw the text form of the control */
		str = g_strings[i + KEYS_START];

		v_pen = i == current ? PEN_3 : PEN_2;
		video_print_text(str, x, y);
		cpct_drawSolidBox(
			cpct_getScreenPtr(CPCT_VMEM_START, z, y), 0, 10, 8);

		for (u8 s = 0; s < 6; s++) {
			if (controls[i] == special_keys[s]) {
				video_print_text(
					g_strings[special_strs[s]], z, y);
				printed = true;
				break;
			}
		}

		if (!printed) {
			key[0] = utils_map_key_to_ascii(controls[i]);
			video_print_text(key, z, y);
		}

		y += LINE_P_H << 1;
	}

	/* Draw Instructions */
	v_pen = PEN_3;
	x = KEYS_X << LINE_P_W_SHIFT;
	y = PRESS_REDEFINE_Y << LINE_P_H_SHIFT;
	video_print_text(g_strings[PRESS_KEY_FOR_TEXT], x, y);
	x = (KEYS_X + 18) << LINE_P_W_SHIFT;
	video_print_text(g_strings[current + KEYS_START], x, y);
	video_print_centred_text(g_strings[CANCEL_TEXT], y + (LINE_P_H << 1));
}

/* Is a Control already used (excluding the control currently being edited)? */
static bool redefine_is_control_used(control_t current, cpct_keyID candidate) {

	for (control_t i = KEY_UP; i < JOY_UP; i++) {
		if (i == current)
			continue; /* Allow re-selecting the same key */

		if (controls[i] == candidate)
			return true; /* Used by a different control */
	}

	return false;
}

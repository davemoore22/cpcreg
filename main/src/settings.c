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

#include "settings.h"

/* Private Functions */
static void settings_draw(void);

/* Start Settings Screen */
void settings_start(void) {

	cpct_keyID key;
	bool options_text = g_options & OPT_TEXT;

	video_clear_centre();
	settings_draw();

	bool flash = false;
	while (1) {

		static const cpct_keyID keys[] = {
			Key_1, Key_2, Key_3, Key_4, Key_Esc};

		key = utils_wait_for_keys(keys, 5);

		if (key == Key_1) {
			g_options ^= OPT_SFX;
			flash = true;
		} else if (key == Key_2) {
			g_options ^= OPT_CHEAT;
			flash = true;
		} else if (key == Key_3) {
			g_options ^= OPT_GREEN_SCREEN;
			flash = true;
		} else if (key == Key_4) {
			g_options ^= OPT_TEXT;
			flash = true;
		} else if (key == Key_Esc) {
			cpct_memset(g_game.hints, options_text, HINTS_SZ);
			return;
		}

		if (flash) {

			video_flash_border(TRIPLET_BLUE);

			flash = false;
		}

		settings_draw();
	}
}

/* Stop Hiscores Screen */
void settings_stop(void) {

	m_menu_input_enabled = true;
}

/* Draw Settings Screen */
static void settings_draw(void) {

	u8 y = SETTINGS_Y * LINE_P_H;
	const char *str;

	static const u8 option_indices[] = {
		OPT_SFX,
		OPT_CHEAT,
		OPT_GREEN_SCREEN,
		OPT_TEXT,
	};
	static const u8 string_indices[] = {
		SETTINGS_START,
		SETTINGS_START + 1,
		SETTINGS_START + 2,
		SETTINGS_START + 3,
	};

	/* Draw Settings Info */
	v_pen = PEN_NO_RECOLOUR;
	video_print_centred_text(
		g_strings[SETTINGS_SUBTITLE], TITLE_Y * LINE_P_H);

	for (u8 i = 0; i < 4; ++i) {
		v_pen = PEN_3;
		video_print_text(g_strings[string_indices[i]], SETTINGS_X, y);

		if (g_options & option_indices[i])
			str = " ON";
		else
			str = "OFF";

		v_pen = PEN_2;
		video_print_text(str, TOGGLE_X * LINE_P_W, y);

		y += LINE_P_H * 2;
	}

	y = RETURN_Y * LINE_P_H;
	v_pen = PEN_3;
	video_print_centred_text(g_strings[RETURN_TEXT], y);
}
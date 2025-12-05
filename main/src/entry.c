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

#include "entry.h"

/* Insert a score into the highscore table */
void entry_insert(const char *initials, const u32 score, const u8 pos) {

	g_hiscores[pos].score = score;
	utils_strcpy(g_hiscores[pos].initials, initials);
	g_hiscores[pos].width = utils_get_str_width(score);
}

void entry_start(void) {

	/* If no hiscore reached, skip entirely */
	if (g_game.score <= g_hiscores[HISCORES_SZ - 1].score)
		return;

	video_full_clear();
	cpct_waitVSYNC();

	/* Draw congratulations text */
	v_pen = PEN_3;
	u8 y = CONGRATS_Y * LINE_P_H;
	video_print_centred_text(g_strings[CONGRATS_TEXT], y);

	v_pen = PEN_2;
	video_print_centred_text(
		g_strings[CONGRATS_TEXT + 1], y += (LINE_P_H * 3));
	video_print_centred_text(
		g_strings[CONGRATS_TEXT + 2], y += (LINE_P_H * 2));
	video_reset_palette();

	y = INITIALS_Y * LINE_P_H;

	u8 len = 0;
	char name[4] = "";
	while (len < 3) {

		cpct_scanKeyboard();

		/* Handle delete */
		if (cpct_isKeyPressed(Key_Del) && len > 0) {
			len--;
			name[len] = 0;
			while (cpct_isKeyPressed(Key_Del))
				cpct_scanKeyboard();
			continue;
		}

		/* Detect A–Z */
		for (u8 i = 0; i < KEY_MAPPING_SZ; ++i) {
			if (cpct_isKeyPressed(u_key_mapping[i].key)) {
				name[len++] = u_key_mapping[i].ascii;
				name[len] = 0;

				/* Debounce */
				while (cpct_isKeyPressed(u_key_mapping[i].key))
					cpct_scanKeyboard();
				break;
			}
		}

		cpct_waitVSYNC();
		v_pen = PEN_3;
		video_print_text(g_strings[INITIALS_TEXT], 36, y);
		video_print_text(name, 36, y);
	}

	/* Insert high score */
	name[3] = '\0';
	entry_insert(name, g_game.score, HISCORES_SZ - 1);
	utils_sort_hiscores();

	video_full_clear();
}

void entry_stop(void) {
}
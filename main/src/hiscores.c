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

#include "hiscores.h"

/* Private Functions */
static void hiscores_draw(void);

/* Start Hiscores Screen */
void hiscores_start(void) {

	/* Draw the Screen */
	video_clear_centre();
	hiscores_draw();

	/* Wait for a Keypress */
	bool kp = false;
	while (!kp)
		kp = cpct_isAnyKeyPressed();
}

/* Stop Hiscores Screen */
void hiscores_stop(void) {

	m_menu_input_enabled = true;
}

/* Draw Hiscore Table */
static void hiscores_draw(void) {

	/* Draw each line of the Hi Score table */
	v_pen = PEN_NO_RECOLOUR;
	video_print_centred_text(
		g_strings[HISCORES_SUBTITLE], TITLE_Y * LINE_P_H);

	/* Remember this is always sorted in ascending order */
	char buf[7];
	u8 y = (SCORES_Y * LINE_P_H) - 4;
	for (u8 i = 0; i < HISCORES_SZ; i++) {

		/* Display each line of the Hi-Score table */
		v_pen = PEN_2;
		video_print_text(g_hiscores[i].initials, SCORES_X, y);
		video_print_text(
			g_strings[HISCORES_START + 1], SCORES_X + 23, y);

		utils_itoa_6(buf, g_hiscores[i].score);

		video_print_text(
			buf, (SCORES_X + 43) - (g_hiscores[i].width * 2), y);

		v_pen = PEN_3;
		video_print_text(g_strings[HISCORES_START], SCORES_X + 7, y);
		y += (LINE_P_H * 2);
	}

	/* Last Pen set was Pen 2 */
	video_print_centred_text(g_strings[RETURN_TEXT], RETURN_Y * LINE_P_H);
}
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

#include "between.h"

/* Private Functions */
static void between_draw(void);
static void between_interrupt(void);

/* Start a Transition "Between" Screen */
void between_start(void) {

	/* Clear the Screen */
	video_blank_screen();
	video_clear_screen();

	/* Make sure the Timer Interrupt is off */
	g_clock_on = false;

	/* Draw Screen */
	between_draw();

	/* Set up Clock Interrupt */
	g_clock_on = false;
	utils_reset_clock();
	video_reset_timers();
	cpct_waitVSYNC();
	cpct_setInterruptHandler(between_interrupt);

	/* Start Clock */
	u16 duration = 5;
	g_clock_on = true;

	utils_clear_input();

	/* Display for a number of seconds or until a keypress */
	bool kp = false;
	while ((!kp) && (g_clock.s < duration)) {

		cpct_waitVSYNC();
		utils_clock_tick();
		if (cpct_isAnyKeyPressed())
			kp = true;
	}

	utils_clear_input();

	/* Stop Clock */
	g_clock_on = false;
}

/* Stop the Transition "Between" Screen */
void between_stop(void) {

	cpct_removeInterruptHandler();
	utils_reset_clock();
}

/* Draw the Grid Graphic */
static void between_draw(void) {

	/* Load and display the Transition Screen */
	utils_load("GETREADYSCR", VIDEO_MEM_START);

	char level_str[] = "LEVEL 0";
	level_str[6] = '0' + g_game.level;

	/* Add the Level Data */
	v_pen = PEN_3;
	video_print_centred_text(level_str, ((INBETWEEN_Y - 1) * LINE_P_H) + 4);
	video_print_centred_text(
		g_strings[GET_READY_TEXT], (INBETWEEN_Y * LINE_P_H) + 4);
}

static void between_interrupt(void) {

	/* Data for Colour Rasters */
	static const u8 palette_mc[6][4] = {
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_ORANGE},
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_ORANGE},
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_ORANGE},
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_ORANGE},
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_BRIGHT_WHITE},
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_BRIGHT_WHITE},
	};

	if (v_int_idx == 0) {
		if (++v_frame_c == FC_MAX)
			v_frame_c = 0;
	}

	if (v_int_idx == 2)
		cpct_scanKeyboard_if();

	/* Adjust Raster Positions */
	cpct_setPalette(palette_mc[v_int_idx], sizeof(palette_mc[v_int_idx]));

	if (++v_int_idx == 6)
		v_int_idx = 0;
}
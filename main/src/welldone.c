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

#include "welldone.h"

/* Private Functions */
static void welldone_draw(void);
static void welldone_interrupt(void);

/* Start a Transition "Welldone" Screen */
void welldone_start(void) {

	u16 duration;
	bool kp = false;

	/* Clear the Screen */
	video_blank_screen();
	video_clear_screen();

	/* Make sure the Timer Interrupt is off */
	g_clock_on = false;

	/* Draw Screen */
	welldone_draw();

	/* Set up Clock Interrupt */
	g_clock_on = false;
	utils_reset_clock();
	video_reset_timers();
	cpct_waitVSYNC();
	cpct_setInterruptHandler(welldone_interrupt);

	/* Start Clock */
	duration = 5;
	g_clock_on = true;

	utils_clear_input();

	/* Display for a number of seconds or until a keypress */
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
void welldone_stop(void) {

	cpct_removeInterruptHandler();
	utils_reset_clock();
}

/* Draw the Grid Graphic */
static void welldone_draw(void) {

	char level_str[2];

	level_str[0] = '0' + g_game.level;
	level_str[1] = '\0';

	/* Load and display the Transition Screen */
	utils_load("WELLDONEBIN", VIDEO_MEM_START);

	v_pen = PEN_3;
	video_print_centred_text("Level Complete!", INBETWEEN_Y * LINE_P_H);
}

static void welldone_interrupt(void) {

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
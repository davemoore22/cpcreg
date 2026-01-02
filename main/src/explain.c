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

#include "explain.h"

/* Private Functions */
static void explain_draw(void);
static void explain_interrupt(void);

/* Start a Transition "Between" Screen */
void explain_start(void) {

	/* Clear the Screen */
	video_blank_screen();
	video_clear_screen();

	/* Make sure the Timer Interrupt is off */
	g_clock_on = false;

	/* Draw Screen */
	explain_draw();

	/* Set up Clock Interrupt */
	g_clock_on = false;
	utils_reset_clock();
	video_reset_timers();
	cpct_waitVSYNC();
	v_int_idx = 0;
	cpct_setInterruptHandler(explain_interrupt);

	/* Start Clock */
	u16 duration = 60;
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
void explain_stop(void) {

	cpct_removeInterruptHandler();
	video_blank_screen();

	utils_reset_clock();
}

/* Draw the Grid Graphic */
static void explain_draw(void) {

	static const u8 palette_e[4] = {
		HW_BLACK,
		HW_RED,
		HW_BRIGHT_RED,
		HW_PASTEL_YELLOW,
	};

	/* Load and display the Transition Screen */
	utils_load("EXPLAIN SCR", VIDEO_MEM_START);

	cpct_setPalette(palette_e, sizeof(palette_e));
}

static void explain_interrupt(void) {

	if (v_int_idx == 0) {
		if (++v_frame_c == FC_MAX)
			v_frame_c = 0;
	}

	if (v_int_idx == 2)
		cpct_scanKeyboard_if();

	if (++v_int_idx == 6)
		v_int_idx = 0;
}
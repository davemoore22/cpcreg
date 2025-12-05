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

#include "titles.h"

/* Private Functions */
static void presents_draw(void);

/* Start the Title Screen */
void presents_start(void) {

  u16 duration;
  bool kp = false;

  video_clr_scr();
  video_reset_pal();

  /* Clear the Screen */
  video_blk_scr();
  video_clr_scr();

  /* Make sure the Timer Interrupt is off */
  g_clock_on = false;

  /* Draw Screen */
  presents_draw();
  video_reset_pal_presents();

  /* Set up Clock Interrupt */
  g_clock_on = false;
  utils_reset_clock();
  cpct_setInterruptHandler(utils_clock_interrupt);

  /* Start Clock */
  duration = 3;
  g_clock_on = true;

  /* Display for a number of seconds or until a keypress */
  while ((!kp) && (g_clock.s < duration)) {

    /* Check for a keypress */
    kp = cpct_isAnyKeyPressed();
  }

  /* Stop Clock */
  g_clock_on = false;
}

/* Stop the Transition "Between" Screen */
void presents_stop(void) {

  video_wipe_scr(true);
  video_blk_scr();
  utils_reset_clock();
}

/* Draw the Grid Graphic */
static void presents_draw(void) {

  /* Decompresse image data from a compressed file onto the screen */
  utils_load("PRESENTSSCR", VIDEO_MEM_START);
}
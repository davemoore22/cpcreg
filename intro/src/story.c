/*
 * Reginald and the She Vampires for the Amstrad CPC
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

#include "story.h"

/* Private Functions */
static void story_draw(void);

/* Start the Title Screen */
void story_start(void) {

  u8 duration;
  bool kp = false;
  u8 page = 0;

  /* Clear the Screen */
  video_blk_scr();
  video_clr_scr();

  /* Make sure the Timer Interrupt is off */
  g_clock_on = false;

  /* Draw Screen */
  story_draw();
  video_reset_pal();

  /* Initialise Music */
  cpct_akp_musicInit(g_music);

  /* Set up Clock Interrupt */
  g_clock_on = false;
  utils_reset_clock();
  video_reset_timers();
  cpct_setInterruptHandler(story_interrupt);

  /* Start Clock */
  duration = 9;
  g_clock_on = true;

  while (!kp) {

    // Draw the page
    instruct_draw(page);

    // Reset page timer
    utils_reset_clock();

    // Wait for either timeout OR keypress
    while (g_clock.s < duration) {
      cpct_waitVSYNC();

      if (cpct_isAnyKeyPressed()) {
        kp = true; // mark for exit
        break;     // break inner loop
      }
    }

    if (kp)
      break; // break outer loop too

    // Advance to next page
    page++;
    if (page == 3)
      page = 0;
  }

  /* Stop Clock */
  g_clock_on = false;
}

/* Stop the Transition "Between" Screen */
void story_stop(void) {

  video_wipe_scr(true);
  video_blk_scr();
  cpct_akp_stop();
  cpct_removeInterruptHandler();
  utils_reset_clock();
}

/* Draw the Grid Graphic */
static void story_draw(void) {

  /* Decompresse image data from a compressed file onto the screen */
  utils_load("STORY   SCR", VIDEO_MEM_START);
}

/* Interrupt for Rasters and Colour Cycling etc on the Title Screen */
void story_interrupt(void) {
  /* Scan Keyboard every 1/50 of a second */
  if (v_int_idx == 1)
    cpct_scanKeyboard_if();

  /* Play Music */
  if (v_int_idx == 4)
    cpct_akp_musicPlay();

  /* Increase the Counters */
  v_int_idx = ++v_int_idx % 6;
  v_frame_c = ++v_frame_c % 50;

  /* Call the Clock */
  utils_clock_interrupt();
}
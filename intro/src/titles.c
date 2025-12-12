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

#include "titles.h"

/* Scrolling Text Buffer (with space for /0 at end!) */
static char t_scroller[41];

/* Private Functions */
static void titles_draw(void);

/* Start the Title Screen */
void titles_start(void) {

  u16 duration, scroller_size;
  bool kp = false, scrolled;

  video_clr_scr();
  video_reset_pal();

  /* Clear the Screen */
  video_blk_scr();
  video_clr_scr();

  /* Make sure the Timer Interrupt is off */
  g_clock_on = false;

  /* Draw Screen */
  titles_draw();
  video_reset_pal();

  /* Initialise Music */
  cpct_akp_musicInit(g_music);

  /* Set up Clock Interrupt */
  g_clock_on = false;
  utils_reset_clock();
  video_reset_timers();
  cpct_setInterruptHandler(titles_interrupt);

  /* Start Clock */
  duration = 300;
  g_clock_on = true;
  scroller_size = SCROLLER_TEXT_LEN;
  scrolled = false;

  /* Display for a number of seconds or until a keypress */
  while ((!kp) && (g_clock.s < duration)) {

    /* Check for a keypress */
    kp = cpct_isAnyKeyPressed();

    /* Do scrolling text */
    if (g_clock.ms % 100 == 0) {

      utils_rotate_str_fixed(g_strings[SCROLLING_TITLE_TEXT], 1, scroller_size);
      utils_str_cpy_n(t_scroller, g_strings[SCROLLING_TITLE_TEXT], 40);
      video_print(t_scroller, 0, 192);
    }
  }

  /* Stop Clock */
  g_clock_on = false;
}

/* Stop the Transition "Between" Screen */
void titles_stop(void) {

  video_wipe_scr(true);
  video_blk_scr();
  cpct_akp_stop();
  cpct_removeInterruptHandler();
  utils_reset_clock();
}

/* Draw the Grid Graphic */
static void titles_draw(void) {

  /* Decompresse image data from a compressed file onto the screen */
  utils_load("TITLE   SCR", VIDEO_MEM_START);

  /* Setup Initial Scroll Text */
  utils_str_cpy_n(t_scroller, g_strings[SCROLLING_TITLE_TEXT], 40);
  video_print(t_scroller, 0, 192);
}

/* Interrupt for Rasters and Colour Cycling etc on the Title Screen */
void titles_interrupt(void) {

  /* Data for Colour Rasters */
  static const u8 palette[6][4] = {
      {HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PINK},
      {HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PINK},
      {HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_BRIGHT_RED},
      {HW_BLACK, HW_RED, HW_BRIGHT_YELLOW, HW_ORANGE},
      {HW_BLACK, HW_RED, HW_BRIGHT_YELLOW, HW_ORANGE},
      {HW_BLACK, HW_RED, HW_WHITE, HW_BRIGHT_WHITE}};

  static const u8 story_palette[4] = {HW_BLACK, HW_BLUE, HW_BRIGHT_BLUE,
                                      HW_BRIGHT_WHITE};

  /* Scan Keyboard every 1/50 of a second */
  if (v_int_idx == 1)
    cpct_scanKeyboard_if();

  /* Play Music */
  if (v_int_idx == 4)
    cpct_akp_musicPlay();

  cpct_setPalette(palette[v_int_idx], sizeof(palette[v_int_idx]));

  /* Increase the Counters */
  v_int_idx = ++v_int_idx % 6;
  v_frame_c = ++v_frame_c % 50;

  /* Call the Clock */
  utils_clock_interrupt();
}

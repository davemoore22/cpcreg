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
 * * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#include "video.h"

/* Interrupt Indexes */
u8 v_int_idx = 0;
u8 v_pal_idx = 0;
u8 v_frame_c = 0;

/* Initialise Video and Clear the Screen */
void video_init(void) {

  /* Mode 1 */
  cpct_setVideoMode(1);
  cpct_waitVSYNCStart();
  cpct_clearScreen_f64(0);
}

/* Reset all Screen Pens to Black, effectively blanking the screen */
void video_blk_scr(void) {

  static const u8 blank_pal[16] = {HW_BLACK, HW_BLACK, HW_BLACK, HW_BLACK,
                                   HW_BLACK, HW_BLACK, HW_BLACK, HW_BLACK,
                                   HW_BLACK, HW_BLACK};

  cpct_removeInterruptHandler();
  cpct_waitVSYNC();
  cpct_setPalette(blank_pal, sizeof(blank_pal));
  cpct_setBorder(HW_BLACK);
}

/* Wipe the Screen in a Direction */
void video_wipe_scr(bool dir) {

  u8 *v_pos;

  if (dir) {

    /* Wipe to the right */
    for (u8 x = 0; x < 80; x++) {
      if (x % 2 == 0) {
        cpct_waitVSYNC();
        v_pos = video_get_pos(x, 0);
        cpct_drawSolidBox(v_pos, 0, 2, 200);
      }
    }
  } else {

    /* Wipe to the left */
    for (u8 x = 78; x > 0; x--) {
      if (x % 2 == 0) {
        cpct_waitVSYNC();
        v_pos = video_get_pos(x, 0);
        cpct_drawSolidBox(v_pos, 0, 2, 200);
      }
    }
  }
}

/* Clear the Screen to Pen 0 */
void video_clr_scr(void) {

  cpct_waitVSYNCStart();
  cpct_clearScreen_f64(0);
}

/* Reset the Palette back to Normal Mode 1 Colours */
void video_reset_pal(void) {

  static const u8 normal_pal[4] = {HW_BLACK, HW_BLUE, HW_BRIGHT_BLUE,
                                   HW_BRIGHT_WHITE};

  cpct_waitVSYNC();
  cpct_setPalette(normal_pal, sizeof(normal_pal));
  cpct_setBorder(HW_BLACK);
}

/* Reset the Palette back to Alternate Mode 1 Colours */
void video_reset_pal_presents(void) {

  static const u8 normal_pal[4] = {HW_BLACK, HW_MAGENTA, HW_BRIGHT_MAGENTA,
                                   HW_PASTEL_MAGENTA};

  cpct_waitVSYNC();
  cpct_setPalette(normal_pal, sizeof(normal_pal));
  cpct_setBorder(HW_BLACK);
}

/* Wait for a specified number of VSYNCs */
void video_wait_VSYNC(u8 n) {

  do {
    cpct_waitVSYNC();
    if (--n) {
      __asm__("halt");
      __asm__("halt");
    }
  } while (n);
}

/* Get Screen Position from Byte Coordinates */
inline u8 *video_get_pos(const u8 x, const u8 y) {

  return cpct_getScreenPtr(CPCT_VMEM_START, x, y);
}

/* Reset Interrupt Timers */
void video_reset_timers(void) {

  v_int_idx = 0;
  v_pal_idx = 0;
  v_frame_c = 0;
}

/* Print a string using the Font sprites but centered horizontally */
void video_print_c(const char *str, const u8 y) {

  u8 x = (40) - (utils_str_len(str) * 2) / 2;

  video_print(str, x, y);
}

/* Print a string using the Font sprites (optionally use to len chars)*/
void video_print(const char *str, const u8 x, const u8 y) {

  u8 *v_pos;
  u8 cx = x, cy = y, idx, count = 0;
  u16 i = 0, rplc;

  /* Iterate the through string */
  while (str[i] != '\0') {

    /* Tilemap for Text starts at ASCII 32 (Space) */
    idx = (int)str[i] - 32;
    v_pos = video_get_pos(cx, cy);

    /* Font is 8 x 8 pixels (2 x 8 bytes) - is Ink 2/3 in
     * Sprite */
    cpct_drawSprite(font_ts[idx], v_pos, 2, 8);

    cx = cx + LINE_P_W;

    i++;
  }
}

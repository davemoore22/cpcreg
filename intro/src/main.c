/*
 * Reginald and the She Vampires for the Amstrad CPC
 * Copyright (C) 2026 davy moore
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

#include "main.h"

/* Main Application Entry Point */
void main(void) {

  u16 firmware;

  /* Note that Firmware is disabled */
  firmware = cpct_disableFirmware();

  /* Initialise Display */
  video_init();

  /* Show Pressents Screen */
  presents_start();
  presents_stop();

  /* Show Title Screen */
  titles_start();
  titles_stop();

  /* Story */
  story_start();
  story_stop();

  /* Guide */
  guide_start();
  guide_stop();

  /* Reenable Firmware */
  cpct_reenableFirmware(firmware);
}
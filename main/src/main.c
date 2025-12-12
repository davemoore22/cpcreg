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

#pragma codeseg CODE

#include "main.h"

void main(void) {

	cpct_disableFirmware();
	cpct_setStackLocation(STACK_LOC);
	start();
}

void start(void) {

	bool quit = false;
	bool redraw = true;
	cpct_keyID key;

	game_setup();
	video_init();

	/* Initial draw whilst blanked */
	menu_draw_from_disc(true);

	menu_start();

	while (!quit) {

		key = menu_poll_input();

		if (key != 0xFF) { /*non-blocking check */

			quit = (key == Key_0);

			if (key == Key_1) {
				video_clear_centre();
				redefine_start();
				redefine_stop();
				menu_init_walkers();
				redraw = true;
			}

			if (key == Key_2) {
				video_clear_centre();
				settings_start();
				settings_stop();
				menu_init_walkers();
				redraw = true;
			}

			if (key == Key_3) {
				video_clear_centre();
				hiscores_start();
				hiscores_stop();
				menu_init_walkers();
				redraw = true;
			}

			if (key == Key_4 && m_toggle_cooldown == 0) {
				g_options ^= OPT_CHARACTER;
				menu_draw_title();
				video_flash_border(TRIPLET_ORANGE);
				redraw = false;
				m_toggle_cooldown = 10;
			}

			if (key == Key_5) {
				menu_stop();
				explain_start();
				explain_stop();
				menu_draw_from_disc(true);
				menu_start();
				redraw = false;
			}

			if (key == Key_9) {
				menu_stop();
				game_start();
				game_stop();

				menu_draw_from_disc(true);
				menu_start();
				redraw = false;
			}

			if (key == Key_Tab && g_options & OPT_CHEAT) {
				menu_stop();
				victory_start();
				victory_stop();

				menu_draw_from_disc(true);
				menu_start();
				redraw = false;
			}

			if (!quit && redraw)
				menu_draw_from_disc(false);
		}

		/* Always animate walkers */
		menu_draw_walkers();
	}

	menu_stop();
}
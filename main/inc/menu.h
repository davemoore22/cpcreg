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

#pragma once

#include "main.h"

extern u8 m_toggle_cooldown;
extern bool m_menu_input_enabled;

/* Public Functions */
void menu_start(void);
void menu_draw_from_disc(const bool load_bg);
void menu_stop(void);
void menu_interrupt(void);
void menu_draw_centre(void);
void menu_draw_title(void);
void menu_draw_walkers(void);
cpct_keyID menu_poll_input(void);
void menu_init_walkers(void);
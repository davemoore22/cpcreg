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

/* Library Includes */
#include <cpctelera.h>
#include <stdbool.h> /* For Bool Type */

/* Top Level Includes */
#include "lib/defines.h"
#include "lib/enums.h"
#include "lib/macros.h"
#include "lib/types.h"

/* Library Includes */
#include "lib/memory.h"
#include "lib/utilities.h"
#include "lib/video.h"

/* Data Includes */
#include "dat/fonts.h"
#include "dat/images.h"
#include "dat/levels.h"
#include "dat/sfx.h"
#include "dat/strings.h"
#include "dat/tiles.h"

/* Game Parts */
#include "between.h"
#include "defeat.h"
#include "entry.h"
#include "explain.h"
#include "game.h"
#include "hiscores.h"
#include "menu.h"
#include "monster.h"
#include "redefine.h"
#include "settings.h"
#include "victory.h"
#include "welldone.h"

void start(void);
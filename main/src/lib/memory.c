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

#include "lib/memory.h"

/* Fixed Memory Data Structures */

/* Disc File Loading Table */
__at(DISK_TABLE_LOC) u8 g_disk_table[256];

/* Suppress incorrect error reporting in VSCode with the next line */
#ifdef __INTELLISENSE__
#pragma diag_suppress 169
#pragma diag_suppress 99
#pragma diag_suppress 65
#pragma diag_suppress 130
#endif

/* Sets the transparent mask table for color 0, mode 1 */
cpctm_createTransparentMaskTable(v_mask_table, MASK_TABLE_LOC, M1, 0);

/* And reenable warnings (can ignore any other errors reported in this file) */
#ifdef __INTELLISENSE__
#pragma diag_default 169
#pragma diag_default 99
#pragma diag_default 65
#pragma diag_default 130
#endif

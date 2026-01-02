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

#pragma once

#include "main.h"

/* Fixed Memory Data Areas */
__at(DISK_TABLE_LOC) extern u8 g_disk_table[256];

/* Mask Table */
cpctm_declareMaskTable(v_mask_table);

/* FDC Tools SDCC4.5 (via https://www.julien-nevo.com/arkos/fdc-tools/) */

#ifdef __INTELLISENSE__
#pragma diag_suppress 130
#endif
extern void asm_load_file(u8 *fileName, u8 *destBuffer,
                          u8 *sectorTable) __z88dk_callee;
#ifdef __INTELLISENSE__
#pragma diag_default 130
#endif
extern void asm_fdc_off(void);
extern void asm_fdc_on(void);
extern u8 detect_128k(void);

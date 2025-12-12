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

#pragma once

#include "main.h"

/* Global Variables */
extern const u8 l_next_screen[6][4][12];
extern const screen_bg_t level_bgs[6][12];

extern const u8 palette_level_1[6][4];
extern const u8 palette_level_2[6][4];
extern const u8 palette_level_3[6][4];
extern const u8 palette_level_4[6][4];
extern const u8 palette_level_5[6][4];
extern const u8 palette_level_6[6][4];

// extern const u8 l_minimap_masks[6][12];

// Declaration of the compressed arrays
extern const unsigned char l_level_1_fg[404];
extern const unsigned char l_level_2_fg[443];
extern const unsigned char l_level_3_fg[349];
extern const unsigned char l_level_4_fg[389];
extern const unsigned char l_level_5_fg[445];
extern const unsigned char l_level_6_fg[160];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define l_level_1_fg_end (l_level_1_fg + 404 - 1)

// Compressed and uncompressed sizes
#define l_level_1_fg_size_z 404
#define l_level_1_fg_size 1728

// File 'out/level_2_fg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/level2-fg.bin' ]
// Uncompressed:     1728 bytes
// Compressed:       443 bytes
// Space saved:      1285 bytes
//

#ifndef l_level_2_fg_443_H
#define l_level_2_fg_443_H

// Address of the latest byte of the compressed array (for unpacking purposes)
#define l_level_2_fg_end (l_level_2_fg + 443 - 1)

// Compressed and uncompressed sizes
#define l_level_2_fg_size_z 443
#define l_level_2_fg_size 1728

#endif

// File 'out/level_3_fg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/level3-fg.bin' ]
// Uncompressed:     1728 bytes
// Compressed:       349 bytes
// Space saved:      1379 bytes
//

#ifndef l_level_3_fg_349_H
#define l_level_3_fg_349_H

// Address of the latest byte of the compressed array (for unpacking purposes)
#define l_level_3_fg_end (l_level_3_fg + 349 - 1)

// Compressed and uncompressed sizes
#define l_level_3_fg_size_z 349
#define l_level_3_fg_size 1728

#endif

// File 'out/l_level_4_fg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/level4-fg.bin' ]
// Uncompressed:     1728 bytes
// Compressed:       389 bytes
// Space saved:      1339 bytes
//

#ifndef l_level_4_fg_389_H
#define l_level_4_fg_389_H

// Address of the latest byte of the compressed array (for unpacking purposes)
#define l_level_4_fg_end (l_level_4_fg + 389 - 1)

// Compressed and uncompressed sizes
#define l_level_4_fg_size_z 389
#define l_level_4_fg_size 1728
#endif

// File 'out/l_level_5_fg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/level5-fg.bin' ]
// Uncompressed:     1728 bytes
// Compressed:       445 bytes
// Space saved:      1283 bytes
//

#ifndef l_level_5_fg_445_H
#define l_level_5_fg_445_H

// Address of the latest byte of the compressed array (for unpacking purposes)
#define l_level_5_fg_end (l_level_5_fg + 445 - 1)

// Compressed and uncompressed sizes
#define l_level_5_fg_size_z 445
#define l_level_5_fg_size 1728

#endif

// File 'out/l_level_6_fg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/level6-fg.bin' ]
// Uncompressed:     1728 bytes
// Compressed:       160 bytes
// Space saved:      1568 bytes
//

#ifndef l_level_6_fg_160_H
#define l_level_6_fg_160_H

// Address of the latest byte of the compressed array (for unpacking purposes)
#define l_level_6_fg_end (l_level_6_fg + 160 - 1)

// Compressed and uncompressed sizes
#define l_level_6_fg_size_z 160
#define l_level_6_fg_size 1728

#endif

#ifndef level_1_0_bg_47_H
#define level_1_0_bg_47_H

// Declaration of the compressed array
extern const unsigned char level_1_0_bg[47];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_0_bg_end (level_1_0_bg + 47 - 1)

// Compressed and uncompressed sizes
#define level_1_0_bg_size_z 47
#define level_1_0_bg_size 144

#endif

// File 'out/level_1_1_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-1-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       40 bytes
// Space saved:      104 bytes
//

#ifndef level_1_1_bg_40_H
#define level_1_1_bg_40_H

// Declaration of the compressed array
extern const unsigned char level_1_1_bg[40];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_1_bg_end (level_1_1_bg + 40 - 1)

// Compressed and uncompressed sizes
#define level_1_1_bg_size_z 40
#define level_1_1_bg_size 144

#endif

// File 'out/level_1_2_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-2-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       31 bytes
// Space saved:      113 bytes
//

#ifndef level_1_2_bg_31_H
#define level_1_2_bg_31_H

// Declaration of the compressed array
extern const unsigned char level_1_2_bg[31];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_2_bg_end (level_1_2_bg + 31 - 1)

// Compressed and uncompressed sizes
#define level_1_2_bg_size_z 31
#define level_1_2_bg_size 144

#endif

// File 'out/level_1_3_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-3-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       49 bytes
// Space saved:      95 bytes
//

#ifndef level_1_3_bg_49_H
#define level_1_3_bg_49_H

// Declaration of the compressed array
extern const unsigned char level_1_3_bg[49];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_3_bg_end (level_1_3_bg + 49 - 1)

// Compressed and uncompressed sizes
#define level_1_3_bg_size_z 49
#define level_1_3_bg_size 144

#endif

// File 'out/level_1_4_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-4-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       40 bytes
// Space saved:      104 bytes
//

#ifndef level_1_4_bg_40_H
#define level_1_4_bg_40_H

// Declaration of the compressed array
extern const unsigned char level_1_4_bg[40];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_4_bg_end (level_1_4_bg + 40 - 1)

// Compressed and uncompressed sizes
#define level_1_4_bg_size_z 40
#define level_1_4_bg_size 144

#endif

// File 'out/level_1_5_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-5-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       46 bytes
// Space saved:      98 bytes
//

#ifndef level_1_5_bg_46_H
#define level_1_5_bg_46_H

// Declaration of the compressed array
extern const unsigned char level_1_5_bg[46];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_5_bg_end (level_1_5_bg + 46 - 1)

// Compressed and uncompressed sizes
#define level_1_5_bg_size_z 46
#define level_1_5_bg_size 144

#endif

// File 'out/level_1_6_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-6-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       43 bytes
// Space saved:      101 bytes
//

#ifndef level_1_6_bg_43_H
#define level_1_6_bg_43_H

// Declaration of the compressed array
extern const unsigned char level_1_6_bg[43];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_6_bg_end (level_1_6_bg + 43 - 1)

// Compressed and uncompressed sizes
#define level_1_6_bg_size_z 43
#define level_1_6_bg_size 144

#endif

// File 'out/level_1_7_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-7-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       33 bytes
// Space saved:      111 bytes
//

#ifndef level_1_7_bg_33_H
#define level_1_7_bg_33_H

// Declaration of the compressed array
extern const unsigned char level_1_7_bg[33];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_7_bg_end (level_1_7_bg + 33 - 1)

// Compressed and uncompressed sizes
#define level_1_7_bg_size_z 33
#define level_1_7_bg_size 144

#endif

// File 'out/level_1_8_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-8-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       40 bytes
// Space saved:      104 bytes
//

#ifndef level_1_8_bg_40_H
#define level_1_8_bg_40_H

// Declaration of the compressed array
extern const unsigned char level_1_8_bg[40];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_8_bg_end (level_1_8_bg + 40 - 1)

// Compressed and uncompressed sizes
#define level_1_8_bg_size_z 40
#define level_1_8_bg_size 144

#endif

// File 'out/level_1_9_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-9-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       45 bytes
// Space saved:      99 bytes
//

#ifndef level_1_9_bg_45_H
#define level_1_9_bg_45_H

// Declaration of the compressed array
extern const unsigned char level_1_9_bg[45];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_9_bg_end (level_1_9_bg + 45 - 1)

// Compressed and uncompressed sizes
#define level_1_9_bg_size_z 45
#define level_1_9_bg_size 144

#endif

// File 'out/level_1_10_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-10-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       46 bytes
// Space saved:      98 bytes
//

#ifndef level_1_10_bg_46_H
#define level_1_10_bg_46_H

// Declaration of the compressed array
extern const unsigned char level_1_10_bg[46];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_10_bg_end (level_1_10_bg + 46 - 1)

// Compressed and uncompressed sizes
#define level_1_10_bg_size_z 46
#define level_1_10_bg_size 144

#endif

// File 'out/level_1_11_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/1-11-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       34 bytes
// Space saved:      110 bytes
//

#ifndef level_1_11_bg_34_H
#define level_1_11_bg_34_H

// Declaration of the compressed array
extern const unsigned char level_1_11_bg[34];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_1_11_bg_end (level_1_11_bg + 34 - 1)

// Compressed and uncompressed sizes
#define level_1_11_bg_size_z 34
#define level_1_11_bg_size 144

#endif

// File 'out/level_2_0_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-0-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       28 bytes
// Space saved:      116 bytes
//

#ifndef level_2_0_bg_28_H
#define level_2_0_bg_28_H

// Declaration of the compressed array
extern const unsigned char level_2_0_bg[28];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_0_bg_end (level_2_0_bg + 28 - 1)

// Compressed and uncompressed sizes
#define level_2_0_bg_size_z 28
#define level_2_0_bg_size 144

#endif

// File 'out/level_2_1_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-1-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       20 bytes
// Space saved:      124 bytes
//

#ifndef level_2_1_bg_20_H
#define level_2_1_bg_20_H

// Declaration of the compressed array
extern const unsigned char level_2_1_bg[20];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_1_bg_end (level_2_1_bg + 20 - 1)

// Compressed and uncompressed sizes
#define level_2_1_bg_size_z 20
#define level_2_1_bg_size 144

#endif

// File 'out/level_2_2_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-2-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       26 bytes
// Space saved:      118 bytes
//

#ifndef level_2_2_bg_26_H
#define level_2_2_bg_26_H

// Declaration of the compressed array
extern const unsigned char level_2_2_bg[26];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_2_bg_end (level_2_2_bg + 26 - 1)

// Compressed and uncompressed sizes
#define level_2_2_bg_size_z 26
#define level_2_2_bg_size 144

#endif

// File 'out/level_2_3_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-3-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       38 bytes
// Space saved:      106 bytes
//

#ifndef level_2_3_bg_38_H
#define level_2_3_bg_38_H

// Declaration of the compressed array
extern const unsigned char level_2_3_bg[38];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_3_bg_end (level_2_3_bg + 38 - 1)

// Compressed and uncompressed sizes
#define level_2_3_bg_size_z 38
#define level_2_3_bg_size 144

#endif

// File 'out/level_2_4_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-4-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       37 bytes
// Space saved:      107 bytes
//

#ifndef level_2_4_bg_37_H
#define level_2_4_bg_37_H

// Declaration of the compressed array
extern const unsigned char level_2_4_bg[37];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_4_bg_end (level_2_4_bg + 37 - 1)

// Compressed and uncompressed sizes
#define level_2_4_bg_size_z 37
#define level_2_4_bg_size 144

#endif

// File 'out/level_2_5_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-5-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       28 bytes
// Space saved:      116 bytes
//

#ifndef level_2_5_bg_28_H
#define level_2_5_bg_28_H

// Declaration of the compressed array
extern const unsigned char level_2_5_bg[28];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_5_bg_end (level_2_5_bg + 28 - 1)

// Compressed and uncompressed sizes
#define level_2_5_bg_size_z 28
#define level_2_5_bg_size 144

#endif

// File 'out/level_2_6_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-6-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       27 bytes
// Space saved:      117 bytes
//

#ifndef level_2_6_bg_27_H
#define level_2_6_bg_27_H

// Declaration of the compressed array
extern const unsigned char level_2_6_bg[27];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_6_bg_end (level_2_6_bg + 27 - 1)

// Compressed and uncompressed sizes
#define level_2_6_bg_size_z 27
#define level_2_6_bg_size 144

#endif

// File 'out/level_2_7_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-7-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       43 bytes
// Space saved:      101 bytes
//

#ifndef level_2_7_bg_43_H
#define level_2_7_bg_43_H

// Declaration of the compressed array
extern const unsigned char level_2_7_bg[43];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_7_bg_end (level_2_7_bg + 43 - 1)

// Compressed and uncompressed sizes
#define level_2_7_bg_size_z 43
#define level_2_7_bg_size 144

#endif

// File 'out/level_2_8_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-8-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       54 bytes
// Space saved:      90 bytes
//

#ifndef level_2_8_bg_54_H
#define level_2_8_bg_54_H

// Declaration of the compressed array
extern const unsigned char level_2_8_bg[54];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_8_bg_end (level_2_8_bg + 54 - 1)

// Compressed and uncompressed sizes
#define level_2_8_bg_size_z 54
#define level_2_8_bg_size 144

#endif

// File 'out/level_2_9_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-9-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       23 bytes
// Space saved:      121 bytes
//

#ifndef level_2_9_bg_23_H
#define level_2_9_bg_23_H

// Declaration of the compressed array
extern const unsigned char level_2_9_bg[23];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_9_bg_end (level_2_9_bg + 23 - 1)

// Compressed and uncompressed sizes
#define level_2_9_bg_size_z 23
#define level_2_9_bg_size 144

#endif

// File 'out/level_2_10_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-10-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       31 bytes
// Space saved:      113 bytes
//

#ifndef level_2_10_bg_31_H
#define level_2_10_bg_31_H

// Declaration of the compressed array
extern const unsigned char level_2_10_bg[31];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_10_bg_end (level_2_10_bg + 31 - 1)

// Compressed and uncompressed sizes
#define level_2_10_bg_size_z 31
#define level_2_10_bg_size 144

#endif

// File 'out/level_2_11_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/2-11-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       35 bytes
// Space saved:      109 bytes
//

#ifndef level_2_11_bg_35_H
#define level_2_11_bg_35_H

// Declaration of the compressed array
extern const unsigned char level_2_11_bg[35];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_2_11_bg_end (level_2_11_bg + 35 - 1)

// Compressed and uncompressed sizes
#define level_2_11_bg_size_z 35
#define level_2_11_bg_size 144

#endif

// File 'out/level_3_0_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-0-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       32 bytes
// Space saved:      112 bytes
//

#ifndef level_3_0_bg_32_H
#define level_3_0_bg_32_H

// Declaration of the compressed array
extern const unsigned char level_3_0_bg[32];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_0_bg_end (level_3_0_bg + 32 - 1)

// Compressed and uncompressed sizes
#define level_3_0_bg_size_z 32
#define level_3_0_bg_size 144

#endif

// File 'out/level_3_1_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-1-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       39 bytes
// Space saved:      105 bytes
//

#ifndef level_3_1_bg_39_H
#define level_3_1_bg_39_H

// Declaration of the compressed array
extern const unsigned char level_3_1_bg[39];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_1_bg_end (level_3_1_bg + 39 - 1)

// Compressed and uncompressed sizes
#define level_3_1_bg_size_z 39
#define level_3_1_bg_size 144

#endif

// File 'out/level_3_2_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-2-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       53 bytes
// Space saved:      91 bytes
//

#ifndef level_3_2_bg_53_H
#define level_3_2_bg_53_H

// Declaration of the compressed array
extern const unsigned char level_3_2_bg[53];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_2_bg_end (level_3_2_bg + 53 - 1)

// Compressed and uncompressed sizes
#define level_3_2_bg_size_z 53
#define level_3_2_bg_size 144

#endif

// File 'out/level_3_3_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-3-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       22 bytes
// Space saved:      122 bytes
//

#ifndef level_3_3_bg_22_H
#define level_3_3_bg_22_H

// Declaration of the compressed array
extern const unsigned char level_3_3_bg[22];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_3_bg_end (level_3_3_bg + 22 - 1)

// Compressed and uncompressed sizes
#define level_3_3_bg_size_z 22
#define level_3_3_bg_size 144

#endif

// File 'out/level_3_4_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-4-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       44 bytes
// Space saved:      100 bytes
//

#ifndef level_3_4_bg_44_H
#define level_3_4_bg_44_H

// Declaration of the compressed array
extern const unsigned char level_3_4_bg[44];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_4_bg_end (level_3_4_bg + 44 - 1)

// Compressed and uncompressed sizes
#define level_3_4_bg_size_z 44
#define level_3_4_bg_size 144

#endif

// File 'out/level_3_5_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-5-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       37 bytes
// Space saved:      107 bytes
//

#ifndef level_3_5_bg_37_H
#define level_3_5_bg_37_H

// Declaration of the compressed array
extern const unsigned char level_3_5_bg[37];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_5_bg_end (level_3_5_bg + 37 - 1)

// Compressed and uncompressed sizes
#define level_3_5_bg_size_z 37
#define level_3_5_bg_size 144

#endif

// File 'out/level_3_6_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-6-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       37 bytes
// Space saved:      107 bytes
//

#ifndef level_3_6_bg_37_H
#define level_3_6_bg_37_H

// Declaration of the compressed array
extern const unsigned char level_3_6_bg[37];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_6_bg_end (level_3_6_bg + 37 - 1)

// Compressed and uncompressed sizes
#define level_3_6_bg_size_z 37
#define level_3_6_bg_size 144

#endif

// File 'out/level_3_7_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-7-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       35 bytes
// Space saved:      109 bytes
//

#ifndef level_3_7_bg_35_H
#define level_3_7_bg_35_H

// Declaration of the compressed array
extern const unsigned char level_3_7_bg[35];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_7_bg_end (level_3_7_bg + 35 - 1)

// Compressed and uncompressed sizes
#define level_3_7_bg_size_z 35
#define level_3_7_bg_size 144

#endif

// File 'out/level_3_8_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-8-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       51 bytes
// Space saved:      93 bytes
//

#ifndef level_3_8_bg_51_H
#define level_3_8_bg_51_H

// Declaration of the compressed array
extern const unsigned char level_3_8_bg[51];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_8_bg_end (level_3_8_bg + 51 - 1)

// Compressed and uncompressed sizes
#define level_3_8_bg_size_z 51
#define level_3_8_bg_size 144

#endif

// File 'out/level_3_9_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-9-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       50 bytes
// Space saved:      94 bytes
//

#ifndef level_3_9_bg_50_H
#define level_3_9_bg_50_H

// Declaration of the compressed array
extern const unsigned char level_3_9_bg[50];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_9_bg_end (level_3_9_bg + 50 - 1)

// Compressed and uncompressed sizes
#define level_3_9_bg_size_z 50
#define level_3_9_bg_size 144

#endif

// File 'out/level_3_10_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-10-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       58 bytes
// Space saved:      86 bytes
//

#ifndef level_3_10_bg_58_H
#define level_3_10_bg_58_H

// Declaration of the compressed array
extern const unsigned char level_3_10_bg[58];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_10_bg_end (level_3_10_bg + 58 - 1)

// Compressed and uncompressed sizes
#define level_3_10_bg_size_z 58
#define level_3_10_bg_size 144

#endif

// File 'out/level_3_11_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/3-11-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       31 bytes
// Space saved:      113 bytes
//

#ifndef level_3_11_bg_31_H
#define level_3_11_bg_31_H

// Declaration of the compressed array
extern const unsigned char level_3_11_bg[31];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_3_11_bg_end (level_3_11_bg + 31 - 1)

// Compressed and uncompressed sizes
#define level_3_11_bg_size_z 31
#define level_3_11_bg_size 144

#endif

// File 'out/level_4_0_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-0-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       40 bytes
// Space saved:      104 bytes
//

#ifndef level_4_0_bg_40_H
#define level_4_0_bg_40_H

// Declaration of the compressed array
extern const unsigned char level_4_0_bg[40];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_0_bg_end (level_4_0_bg + 40 - 1)

// Compressed and uncompressed sizes
#define level_4_0_bg_size_z 40
#define level_4_0_bg_size 144

#endif
// File 'out/level_4_1_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-1-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       42 bytes
// Space saved:      102 bytes
//

#ifndef level_4_1_bg_42_H
#define level_4_1_bg_42_H

// Declaration of the compressed array
extern const unsigned char level_4_1_bg[42];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_1_bg_end (level_4_1_bg + 42 - 1)

// Compressed and uncompressed sizes
#define level_4_1_bg_size_z 42
#define level_4_1_bg_size 144

#endif
// File 'out/level_4_2_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-2-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       40 bytes
// Space saved:      104 bytes
//

#ifndef level_4_2_bg_40_H
#define level_4_2_bg_40_H

// Declaration of the compressed array
extern const unsigned char level_4_2_bg[40];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_2_bg_end (level_4_2_bg + 40 - 1)

// Compressed and uncompressed sizes
#define level_4_2_bg_size_z 40
#define level_4_2_bg_size 144

#endif
// File 'out/level_4_3_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-3-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       40 bytes
// Space saved:      104 bytes
//

#ifndef level_4_3_bg_40_H
#define level_4_3_bg_40_H

// Declaration of the compressed array
extern const unsigned char level_4_3_bg[40];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_3_bg_end (level_4_3_bg + 40 - 1)

// Compressed and uncompressed sizes
#define level_4_3_bg_size_z 40
#define level_4_3_bg_size 144

#endif
// File 'out/level_4_4_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-4-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       42 bytes
// Space saved:      102 bytes
//

#ifndef level_4_4_bg_42_H
#define level_4_4_bg_42_H

// Declaration of the compressed array
extern const unsigned char level_4_4_bg[42];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_4_bg_end (level_4_4_bg + 42 - 1)

// Compressed and uncompressed sizes
#define level_4_4_bg_size_z 42
#define level_4_4_bg_size 144

#endif
// File 'out/level_4_5_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-5-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       36 bytes
// Space saved:      108 bytes
//

#ifndef level_4_5_bg_36_H
#define level_4_5_bg_36_H

// Declaration of the compressed array
extern const unsigned char level_4_5_bg[36];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_5_bg_end (level_4_5_bg + 36 - 1)

// Compressed and uncompressed sizes
#define level_4_5_bg_size_z 36
#define level_4_5_bg_size 144

#endif
// File 'out/level_4_6_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-6-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       49 bytes
// Space saved:      95 bytes
//

#ifndef level_4_6_bg_49_H
#define level_4_6_bg_49_H

// Declaration of the compressed array
extern const unsigned char level_4_6_bg[49];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_6_bg_end (level_4_6_bg + 49 - 1)

// Compressed and uncompressed sizes
#define level_4_6_bg_size_z 49
#define level_4_6_bg_size 144

#endif
// File 'out/level_4_7_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-7-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       46 bytes
// Space saved:      98 bytes
//

#ifndef level_4_7_bg_46_H
#define level_4_7_bg_46_H

// Declaration of the compressed array
extern const unsigned char level_4_7_bg[46];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_7_bg_end (level_4_7_bg + 46 - 1)

// Compressed and uncompressed sizes
#define level_4_7_bg_size_z 46
#define level_4_7_bg_size 144

#endif
// File 'out/level_4_8_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-8-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       34 bytes
// Space saved:      110 bytes
//

#ifndef level_4_8_bg_34_H
#define level_4_8_bg_34_H

// Declaration of the compressed array
extern const unsigned char level_4_8_bg[34];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_8_bg_end (level_4_8_bg + 34 - 1)

// Compressed and uncompressed sizes
#define level_4_8_bg_size_z 34
#define level_4_8_bg_size 144

#endif
// File 'out/level_4_9_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-9-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       40 bytes
// Space saved:      104 bytes
//

#ifndef level_4_9_bg_40_H
#define level_4_9_bg_40_H

// Declaration of the compressed array
extern const unsigned char level_4_9_bg[40];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_9_bg_end (level_4_9_bg + 40 - 1)

// Compressed and uncompressed sizes
#define level_4_9_bg_size_z 40
#define level_4_9_bg_size 144

#endif

//

#ifndef level_4_10_bg_42_H
#define level_4_10_bg_42_H

// Declaration of the compressed array
extern const unsigned char level_4_10_bg[42];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_10_bg_end (level_4_10_bg + 42 - 1)

// Compressed and uncompressed sizes
#define level_4_10_bg_size_z 42
#define level_4_10_bg_size 144

#endif

// File 'out/level_4_11_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/4-11-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       33 bytes
// Space saved:      111 bytes
//

#ifndef level_4_11_bg_33_H
#define level_4_11_bg_33_H

// Declaration of the compressed array
extern const unsigned char level_4_11_bg[33];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_4_11_bg_end (level_4_11_bg + 33 - 1)

// Compressed and uncompressed sizes
#define level_4_11_bg_size_z 33
#define level_4_11_bg_size 144

#endif

// File 'out/level_5_0_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-0-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       38 bytes
// Space saved:      106 bytes
//

#ifndef level_5_0_bg_38_H
#define level_5_0_bg_38_H

// Declaration of the compressed array
extern const unsigned char level_5_0_bg[38];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_0_bg_end (level_5_0_bg + 38 - 1)

// Compressed and uncompressed sizes
#define level_5_0_bg_size_z 38
#define level_5_0_bg_size 144

#endif
// File 'out/level_5_1_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-1-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       46 bytes
// Space saved:      98 bytes
//

#ifndef level_5_1_bg_46_H
#define level_5_1_bg_46_H

// Declaration of the compressed array
extern const unsigned char level_5_1_bg[46];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_1_bg_end (level_5_1_bg + 46 - 1)

// Compressed and uncompressed sizes
#define level_5_1_bg_size_z 46
#define level_5_1_bg_size 144

#endif
// File 'out/level_5_2_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-2-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       37 bytes
// Space saved:      107 bytes
//

#ifndef level_5_2_bg_37_H
#define level_5_2_bg_37_H

// Declaration of the compressed array
extern const unsigned char level_5_2_bg[37];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_2_bg_end (level_5_2_bg + 37 - 1)

// Compressed and uncompressed sizes
#define level_5_2_bg_size_z 37
#define level_5_2_bg_size 144

#endif
// File 'out/level_5_3_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-3-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       45 bytes
// Space saved:      99 bytes
//

#ifndef level_5_3_bg_45_H
#define level_5_3_bg_45_H

// Declaration of the compressed array
extern const unsigned char level_5_3_bg[45];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_3_bg_end (level_5_3_bg + 45 - 1)

// Compressed and uncompressed sizes
#define level_5_3_bg_size_z 45
#define level_5_3_bg_size 144

#endif
// File 'out/level_5_4_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-4-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       44 bytes
// Space saved:      100 bytes
//

#ifndef level_5_4_bg_44_H
#define level_5_4_bg_44_H

// Declaration of the compressed array
extern const unsigned char level_5_4_bg[44];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_4_bg_end (level_5_4_bg + 44 - 1)

// Compressed and uncompressed sizes
#define level_5_4_bg_size_z 44
#define level_5_4_bg_size 144

#endif
// File 'out/level_5_5_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-5-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       41 bytes
// Space saved:      103 bytes
//

#ifndef level_5_5_bg_41_H
#define level_5_5_bg_41_H

// Declaration of the compressed array
extern const unsigned char level_5_5_bg[41];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_5_bg_end (level_5_5_bg + 41 - 1)

// Compressed and uncompressed sizes
#define level_5_5_bg_size_z 41
#define level_5_5_bg_size 144

#endif
// File 'out/level_5_6_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-6-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       61 bytes
// Space saved:      83 bytes
//

#ifndef level_5_6_bg_61_H
#define level_5_6_bg_61_H

// Declaration of the compressed array
extern const unsigned char level_5_6_bg[61];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_6_bg_end (level_5_6_bg + 61 - 1)

// Compressed and uncompressed sizes
#define level_5_6_bg_size_z 61
#define level_5_6_bg_size 144

#endif
// File 'out/level_5_7_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-7-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       37 bytes
// Space saved:      107 bytes
//

#ifndef level_5_7_bg_37_H
#define level_5_7_bg_37_H

// Declaration of the compressed array
extern const unsigned char level_5_7_bg[37];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_7_bg_end (level_5_7_bg + 37 - 1)

// Compressed and uncompressed sizes
#define level_5_7_bg_size_z 37
#define level_5_7_bg_size 144

#endif
// File 'out/level_5_8_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-8-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       30 bytes
// Space saved:      114 bytes
//

#ifndef level_5_8_bg_30_H
#define level_5_8_bg_30_H

// Declaration of the compressed array
extern const unsigned char level_5_8_bg[30];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_8_bg_end (level_5_8_bg + 30 - 1)

// Compressed and uncompressed sizes
#define level_5_8_bg_size_z 30
#define level_5_8_bg_size 144

#endif
// File 'out/level_5_9_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-9-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       40 bytes
// Space saved:      104 bytes
//

#ifndef level_5_9_bg_40_H
#define level_5_9_bg_40_H

// Declaration of the compressed array
extern const unsigned char level_5_9_bg[40];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_9_bg_end (level_5_9_bg + 40 - 1)

// Compressed and uncompressed sizes
#define level_5_9_bg_size_z 40
#define level_5_9_bg_size 144

#endif

#ifndef level_5_10_bg_53_H
#define level_5_10_bg_53_H

// Declaration of the compressed array
extern const unsigned char level_5_10_bg[53];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_10_bg_end (level_5_10_bg + 53 - 1)

// Compressed and uncompressed sizes
#define level_5_10_bg_size_z 53
#define level_5_10_bg_size 144

#endif

// File 'out/level_5_11_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/5-11-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       40 bytes
// Space saved:      104 bytes
//

#ifndef level_5_11_bg_40_H
#define level_5_11_bg_40_H

// Declaration of the compressed array
extern const unsigned char level_5_11_bg[40];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_5_11_bg_end (level_5_11_bg + 40 - 1)

// Compressed and uncompressed sizes
#define level_5_11_bg_size_z 40
#define level_5_11_bg_size 144
#endif

// File 'out/level_6_0_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/6-0-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       6 bytes
// Space saved:      138 bytes
//

#ifndef level_6_0_bg_6_H
#define level_6_0_bg_6_H

// Declaration of the compressed array
extern const unsigned char level_6_0_bg[6];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_6_0_bg_end (level_6_0_bg + 6 - 1)

// Compressed and uncompressed sizes
#define level_6_0_bg_size_z 6
#define level_6_0_bg_size 144

#endif

// File 'out/level_6_1_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/6-1-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       32 bytes
// Space saved:      112 bytes
//

#ifndef level_6_1_bg_32_H
#define level_6_1_bg_32_H

// Declaration of the compressed array
extern const unsigned char level_6_1_bg[32];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_6_1_bg_end (level_6_1_bg + 32 - 1)

// Compressed and uncompressed sizes
#define level_6_1_bg_size_z 32
#define level_6_1_bg_size 144

#endif

// File 'out/level_6_2_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/6-2-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       41 bytes
// Space saved:      103 bytes
//

#ifndef level_6_2_bg_41_H
#define level_6_2_bg_41_H

// Declaration of the compressed array
extern const unsigned char level_6_2_bg[41];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_6_2_bg_end (level_6_2_bg + 41 - 1)

// Compressed and uncompressed sizes
#define level_6_2_bg_size_z 41
#define level_6_2_bg_size 144

#endif

// File 'out/level_6_3_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/6-3-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       48 bytes
// Space saved:      96 bytes
//

#ifndef level_6_3_bg_48_H
#define level_6_3_bg_48_H

// Declaration of the compressed array
extern const unsigned char level_6_3_bg[48];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_6_3_bg_end (level_6_3_bg + 48 - 1)

// Compressed and uncompressed sizes
#define level_6_3_bg_size_z 48
#define level_6_3_bg_size 144

#endif

// File 'out/level_6_4_bg.h' generated using cpct_pack
// Compresor used:   zx7b
// Files compressed: [ 'out/6-4-bg.bin' ]
// Uncompressed:     144 bytes
// Compressed:       35 bytes
// Space saved:      109 bytes
//

#ifndef level_6_4_bg_35_H
#define level_6_4_bg_35_H

// Declaration of the compressed array
extern const unsigned char level_6_4_bg[35];

// Address of the latest byte of the compressed array (for unpacking purposes)
#define level_6_4_bg_end (level_6_4_bg + 35 - 1)

// Compressed and uncompressed sizes
#define level_6_4_bg_size_z 35
#define level_6_4_bg_size 144

#endif
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

// clang-format off
#define IS_WALKABLE(x) ((x) >= WALK_TILE_FIRST && (x) <= WALK_TILE_LAST)

#define ANY_IS_WALKABLE(a, b, c, d) \
    (IS_WALKABLE(a) || IS_WALKABLE(b) || IS_WALKABLE(c) || IS_WALKABLE(d))

#define IS_ITEM(x) ((x) == ITEM_KEY || (x) == ITEM_HEALTH || (x) == ITEM_BOMB || (x) == ITEM_ARTIFACT)

#define IS_FURNITURE(x) \
    ((x) == SARC_1_TOP || (x) == SARC_1_BOTTOM || (x) == SARC_2_LEFT || \
     (x) == SARC_2_RIGHT || (x) == SARC_3_TOP || (x) == SARC_3_BOTTOM || \
     (x) == PHYLACTERY  || (x) == CANOPTIC_JAR)

#define ANY_IS_FURNITURE(a, b, c, d) \
    (IS_FURNITURE(a) || IS_FURNITURE(b) || IS_FURNITURE(c) || IS_FURNITURE(d))

#define IS_DOOR(x) ((x) >= DOOR_TILE_FIRST && (x) <= DOOR_TILE_LAST)

#define IS_STATUE(x) (x) == STATUE_GFX

#define IS_PHYLACTERY(x) (x) == PHYLACTERY

#define IS_JAR(x) (x) == CANOPTIC_JAR

#define IS_GRAVE(x) (x) == OPEN_GRAVE

#define IS_ARTIFACT(x) (x) == HOLY_ARTIFACT

#define IS_SARCOGRAPHUS(x) \
    ((x) == SARC_1_TOP || (x) == SARC_1_BOTTOM || (x) == SARC_2_LEFT || \
     (x) == SARC_2_RIGHT || (x) == SARC_3_TOP || (x) == SARC_3_BOTTOM )


#define IS_HDOOR(x) ((x) == DOOR_TILE_H_M || (x) == DOOR_TILE_H_L || (x) == DOOR_TILE_H_R)

#define IS_VDOOR(x) ((x) == DOOR_TILE_V_M || (x) == DOOR_TILE_V_L || (x) == DOOR_TILE_V_R)

#define FG_SET_MONSTER(fg, type) \
    (((fg) & 0x1F) | FG_MONSTER_PRESENT | ((type) << 6))

#define FG_CLEAR_MONSTER(fg) ((fg) & 0x1F)

#define FG_GET_MONSTER_TYPE(fg) \
    (((fg) & FG_MONSTER_TYPEMASK) >> 6)

#define FG_HAS_MONSTER(fg)  ((fg) & FG_MONSTER_PRESENT)

#define IS_SMASHED_SARCOGRAPHUS(fg)  (((fg) == (SARC_1_TOP+2))   || ((fg) == (SARC_1_BOTTOM+2)) || \
                               ((fg) == (SARC_2_LEFT+2)) || ((fg) == (SARC_2_RIGHT+2))  || \
                               ((fg) == (SARC_3_TOP+2))  || ((fg) == (SARC_3_BOTTOM+2)))

#define IS_WALKABLE_FG(fg) \
    ((fg)==0 || IS_SMASHED_SARCOGRAPHUS(fg) || IS_ITEM(fg))


#define IS_BOSS(x) ((x) >= BOSS_START && (x) <= BOSS_END)

// clang-format oN

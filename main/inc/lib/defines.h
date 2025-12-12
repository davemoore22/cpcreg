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

#include <cpctelera.h>

/* Level Screen Size */
#define SCREEN_U_W 16
#define SCREEN_U_H 9
#define LEVEL_SCRS 12
#define TILE_ARRAY_W 48
#define SCREENS_W 3
#define SCREENS_H 4

/* Data Locations */
#define STACK_LOC ((void *)0x00FF)
#define MASK_TABLE_LOC 0x0200 /* 0x0100 bytes long */
#define DISK_TABLE_LOC 0x0300 /* 0x0100 bytes long */
#define CODE_START_LOC 0x0480 /* See build_config.mk */
#define DATA_START_LOC 0x6680 /* See build_config.mk */

#define VIDEO_MEM_START ((u8 *)0xC000)
#define VIDEO_MEM_END ((void *)0xFFFF)
#define VIDEO_MEM_SIZE ((u8)0x4000)

/* Run time storage for level data */
#define g_level_fg ((u8 *)0xA620)
#define g_level_fg_sz LEVEL_SCRS * SCREEN_U_W * SCREEN_U_H
#define g_screen_bg ((u8 *)0xAD20)
#define g_screen_bg_sz 16 * 9
#define g_temp_bg ((u8 *)0xAE20)
#define g_temp_bg_sz 16 * 9

#define KEY_NONE 0xFF

/* Size of Character Font in Bytes/Lines (8x8 pixels) */
#define LINE_P_W 2
#define LINE_P_W_SHIFT 1
#define LINE_P_H 8
#define LINE_P_H_SHIFT 3

/* Size of Graphics in Bytes/Lines (16x16 pixels) */
#define TILE_B_W 4
#define TILE_B_W_SHIFT 2
#define TILE_B_H 16
#define TILE_B_H_SHIFT 4
#define PLAYER_B_W 4
#define PLAYER_B_H 16
#define SPRITE_B_W 4
#define SPRITE_B_H 16
#define BYTE_X 4
#define BYTE_Y 1
#define TILE_STEP_X 4
#define TILE_STEP_Y 160

#define WALKER_ANIM_RATE 2
#define WALKER_TOP 40
#define WALKER_BOTTOM 128

/* Menu Screens Layout */
#define TITLE_Y 2
#define MENU_X 20
#define MENU_Y 6
#define EXTENDED_X 10
#define EXTENDED_Y 23
#define ABOUT_Y 21
#define KEYS_X 10
#define KEYS_Y 6
#define KEYS_GAP_X 18
#define PRESS_REDEFINE_Y 20
#define SCORES_X 18
#define SCORES_Y 6
#define SETTINGS_X 18
#define SETTINGS_Y 8
#define TOGGLE_X 28
#define RETURN_Y 22
#define LEVEL_X 28
#define LEVEL_Y 21
#define CONTINUE_Y 22
#define INBETWEEN_Y 18
#define CONGRATS_Y 6
#define INITIALS_Y 16

/* Game Screen Layoaut (Bytes)*/
#define GAME_WINDOW_X 8
#define GAME_WINDOW_Y 8

#define MONMAP_BYTES 36
#define BAT_SPAWN_INTERVAL 50
#define ZOMBIE_SPAWN_INTERVAL 80
#define GHOST_SPAWN_INTERVAL 120

#define NO_LINK 0xFF

/* Monster Bitflags  */
#define MON_NONE 0
#define MON_BAT 1
#define MON_ZOMBIE 2
#define MON_GHOST 3

/* Size of Game "Window */
#define LEVEL_WINDOW_W (SCREEN_U_W * TILE_B_W)
#define LEVEL_WINDOW_H (SCREEN_U_H * TILE_B_H)

#define SCREEN_TILES (SCREEN_W * SCREEN_H)
#define BG_SIZE (SCREEN_U_W * SCREEN_U_H)

/* String Indexes */
#define TITLE_TEXT_REGINALD 0
#define TITLE_TEXT_REGINA 1
#define ABOUT_TEXT 2
#define MENU_TEXT 3
#define REDEFINE_SUBTITLE 10
#define KEYS_START 11
#define NON_ASCII_KEYS_START 18
#define CANCEL_TEXT 24
#define HISCORES_SUBTITLE 25
#define HISCORES_START 26
#define RETURN_TEXT 28
#define SETTINGS_SUBTITLE 29
#define SETTINGS_START 30
#define ON_TEXT 34
#define OFF_TEXT 35
#define LEVEL_TEXT 36
#define GET_READY_TEXT 37
#define HUD_00 38
#define HUD_0000 39
#define HUD_000000 40
#define PRESS_KEY_FOR_TEXT 41
#define GAME_OVER_TEXT 42
#define CONGRATS_TEXT 43
#define INITIALS_TEXT 46
#define PUBLISHED_TEXT 80

/* Array Sizes */
#define CONTROLS_SZ 13
#define HISCORES_SZ 7
#define OPTIONS_SZ 5
#define KEY_MAPPING_SZ 27
#define KEY_MAPPING_REDEFINE_SZ 32
#define CONNECTIONS_SZ 42
#define LEVELS_SZ 12
#define HINTS_SZ 15
#define DIRTY_TILES_SZ 64

#define FINAL_LEVEL 2

#define PAUSE_HINT_IDX 14

/* Settings */
#define OPT_CHARACTER 0x01
#define OPT_CHEAT 0x02
#define OPT_SFX 0x04
#define OPT_GREEN_SCREEN 0x08
#define OPT_TEXT 0x10

/* Pens */
#define PEN_0 0
#define PEN_1 1
#define PEN_2 2
#define PEN_3 3
#define PEN_NO_RECOLOUR 4

/* Timings */
#define FC_MAX 50
#define FC_AI_TICK 10

/* Sprites */
#define BULLET_GFX 0
#define STATUE_GFX 5
#define RIP_GFX 49
#define FLOOR_GFX 16

#define MAX_MONSTERS 8
#define MONSTER_CONTACT_DAMAGE 250

#define BOSS_START 29
#define BOSS_END 31

/* Level Screen Count */
#define LEVEL_SCRS 12

/* Deltas */
#define PLAYER_DELTA_G_X 1
#define PLAYER_DELTA_G_Y 1
#define BULLET_DELTA_G_X 1
#define BULLET_DELTA_G_Y 1

#define DELTA_B_X 2
#define DELTA_B_Y 8

/* WinAPE Breakpoint Macro */
#define WinwApe_Brk __asm__(".dw #0xFFED");

/* Game Status Bit Flags */
#define BIT_PAUSE 1
#define BIT_QUIT 2
#define BIT_SUCCESS 4
#define BIT_INPUT 8
#define BIT_EXPLAIN 16

/* Edge Bits */
#define BIT_TOP 1
#define BIT_BOTTOM 2
#define BIT_LEFT 4
#define BIT_RIGHT 8

/* Walkable Tiles */
#define WALK_TILE_FIRST 12
#define WALK_TILE_LAST 28

/* Furniture Tiles */
#define SARC_1_TOP 37
#define SARC_1_BOTTOM 38
#define SARC_2_LEFT 41
#define SARC_2_RIGHT 42
#define SARC_3_TOP 45
#define SARC_3_BOTTOM 46
#define OPEN_GRAVE 49
#define PHYLACTERY 54
#define CANOPTIC_JAR 55
#define HOLY_ARTIFACT 49

#define START_SCREEN 0

/* Other Tiles */
#define DOOR_TILE_FIRST 56
#define DOOR_TILE_H_M 56
#define DOOR_TILE_H_L 58
#define DOOR_TILE_H_R 59
#define DOOR_TILE_V_M 57
#define DOOR_TILE_V_L 60
#define DOOR_TILE_V_R 61
#define DOOR_TILE_LAST 61

/* Item Tiles */
#define ITEM_ARTIFACT 50
#define ITEM_HEALTH 51
#define ITEM_KEY 52
#define ITEM_BOMB 53
#define ITEM_JAR 55

/* GUI Frame elements */
#define FRAME_TL 0
#define FRAME_TM 1
#define FRAME_TR 2
#define FRAME_MR 3
#define FRAME_BR 4
#define FRAME_BM 5
#define FRAME_BL 6
#define FRAME_ML 7

/* Hints Text */
#define HINT_TEXT_START 50
#define HINT_DURATION 3
#define FRAME_V_OFFSET -12
#define HINT_FRAME_WIDTH 14
#define HINT_FRAME_HEIGHT 5
#define HINT_GET_READY_REGINALD 0
#define HINT_GET_READY_REGINALD_TEXT 50
#define HINT_GET_READY_REGINA 1
#define HINT_GET_READY_REGINA_TEXT 52
#define HINT_FOUND_KEY 2
#define HINT_FOUND_KEY_TEXT 54
#define HINT_NEED_KEY 3
#define HINT_NEED_KEY_TEXT 56
#define HINT_OPENED_DOOR 4
#define HINT_OPENED_DOOR_TEXT 58
#define HINT_FOUND_ARTIFACT 5
#define HINT_FOUND_ARTIFACT_TEXT 60
#define HINT_FOUND_GRAVE 6
#define HINT_FOUND_GRAVE_TEXT 62
#define HINT_FOUND_HEALTH 7
#define HINT_FOUND_HEALTH_TEXT 64
#define HINT_FOUND_BOMB 8
#define HINT_FOUND_BOMB_TEXT 66
#define HINT_FOUND_SARCOGRAPHUS 9
#define HINT_FOUND_SARCOGRAPHUS_TEXT 68
#define HINT_BUMP_JAR 10
#define HINT_BUMP_JAR_TEXT 70
#define HINT_BUMP_STATUE 11
#define HINT_BUMP_STATUE_TEXT 72
#define HINT_PHLACTERY_NO_ARTEFACT 12
#define HINT_PHLACTERY_NO_ARTEFACT_TEXT 74
#define HINT_PHLACTERY_DESTROY 13
#define HINT_PHLACTERY_DESTROY_TEXT 76

/* Border Flashes */

#define TRIPLET_BLUE HW_BLUE, HW_BRIGHT_BLUE, HW_PASTEL_BLUE
#define TRIPLET_RED HW_RED, HW_BRIGHT_RED, HW_ORANGE
#define TRIPLET_GREEN HW_GREEN, HW_BRIGHT_GREEN, HW_PASTEL_GREEN
#define TRIPLET_CYAN HW_CYAN, HW_BRIGHT_CYAN, HW_PASTEL_CYAN
#define TRIPLET_MAGENTA HW_MAGENTA, HW_BRIGHT_MAGENTA, HW_PASTEL_MAGENTA
#define TRIPLET_PURPLE HW_MAGENTA, HW_PURPLE, HW_BRIGHT_MAGENTA
#define TRIPLET_YELLOW HW_YELLOW, HW_BRIGHT_YELLOW, HW_PASTEL_YELLOW
#define TRIPLET_GREY HW_BLACK, HW_WHITE, HW_BRIGHT_WHITE
#define TRIPLET_ORANGE HW_ORANGE, HW_PASTEL_YELLOW, HW_BRIGHT_WHITE
#define TRIPLET_MAUVE HW_MAUVE, HW_PASTEL_BLUE, HW_PASTEL_MAGENTA
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

#pragma codeseg CODE

#include "lib/video.h"

/* Interrupt Indexes */
u8 v_int_idx = 0;
u8 v_pal_idx = 0;
u8 v_frame_c = 0;
u8 v_pen = PEN_3;

/* Redrawing Flags */
u8 *v_game_window_pos;

dirty_t dirty_tiles[DIRTY_TILES_SZ];
u8 num_dirty_tiles = 0;

/* Precomputed frame tile sprites */
static const u8 *frame_tile[8];

static const u8 *v_tileset_start;
static const u8 *v_tile_bullet;
static const u8 *v_gui_start;

/* Private Functions */
static void video_init_hint_tiles(void);

/* Initialise Video and Clear the Screen */
void video_init(void) {

	/* Mode 1 */
	cpct_setVideoMode(1);
	video_blank_screen();
	cpct_waitVSYNCStart();
	cpct_clearScreen_f64(0);

	/* Game window position pointer */
	v_game_window_pos = cpct_getScreenPtr(
		CPCT_VMEM_START, GAME_WINDOW_X, GAME_WINDOW_Y);

	v_tileset_start = tile_nm_16x16_00;
	v_tile_bullet = tile_m_16x16_00;
	v_gui_start = gui_nm_16x16_00;

	video_init_hint_tiles();
}

static void video_init_hint_tiles(void) {

	static const u8 tile_ids[8] = {FRAME_TL, FRAME_TM, FRAME_TR, FRAME_ML,
		FRAME_MR, FRAME_BL, FRAME_BM, FRAME_BR};

	for (u8 i = 0; i < 8; i++)
		frame_tile[i] = v_gui_start + ((u16)tile_ids[i] << 6);
}

/* Reset all Screen Pens to Black, effectively blanking the screen */
void video_blank_screen(void) {

	static const u8 blank_pal[4] = {
		HW_BLACK,
		HW_BLACK,
		HW_BLACK,
		HW_BLACK,
	};

	cpct_removeInterruptHandler();
	cpct_waitVSYNC();
	cpct_setPalette(blank_pal, sizeof(blank_pal));
	cpct_setBorder(HW_BLACK);
}

/* Wipe the Screen in a Direction */
void video_wipe_screen(bool dir) {

	u8 start = dir ? 0 : 78;
	u8 end = dir ? 79 : 1;
	i8 step = dir ? +1 : -1;

	for (u8 x = start; x != end; x += step) {
		if (!(x & 1)) {
			cpct_waitVSYNC();
			cpct_drawSolidBox(
				cpct_getScreenPtr(CPCT_VMEM_START, x, 0), 0, 2,
				200);
		}
	}
}

/* Clear the Screen to Pen 0 */
void video_clear_screen(void) {

	cpct_waitVSYNCStart();
	cpct_clearScreen_f64(0);
}

/* Reset the Palette back to Normal Mode 1 Colours */
void video_reset_palette(void) {

	static const u8 normal_pal[4] = {
		HW_BLACK,
		HW_PASTEL_BLUE,
		HW_ORANGE,
		HW_BRIGHT_RED,
	};

	cpct_waitVSYNC();
	cpct_setPalette(normal_pal, sizeof(normal_pal));
	cpct_setBorder(HW_BLACK);
	v_int_idx = 0;
}

/* Reset Interrupt Timers */
void video_reset_timers(void) {

	v_int_idx = 0;
	v_pal_idx = 0;
	v_frame_c = 0;
}

void video_draw_title(const u8 y) {

	u8 *pg_ptr = (u8 *)0xA601;
	u8 title_text_idx = g_options & OPT_CHARACTER ? TITLE_TEXT_REGINALD
						      : TITLE_TEXT_REGINA;

	if (*pg_ptr == 255)
		title_text_idx = g_options & OPT_CHARACTER
					 ? TITLE_TEXT_REGINALD + 80
					 : TITLE_TEXT_REGINA + 80;

	/* As LINE_P_H is 8, we can shift by 3 instead of multiplying by 8 */
	v_pen = PEN_NO_RECOLOUR;

	video_print_centred_text(g_strings[title_text_idx], y << 3);
}

void video_full_clear(void) {

	video_blank_screen();
	video_clear_screen();
}

void video_clear_centre(void) {

	u8 *v_pos;

	v_pos = cpct_getScreenPtr(CPCT_VMEM_START, 10, 8);
	cpct_drawSolidBox(v_pos, 0, 60, 184);
}

/* Print a string using the Font sprites but centered horizontally */
void video_print_centred_text(const char *str, const u8 y) {

	u8 x = (40) - ((utils_strlen(str) << 1) >> 1);

	video_print_text(str, x, y);
}

/* Print a string using the Font sprites (optionally use to len chars) */
void video_print_text(const char *str, const u8 x, const u8 y) {

	const u8 *font = font_ts_00; /* font tile set */
	u8 *v_pos;		     /* screen position pointer */
	const u8 *spr;		     /* sprite pointer */
	u16 i = 0;
	u16 offset;
	u16 rplc = 0;

	/* Initial screen pos */
	v_pos = cpct_getScreenPtr(CPCT_VMEM_START, x, y);

	/* Precompute recolour pattern if needed */
	if (v_pen != PEN_NO_RECOLOUR)
		rplc = cpct_pens2pixelPatternPairM1(3, v_pen);

	/* Render loop */
	while (str[i] != '\0') {

		char c = str[i];

		/* Force Uppercase  */
		if (c >= 'a' && c <= 'z')
			c -= 32;

		/* Optional: replace weird chars with '?' */
		if (c < 32 || c > 126)
			c = '?';

		offset = ((u8)c - 32u) << 4; /* Each gyph is 16 bytes */
		spr = font + offset;

		if (v_pen != PEN_NO_RECOLOUR)
			cpct_drawSpriteColorizeM1(spr, v_pos, 2, 8, rplc);
		else
			cpct_drawSprite(spr, v_pos, 2, 8);

		v_pos += 2;
		++i;
	}
}

/* Draw In-Game GUI */
void video_draw_GUI(void) {

	utils_load("HUD     BIN", VIDEO_MEM_START);
}

void video_clear_HUD(void) {

	/* Default Values */
	v_pen = PEN_3;
	video_print_text("0000", 10, 186);
	video_print_text("00", 27, 176);
	video_print_text("00", 37, 176);
	video_print_text("00", 47, 176);
	video_print_text("000000", 57, 176);
}

/* Draw HUD */
void video_draw_HUD(void) {

	u8 width;
	char buf[7];

	/* Current Values */
	v_pen = PEN_3;
	video_print_text(g_game.health_str, 10, 186);
	video_print_text(g_game.keys_str, 27, 176);
	video_print_text(g_game.bombs_str, 37, 176);
	video_print_text(g_game.artifacts_str, 47, 176);

	width = utils_get_str_width(g_game.score);
	utils_itoa_6(buf, g_game.score);
	video_print_text(buf, 61 + (8 - (width << 1)), 176);

	if (g_options & OPT_CHEAT) {
		video_print_centred_text("***CHEAT***", 192);

		char debug_str[] = " / ";
		debug_str[0] = '0' + g_game.level;
		debug_str[2] = '0' + g_player.screen;
		video_print_text(debug_str, 74, 192);
	}
}

void video_draw_rect(u8 tx, u8 ty, u8 tw, u8 th) {

	u8 *row_pos;
	u8 *tile_pos;
	u8 *spr;
	u16 idx;
	u16 offset;
	u8 x, y;
	u8 screen = g_player.screen;

	/* Start VRAM address for top-left tile of region */

	/*
	 * We have optmised out the following to use shifts instead:
	 * row_pos = v_game_window_pos + (ty * 160) + (tx * 4);
	 */
	row_pos = v_game_window_pos + (ty << 7) + (ty << 5) + (tx << 2);

	for (y = 0; y < th; y++) {

		tile_pos = row_pos;

		for (x = 0; x < tw; x++) {

			u8 bg;

			/* Map index */
			idx = utils_get_screen_x_y(screen, tx + x, ty + y);

			/* Draw background */
			bg = g_screen_bg[(ty + y) * SCREEN_U_W + (tx + x)];
			offset = (u16)bg << 6;
			spr = v_tileset_start + offset;
			cpct_drawSprite(spr, tile_pos, TILE_B_W, TILE_B_H);

			/* Draw foreground (if any) */
			if (g_level_fg[idx] != 0) {
				offset = (u16)g_level_fg[idx] << 6;
				spr = v_tileset_start + offset;
				cpct_drawSprite(
					spr, tile_pos, TILE_B_W, TILE_B_H);
			}

			tile_pos += 4; /* next tile (4 bytes = 16px) */
		}

		row_pos += 160; /* next row (160 bytes = 16px) */
	}
}

/* Draw a centred hint (these params include corners and are in tile units) */
void video_draw_hint(const u8 hint_id) {

	u8 *v_pos, *row_start;
	u8 w = HINT_FRAME_WIDTH;
	u8 h = HINT_FRAME_HEIGHT;
	u8 i, rows;
	u16 offs;
	u8 bytes_w = w << 2; /* tiles * 4 bytes */
	u8 bytes_h = h << 4; /* tiles * 16 bytes */
	u8 start_x = (80 - bytes_w) >> 1;
	u8 start_y = ((200 - bytes_h) >> 1) + FRAME_V_OFFSET;
	u8 base = HINT_TEXT_START + (hint_id << 1);

	/* Top-left vpos */
	row_start = cpct_getScreenPtr(CPCT_VMEM_START, start_x, start_y);
	v_pos = row_start;

	/* TL */
	cpct_drawSprite(frame_tile[FT_TL], v_pos, TILE_B_W, TILE_B_H);
	v_pos += TILE_STEP_X;

	/* TM tiles */
	for (i = 0; i < w - 2; i++) {
		cpct_drawSprite(frame_tile[FT_TM], v_pos, TILE_B_W, TILE_B_H);
		v_pos += TILE_STEP_X;
	}

	/* TR */
	cpct_drawSprite(frame_tile[FT_TR], v_pos, TILE_B_W, TILE_B_H);

	/* Note TILE_STEP_X is 4 so we can shift by 2 instead */
	v_pos = row_start + TILE_STEP_Y;
	for (i = 0; i < h - 2; i++) {
		cpct_drawSprite(frame_tile[FT_MR], v_pos + ((w - 1) << 2),
			TILE_B_W, TILE_B_H);
		v_pos += TILE_STEP_Y;
	}

	/*
	 * We have optmised out the following to use shifts instead:
	 * row_start += (h - 1) * TILE_STEP_Y;
	 */
	rows = (h - 1);
	offs = (rows << 7) + (rows << 5);
	row_start += offs;

	v_pos = row_start + ((w - 1) << 2);

	/* BR */
	cpct_drawSprite(frame_tile[FT_BR], v_pos, TILE_B_W, TILE_B_H);
	v_pos -= TILE_STEP_X;

	/* BM tiles */
	for (i = 0; i < w - 2; i++) {
		cpct_drawSprite(frame_tile[FT_BM], v_pos, TILE_B_W, TILE_B_H);
		v_pos -= TILE_STEP_X;
	}

	/* BL */
	cpct_drawSprite(frame_tile[FT_BL], v_pos, TILE_B_W, TILE_B_H);

	v_pos = row_start - TILE_STEP_Y;
	for (i = 0; i < h - 2; i++) {
		cpct_drawSprite(frame_tile[FT_ML], v_pos, TILE_B_W, TILE_B_H);
		v_pos -= TILE_STEP_Y;
	}

	/* Clear centre */
	{
		u8 *inner_pos = cpct_getScreenPtr(
			CPCT_VMEM_START, start_x + 4, start_y + 16);

		cpct_drawSolidBox(inner_pos, 0, /* colour */
			(w - 2) << 2,		/* bytes width  */
			(h - 2) << 4);		/* bytes height */
	}
	/* Draw Hint Text */
	v_pen = PEN_3;

	video_print_centred_text(g_strings[base], 96 + FRAME_V_OFFSET - 8);
	video_print_centred_text(g_strings[base + 1], 96 + FRAME_V_OFFSET + 8);
}

/* Set tile as dirty */
void video_mark_dirty_tile(const u8 x, const u8 y) {

	if (num_dirty_tiles >= DIRTY_TILES_SZ)
		return;

	dirty_tiles[num_dirty_tiles].x = x;
	dirty_tiles[num_dirty_tiles].y = y;
	++num_dirty_tiles;
}

/* Clear dirty tiles */
void video_clear_dirty_list(void) {

	num_dirty_tiles = 0;
}

/* Draw all dirty tiles */
void video_draw_dirty_tiles(void) {

	u8 *spr;
	u16 tile, offset;

	for (u8 i = 0; i < num_dirty_tiles; ++i) {

		u8 dx = dirty_tiles[i].x;
		u8 dy = dirty_tiles[i].y;

		/* Bounds check (protect against out-of-range coordinates) */
		if (dx >= SCREEN_U_W)
			dx = SCREEN_U_W - 1;
		if (dy >= SCREEN_U_H)
			dy = SCREEN_U_H - 1;

		/*
		 * We need to recompute v_pos, as it might be misaligned during
		 * the tween frames, especially on the bottom row
		 */
		u8 vx = GAME_WINDOW_X + (dx << TILE_B_W_SHIFT); /* dx * 4 */
		u8 vy = GAME_WINDOW_Y + (dy << TILE_B_H_SHIFT); /* dy * 16 */
		u8 *v_pos = cpct_getScreenPtr(CPCT_VMEM_START, vx, vy);

		/* Compute linear FG/BG tile index for this screen */
		tile = utils_get_screen_x_y(g_player.screen, dx, dy);

		/* Foreground tile gets priority */
		if (g_level_fg[tile] != 0) {

			offset = ((u16)g_level_fg[tile]) << 6; /* *64 bytes */
			spr = (u8 *)(v_tileset_start + offset);

			cpct_drawSprite(spr, v_pos, TILE_B_W, TILE_B_H);

		} else {

			u8 bg = g_screen_bg[(dy * SCREEN_U_W) + dx];

			offset = ((u16)bg) << 6;
			spr = (u8 *)(v_tileset_start + offset);

			cpct_drawSprite(spr, v_pos, TILE_B_W, TILE_B_H);
		}
	}
}

void video_draw_bullet(void) {

	if (!g_bullet.active)
		return;

	cpct_drawSpriteMaskedAlignedTable(
		v_tile_bullet, /* your bullet sprite base */
		g_bullet.v_pos, TILE_B_W, TILE_B_H, v_mask_table);
}

/* Draw player sprite (masked using the transparency table)  */
void video_draw_player(void) {

	u16 offset;
	u8 *spr;
	u16 tile;

	/* Get tile to draw (each is 64 bytes) */
	offset = ((u16)g_player.s_idx << 6);
	if (g_options & OPT_CHARACTER)
		spr = (u8 *)(reginald_m_16x16_00) + offset;
	else
		spr = (u8 *)(regina_m_16x16_00) + offset;

	cpct_drawSpriteMaskedAlignedTable(
		spr, g_player.v_pos, PLAYER_B_W, PLAYER_B_H, v_mask_table);

	tile = utils_get_screen_x_y(
		g_player.screen, g_player.grid_x, g_player.grid_y);
}

void video_flash_border_triplet(u8 c0, u8 c1, u8 c2) {

	/* Fade up */
	cpct_setBorder(c0);
	cpct_waitVSYNC();

	cpct_setBorder(c1);
	cpct_waitVSYNC();

	cpct_setBorder(c2);
	cpct_waitVSYNC();

	/* Fade down */
	cpct_setBorder(c1);
	cpct_waitVSYNC();

	cpct_setBorder(c0);
	cpct_waitVSYNC();

	cpct_setBorder(HW_BLACK);
}

void video_monster_draw_all(void) {

	monster_t *m;
	u8 i;
	u8 sx, sy;
	u8 *vpos;
	u8 spr_index;
	u8 base, dir_offset;
	u16 offset;
	u8 *spr;

	for (i = 0; i < MAX_MONSTERS; ++i) {

		m = &g_monsters[i];

		if (!m->active)
			continue;

		if (m->screen != g_player.screen)
			continue;

		/* Fresh pointer (supports half-tile movement) */
		sx = GAME_WINDOW_X + m->byte_x;
		sy = GAME_WINDOW_Y + m->byte_y;
		vpos = cpct_getScreenPtr(CPCT_VMEM_START, sx, sy);

		/*  Determine sprite index */
		switch (m->type) {

		case MON_BAT:
			/* 2-frame flap cycle */
			spr_index = (g_frame_c & 0x08) ? 1 : 2;
			break;

		case MON_ZOMBIE:
			base = 3;		 /* Zombie frames start at 3 */
			dir_offset = m->dir * 3; /* NSEW → 0,3,6,9 */
			spr_index = base + dir_offset + m->anim_frame;
			break;

		case MON_GHOST:
			base = 15;		 /* Ghost frames start at 15 */
			dir_offset = m->dir * 3; /* NSEW → 0,3,6,9 */
			spr_index = base + dir_offset + m->anim_frame;
			break;

		default:
			continue;
		}

		/* Convert sprite index → pointer (×64 bytes) */
		offset = ((u16)spr_index) << 6;
		spr = (u8 *)(tile_m_16x16_00) + offset;

		cpct_drawSpriteMaskedAlignedTable(
			spr, vpos, TILE_B_W, TILE_B_H, v_mask_table);
	}
}

void video_draw_xor_sprite(const u8 *spr, u8 x, u8 y) {

	u8 *vpos = cpct_getScreenPtr(CPCT_VMEM_START, x, y);

	cpct_drawSpriteBlended(vpos, 16, 4, spr);
}
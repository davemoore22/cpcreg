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

#pragma codeseg CODE

#include "menu.h"

u8 m_toggle_cooldown = 0;
bool m_menu_input_enabled = true;

const u8 border_flash[] = {
	HW_BLACK,
	HW_RED,
	HW_BRIGHT_RED,
	HW_RED,
	HW_BLACK,
};

walker_t reg_walk, regina_walk;

static void menu_step_walker(walker_t *w);
static const u8 *victory_reginald_frame(u8 idx);
static const u8 *victory_regina_frame(u8 idx);

void menu_start(void) {

	cpct_akp_musicInit(g_music);

	video_reset_timers();
	cpct_waitVSYNCStart();
	cpct_setInterruptHandler(menu_interrupt);

	m_menu_input_enabled = true;
	menu_init_walkers();
}

void menu_draw_from_disc(const bool load_bg) {

	if (load_bg)
		utils_load("MENU    SCR", VIDEO_MEM_START);

	video_clear_centre();
	menu_draw_title();
	menu_draw_centre();
}

void menu_stop(void) {

	/* Only when leaving for the game do we actually clear */
	cpct_akp_stop();
	cpct_removeInterruptHandler();
	video_full_clear();
}

void menu_draw_title(void) {

	video_draw_title(TITLE_Y);
}

void menu_draw_centre(void) {

	u8 x = MENU_X, y = MENU_Y;

	v_pen = PEN_3;
	for (u8 i = 0; i < 7; ++i) {
		video_print_text(
			g_strings[MENU_TEXT + i], x, y << LINE_P_H_SHIFT);
		y += 2;
	}

	video_print_centred_text(
		g_strings[ABOUT_TEXT], ABOUT_Y << LINE_P_H_SHIFT);
	video_print_centred_text(
		g_strings[PUBLISHED_TEXT], (ABOUT_Y + 1) << LINE_P_H_SHIFT);

	v_pen = PEN_2;
	video_print_centred_text("v1.0.3", (ABOUT_Y + 2) << LINE_P_H_SHIFT);

	v_pen = PEN_1;
}

void menu_interrupt(void) {

	static const u8 palette[6][4] = {
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PASTEL_YELLOW},
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_ORANGE},
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PASTEL_YELLOW},
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PASTEL_YELLOW},
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PASTEL_BLUE},
		{HW_BLACK, HW_RED, HW_BRIGHT_RED, HW_PASTEL_BLUE}};

	if (v_int_idx == 4)
		utils_wait(58);

	cpct_setPalette(palette[v_int_idx], sizeof(palette[v_int_idx]));

	if (v_int_idx == 1 && m_menu_input_enabled)
		cpct_scanKeyboard_if();

	if (v_int_idx == 0 && m_toggle_cooldown > 0)
		--m_toggle_cooldown;

	/* Play Music */
	// if (v_int_idx == 4)
	//	cpct_akp_musicPlay();

	if (++v_int_idx == 6)
		v_int_idx = 0;

	if (++v_frame_c == 50)
		v_frame_c = 0;
}

void menu_init_walkers(void) {

	reg_walk.y = WALKER_BOTTOM;
	reg_walk.going_down = true;
	reg_walk.frame = 0;
	reg_walk.drawn = false;
	reg_walk.anim_delay = 6;
	reg_walk.anim_phase = 0;

	regina_walk.y = WALKER_TOP;
	regina_walk.going_down = true;
	regina_walk.frame = 0;
	regina_walk.drawn = false;
	regina_walk.anim_delay = 6;
	regina_walk.anim_phase = 0;
}

static void menu_step_walker(walker_t *w) {

	bool old_dir = w->going_down;

	/* Move vertical position */
	if (w->going_down) {
		if (++w->y >= WALKER_BOTTOM)
			w->going_down = false;
	} else {
		if (--w->y <= WALKER_TOP)
			w->going_down = true;
	}

	/* f direction flipped this frame */
	if (old_dir != w->going_down) {

		if (w->going_down) {
			/* SOUTH = frames 3–5 */
			w->frame = 3;
		} else {
			/* NORTH = frames 0–2 */
			w->frame = 0;
		}

		w->anim_phase = 0;
		return;
	}

	/* Animation pacing */
	if (++w->anim_phase >= w->anim_delay) {

		w->anim_phase = 0;

		if (w->going_down) {
			/* SOUTH band */
			w->frame++;
			if (w->frame > 5)
				w->frame = 3;
		} else {
			/* NORTH band */
			w->frame++;
			if (w->frame > 2)
				w->frame = 0;
		}
	}
}

static const u8 *victory_reginald_frame(u8 idx) {

	return reginald_m_16x16_00 + (idx << 6);
}

static const u8 *victory_regina_frame(u8 idx) {

	return regina_m_16x16_00 + (idx << 6);
}

void menu_draw_walkers(void) {

	if (v_int_idx != 0)
		return;

	{
		u8 x = 16;

		if (reg_walk.drawn) {
			video_draw_xor_sprite(
				victory_reginald_frame(reg_walk.frame), x,
				reg_walk.y);
		}

		menu_step_walker(&reg_walk);
		video_draw_xor_sprite(
			victory_reginald_frame(reg_walk.frame), x, reg_walk.y);

		reg_walk.drawn = true;
	}

	{
		u8 x = 60;

		if (regina_walk.drawn) {
			video_draw_xor_sprite(
				victory_regina_frame(regina_walk.frame), x,
				regina_walk.y);
		}

		menu_step_walker(&regina_walk);
		video_draw_xor_sprite(victory_regina_frame(regina_walk.frame),
			x, regina_walk.y);

		regina_walk.drawn = true;
	}
}

cpct_keyID menu_poll_input(void) {

	cpct_scanKeyboard_f();

	if (cpct_isKeyPressed(Key_0))
		return Key_0;
	if (cpct_isKeyPressed(Key_1))
		return Key_1;
	if (cpct_isKeyPressed(Key_2))
		return Key_2;
	if (cpct_isKeyPressed(Key_3))
		return Key_3;
	if (cpct_isKeyPressed(Key_4))
		return Key_4;
	if (cpct_isKeyPressed(Key_5))
		return Key_5;
	if (cpct_isKeyPressed(Key_Tab) && (g_options & OPT_CHEAT))
		return Key_Tab;
	if (cpct_isKeyPressed(Key_9))
		return Key_9;

	return 0xFF;
}
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

#include "victory.h"

/* Globals */
static u16 last_x[2] = {0, 0};
static u8 last_valid[2] = {0, 0};

static const u8 palette_1[4] = {
	HW_BLACK,
	HW_RED,
	HW_PURPLE,
	HW_BRIGHT_WHITE,
};
static const u8 palette_2[4] = {
	HW_BLACK,
	HW_RED,
	HW_BRIGHT_RED,
	HW_PASTEL_YELLOW,
};

static u8 v_animation_frame;

/* Private Functions */
static void victory_draw(void);
static void victory_reset_colours(bool which);
static void victory_interrupt(void);
static void victory_fade_to_black(void);
static void victory_wait_or_kp(void);
static void victory_show_text(const char *s);
static void victory_wait_s(u8 s);
static void victory_draw_character(u8 id, u16 x, u8 y);
static void victory_erase_character(u8 id);
static void victory_clear_text(void);
static void victory_do_kill(void);
static void victory_do_animation(void);
static void victory_do_return(void);
static void victory_do_uncle(void);
static void victory_draw_weems_xor_sprite(const u8 *spr, u8 x, u8 y);
static inline void victory_wait_n_vsync(u8 n);

static const u8 *victory_regina_frame(u8 idx);
static const u8 *victory_reginald_frame(u8 idx);

/* Character IDs */
#define CHAR_WEEMS 0
#define CHAR_REGINALD 1
#define CHAR_REGINA 2

/* Where on screen they walk (Mode 1, sprite height assumed) */
#define WALK_Y 120
#define LEFT_X 0
#define RIGHT_X 74

/* Movement speed in pixels per frame */
#define STEP 2

/* Start the Victory Screen */
void victory_start(void) {

	cpct_setInterruptHandler(victory_interrupt);

	cpct_waitVSYNC();

	victory_reset_colours(false);
	video_reset_timers();

	/* Just in case the Sprites were left facing the "wrong" way */
	game_update_player_facing(DIR_EAST);

	victory_do_kill();
	victory_do_uncle();
	victory_do_animation();
	victory_do_return();
}

static void victory_wait_or_kp(void) {

	utils_reset_clock();

	/* Start Clock */
	u16 duration = 20;
	g_clock_on = true;

	utils_clear_input();

	/* Display for a number of seconds or until a keypress */
	bool kp = false;
	while ((!kp) && (g_clock.s < duration)) {

		cpct_waitVSYNC();
		utils_clock_tick();
		if (cpct_isAnyKeyPressed())
			kp = true;
	}

	utils_clear_input();

	/* Stop Clock */
	g_clock_on = false;
}

/* Stop the Transition "Between" Screen */
void victory_stop(void) {

	cpct_removeInterruptHandler();
	utils_reset_clock();
}

static void victory_reset_colours(bool which) {

	cpct_setPalette(which ? palette_1 : palette_2, 4);
}

static void victory_draw(void) {

	utils_load("VICTORY SCR", VIDEO_MEM_START);
}

static void victory_interrupt(void) {

	if (v_int_idx == 0) {
		if (++g_frame_c == FC_MAX)
			g_frame_c = 0;
	}

	if (v_int_idx == 2)
		cpct_scanKeyboard_if();

	if (v_int_idx == 4)
		sfx_update();

	if (++v_int_idx == 6)
		v_int_idx = 0;

	utils_clock_interrupt();
}

/* Random-pixel fade-to-black */
static void victory_fade_to_black(void) {

	u8 *vmem = (u8 *)CPCT_VMEM_START;
	const u16 screen_bytes = 0x4000;
	const u32 iterations = screen_bytes * 6UL;
	bool swap = false;
	cpct_setBorder(HW_RED);

	for (u32 i = 0; i < iterations; i++) {

		u16 offset = cpct_getRandom_glfsr16_u16() & (screen_bytes - 1);
		vmem[offset] = 0x00;

		if ((i & 0x0FFF) == 0) {
			cpct_waitVSYNC();
			swap = !swap;
			if (swap) {
				cpct_setBorder(HW_BRIGHT_RED);
				cpct_setPALColour(3, HW_ORANGE);
			} else {
				cpct_setBorder(HW_ORANGE);
				cpct_setPALColour(3, HW_BRIGHT_YELLOW);
			}
			sfx_start((void *)sfx_splat);
		}
	}
}

static void victory_do_uncle(void) {

	/* Clear the Screen */
	video_blank_screen();
	video_clear_screen();
	victory_reset_colours(false);

	video_print_centred_text("BUT WHERE IS YOUR UNCLE?", 10 * LINE_P_H);
	video_print_centred_text("HE IS NOWHERE TO BE FOUND!", 12 * LINE_P_H);
	victory_wait_or_kp();

	v_pen = 2;
	video_print_centred_text(
		"SUDDENLY THERE IS A SCREAM FROM NEARBY!", 15 * LINE_P_H);
	v_pen = 3;
	victory_wait_or_kp();
	video_clear_screen();
}

static void victory_do_kill(void) {

	v_pen = 3;
	video_print_centred_text(
		"YOU HAVE FOUND THE DREAD VAMPIRESS!", 10 * LINE_P_H);
	video_print_centred_text("SHE IS ASLEEP!", 12 * LINE_P_H);
	victory_wait_or_kp();

	video_print_centred_text(
		"QUICKLY YOU SLAY HER BEFORE SHE WAKES!", 15 * LINE_P_H);
	victory_wait_or_kp();

	video_blank_screen();
	video_clear_screen();

	/* Draw Graphic */
	g_clock_on = false;

	cpct_removeInterruptHandler();
	victory_draw();
	cpct_setInterruptHandler(victory_interrupt);
	g_clock_on = true;

	victory_reset_colours(true);
	victory_wait_or_kp();

	cpct_setPALColour(2, HW_BRIGHT_RED);
	cpct_setPALColour(3, HW_ORANGE);
	victory_fade_to_black();
	video_clear_screen();
	video_blank_screen();
}

static void victory_do_return(void) {

	video_clear_screen();
	victory_reset_colours(false);
	video_print_centred_text(
		"REGINALD AND REGINA WILL RETURN!", 7 * LINE_P_H);
	victory_wait_or_kp();

	v_pen = 2;
	video_print_centred_text("AND SO WILL MR WEEMS!", 10 * LINE_P_H);
	victory_wait_or_kp();
	video_print_centred_text("IF HE CAN BE CAUGHT!", 12 * LINE_P_H);
	victory_wait_or_kp();
	v_pen = 3;
	video_print_centred_text("KEEP AN EYE OUT FOR:", 15 * LINE_P_H);
	video_print_centred_text(
		"WEEMS 3: REGINA AND THE HE VAMPIRES!", 17 * LINE_P_H);
	victory_wait_or_kp();
	victory_wait_or_kp();
	video_clear_screen();
	video_blank_screen();
}

void victory_do_animation(void) {

	/* Step 1: Mr Weems appears on the left */
	u16 x = LEFT_X;
	v_animation_frame = 0;
	victory_draw_character(CHAR_WEEMS, x, WALK_Y);

	v_pen = PEN_2;
	victory_show_text("AIEEEE!!!!! ARGHHHHH!!!!!");
	victory_wait_s(5);
	victory_clear_text();

	/* Step 2: Mr Weems runs to the right */
	while (x < RIGHT_X) {
		x += STEP;
		victory_draw_character(CHAR_WEEMS, x, WALK_Y);
		victory_wait_n_vsync(30);
	}

	victory_show_text("BLURBLE BLURBLE BLURBLE!");
	victory_wait_s(5);
	victory_clear_text();

	/* Step 3: Reginald/Regina appears */
	u8 reg_id = (g_options & OPT_CHARACTER) ? CHAR_REGINALD : CHAR_REGINA;

	x = LEFT_X;
	victory_wait_s(5);
	v_animation_frame = 0;
	victory_draw_character(reg_id, x, WALK_Y);

	v_pen = PEN_3;
	if (g_options & OPT_CHARACTER)
		victory_show_text("UNCLE! ARE YOU OK? ITS ME, REGINALD!");
	else
		victory_show_text("UNCLE! ARE YOU OK? ITS ME, REGINA!");
	victory_wait_s(5);
	victory_clear_text();

	v_pen = PEN_2;
	victory_show_text("WIBBLE!!! GET AWAY FROM ME, FIEND!");
	victory_wait_s(5);
	victory_clear_text();

	/* Step 4: Mr Weems disappears */
	victory_erase_character(CHAR_WEEMS);
	victory_wait_s(5);

	v_pen = PEN_3;
	victory_show_text("COME BACK, UNCLE!");
	victory_wait_s(5);
	victory_clear_text();

	/* Step 5: Reginald/Regina runs to the right */
	while (x < RIGHT_X) {
		x += STEP;
		victory_draw_character(reg_id, x, WALK_Y);
		victory_wait_n_vsync(30);
	}

	victory_wait_s(5);
}

static inline void victory_wait_n_vsync(u8 n) {

	while (n--)
		cpct_waitVSYNC();
}

/* Show bottom dialogue text (placeholder) */
static void victory_show_text(const char *s) {

	video_print_centred_text(s, LINE_P_H * 22);
}

static void victory_clear_text(void) {

	video_print_text(
		"                                       ", 0, LINE_P_H * 22);
}

static void victory_wait_s(u8 seconds) {

	utils_reset_clock();
	g_clock_on = true;

	while (g_clock.s < seconds) {
		cpct_waitVSYNC();
		utils_clock_tick();
	}

	g_clock_on = false;
}

static void victory_draw_character(u8 id, u16 x, u8 y) {

	if (last_valid[id])
		victory_erase_character(id);

	++v_animation_frame;
	if (v_animation_frame > 2)
		v_animation_frame = 0;

	u8 *spr;
	if (id == CHAR_REGINALD || id == CHAR_REGINA)
		spr = (id == CHAR_REGINALD)
			      ? victory_reginald_frame(6 + v_animation_frame)
			      : victory_regina_frame(6 + v_animation_frame);
	else {
		if (v_animation_frame == 0)
			spr = weems_m_24x24_03;
		else if (v_animation_frame == 1)
			spr = weems_m_24x24_04;
		else
			spr = weems_m_24x24_05;
	}

	if (id == CHAR_WEEMS)
		victory_draw_weems_xor_sprite(spr, x, y - 8);
	else
		video_draw_xor_sprite(spr, x, y);

	last_x[id] = x;
	last_valid[id] = 1;
}

static void victory_erase_character(u8 id) {

	if (!last_valid[id])
		return;

	u8 *v_pos = cpct_getScreenPtr(CPCT_VMEM_START, last_x[id], 112);
	cpct_drawSolidBox(v_pos, 0, 6, 24);
}

static const u8 *victory_reginald_frame(u8 idx) {

	return reginald_m_16x16_00 + (idx << 6);
}

static const u8 *victory_regina_frame(u8 idx) {

	return regina_m_16x16_00 + (idx << 6);
}

static void victory_draw_weems_xor_sprite(const u8 *spr, u8 x, u8 y) {

	u8 *vpos = cpct_getScreenPtr(CPCT_VMEM_START, x, y);

	cpct_drawSpriteBlended(vpos, 24, 6, spr);
}
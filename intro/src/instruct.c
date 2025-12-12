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

#include "instruct.h"

static const char *const i_strings[3][17] = {{
                                                 "you are young weems",
                                                 "and you are looking",
                                                 " for your uncle, mr",
                                                 "weems, who has been",
                                                 "  kidnapped by the ",
                                                 "  she vampires and ",
                                                 "their foul minions!",
                                                 "",
                                                 "  armed with your  ",
                                                 "trusty shotgun, and",
                                                 "   a case of holy  ",
                                                 "  water (and some  ",
                                                 "extra blood just in",
                                                 " case!), it is time",
                                                 "   to rescue your  ",
                                                 "uncle and kick some",
                                                 "   undead arse!",
                                             },

                                             {
                                                 "",
                                                 "",
                                                 "",
                                                 " you should avoid  ",
                                                 "  the open graves  ",
                                                 " with your name on ",
                                                 " them and blast the",
                                                 "canoptic urns; then",
                                                 "  smash the creepy ",
                                                 "  sarcophagi, and  ",
                                                 " stick your tongue ",
                                                 " out at the weird  ",
                                                 "  ominous statues! ",
                                                 "",
                                                 "",
                                                 "",
                                                 "",
                                             },

                                             {
                                                 "search for keys to ",
                                                 "  open the creaky  ",
                                                 " doors to retrieve ",
                                                 " the ancient relics",
                                                 "  you will need to ",
                                                 "  destroy the evil ",
                                                 " lich phylacteries ",
                                                 "    so you can     ",
                                                 "confront the dread ",
                                                 " vampire queen, and",
                                                 "  obliterate her   ",
                                                 " before your uncle ",
                                                 " becomes one of the",
                                                 "  dreaded undead!  ",
                                                 "",
                                                 "",
                                                 "  <PRESS ANY KEY>  ",
                                             }};

/* Draw Instructions Screen */
void instruct_draw(u8 page) {

  u8 y = 4 * LINE_P_H;
  u8 x = 20 * LINE_P_W;

  u8 *v_pos;

  v_pos = video_get_pos(40, y);
  cpct_drawSolidBox(v_pos, 0, 40, 140);

  for (u8 i = 0; i < 17; i++) {
    video_print(i_strings[page][i], x, y);
    y += LINE_P_H;
  }
}

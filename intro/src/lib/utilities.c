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

#include "utilities.h"

/* Enable Global Timer */
bool g_clock_on;

/* Private Functions */
static void u_reverse_str(char *str, u16 length);
static void u_reverse_fixed_str(char *str, u16 start, u16 end);

/* Realtime Clock */
clock_t g_clock = {.ms = 0, .s = 0};

/* Reverse a String */
static void u_reverse_str(char *str, u16 length) {

  u16 start = 0, end = length - 1;
  while (start < end) {
    char tmp = str[start];
    str[start++] = str[end];
    str[end--] = tmp;
  }
}

/* String Length (without using strlen) */
u8 utils_str_len(const char *str) {

  u8 length = 0;

  while (*str != '\0') {
    length++;
    str++;
  }

  return length;
}

/* Rotate a string left (without using any additional memory) */
void utils_rotate_str_fixed(char *str, u16 n, u16 len) {

  if (len <= 1)
    return;

  n = n % len;
  if (n == 0)
    return;

  u_reverse_fixed_str(str, 0, n - 1);
  u_reverse_fixed_str(str, n, len - 1);
  u_reverse_fixed_str(str, 0, len - 1);
}

/* Reverse a fixed string */
static void u_reverse_fixed_str(char *str, u16 start, u16 end) {

  char tmp;

  while (start < end) {
    tmp = str[start];
    str[start] = str[end];
    str[end] = tmp;
    start++;
    end--;
  }
}

/* Copy a string (without using strcpy) up to a certain length */
void utils_str_cpy_n(char *dest, const char *src, u16 n) {

  u16 i = 0;

  /* Copy up to n characters or until null terminator in src */
  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }

  /* Null-terminate the destination string */
  if (i < n) {
    dest[i] = '\0';
  } else {
    dest[n - 1] = '\0'; /* ensure null-termination at last byte if
                           limit hit */
  }
}

/* Copy a string (without using strcpy) */
char *utils_str_cpy(char *dest, const char *src) {

  char *original_dest = dest;

  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }

  /* Null-terminate the destination string */
  *dest = '\0';

  return original_dest;
}

/* Get the Width (in digits, i.e. characters) of a Number */
u8 u_get_width(const u32 score) {

  u8 width = 0;
  u32 num = score;

  do {
    num /= 10;
    ++width;
  } while (num != 0);

  return width;
}

/* Interrupt function used by Realtime Clock */
void utils_clock_interrupt(void) {

  static u8 count = 0;

  /* Skip if the Realtime Clock is not enabled */
  if (g_clock_on) {

    /*
     * On a CPC, interrupts are called every 1/300 of a second,
     * therefore we throttle this function down to only do a tick
     * every 1/50 of a second (20 microseconds)
     */
    count = ++count % 6;
    if (count == 5) {
      g_clock.ms += 20;
      if (g_clock.ms == 1000) {
        ++g_clock.s;
        g_clock.ms = 0;
      }
    }

    /*
     * Note that this will cause an error once g_timer_s > 65535,
     * or just over 18 hours; for efficiency purposes we do not
     * check for this overlow!
     */
  }
}

/* Reset Clock */
void utils_reset_clock(void) { g_clock.ms = g_clock.s = 0; }

void utils_load(char file_name[12], u8 *loc) {

  asm_fdc_on();
  asm_load_file(file_name, loc, g_disk_table);
  asm_fdc_off();
}

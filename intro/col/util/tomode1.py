#!/usr/bin/env python3

import struct
import sys
import os

# ---------------------------------------------------------------
# Utility: read next meaningful line (skip comments & blank lines)
# ---------------------------------------------------------------
def ppm_readline(f):
    while True:
        line = f.readline()
        if not line:
            return None
        line = line.strip()
        if line == "" or line.startswith("#"):
            continue
        return line

# ---------------------------------------------------------------
# MODE 1 byte encoding (4 pixels -> 1 byte)
# ---------------------------------------------------------------
def pack_mode1_pixels(a, b, c, d):
    # MODE 1 uses 2 bits per pixel, arranged strangely:
    # bit7=a1 bit6=b1 bit5=c1 bit4=d1 bit3=a0 bit2=b0 bit1=c0 bit0=d0
    return ((a & 1) << 7) | ((b & 1) << 6) | ((c & 1) << 5) | ((d & 1) << 4) | \
           ((a >> 1) << 3) | ((b >> 1) << 2) | ((c >> 1) << 1) | ((d >> 1))

# ---------------------------------------------------------------
# MAIN CONVERSION FUNCTION
# ---------------------------------------------------------------
def convert_ppm_to_scr(input_filename):

    # Output file
    base = os.path.splitext(input_filename)[0]
    out_filename = base + ".scr"

    # -----------------------------------------------------------
    # Load PPM
    # -----------------------------------------------------------
    with open(input_filename, "r") as f:

        # Header
        magic = ppm_readline(f)
        if magic != "P3":
            print("ERROR: Only ASCII PPM (P3) supported.")
            return

        dims = ppm_readline(f)
        xdim, ydim = [int(v) for v in dims.split()]

        maxval = int(ppm_readline(f))
        if maxval != 255:
            print("WARNING: maxval != 255, colours may be scaled.")

        # -------------------------------------------------------
        # Read pixel data, build initial palette
        # -------------------------------------------------------
        palette = []
        pixel_data = []

        # --- NEW: Force black to be palette index 0 if present ---
        FORCE_BLACK = True
        if FORCE_BLACK:
            palette.append((0, 0, 0))   # reserve pen 0 for black

        for y in range(ydim):
            row = []
            for x in range(xdim):

                r = int(ppm_readline(f))
                g = int(ppm_readline(f))
                b = int(ppm_readline(f))

                col = (r, g, b)

                if col not in palette:
                    if len(palette) >= 4:
                        print("ERROR: More than 4 colours found (not valid MODE 1).")
                        return
                    palette.append(col)

                row.append(palette.index(col))

            pixel_data.append(row)

    # -----------------------------------------------------------
    # Warn on non-standard size
    # -----------------------------------------------------------
    if xdim != 320 or ydim != 200:
        print("WARNING: Expected 320x200 for full CPC screen")

    # -----------------------------------------------------------
    # CPC SCREEN MEMORY MAPPING
    # -----------------------------------------------------------
    scr = bytearray(16384)  # Exact size of a CPC .SCR file

    # CPC line layout:
    # y → (y % 8) * 2048  +  (y // 8) * 80
    for y in range(ydim):
        row_group  = y // 8
        row_offset = y % 8
        base_addr = (row_offset * 2048) + (row_group * 80)

        # pack 4 pixels at a time
        for x in range(0, xdim, 4):
            p0 = pixel_data[y][x]
            p1 = pixel_data[y][x+1]
            p2 = pixel_data[y][x+2]
            p3 = pixel_data[y][x+3]

            scr[base_addr + (x // 4)] = pack_mode1_pixels(p0, p1, p2, p3)

    # -----------------------------------------------------------
    # Write output
    # -----------------------------------------------------------
    with open(out_filename, "wb") as f:
        f.write(scr)

    # -----------------------------------------------------------
    # Print Palette Summary
    # -----------------------------------------------------------
    print(f"✓ Wrote SCR file: {out_filename}")
    print(f"Final Palette ({len(palette)} colours):")

    for i, (r, g, b) in enumerate(palette):
        # Convert RGB to CPC ink index (0–26)
        cpc = (g // 127) * 9 + (r // 127) * 3 + (b // 127)
        print(f"  INK {i}, {cpc}   ({r},{g},{b})")

    print("\nPen 0 is guaranteed to be black if black appears in the image.")

# ---------------------------------------------------------------
# CLI
# ---------------------------------------------------------------
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 ppm_to_scr_mode1.py image.ppm")
        sys.exit(1)

    convert_ppm_to_scr(sys.argv[1])

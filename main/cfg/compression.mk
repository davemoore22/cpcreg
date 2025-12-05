##-----------------------------LICENSE NOTICE------------------------------------
##  This file is part of CPCtelera: An Amstrad CPC Game Engine 
##  Copyright (C) 2018 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
##
##  This program is free software: you can redistribute it and/or modify
##  it under the terms of the GNU Lesser General Public License as published by
##  the Free Software Foundation, either version 3 of the License, or
##  (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU Lesser General Public License for more details.
##
##  You should have received a copy of the GNU Lesser General Public License
##  along with this program.  If not, see <http://www.gnu.org/licenses/>.
##------------------------------------------------------------------------------
############################################################################
##                        CPCTELERA ENGINE                                ##
##                 Automatic compression utilities                        ##
##------------------------------------------------------------------------##
## This file is intended for users to automate the generation of          ##
## compressed files and their inclusion in users' projects.               ##
############################################################################

## COMPRESSION EXAMPLE (Uncomment lines to use)
##

## First 3 calls to ADD2PACK add enemy, hero and background
## graphics (previously converted to binary data) into the 
## compressed group 'mygraphics'. After that, call to PACKZX7B
## compresses all the data and generates an array with the result
## that is placed in src/mygraphics.c & src/mygraphics.h, ready
## to be included and used by other modules.
##
#$(eval $(call ADD2PACK,mygraphics,gfx/enemy.bin))
#$(eval $(call ADD2PACK,mygraphics,gfx/hero.bin))
#$(eval $(call ADD2PACK,mygraphics,gfx/background.bin))
#$(eval $(call PACKZX7B,mygraphics,src/))




############################################################################
##              DETAILED INSTRUCTIONS AND PARAMETERS                      ##
##------------------------------------------------------------------------##
##                                                                        ##
## Macros used for compression are ADD2PACK and PACKZX7B:                 ##
##                                                                        ##
##	ADD2PACK: Adds files to packed (compressed) groups. Each call to this ##
##  		  macro will add a file to a named compressed group.          ##
##  PACKZX7B: Compresses all files in a group into a single binary and    ##
##            generates a C-array and a header to comfortably use it from ##
##            inside your code.                                           ##
##                                                                        ##
##------------------------------------------------------------------------##
##                                                                        ##
##  $(eval $(call ADD2PACK,<packname>,<file>))                            ##
##                                                                        ##
##		Sequentially adds <file> to compressed group <packname>. Each     ##
## call to this macro adds a new <file> after the latest one added.       ##
## packname could be any valid C identifier.                              ##
##                                                                        ##
##  Parameters:                                                           ##
##  (packname): Name of the compressed group where the file will be added ##
##  (file)    : File to be added at the end of the compressed group       ##
##                                                                        ##
##------------------------------------------------------------------------##
##                                                                        ##
##  $(eval $(call PACKZX7B,<packname>,<dest_path>))                       ##
##                                                                        ##
##		Compresses all files in the <packname> group using ZX7B algorithm ##
## and generates 2 files: <packname>.c and <packname>.h that contain a    ##
## C-array with the compressed data and a header file for declarations.   ##
## Generated files are moved to the folder <dest_path>.                   ##
##                                                                        ##
##  Parameters:                                                           ##
##  (packname) : Name of the compressed group to use for packing          ##
##  (dest_path): Destination path for generated output files              ##
##                                                                        ##
############################################################################
##                                                                        ##
## Important:                                                             ##
##  * Do NOT separate macro parameters with spaces, blanks or other chars.##
##    ANY character you put into a macro parameter will be passed to the  ##
##    macro. Therefore ...,src/sprites,... will represent "src/sprites"   ##
##    folder, whereas ...,  src/sprites,... means "  src/sprites" folder. ##
##  * You can omit parameters by leaving them empty.                      ##
##  * Parameters (4) and (5) are optional and generally not required.     ##
############################################################################

## DSM - compress transition image
#$(eval $(call ADD2PACK,between,tmp/between.bin))
#$(eval $(call PACKZX7B,between,out/))

#$(eval $(call ADD2PACK,title,tmp/title.bin))
#$(eval $(call PACKZX7B,title,out/))

#$(eval $(call ADD2PACK,gui,tmp/gui.bin))
#$(eval $(call PACKZX7B,gui,out/))

#$(eval $(call ADD2PACK,frame,tmp/frame.bin))
#$(eval $(call PACKZX7B,frame,out/))

#$(eval $(call ADD2PACK,presents,tmp/presents.bin))
#$(eval $(call PACKZX7B,presents,out/))




#$(eval $(call ADD2PACK,l_level_1_fg,out/level1-fg.bin))
#$(eval $(call PACKZX7B,l_level_1_fg,out/))

#$(eval $(call ADD2PACK,level_1_0_bg,out/1-0-bg.bin))
#$(eval $(call PACKZX7B,level_1_0_bg,out/))
#$(eval $(call ADD2PACK,level_1_1_bg,out/1-1-bg.bin))
#$(eval $(call PACKZX7B,level_1_1_bg,out/))
#$(eval $(call ADD2PACK,level_1_2_bg,out/1-2-bg.bin))
#$(eval $(call PACKZX7B,level_1_2_bg,out/))
#$(eval $(call ADD2PACK,level_1_3_bg,out/1-3-bg.bin))
#$(eval $(call PACKZX7B,level_1_3_bg,out/))
#$(eval $(call ADD2PACK,level_1_4_bg,out/1-4-bg.bin))
#$(eval $(call PACKZX7B,level_1_4_bg,out/))
#$(eval $(call ADD2PACK,level_1_5_bg,out/1-5-bg.bin))
#$(eval $(call PACKZX7B,level_1_5_bg,out/))
#$(eval $(call ADD2PACK,level_1_6_bg,out/1-6-bg.bin))
#$(eval $(call PACKZX7B,level_1_6_bg,out/))
#$(eval $(call ADD2PACK,level_1_7_bg,out/1-7-bg.bin))
#$(eval $(call PACKZX7B,level_1_7_bg,out/))
#$(eval $(call ADD2PACK,level_1_8_bg,out/1-8-bg.bin))
#$(eval $(call PACKZX7B,level_1_8_bg,out/))
#$(eval $(call ADD2PACK,level_1_9_bg,out/1-9-bg.bin))
#$(eval $(call PACKZX7B,level_1_9_bg,out/))
#$(eval $(call ADD2PACK,level_1_10_bg,out/1-10-bg.bin))
#$(eval $(call PACKZX7B,level_1_10_bg,out/))
#$(eval $(call ADD2PACK,level_1_11_bg,out/1-11-bg.bin))
#$(eval $(call PACKZX7B,level_1_11_bg,out/))

#$(eval $(call ADD2PACK,level_2_fg,out/level2-fg.bin))
#$(eval $(call PACKZX7B,level_2_fg,out/))


#$(eval $(call ADD2PACK,level_2_0_bg,out/2-0-bg.bin))
#$(eval $(call PACKZX7B,level_2_0_bg,out/))
#$(eval $(call ADD2PACK,level_2_1_bg,out/2-1-bg.bin))
#$(eval $(call PACKZX7B,level_2_1_bg,out/))
#$(eval $(call ADD2PACK,level_2_2_bg,out/2-2-bg.bin))
#$(eval $(call PACKZX7B,level_2_2_bg,out/))
#$(eval $(call ADD2PACK,level_2_3_bg,out/2-3-bg.bin))
#$(eval $(call PACKZX7B,level_2_3_bg,out/))
#$(eval $(call ADD2PACK,level_2_4_bg,out/2-4-bg.bin))
#$(eval $(call PACKZX7B,level_2_4_bg,out/))
#$(eval $(call ADD2PACK,level_2_5_bg,out/2-5-bg.bin))
#$(eval $(call PACKZX7B,level_2_5_bg,out/))
#$(eval $(call ADD2PACK,level_2_6_bg,out/2-6-bg.bin))
#$(eval $(call PACKZX7B,level_2_6_bg,out/))
#$(eval $(call ADD2PACK,level_2_7_bg,out/2-7-bg.bin))
#$(eval $(call PACKZX7B,level_2_7_bg,out/))
#$(eval $(call ADD2PACK,level_2_8_bg,out/2-8-bg.bin))
#$(eval $(call PACKZX7B,level_2_8_bg,out/))
#$(eval $(call ADD2PACK,level_2_9_bg,out/2-9-bg.bin))
#$(eval $(call PACKZX7B,level_2_9_bg,out/))
#$(eval $(call ADD2PACK,level_2_10_bg,out/2-10-bg.bin))
#$(eval $(call PACKZX7B,level_2_10_bg,out/))
#$(eval $(call ADD2PACK,level_2_11_bg,out/2-11-bg.bin))
#$(eval $(call PACKZX7B,level_2_11_bg,out/))

#$(eval $(call ADD2PACK,level_3_fg,out/level3-fg.bin))
#$(eval $(call PACKZX7B,level_3_fg,out/))

#$(eval $(call ADD2PACK,level_3_0_bg,out/3-0-bg.bin))
#$(eval $(call PACKZX7B,level_3_0_bg,out/))
#$(eval $(call ADD2PACK,level_3_1_bg,out/3-1-bg.bin))
#$(eval $(call PACKZX7B,level_3_1_bg,out/))
#$(eval $(call ADD2PACK,level_3_2_bg,out/3-2-bg.bin))
#$(eval $(call PACKZX7B,level_3_2_bg,out/))
#$(eval $(call ADD2PACK,level_3_3_bg,out/3-3-bg.bin))
#$(eval $(call PACKZX7B,level_3_3_bg,out/))
#$(eval $(call ADD2PACK,level_3_4_bg,out/3-4-bg.bin))
#$(eval $(call PACKZX7B,level_3_4_bg,out/))
#$(eval $(call ADD2PACK,level_3_5_bg,out/3-5-bg.bin))
#$(eval $(call PACKZX7B,level_3_5_bg,out/))
#$(eval $(call ADD2PACK,level_3_6_bg,out/3-6-bg.bin))
#$(eval $(call PACKZX7B,level_3_6_bg,out/))
#$(eval $(call ADD2PACK,level_3_7_bg,out/3-7-bg.bin))
#$(eval $(call PACKZX7B,level_3_7_bg,out/))
#$(eval $(call ADD2PACK,level_3_8_bg,out/3-8-bg.bin))
#$(eval $(call PACKZX7B,level_3_8_bg,out/))
#$(eval $(call ADD2PACK,level_3_9_bg,out/3-9-bg.bin))
#$(eval $(call PACKZX7B,level_3_9_bg,out/))
#$(eval $(call ADD2PACK,level_3_10_bg,out/3-10-bg.bin))
#$(eval $(call PACKZX7B,level_3_10_bg,out/))
#$(eval $(call ADD2PACK,level_3_11_bg,out/3-11-bg.bin))
#$(eval $(call PACKZX7B,level_3_11_bg,out/))


#$(eval $(call ADD2PACK,l_level_4_fg,out/level4-fg.bin))
#$(eval $(call PACKZX7B,l_level_4_fg,out/))

#$(eval $(call ADD2PACK,level_4_0_bg,out/4-0-bg.bin))
#$(eval $(call PACKZX7B,level_4_0_bg,out/))
#$(eval $(call ADD2PACK,level_4_1_bg,out/4-1-bg.bin))
#$(eval $(call PACKZX7B,level_4_1_bg,out/))
#$(eval $(call ADD2PACK,level_4_2_bg,out/4-2-bg.bin))
#$(eval $(call PACKZX7B,level_4_2_bg,out/))
#$(eval $(call ADD2PACK,level_4_3_bg,out/4-3-bg.bin))
#$(eval $(call PACKZX7B,level_4_3_bg,out/))
#$(eval $(call ADD2PACK,level_4_4_bg,out/4-4-bg.bin))
#$(eval $(call PACKZX7B,level_4_4_bg,out/))
#$(eval $(call ADD2PACK,level_4_5_bg,out/4-5-bg.bin))
#$(eval $(call PACKZX7B,level_4_5_bg,out/))
#$(eval $(call ADD2PACK,level_4_6_bg,out/4-6-bg.bin))
#$(eval $(call PACKZX7B,level_4_6_bg,out/))
#$(eval $(call ADD2PACK,level_4_7_bg,out/4-7-bg.bin))
#$(eval $(call PACKZX7B,level_4_7_bg,out/))
#$(eval $(call ADD2PACK,level_4_8_bg,out/4-8-bg.bin))
#$(eval $(call PACKZX7B,level_4_8_bg,out/))
#$(eval $(call ADD2PACK,level_4_9_bg,out/4-9-bg.bin))
#$(eval $(call PACKZX7B,level_4_9_bg,out/))
#$(eval $(call ADD2PACK,level_4_10_bg,out/4-10-bg.bin))
#$(eval $(call PACKZX7B,level_4_10_bg,out/))
#$(eval $(call ADD2PACK,level_4_11_bg,out/4-11-bg.bin))
#$(eval $(call PACKZX7B,level_4_11_bg,out/))

#$(eval $(call ADD2PACK,l_level_5_fg,out/level5-fg.bin))
#$(eval $(call PACKZX7B,l_level_5_fg,out/))


#$(eval $(call ADD2PACK,level_5_0_bg,out/5-0-bg.bin))
#$(eval $(call PACKZX7B,level_5_0_bg,out/))
#$(eval $(call ADD2PACK,level_5_1_bg,out/5-1-bg.bin))
#$(eval $(call PACKZX7B,level_5_1_bg,out/))
#$(eval $(call ADD2PACK,level_5_2_bg,out/5-2-bg.bin))
#$(eval $(call PACKZX7B,level_5_2_bg,out/))
#$(eval $(call ADD2PACK,level_5_3_bg,out/5-3-bg.bin))
#$(eval $(call PACKZX7B,level_5_3_bg,out/))
#$(eval $(call ADD2PACK,level_5_4_bg,out/5-4-bg.bin))
#$(eval $(call PACKZX7B,level_5_4_bg,out/))
#$(eval $(call ADD2PACK,level_5_5_bg,out/5-5-bg.bin))
#$(eval $(call PACKZX7B,level_5_5_bg,out/))
#$(eval $(call ADD2PACK,level_5_6_bg,out/5-6-bg.bin))
#$(eval $(call PACKZX7B,level_5_6_bg,out/))
#$(eval $(call ADD2PACK,level_5_7_bg,out/5-7-bg.bin))
#$(eval $(call PACKZX7B,level_5_7_bg,out/))
#$(eval $(call ADD2PACK,level_5_8_bg,out/5-8-bg.bin))
#$(eval $(call PACKZX7B,level_5_8_bg,out/))
#$(eval $(call ADD2PACK,level_5_9_bg,out/5-9-bg.bin))
#$(eval $(call PACKZX7B,level_5_9_bg,out/))
#$(eval $(call ADD2PACK,level_5_10_bg,out/5-10-bg.bin))
#$(eval $(call PACKZX7B,level_5_10_bg,out/))
#$(eval $(call ADD2PACK,level_5_11_bg,out/5-11-bg.bin))
#$(eval $(call PACKZX7B,level_5_11_bg,out/))


#$(eval $(call ADD2PACK,l_level_6_fg,out/level6-fg.bin))
#$(eval $(call PACKZX7B,l_level_6_fg,out/))

#$(eval $(call ADD2PACK,level_6_0_bg,out/6-0-bg.bin))
#$(eval $(call PACKZX7B,level_6_0_bg,out/))
#$(eval $(call ADD2PACK,level_6_1_bg,out/6-1-bg.bin))
#$(eval $(call PACKZX7B,level_6_1_bg,out/))
#$(eval $(call ADD2PACK,level_6_2_bg,out/6-2-bg.bin))
#$(eval $(call PACKZX7B,level_6_2_bg,out/))
#$(eval $(call ADD2PACK,level_6_3_bg,out/6-3-bg.bin))
#$(eval $(call PACKZX7B,level_6_3_bg,out/))
#$(eval $(call ADD2PACK,level_6_4_bg,out/6-4-bg.bin))
#$(eval $(call PACKZX7B,level_6_4_bg,out/))
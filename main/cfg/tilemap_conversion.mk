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
##                 Automatic image conversion file                        ##
##------------------------------------------------------------------------##
## This file is intended for users to automate tilemap conversion from    ##
## original files (like Tiled .tmx) into C-arrays.                        ##
############################################################################

##
## NEW MACROS
##

# Default values
#$(eval $(call TMX2DATA, SET_ASMVARPREFIX, yes       ))   { yes, no      }
#$(eval $(call TMX2DATA, SET_USEMACROS   , yes       ))   { yes, no      }
#$(eval $(call TMX2DATA, SET_OUTPUTS     , h c       ))   { bin hs h s c }
#$(eval $(call TMX2DATA, SET_BASE        , dec       ))   { dec hex bin }
#$(eval $(call TMX2DATA, SET_BITSPERITEM , 8         ))   { 1, 2, 4, 6, 8 }
#$(eval $(call TMX2DATA, SET_FOLDER      , src/      )) 
#$(eval $(call TMX2DATA, SET_EXTRAPAR    ,           ))	
# Conversion 
#$(eval $(call TMX2DATA, CONVERT, tmxfile, array )) 

$(eval $(call TMX2DATA, SET_ASMVARPREFIX, yes       ))
$(eval $(call TMX2DATA, SET_USEMACROS   , yes       ))
$(eval $(call TMX2DATA, SET_OUTPUTS     , bin       ))
$(eval $(call TMX2DATA, SET_BASE        , hex       ))
$(eval $(call TMX2DATA, SET_BITSPERITEM , 8         ))
$(eval $(call TMX2DATA, SET_FOLDER      , out/      )) 
$(eval $(call TMX2DATA, SET_EXTRAPAR    ,           ))

#$(eval $(call TMX2DATA, CONVERT, col/dat/level1-fg.tmx, fg_data ))
#$(eval $(call TMX2DATA, CONVERT, col/dat/level2-fg.tmx, fg_data ))
#$(eval $(call TMX2DATA, CONVERT, col/dat/level3-fg.tmx, fg_data ))
#$(eval $(call TMX2DATA, CONVERT, col/dat/level4-fg.tmx, fg_data ))
#$(eval $(call TMX2DATA, CONVERT, col/dat/level5-fg.tmx, fg_data ))
#$(eval $(call TMX2DATA, CONVERT, col/dat/level6-fg.tmx, fg_data ))

#$(eval $(call TMX2DATA, CONVERT, col/dat/1-0-bg.tmx, bg_data_1_0))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-1-bg.tmx, bg_data_1_1))
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-2-bg.tmx, bg_data_1_2))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-3-bg.tmx, bg_data_1_3))
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-4-bg.tmx, bg_data_1_4))
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-5-bg.tmx, bg_data_1_5))
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-6-bg.tmx, bg_data_1_6))
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-7-bg.tmx, bg_data_1_7))
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-8-bg.tmx, bg_data_1_8))
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-9-bg.tmx, bg_data_1_9))
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-10-bg.tmx, bg_data_1_10))
#$(eval $(call TMX2DATA, CONVERT, col/dat/1-11-bg.tmx, bg_data_1_11))	

#$(eval $(call TMX2DATA, CONVERT, col/dat/2-0-bg.tmx, bg_data_2_0))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-1-bg.tmx, bg_data_2_1))
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-2-bg.tmx, bg_data_2_2))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-3-bg.tmx, bg_data_2_3))
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-4-bg.tmx, bg_data_2_4))
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-5-bg.tmx, bg_data_2_5))
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-6-bg.tmx, bg_data_2_6))
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-7-bg.tmx, bg_data_2_7))
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-8-bg.tmx, bg_data_2_8))
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-9-bg.tmx, bg_data_2_9))
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-10-bg.tmx, bg_data_2_10))
#$(eval $(call TMX2DATA, CONVERT, col/dat/2-11-bg.tmx, bg_data_2_11))	

#$(eval $(call TMX2DATA, CONVERT, col/dat/3-0-bg.tmx, bg_data_3_0))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-1-bg.tmx, bg_data_3_1))
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-2-bg.tmx, bg_data_3_2))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-3-bg.tmx, bg_data_3_3))
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-4-bg.tmx, bg_data_3_4))
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-5-bg.tmx, bg_data_3_5))
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-6-bg.tmx, bg_data_3_6))
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-7-bg.tmx, bg_data_3_7))
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-8-bg.tmx, bg_data_3_8))
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-9-bg.tmx, bg_data_3_9))
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-10-bg.tmx, bg_data_3_10))
#$(eval $(call TMX2DATA, CONVERT, col/dat/3-11-bg.tmx, bg_data_3_11))	

#$(eval $(call TMX2DATA, CONVERT, col/dat/4-0-bg.tmx, bg_data_4_0))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-1-bg.tmx, bg_data_4_1))
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-2-bg.tmx, bg_data_4_2))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-3-bg.tmx, bg_data_4_3))
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-4-bg.tmx, bg_data_4_4))
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-5-bg.tmx, bg_data_4_5))
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-6-bg.tmx, bg_data_4_6))
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-7-bg.tmx, bg_data_4_7))
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-8-bg.tmx, bg_data_4_8))
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-9-bg.tmx, bg_data_4_9))
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-10-bg.tmx, bg_data_4_10))
#$(eval $(call TMX2DATA, CONVERT, col/dat/4-11-bg.tmx, bg_data_4_11))	

#$(eval $(call TMX2DATA, CONVERT, col/dat/5-0-bg.tmx, bg_data_5_0))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-1-bg.tmx, bg_data_5_1))
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-2-bg.tmx, bg_data_5_2))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-3-bg.tmx, bg_data_5_3))
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-4-bg.tmx, bg_data_5_4))
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-5-bg.tmx, bg_data_5_5))
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-6-bg.tmx, bg_data_5_6))
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-7-bg.tmx, bg_data_5_7))
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-8-bg.tmx, bg_data_5_8))
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-9-bg.tmx, bg_data_5_9))
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-10-bg.tmx, bg_data_5_10))
#$(eval $(call TMX2DATA, CONVERT, col/dat/5-11-bg.tmx, bg_data_5_11))

#$(eval $(call TMX2DATA, CONVERT, col/dat/6-0-bg.tmx, bg_data_6_0))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/6-1-bg.tmx, bg_data_6_1))
#$(eval $(call TMX2DATA, CONVERT, col/dat/6-2-bg.tmx, bg_data_6_2))  
#$(eval $(call TMX2DATA, CONVERT, col/dat/6-3-bg.tmx, bg_data_6_3))
#$(eval $(call TMX2DATA, CONVERT, col/dat/6-4-bg.tmx, bg_data_6_4))


##
## OLD MACROS (For compatibility)
##

## TILEMAP CONVERSION EXAMPLES (Uncomment EVAL lines to use)
##

## Convert img/tilemap.tmx to src/tilemap.c and src/tilemap.h
##		This file contains a tilemap created with Tiled that uses tiles
## in img/tiles.png. This macro will convert the tilemap into a C-array
## named g_tilemap, containing all the IDs of the tiles that are located 
## at each given location of the C-array. 
##

#$(eval $(call TMX2C,img/tilemap.tmx,g_tilemap,src/,4))

## Convert img/level0b.tmx to src/levels/level0b.c and src/levels/level0b.h
##		This file contains another tilemap created with Tiled. This macro 
## will convert the tilemap into a C bitarray of 4-bits per item. The array
## will be named g_level0_4bit. For each tile ID included into the final 
## bitarray, only 4 bits will be used. Therefore, each byte of the array 
## will contain 2 tile IDs.
##

#$(eval $(call TMX2C,img/level0b.tmx,g_level0_4bit,src/levels/,4))




############################################################################
##              DETAILED INSTRUCTIONS AND PARAMETERS                      ##
##------------------------------------------------------------------------##
##                                                                        ##
## Macro used for conversion is TMX2C, which has up to 4 parameters:      ##
##  (1): TMX file to be converted to C array                              ##
##  (2): C identifier for the generated C array                           ##
##  (3): Output folder for C and H files generated (Default same folder)  ##
##  (4): Bits per item (1,2,4 or 6 to codify tilemap into a bitarray).    ##
##       Blanck for normal integer tilemap array (8 bits per item)        ##
##  (5): Aditional options (aditional modifiers for cpct_tmx2csv)         ##
##                                                                        ##
## Macro is used in this way (one line for each image to be converted):   ##
##  $(eval $(call TMX2C,(1),(2),(3),(4),(5)))                             ##
##                                                                        ##
## Important:                                                             ##
##  * Do NOT separate macro parameters with spaces, blanks or other chars.##
##    ANY character you put into a macro parameter will be passed to the  ##
##    macro. Therefore ...,src/sprites,... will represent "src/sprites"   ##
##    folder, whereas ...,  src/sprites,... means "  src/sprites" folder. ##
##  * You can omit parameters by leaving them empty.                      ##
##  * Parameters (4) and (5) are optional and generally not required.     ##
############################################################################

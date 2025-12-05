10 MODE 1
20 BORDER 0
30 INK 0,0
40 INK 1,5
50 INK 2,11
60 INK 3,25
70 PEN 3
80 LOCATE 1,1
90 POKE &A601, 0
100 PRINT "REGINALD AND THE SEX VAMPIRES"
110 PRINT "============================="
120 PRINT
130 PRINT "DECEMBER 2025 BETA"
140 PEN 2
150 PRINT
160 PRINT "THIS IS A COMPLETE AND PLAYABLE VERSION"
170 PRINT
180 PRINT "Currently yet to be implemented:"
190 PRINT
200 PRINT "* In-game SFX"
210 PRINT "* Level 5"
220 PRINT "* Final Boss Battle"
230 PRINT "* Victory Screen"
240 PRINT
250 PEN 3
260 PRINT "Updated versions be found at:"
270 PRINT "HTTP://TYPHONSOFT,ITCH.IO"
280 PRINT
290 PEN 2
300 PRINT "Disk #1 (this disk): Story/Intro"
310 PEN 2
320 PRINT "Disk #2 (other disk): Main Game"
330 PEN 3
340 PRINT
350 PRINT "You can run DISC.BAS from Disk #2"
360 PRINT "to start the main game directly."
370 PRINT
380 PRINT "For a PG version run PGDISC.BAS"
390 LOCATE 1, 25
400 PRINT "<Press any key to continue>"
410 WHILE INKEY$="":WEND
420 CLS
430 RUN "REGINTRO.BAS"
440 
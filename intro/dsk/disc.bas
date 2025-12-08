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
130 PRINT "DECEMBER 2025 v1.00"
140 PEN 2
150 PRINT
160 PRINT "THIS IS A COMPLETE AND PLAYABLE VERSION"
170 PRINT
180 PRINT "Currently yet to be implemented:"
190 PRINT
200 PRINT "* In-game SFX"
210 PRINT
220 PEN 3
230 PRINT "Updated versions be found at:"
240 PRINT "HTTP://TYPHONSOFT,ITCH.IO"
250 PRINT
260 PEN 2
270 PRINT "Disk #1 (this disk): Story/Intro"
280 PEN 2
290 PRINT "Disk #2 (other disk): Main Game"
300 PEN 3
310 PRINT
320 PRINT "You can run DISC.BAS from Disk #2"
330 PRINT "to start the main game directly."
340 PRINT
350 PRINT "For a PG version run PGDISC.BAS"
360 LOCATE 1, 25
370 PRINT "<Press any key to continue>"
380 WHILE INKEY$="":WEND
390 CLS
400 RUN "REGINTRO.BAS"
410 
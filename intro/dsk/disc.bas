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
180 PRINT "Note there is currently no in-game SFX,"
190 PRINT "as I am awaiting full Arkos Tracker 3"
200 PRINT "support in CPCTeleraNext/SDCC 4.5"
210 PRINT
220 PEN 3
230 PRINT "Get News and Updates at:"
240 PRINT
250 PRINT "TYPHONSOFT,ITCH.IO"
260 PRINT
270 PEN 2
280 PRINT "Disk #1 (this disk): Story/Intro"
290 PEN 2
300 PRINT "Disk #2 (other disk): Main Game"
310 PEN 3
320 PRINT
330 PRINT "You can run DISC.BAS from Disk #2"
340 PRINT "to start the main game directly."
350 PRINT
360 PRINT "For a PG version run PGDISC.BAS"
370 LOCATE 1, 25
380 PRINT "<Press any key to continue>"
390 WHILE INKEY$="":WEND
400 CLS
410 RUN "REGINTRO.BAS"
420 
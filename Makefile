#
#	Commands
#

# Compilers
CC=gcc

# Misc
ECHO=@echo

#
#	Misc Variables
#

# C Flags
CLIBS=-lm -lncurses
CFLAGS=-Wall -std=c99 -Wextra -pedantic -ggdb

# Misc

#
#	Main Target
#
main: testDisp

#
#	Multiple Targets
#

all: testBoard game testDisp

#
#	Executables
#
testBoard: testBoard.o board.o
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)

testDisp: testDisp.o dispBase.o dispPrint.o dispCurses.o
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)

testPrintDisp: testPrintDisp.o board.o printDisp.o
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)

game: game.o board.o printDisp.o cursesDisp.o
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)

testCursesDisp: testCursesDisp.o board.o cursesDisp.o
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)

#
#				Object Files
#
%.o: %.c
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -c -o $@ $^

#
#				Misc Commands
#

.PHONY: clean realclean

clean:
	-rm *.o

realclean: clean
	-rm testBoard
	-rm testPrintDisp
	-rm game
	-rm testCursesDisp
	-rm testDisp
 

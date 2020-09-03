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
main: game

#
#	Multiple Targets
#

all: testBoard testPrintDisp game

#
#	Executables
#
testBoard: testBoard.o board.o
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)


testPrintDisp: testPrintDisp.o board.o printDisp.o
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)

game: game.o board.o printDisp.o
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
 

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
main: testBoard

#
#	Multiple Targets
#

all: testBoard

#
#	Executables
#
testBoard: testBoard.o board.o
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o testBoard $^ $(CLIBS)
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
 

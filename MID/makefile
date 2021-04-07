CC= gcc
CFLAGS= -Wall -Wextra -std=c11 -O2
LDLIBS= -lm
NAMEONE= mid01
ONE= mid01.o
NAMET= mid02
TWO= mid02.o
NAMETH= mid03
THR= mid03.o

.PHONY: all clean

all: mid01

mid01: mid01.o
	$(CC) $(CFLAGS) -o $(NAMEONE) $(ONE)  $(LDLIBS)

mid02: mid02.o
	$(CC) $(CFLAGS) -o $(NAMET) $(TWO)  $(LDLIBS)

mid03: mid03.o
	$(CC) $(CFLAGS) -o $(NAMETH) $(THR)  $(LDLIBS)

clean:
	-rm -rf $(NAMEONE) $(ONE)

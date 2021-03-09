CC= gcc
CFLAGS= -Wall -Wextra -std=c11 -O2
LDLIBS= -lm
NAMEONE= hw0101
ONE= hw0101.o readp.o
NAMET= hw0102
TWO= hw0102.o
NAMETH= hw0103
THR= hw0103.o
NAMEFO= hw0604
FOU= hw0604.o proj.o
NAMEFI= hw0605
FIV= hw0605.o PA.o

.PHONY: all clean

all: hw0101 hw0102 hw0103

hw0101: hw0101.o readp.o
	$(CC) $(CFLAGS) -o $(NAMEONE) $(ONE)  $(LDLIBS)

hw0102: hw0102.o
	$(CC) $(CFLAGS) -o $(NAMET) $(TWO)  $(LDLIBS)

hw0103: hw0103.o
	$(CC) $(CFLAGS) -o $(NAMETH) $(THR)  $(LDLIBS)

hw0604: hw0604.o proj.o
	$(CC) $(CFLAGS) -o $(NAMEFO) $(FOU)  $(LDLIBS)

hw0605: hw0605.o PA.o
	$(CC) $(CFLAGS) -o $(NAMEFI) $(FIV)  $(LDLIBS)

clean:
	-rm -rf $(NAMETH) $(THR)
	-rm -rf $(NAMET) $(TWO)
	-rm -rf $(NAMEONE) $(ONE)

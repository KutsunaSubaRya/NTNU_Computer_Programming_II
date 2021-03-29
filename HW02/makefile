CC= gcc
CFLAGS= -Wall -Wextra -std=c11 -O2
LDLIBS= -lm
NAMEONE= hw0201
ONE= hw0201.o mixed.o
NAMET= hw0202
TWO= hw0202.o
NAMETH= hw0203
THR= hw0203.o
NAMEFO= hw0204
FOU= hw0204.o bignum.o

.PHONY: all clean

all: hw0201 hw0202 hw0203 hw0204

hw0201: hw0201.o mixed.o
	$(CC) $(CFLAGS) -o $(NAMEONE) $(ONE)  $(LDLIBS)

hw0202: hw0202.o
	$(CC) $(CFLAGS) -o $(NAMET) $(TWO)  $(LDLIBS)

hw0203: hw0203.o
	$(CC) $(CFLAGS) -o $(NAMETH) $(THR)  $(LDLIBS)

hw0204: hw0204.o bignum.o
	$(CC) $(CFLAGS) -o $(NAMEFO) $(FOU)  $(LDLIBS)

clean:
	-rm -rf $(NAMEONE) $(ONE)
	-rm -rf $(NAMET) $(TWO)
	-rm -rf $(NAMETH) $(THR)
	-rm -rf $(NAMEFO) $(FOU)
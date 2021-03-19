CC= gcc
CFLAGS= -Wall -Wextra -std=c11 -O2
LDLIBS= -lm
NAMEONE= hw0201
ONE= hw0201.o mixed.o
NAMET= hw0102
TWO= hw0102.o
NAMETH= hw0103
THR= hw0103.o
NAMEFO= hw0104 Json.o
FOU= hw0104.o
NAMEFI= hw0105
FIV= hw0105.o mystring.o

.PHONY: all clean

all: hw0201

hw0201: hw0201.o mixed.o
	$(CC) $(CFLAGS) -o $(NAMEONE) $(ONE)  $(LDLIBS)

hw0102: hw0102.o
	$(CC) $(CFLAGS) -o $(NAMET) $(TWO)  $(LDLIBS)

hw0103: hw0103.o
	$(CC) $(CFLAGS) -o $(NAMETH) $(THR)  $(LDLIBS)

hw0104: hw0104.o Json.o
	$(CC) $(CFLAGS) -o $(NAMEFO) $(FOU)  $(LDLIBS)

hw0105: hw0105.o mystring.o
	$(CC) $(CFLAGS) -o $(NAMEFI) $(FIV)  $(LDLIBS)

clean:
	-rm -rf $(NAMEONE) $(ONE)
CC= gcc
CFLAGS=  -std=c11 -O2
LDLIBS= -lm
NAME= main
ONE= main.o comp.o

.PHONY: all clean

all: main

main: main.o comp.o
	$(CC) $(CFLAGS) -o $(NAME) $(ONE)  $(LDLIBS)

clean:
	-rm -rf $(NAME) $(ONE)
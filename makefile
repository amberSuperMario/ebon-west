CC = gcc
CFLAGS = -lncurses -lm -I./include/
SOURCES = ./src/*.c

all: out run clean

out:
	$(CC) $(SOURCES) $(CFLAGS) -o rogue 

run:
	./rogue

clean:
	rm rogue

CC = gcc
CFLAGS = -g -I/usr/include/ncursesw -lncursesw -lm -I./include/
SOURCES = ./src/*.c ./src/*/*.c

all: out run clean

out:
	$(CC) $(SOURCES) $(CFLAGS) -o rogue 

run:
	./rogue

clean:
	rm rogue

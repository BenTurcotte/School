ALL_FILES = main.c permute.c ackermann.c newton.c
CC = gcc
FLAGS = -std=c99 -Wall

all: $(ALL_FILES)
	$(CC) $(FLAGS) $(ALL_FILES) -o runme

.PHONY: clean

clean:
	rm runme
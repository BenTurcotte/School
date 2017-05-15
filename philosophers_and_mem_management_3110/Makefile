CC = gcc
FLAGS = -std=c99 -Wall -g -pthread

all: dine holes

dine: dine.c
	${CC} ${FLAGS} dine.c -o dine

holes: holes.c
	${CC} ${FLAGS} holes.c -o holes

clean:
	if [ -a dine  ]; then rm dine;  fi; \
	if [ -a holes ]; then rm holes; fi;
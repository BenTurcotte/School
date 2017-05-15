SHELL = /bin/bash

# Bturcott - 0832217
# Assignment 4 - CIS*3190
# "Sieve of Atkin" - Makefile

CC = gcc
CFLAGS = -std=c99 -Wall -g
FC = gfortran
FFLAGS = 
AC = gnatmake
AFLAGS = 
LIMIT = 10000

all: a c f

run: a c f
	./a; ./c; ./f;

race: a c f
	time -p ./a ;\
	time -p ./c ;\
	time -p ./f


a: a4.adb
	${AC} ${AFLAGS} a4.adb -o a ;\
	if [ -a a4.o ];   then rm a4.o;   fi;\
	if [ -a a4.ali ]; then rm a4.ali; fi;

c: a4.c
	${CC} ${CFLAGS} a4.c -o c -lm

f: a4.f95
	${FC} ${FFLAGS} a4.f95 -o f -g

clean:
	if [ -a a ];      then rm a;      fi;\
	if [ -a c ];      then rm c;      fi;\
	if [ -a f ];      then rm f;      fi;

clobber:
	${MAKE} clean
	if [ -a ada_output.txt ];     then rm ada_output.txt;     fi;\
	if [ -a c_output.txt ];       then rm c_output.txt;       fi;\
	if [ -a fortran_output.txt ]; then rm fortran_output.txt; fi;
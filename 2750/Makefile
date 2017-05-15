SHELL = /bin/bash

# ------------------------------------------------------------------------------
#        Name:  Ben Turcotte
#  Student ID:  Bturcott
#   Student #:  0832217
#       Email:  bturcott@mail.uoguelph.ca
#       Class:  CIS*2750
#  Assignment:  4, makefile
# ------------------------------------------------------------------------------

# macros intent: external ------------------------------------------------------
IN = home.wpml
OUT =
ARGS =
TRASH =


# macros intent: internal ------------------------------------------------------
CC = gcc
CFLAGS = -g -ansi -Wall


# everything for a4 ------------------------------------------------------------
all: config_parser a1_a2 db_init

db_init: db
	./db -init

db: db.o
	${CC} ${CFLAGS} db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

db.o: db.c
	${CC} ${CFLAGS} -c db.c -o db.o

# everything from the previous 3 assignments -----------------------------------
view:
	./view.py ${ARGS}

get_page: config_parser
	./config_parser ${IN}

config_parser: config_parser.c
	${CC} ${CFLAGS} config_parser.c -o config_parser

a1_a2:  addauthor post view.py
	chmod 775 view.py
	chmod 775 errorlog.txt

post: post.o libstream.a
	gcc ${FLAGS} post.o -o post -L. -lstream

post.o: post.c
	gcc -c ${FLAGS} post.c -o post.o

post.c: post.cc a1
	./a1 post.cc

a1: a1.o
	gcc ${FLAGS} a1.o -o a1

a1.o: a1.c
	gcc -c ${FLAGS} a1.c -o a1.o

addauthor: addauthor.o libstream.a
	gcc ${FLAGS} addauthor.o -o addauthor -L. -lstream

addauthor.o: addauthor.c
	gcc -c ${FLAGS} addauthor.c -o addauthor.o

libstream.a: stream.o
	ar cr libstream.a stream.o

stream.o: stream.c stream.h
	gcc -c ${FLAGS} stream.c -o stream.o


# take out the trash -----------------------------------------------------------
clobber: db
	./db -reset
#    if [ -a errlog.txt ]; then rm errlog.txt; fi;
#	 if [ -a sad_drake.txt ]; then rm sad_drake.txt; fi;
	${MAKE} clean

cleanse: db
	./db -clean
	${MAKE} clean

clean:
	if [ -a db ];            then rm db;            fi;\
	if [ -a config_parser ]; then rm config_parser; fi;\
	if [ -a post.c ];        then rm post.c;        fi;\
	if [ -a libstream.a ];   then rm libstream.a;   fi;\
	if [ -a a1 ];            then rm a1;            fi;\
	if [ -a post ];          then rm post;          fi;\
	if [ -a addauthor ];     then rm addauthor;     fi;\
	rm *.o;


# --------------------------------------------------------------------------- END
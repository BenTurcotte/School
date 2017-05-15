CC = cobc
FLAGS = -x -free -Wall
SRC = stat.cob

all: ${SRC}
	${CC} ${FLAGS} ${SRC} -o runme

new: stat.cob
	${CC} ${FLAGS} stat.cob

old: old_stat.cob
	${CC} ${FLAGS} old_stat.cob

clean:
	if [ -a runme ];    then rm runme;    fi;
	if [ -a stat ];     then rm stat;     fi;
	if [ -a old_stat ]; then rm old_stat; fi;
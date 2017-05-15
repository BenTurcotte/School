CC = gcc
FLAGS = -g -std=c99 -Wall
SRC = main.c P11.c P12.c P21.c P22.c P23.c
IN1 = data_q1.txt
IN2 = data_q2.txt

all:
	${CC} ${FLAGS} ${SRC} -o runme

runq1: q1
	./q1 ${IN1}
q1: a3_q1.c
	${CC} ${FLAGS} a3_q1.c -o q1

runq2: q2
	./q2 ${IN2}
q2: a3_q2.c
	${CC} ${FLAGS} a3_q2.c -o q2

clean:
	if [ -a q1 ]; then rm q1; fi;\
	if [ -a q2 ]; then rm q2; fi;\
	if [ -a runme ]; then rm runme; fi;
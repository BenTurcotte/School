CC = gcc
FLAGS = -g -std=c99 -Wall
SRC = a2.c

all:
	${CC} ${FLAGS} ${SRC} -o simcpu

t0: simcpu
	./simcpu < testcases/testcase0.txt
t1: simcpu
	./simcpu < testcases/testcase1.txt
t2: simcpu
	./simcpu < testcases/testcase2.txt
t3: simcpu
	./simcpu < testcases/testcase3.txt

t0d: simcpu
	./simcpu -d < testcases/testcase0.txt
t1d: simcpu
	./simcpu -d < testcases/testcase1.txt
t2d: simcpu
	./simcpu -d < testcases/testcase2.txt
t3d: simcpu
	./simcpu -d < testcases/testcase3.txt

t0v: simcpu
	./simcpu -v < testcases/testcase0.txt
t1v: simcpu
	./simcpu -v < testcases/testcase1.txt
t2v: simcpu
	./simcpu -v < testcases/testcase2.txt
t3v: simcpu
	./simcpu -v < testcases/testcase3.txt

t0dv: simcpu
	./simcpu -d -v < testcases/testcase0.txt
t1dv: simcpu
	./simcpu -d -v < testcases/testcase1.txt
t2dv: simcpu
	./simcpu -d -v < testcases/testcase2.txt
t3dv: simcpu
	./simcpu -d -v < testcases/testcase3.txt

t0rr: simcpu
	./simcpu -r 25 < testcases/testcase0.txt
t1rr: simcpu
	./simcpu -r 25 < testcases/testcase1.txt
t2rr: simcpu
	./simcpu -r 25 < testcases/testcase2.txt
t3rr: simcpu
	./simcpu -r 25 < testcases/testcase3.txt

t0drr: simcpu
	./simcpu -d -r 25 < testcases/testcase0.txt
t1drr: simcpu
	./simcpu -d -r 25 < testcases/testcase1.txt
t2drr: simcpu
	./simcpu -d -r 25 < testcases/testcase2.txt
t3drr: simcpu
	./simcpu -d -r 25 < testcases/testcase3.txt

t0vrr: simcpu
	./simcpu -v -r 25 < testcases/testcase0.txt
t1vrr: simcpu
	./simcpu -v -r 25 < testcases/testcase1.txt
t2vrr: simcpu
	./simcpu -v -r 25 < testcases/testcase2.txt
t3vrr: simcpu
	./simcpu -v -r 25 < testcases/testcase3.txt

t0dvrr: simcpu
	./simcpu -d -v -r 25 < testcases/testcase0.txt
t1dvrr: simcpu
	./simcpu -d -v -r 25 < testcases/testcase1.txt
t2dvrr: simcpu
	./simcpu -d -v -r 25 < testcases/testcase2.txt
t3dvrr: simcpu
	./simcpu -d -v -r 25 < testcases/testcase3.txt

simcpu:
	${CC} ${FLAGS} ${SRC} -o simcpu

clean:
	rm simcpu

clobber:
	rm simcpu;\
	rm -r testcases

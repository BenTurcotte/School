SRC=newHang4.f95

all: ${SRC}
	gfortran -std=f95 ${SRC} -o v2

old: hang4.for
	gfortran hang4.for -o v1

clean:
	rm v1 v2

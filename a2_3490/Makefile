all: sorting.o convex_hull.o
	gcc -g -std=c99 -Wall sorting.o -o sorting -lm ;\
	gcc -g -std=c99 -Wall convex_hull.o -o convex_hull -lm

sorting.o: sorting.c
	gcc -g -c -std=c99 -Wall sorting.c -o sorting.o

convex_hull.o: convex_hull.c
	gcc -g -c -std=c99 -Wall convex_hull.c -o convex_hull.o

clean:
	rm *.o sorting convex_hull

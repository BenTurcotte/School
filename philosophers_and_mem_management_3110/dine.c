/******************************************************************************
 *       name:  Ben Turcotte                                                  *
 *         ID:  Bturcott                                                      *
 *          #:  0832217                                                       *
 *      email:  bturcott@mail.guelph.ca                                       *
 *      class:  CIS*3110                                                      *
 * assignment:  3 - Part 1: Dining Philosophers                               *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define badmalloc { printf("malloc failed.\n"); exit(0); }

typedef struct Ph {
  int pos;
  int *f;
} Ph;

int n = 0;
int e = 0;

void * live (void *x) {
  
  Ph *ntk = (Ph*)x;
  
  for (int i = 0; i < e; i++) {
  
    if (ntk->pos % 2) { // odd numnbered, pick up left then right
      while(!(ntk->f[(ntk->pos +1) % n]));
      ntk->f[(ntk->pos +1) % n] = 0;
      while(!(ntk->f[ntk->pos]));
      ntk->f[ntk->pos] = 0;
    }
  
    else { // even numbered, pick up right then left
      while(!(ntk->f[ntk->pos]));
      ntk->f[ntk->pos] = 0;
      while(!(ntk->f[(ntk->pos +1) % n]));
      ntk->f[(ntk->pos +1) % n] = 0;
    }
  
    printf("Philosopher %d went from thinking to eating. (eat count: %d)\n", ntk->pos +1, i +1);
    ntk->f[(ntk->pos +1) % n] = 1;
    ntk->f[ntk->pos] = 1;
    printf("Philosopher %d went from eating to thinking.\n", ntk->pos +1);
  }
  
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("invalid input.\n");
    exit(0);
  }

  n = atoi(argv[1]);
  e = atoi(argv[2]);
  int *f = malloc(sizeof(int) * n);  
  pthread_t *p = malloc(sizeof(pthread_t) * n);

  for (int i = 0; i < n; i++)
    f[i] = 1;

  // make and run threads for all of the thinkers
  for (int i = 0; i < n; i++) {
    Ph *ntk = malloc(sizeof(Ph));
    if (!ntk) badmalloc
    ntk->pos = i;
    ntk->f = f;
    pthread_create(&p[i], NULL, live, (void *)ntk);
  }

  pthread_exit(NULL); // can't exit until everyone's tummys are full
  return 0;
}
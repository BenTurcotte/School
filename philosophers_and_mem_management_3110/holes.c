/*******************************************************************************
 *       name:  Ben Turcotte                                                   *
 *         ID:  Bturcott                                                       *
 *          #:  0832217                                                        *
 *      email:  bturcott@mail.guelph.ca                                        *
 *      class:  CIS*3110                                                       *
 * assignment:  3 - Part 2: Memory Management                                  *
 *******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define badmalloc { printf("malloc failed.\n"); exit(0); }
#define MAX_MEM 128

typedef struct Node {
  char id;
  struct Node *n;
} Node;

typedef struct process_t {
    char id;
    int  size;
    int  swaps;
    int  loaded;
    time_t timestamp;
} process_t;

typedef struct stats_t {
  int num_loaded;
  int num_holes;
  float usage;
} stats_t;

int next_to_load_index(process_t map[256]) {
  int n = -1;
  for (int i = 0; i < 256; i++) {
    if (map[i].id != ' ' && !map[i].loaded && (n == -1 || map[i].timestamp < map[n].timestamp) && map[i].swaps < 3)
        n = i;
  }
  return n;
}

/**
 * ff_index
 * returns index of the array 'mem' of the FIRST FIT for a process of size 'needed'
 * returns -1 if there is not room to accomodate the process
 */
int ff_index(char mem[MAX_MEM], int needed) {
  int temp = 0;
  for (int i = 0; i < MAX_MEM; i++) {
    while (mem[i] != ' ' && i < MAX_MEM) i++;
    temp = i;
    while (mem[i] == ' ' && i < MAX_MEM) i++;
    if (i - temp >= needed) return temp;
  }
  return -1;
}

/**
 * bf_index
 * returns index of the array 'mem' of the BEST FIT for a process of size 'needed'
 * returns -1 if there is not room to accomodate the process
 */
int bf_index(char mem[MAX_MEM], int needed) {
  int bf = -1;
  int bf_size = MAX_MEM +1;
  int temp = 0;
  int i = 0;
  for (i = 0; i < MAX_MEM; i++) {
    while (mem[i] != ' ' && i < MAX_MEM) i++;
    temp = i;
    while (mem[i] == ' ' && i < MAX_MEM)
      i++;
    if (i - temp >= needed && i - temp < bf_size) {
      bf_size = i - temp;
      bf = temp;
    }
  }
  return bf;
}

/**
 * wf_index
 * returns index of the array 'mem' of the WORST FIT for a process of size 'needed'
 * returns -1 if there is not room to accomodate the process
 */
int wf_index(char mem[MAX_MEM], int needed) {
  int wf = -1;
  int wf_size = -1;
  int temp = 0;
  int i = 0;
  for (i = 0; i < MAX_MEM; i++) {
    while (mem[i] != ' ' && i < MAX_MEM) i++;
    temp = i;
    while (mem[i] == ' ' && i < MAX_MEM)
      i++;
    if (i - temp >= needed && i - temp > wf_size) {
      wf_size = i - temp;
      wf = temp;
    }
  }
  return wf;
}

/**
 * nf_index
 * returns index of the array 'mem' of the NEXT FIT for a process of size 'needed'
 * returns -1 if there is not room to accomodate the process
 */
int nf_index(char mem[MAX_MEM], int needed) {
  static int last_used = 0;
  int temp = 0;
  for (int i = last_used; i < MAX_MEM; i++) {
    while (mem[i] != ' ' && i < MAX_MEM) i++;
    temp = i;
    while (mem[i] == ' ' && i < MAX_MEM) i++;
    if (i - temp >= needed) {
      last_used = temp;
      return temp;
    }
  }
  for (int i = 0; i < last_used; i++) {
    while (mem[i] != ' ' && i < MAX_MEM) i++;
    temp = i;
    while (mem[i] == ' ' && i < MAX_MEM) i++;
    if (i - temp >= needed) {
      last_used = temp;
      return temp;
    }
  }
  return -1;
}

void clear_mem(char mem[MAX_MEM]) {
  for (int i = 0; i < MAX_MEM; i++)
    mem[i] = ' ';
}

void clear_map(process_t map[256]) {
  for (int i = 0; i < 256; i++) {
    map[i].id = ' ';
    map[i].size = 0;
    map[i].swaps = 0;
    map[i].loaded = 0;
    map[i].timestamp = 0;
  }
}

void copy_map(process_t orig[256], process_t copy[256]) {
  for (int i = 0; i < 256; i++)
    copy[i] = orig[i];
}

int oldest_loaded_index(process_t map[256]) {
  int empty = 1;
  int old = -1;
  for (int i = 0; i < 256; i++) {
    if (map[i].id != ' ' && map[i].loaded) {
      empty = 0;
      if (old == -1 || map[i].timestamp < map[old].timestamp)
        old = i;
    }
  }
  if (empty) old = 0;
  return old;
}

int all_done(process_t map[256]) {
  for (int i = 0; i < 256; i++) {
    if (map[i].id != ' ' && !map[i].loaded && map[i].swaps < 3)
      return 0;
  }
  return 1;
}

stats_t gen_stats(process_t map[256], char mem[MAX_MEM]) {
  stats_t stats = {0, 0, 0};
  for (int i = 0; i < 256; i++) {
    if (map[i].loaded) {
      stats.num_loaded++;
      stats.usage += map[i].size;
    }
  }
  for (int i = 0; i < MAX_MEM; i++) {
    if (mem[i] == ' ') stats.num_holes++;
    while (mem[i] == ' ' && i < MAX_MEM) i++;
  }
  stats.usage = stats.usage/MAX_MEM * 100;
  return stats;
}


int main(int argc, char *argv[]) {

  int verb = 0;
  
  FILE *fp = NULL;
  if (argc != 2 || !(fp = fopen(argv[1], "r"))) {
    printf("invalid input (bad cmd args, or file does not exist).\n");
    exit(0);
  }

  process_t map_orig[256];
  process_t map[256];
  stats_t stats;
  char MEMORY[MAX_MEM +1]; MEMORY[MAX_MEM] = '\0';
  char BUFF[32];
  char c = ' ';
  int  x =  0;
  int  n = -1;
  long t =  0;
  int  proc_count = 0;
  int  load_count = 0;
  float avg_procs = 0.0;
  float avg_holes = 0.0;
  float cum_usage = 0.0;

  clear_mem(MEMORY);
  clear_map(map_orig);
  clear_map(map);

  for (proc_count = 0; fgets(BUFF, 32, fp); proc_count++) {
    if (sscanf(BUFF, "%c %d", &c, &x) != 2) break;
    map_orig[(int)c].id = c;
    map_orig[(int)c].size = x;
    map_orig[(int)c].timestamp = t++;
  }

  for (int flub = 0; flub < 4; flub++) {
    switch(flub) {
      case 0: printf(" -------- FIRST FIT --------\n"); break;
      case 1: printf(" -------- BEST FIT --------\n"); break;
      case 2: printf(" -------- WORST FIT --------\n"); break;
      case 3: printf(" -------- NEXT FIT --------\n"); break;
    }
    load_count = 0;
    avg_procs  = 0.0;
    avg_holes  = 0.0;
    cum_usage  = 0.0;
    clear_mem(MEMORY);
    copy_map(map_orig, map);
    while ((n = next_to_load_index(map)) != -1) {
      
      if (verb) printf("\n\nnext to load - id: %c, size: %d\n", map[n].id, map[n].size);

      int l;
      switch(flub) {
        case 0: l = ff_index(MEMORY, map[n].size); break;
        case 1: l = bf_index(MEMORY, map[n].size); break;
        case 2: l = wf_index(MEMORY, map[n].size); break;
        case 3: l = nf_index(MEMORY, map[n].size); break;
      }
      if (l == -1) {
        n = oldest_loaded_index(map);
        if (n == -1) break; 
        
        if (verb) {
          printf("CLEAR- time: %ld, n: %d, id: %c, size: %d\n", t, n, map[n].id, map[n].size);
          printf("MEMORY BEFORE: ");
          for (int i = 0; i < MAX_MEM; i++) printf("%c", MEMORY[i]);
          printf("\n");
        }
        
        map[n].loaded = 0;
        map[n].timestamp = t++;
        for (int i = 0; i < MAX_MEM; i++) {
          if (MEMORY[i] == map[n].id)
            MEMORY[i] = ' ';
        }

        if (verb) {
          printf("MEMORY AFTER:  ");
          for (int i = 0; i < MAX_MEM; i++) printf("%c", MEMORY[i]);
          printf("\n");
        }
      }
      else { // load
        
        if (verb) {
          printf("LOAD - time: %ld, n: %d, id: %c, size: %d\n", t, n, map[n].id, map[n].size);
          printf("MEMORY BEFORE: ");
          for (int i = 0; i < MAX_MEM; i++) {
            // if (i!=0&&!(i%64)) printf("\n");
            printf("%c", MEMORY[i]);
          }
          printf("\n");
        }

        for (int i = 0; i < map[n].size; i++)
          MEMORY[l + i] = map[n].id;
        map[n].loaded = 1;
        map[n].swaps++;
        map[n].timestamp = t++;
        
        if (verb) {
          printf("MEMORY AFTER:  ");
          for (int i = 0; i < MAX_MEM; i++) {
            // if (i!=0&&!(i%64)) printf("\n");
            printf("%c", MEMORY[i]);
          }
          printf("\n");
        }

        stats = gen_stats(map, MEMORY);
        load_count++;
        avg_procs += stats.num_loaded;
        avg_holes += stats.num_holes;
        cum_usage += stats.usage;
        // printf("process \"%c\" loaded, #processes: %d, %%memusage: %.4f %%, #holes: %d\n", map[n].id, stats.num_loaded, stats.usage, stats.num_holes);
      }
    }
    avg_procs /= load_count;
    avg_holes /= load_count;
    cum_usage /= load_count;
    printf("Total loads = %d, average #processes = %.4f, average #holes = %.4f, cumulative %%mem = %.4f %%\n", load_count, avg_procs, avg_holes, cum_usage);
  }
  return 0;
}

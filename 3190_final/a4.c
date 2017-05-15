// Bturcott - 0832217
// Assignment 4 - CIS*3190
// "Sieve of Atkin" - c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
  
  // var declarations & initialization
  float lim_sqrt = 0.0;
  int   lim = 2000000;
  int   check_me = 0;
  int   i = 0;
  unsigned int k = 0;
  int *prime_flags = NULL;
  prime_flags = (int*)calloc(20000000, sizeof(int));
  if (!prime_flags) {
    printf("calloc failed.\n");
    exit(1);
  }
  prime_flags[2] = 1;
  prime_flags[3] = 1;
  
  // prompt user for input
  while (1) {
    printf("limit: ");
    scanf("%d", &lim);
    if (lim > 0 && lim < 10000001) break;
    printf("Error! Number must be between 0 and 1000001.\n");
  }

  // init input-dependent var
  lim_sqrt = sqrt((double)lim);
  
  // do maths
  for (i = 1; i <= lim_sqrt; i++) {
    for (k = 1; k <= lim_sqrt; k++) {
      check_me = (4 * i * i) + (k * k);
      if (check_me <= lim && (check_me % 12 == 1 || check_me % 12 == 5)) {
        prime_flags[check_me] = 1;
      }
      check_me = (3 * i * i) + (k * k);
      if (check_me <= lim && check_me % 12 == 7) {
        prime_flags[check_me] = 1;
      }
      if (i > k) {
        check_me = (3 * i * i) - (k * k);
        if (check_me <= lim && check_me % 12 == 11) {
          prime_flags[check_me] = 1;
        }
      }
    }
  }

  // eliminate multiples of primes
  for (i = 2; i < lim; i++) {
    if (prime_flags[i] == 1) {
      for (k = i*i; k < lim; k = k + i) {
        prime_flags[k] = 0;
      }
    }
  }
  
  // print results
  FILE * fp = NULL;
  if (!(fp = fopen("c_output.txt", "w"))) {
    printf("Error: could not open file.\n");
    free(prime_flags);
    exit(1);
  }
  for (i = 0; i <= lim; i++) {
    if (prime_flags[i])
      fprintf(fp, "%d\n", i);
  }
  fclose(fp);
  free(prime_flags);

  // mic drop
  return 0;
}
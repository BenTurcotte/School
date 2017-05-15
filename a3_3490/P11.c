/****************************************
 *       name:  Ben Turcotte            *
 *         ID:  Bturcott                *
 *          #:  0832217                 *
 *      email:  bturcott@mail.guelph.ca *
 * assignment:  3 (question 1.1)        *
 *      class:  CIS*3490                *
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int brute(char *main_str, char *cmp_strs[131072], int n_cmp) {
  
  int  found     = 1;
  int  num_found = 0;
  int  len_str   = strlen(main_str);
  char cmp[128];
  
  for (int n = 0; n < n_cmp; n++) {
    if (strlen(cmp_strs[n]) == len_str) {
      found = 1;
      strcpy(cmp, cmp_strs[n]);
      for (int i = 0; i < len_str; i++) {
        for (int j = 0; j < len_str; j++) {
          if (cmp[j] == main_str[i]) {
            cmp[j] = ' ';
            break;
          }
        }
      }
      for (int j = 0; j < len_str; j++) {
        if (cmp[j] != ' ')
          found = 0;
      }
      if (found)
        num_found++;
    }
  }

  return num_found;
}

int p11(char *filename) {
  
  char str[64];
  char *cmp_strs[131072];
  int  n;
  int num_found= 0;
  clock_t time = 0;
  FILE *fp = NULL;

  // open file
  if ((fp = fopen(filename, "r")) == NULL) {
    printf("Error: file not found.\n");
    return 1;
  }

  // input prompt
  printf("\nEnter string to search: ");
  fgets(str, 64, stdin); str[strlen(str) -1] = '\0'; // get rid of '\n'

  // malloc string array & parse file
  for (n = 0; n < 131072; cmp_strs[n++] = NULL);
  for (n = 0; !(cmp_strs[n] = NULL) && (cmp_strs[n] = malloc(sizeof(char) * 128)) != NULL && fscanf(fp, "%s", cmp_strs[n]) == 1; n++);

  // run algorithms & corresponding stats
  time = clock();
  num_found = brute(str, cmp_strs, n);
  time = clock() - time;
  printf("Brute Force:\n");
  printf("  %d anagrams were found.\n", num_found);
  printf("  %lu clock cycles were consumed.\n\n", time);

  // clean up
  for (n = 0; cmp_strs[n]; free(cmp_strs[n++]));
  fclose(fp);
  return 0;
}
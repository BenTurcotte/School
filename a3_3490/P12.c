/****************************************
 *       name:  Ben Turcotte            *
 *         ID:  Bturcott                *
 *          #:  0832217                 *
 *      email:  bturcott@mail.guelph.ca *
 * assignment:  3 (question 1.2)        *
 *      class:  CIS*3490                *
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int effic(char *main_str, char *cmp_strs[], int n_cmp) {
  
  int  found = 1;
  int  num_found = 0;

  for (int n = 0; n < n_cmp; n++) {
    found = 1;
    for (int i = 0; !(main_str[i] == '\0' || cmp_strs[n][i] == '\0'); i++) {
      if (cmp_strs[n][i] != main_str[i]) {
        found = 0;
        break;
      }
    }
    if (found && strlen(main_str) == strlen(cmp_strs[n]))
      num_found++;
  }

  return num_found;
}


int p12(char *filename) {
  
  char str[64];
  char *cmp_strs[131072];
  char c;
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
  for (n = 0; (cmp_strs[n] = malloc(sizeof(char) * 128)) != NULL && fscanf(fp, "%s", cmp_strs[n]) == 1; n++);

  // presort input string
  for (int i = 0; i < strlen(str) -1; i++) {
    for (int j = i +1; j < strlen(str); j++) {
      if (str[i] > str[j]) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
      }
    }
  }
  // presort strings from input file
  for (int x = 0; x < n; x++) {
    for (int i = 0; i < strlen(cmp_strs[x]) -1; i++) {
      for (int j = i +1; j < strlen(cmp_strs[x]); j++) {
        if (cmp_strs[x][i] > cmp_strs[x][j]) {
          c = cmp_strs[x][i];
          cmp_strs[x][i] = cmp_strs[x][j];
          cmp_strs[x][j] = c;
        }
      }
    }
  }

  // run
  time = clock();
  effic(str, cmp_strs, n);
  time = clock() - time;
  printf("Effecient presorting:\n");
  printf("  %d anagrams were found.\n", num_found);
  printf("  %lu clock cycles were consumed.\n\n", time);
  
  // clean up
  for (n = 0; cmp_strs[n]; free(cmp_strs[n++]));
  fclose(fp);
  return 0;
}
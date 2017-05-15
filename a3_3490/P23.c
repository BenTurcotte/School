/****************************************
 *       name:  Ben Turcotte            *
 *         ID:  Bturcott                *
 *          #:  0832217                 *
 *      email:  bturcott@mail.guelph.ca *
 * assignment:  3 (question 2.3)        *
 *      class:  CIS*3490                *
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int p23(char *filename) {

  char *file_str = NULL;
  if (!(file_str = malloc(sizeof(char) * 10000000))) {
    printf("malloc failed.");
    return 1;
  }
  char pattern[64];
  char c;
  int file_str_len = 0;
  int pattern_len    = 0;
  int  i = 0;
  int found_flag = 1;
  int num_found  = 0;
  clock_t time   = 0;
  FILE *fp = NULL;

  // open file
  if ((fp = fopen(filename, "r")) == NULL) {
    printf("Error: file not found.\n");
    free(file_str);
    return 1;
  }

  // input prompt
  printf("\n2.3 Enter string to search: ");
  fgets(pattern, 64, stdin);
  pattern[strlen(pattern) -1] = '\0'; // get rid of '\n'
  pattern_len = strlen(pattern);

  // malloc string array & parse file
  for (i = 0; i < 10000000 && (c = fgetc(fp)) != EOF; i++)
    file_str[i] = c;
  file_str[i] = '\0';
  file_str_len = i;

  // Boyer-Moore
  num_found = 0;
  time = clock();
  
  time = clock() - time;
  printf("Boyer-Moore:\n");
  printf("  %d matches were found.\n", num_found);
  printf("  %lu clock cycles were consumed.\n\n", time);

  free(file_str);
  fclose(fp);
  return 0;
}
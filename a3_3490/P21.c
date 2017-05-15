/****************************************
 *       name:  Ben Turcotte            *
 *         ID:  Bturcott                *
 *          #:  0832217                 *
 *      email:  bturcott@mail.guelph.ca *
 * assignment:  3 (question 2.1)        *
 *      class:  CIS*3490                *
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int p21(char *filename) {

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

  printf("no seg\n");

  // input prompt
  printf("\n2.1 Enter string to search: ");
  fgets(pattern, 64, stdin);
  printf("no seg\n");
  pattern[strlen(pattern) -1] = '\0'; // get rid of '\n'
  printf("no seg\n");
  pattern_len = strlen(pattern);
  printf("no seg\n");

  // load file into array
  for (i = 0; i < 10000000 && (c = fgetc(fp)) != EOF; i++)
    file_str[i] = c;
  file_str[i] = '\0';
  file_str_len = i;

  // brute force
  num_found = 0;
  time = clock();
  for (int i = 0; i + pattern_len <= file_str_len; i++) {
    found_flag = 1;
    for (int j = 0; j < pattern_len; j++) {
      if (pattern[j] != file_str[i + j]) {
        found_flag = 0;
      }
    }
    if (found_flag)
      num_found++;
  }
  time = clock() - time;
  printf("Brute Force:\n");
  printf("  %d matches were found.\n", num_found);
  printf("  %lu clock cycles were consumed.\n\n", time);

  free(file_str);
  fclose(fp);
  return 0;
}
/****************************************
 *       name:  Ben Turcotte            *
 *         ID:  Bturcott                *
 *          #:  0832217                 *
 *      email:  bturcott@mail.guelph.ca *
 * assignment:  3 (question 2.2)        *
 *      class:  CIS*3490                *
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int p22(char *filename) {

  char *file_str = NULL;
  if (!(file_str = malloc(sizeof(char) * 10000000))) {
    printf("malloc failed.");
    return 1;
  }
  char pattern[64];
  char c;
  int table[58];
  int file_str_len = 0;
  int pattern_len  = 0;
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
  printf("\n2.2 Enter string to search: ");
  fgets(pattern, 64, stdin);
  pattern[strlen(pattern) -1] = '\0'; // get rid of '\n'
  pattern_len = strlen(pattern);

  // load file into character array
  for (i = 0; i < 10000000 && (c = fgetc(fp)) != EOF; i++)
    file_str[i] = c;
  file_str[i] = '\0';
  file_str_len = i;
  printf("file was sucessfully loaded.\n");
  printf("pattern is: %s\n", pattern);

  // make table
  for (i = 0; i < 58; i++)
    table[i] = pattern_len;
  for (i = 0; i < pattern_len -2; i++)
    table[ (int)pattern[i] ] = pattern_len - 1 - i;
  printf("table was sucessfully built\n");

  // Horspool
  num_found = 0;
  time = clock();
  i = 0;
  while (i + pattern_len <= file_str_len) {
    found_flag = 1;
    for (int j = pattern_len -1; j >= 0; j--) {
      if (pattern[j] != file_str[i + j]) {
        if ((int)file_str[i + j] < 65 || (int)file_str[i + j] > 122)
          i += pattern_len;
        else
          i += table[ (int)file_str[i + j] -65 ];
        found_flag = 0;
        break;
      }
    }
    if (found_flag) {
      num_found++;
      printf("matched: ");
      for (int k = 0; k < pattern_len; k++)
        printf("%c", file_str[i + k]);
      printf("\n");
      i += pattern_len;
    }
  }
  time = clock() - time;
  printf("Horspool:\n");
  printf("  %d matches were found.\n", num_found);
  printf("  %lu clock cycles were consumed.\n\n", time);

  free(file_str);
  fclose(fp);
  return 0;
}
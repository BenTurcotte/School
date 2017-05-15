/****************************************
 *       name:  Ben Turcotte            *
 *         ID:  Bturcott                *
 *          #:  0832217                 *
 *      email:  bturcott@mail.guelph.ca *
 * assignment:  3 (question 1.1 & 1.2)  *
 *      class:  CIS*3490                *
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int p11(char *filename);
int p12(char *filename);
int p21(char *filename);
int p22(char *filename);
int p23(char *filename);

int main(int argc, char *argv[]) {
  char *filename = NULL;
  if (!(filename = malloc(sizeof(char) * 64))) {
    printf("\amalloc error.\n");
    return 1;
  }
  if (argc == 2) {
    switch(argv[1][0]) {
      case '1':
        printf("Enter name of file for 1.1: ");
        filename = fgets(filename, 64, stdin);
        filename[strlen(filename) -1] = '\0';
        p11(filename);
        break;
      case '2':
        printf("Enter name of file for 1.2: ");
        fgets(filename, 64, stdin);
        filename[strlen(filename) -1] = '\0';
        p12(filename);
        break;
      case '3':
        printf("Enter name of file for 2.1: ");
        filename = fgets(filename, 64, stdin);
        filename[strlen(filename) -1] = '\0';
        p21(filename);
        break;
      case '4':
        printf("Enter name of file for 2.2: ");
        filename = fgets(filename, 64, stdin);
        filename[strlen(filename) -1] = '\0';
        p22(filename);
        break;
      case '5':
        printf("Enter name of file for 2.3: ");
        filename = fgets(filename, 64, stdin);
        filename[strlen(filename) -1] = '\0';
        p23(filename);
        break;
    }
  }
  else {
    printf("Enter name of file for 1.1 & 1.2: ");
    if ((filename = fgets(filename, 64, stdin))) {
      filename[strlen(filename) -1] = '\0';
      p11(filename);
      p12(filename);
    }
    printf("Enter name of file for 2.1, 2.2, & 2.3: ");
    if ((filename = fgets(filename, 64, stdin))) {
      filename[strlen(filename) -1] = '\0';
      p21(filename);
      p22(filename);
      p23(filename);
    }
  }
  free(filename);
  return 0;
}
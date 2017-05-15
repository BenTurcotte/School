/******************************************************************************
 *        Name:  Ben Turcotte                                                 *
 *  Student ID:  Bturcott                                                     *
 *   Student #:  0832217                                                      *
 *       Email:  bturcott@mail.uoguelph.ca                                    *
 *       Class:  CIS*2750                                                     *
 *  Assignment:  2 - addauthor (used in succeeding assignments as well)       *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "stream.h"

int main(int argc, char *argv[]) {
  char author[512];      author[0]     = '\0';
  char streamList[1024]; streamList[0] = '\0';
  int  rFlag = 0;
  int  i     = 0;
  char *pt = NULL;
  
  /* argv[1] is the username, argv[2] is the streamname */
  if (!strcmp(argv[3], "remove")) {
    rFlag = 1;
  }
  
  if (strstr(argv[2], "no streams")) {
    printf("<p id=\"error\">Error: creating a stream whose name contains \"no streams\" is not permitted.</p>\n");
    return 0;
  }

  if (strstr(argv[2], "<streamname>")) {
    printf("<p id=\"error\">Error: No stream name was entered.</p>\n");
    return 0;
  }

  if (!rFlag && (pt = strstr(argv[2], "all"))
      && (pt[3] == ',' || pt[3] == ' ' || pt[3] == '\0')) {
    printf("<p id=\"error\">Error: creating a stream named \"all\" is not permitted.</p>\n");
    return 0;
  }
  else if (rFlag && (pt = strstr(argv[2], "all"))
      && (pt[3] == ',' || pt[3] == ' ' || pt[3] == '\0')) {
    printf("<p id=\"error\">Error: user cannot remove themselves from all streams at once.<br />(must be done individually, or as a comma separated list).</p>");
    return 0;
  }

  common_add_remove(argv[1], argv[2], rFlag);

  return 0;
}
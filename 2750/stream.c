/******************************************************************************
 *        Name:  Ben Turcotte                                                 *
 *  Student ID:  Bturcott                                                     *
 *   Student #:  0832217                                                      *
 *       Email:  bturcott@mail.uoguelph.ca                                    *
 *       Class:  CIS*2750                                                     *
 *  Assignment:  2 - stream library (used in succeeding assignments as well)  *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "stream.h"

int is_valid_char(char c)  {
  switch (c) {
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '_':
      return 1;
    default:
      return 0;
  }
}

void update_stream(UserPost *st) {
  
  /* assumed: user either has permission, or is creating a new thread */
  char postStr[32768];
  char buf[512];
  char cmd[256];
  FILE *extern_prog = NULL;
  extern FILE *popen();

  strcpy(postStr, "User: ");
  strcat(postStr, st->username);
  strcat(postStr, "<br />\nDate: ");
  strcat(postStr, st->date);
  strcat(postStr, "<br />\nStream: ");
  strcat(postStr, st->streamname);
  strcat(postStr, "<br />\n<br />\n\n");
  strcat(postStr, st->text);
  strcat(postStr, "\n\t\t\t\n");

  /* add post to stream */
  sprintf(cmd, "./db -post \"%s\" \"%s\" \"%s\"", st->username, st->streamname, postStr);
  if (!(extern_prog = popen(cmd, "r"))) {
    printf("<p id=error> Could not run program: db<br />\nfull command: %s</p>\n", cmd);
    exit(0);
  }
  while (fgets(buf, 512, extern_prog)) {
    if (strstr(buf, "Success!")) {
      printf("<p id=success> %s </p>\n", buf);
    }
    else if (strstr(buf, "Error!")) {
      printf("<p id=error> %s </p>\n", buf);
    }
  }
  pclose(extern_prog);
}

void common_add_remove(char *username, char *list, int rFlag) {
  
  char out_msg[512];
  char buf[512];
  char cmd[256];
  char streamname[64];
  FILE *extern_prog = NULL;
  extern FILE *popen();
  int  i   = 0;
  int  k   = 0;

  /* iterate through list of streams, call add/remove for each stream name */
  for (i = 0; !(list[i] == '\0'); i++) {
    if (list[i] == ',') {
      list[i++] = '\0';
      while ( !is_valid_char(list[i]) )
        list[i++] = '\0';
      strcpy(streamname, &(list[k]));
      if (rFlag) {
        sprintf(cmd, "./db -remove \"%s\" \"%s\"", username, streamname);
        if (!(extern_prog = popen(cmd, "r"))) {
          printf("<p id=error> Could not run program: db<br />\nfull command: %s</p>\n", cmd);
          exit(0);
        }
        while (fgets(buf, 512, extern_prog)) {
          if (strstr(buf, "Success!")) {
            printf("<p id=success>\n  %s</p>\n", buf);
          }
          else if (strstr(buf, "Error!")) {
            printf("<p id=error>\n  %s</p>\n", buf);
          }
        }
        pclose(extern_prog);
      }
      else {
        sprintf(cmd, "./db -add \"%s\" \"%s\"", username, streamname);
        if (!(extern_prog = popen(cmd, "r"))) {
          printf("<p id=error> Could not run program: db<br />\nfull command: %s</p>\n", cmd);
          exit(0);
        }
        while (fgets(buf, 512, extern_prog)) {
          if (strstr(buf, "Success!")) {
            printf("<p id=success>\n  %s</p>\n", buf);
          }
          else if (strstr(buf, "Error!")) {
            printf("<p id=error>\n  %s</p>\n", buf);
          }
        }
        pclose(extern_prog);
      }
      k = i;
    }
  }
  strcpy(streamname, &(list[k]));
  if (rFlag) {
    sprintf(cmd, "./db -remove \"%s\" \"%s\"", username, streamname);
    if (!(extern_prog = popen(cmd, "r"))) {
      printf("<p id=error> Could not run program: db<br />\nfull command: %s</p>\n", cmd);
      exit(0);
    }
    while (fgets(buf, 512, extern_prog)) {
      if (strstr(buf, "Success!")) {
        printf("<p id=success>\n  %s</p>\n", buf);
      }
      else if (strstr(buf, "Error!")) {
        printf("<p id=error>\n  %s</p>\n", buf);
      }
    }
    pclose(extern_prog);
  }
  else {
    sprintf(cmd, "./db -add \"%s\" \"%s\"", username, streamname);
    if (!(extern_prog = popen(cmd, "r"))) {
      printf("<p id=error> Could not run program: db<br />\nfull command: %s</p>\n", cmd);
      exit(0);
    }
    while (fgets(buf, 512, extern_prog)) {
      if (strstr(buf, "Success!")) {
        printf("<p id=success>\n  %s</p>\n", buf);
      }
      else if (strstr(buf, "Error!")) {
        printf("<p id=error>\n  %s</p>\n", buf);
      }
    }
    pclose(extern_prog);
  }
}

void add_user(char *username, char *fileName) {

  int  alreadyThere = 0;
  char stream[512]  = "";
  char line[512]    = "";
  char *nullit = NULL;
  FILE *fp     = NULL;

  strcpy(stream, &(fileName[9]));
  nullit = strstr(stream, "Stream");
  if (nullit)
    nullit[0] = '\0';

  if (!access(fileName, W_OK) && (fp = fopen(fileName, "r")) != NULL) {
    char usrSpaces[1024];
    strcpy(usrSpaces, username);
    strcat(usrSpaces, "   ");
    while (fgets(line, 512, fp) && !alreadyThere) {
      if (strstr(line, usrSpaces))
        alreadyThere = 1;
    }
    fclose(fp);
    fp = NULL;
  }
  if (!alreadyThere) {
    if ((fp = fopen(fileName, "a")) != NULL) {
      fprintf(fp, "%s   0\n", username);
      fclose(fp);
      fp = NULL;
      printf("<p id=\"success\">%s was successfully added to %s.</p>", username, stream);
    }
    else
      printf("<p id=\"error>An unexpected error occurred. Could not open file: %s</p>", fileName);
  }
  else
    printf("<p id=\"error>%s already belongs to the \"%s\" stream.</p>", username, stream);
}

void remove_user(char *username, char *fileName) {
  int  foundUser   = 0;
  char stream[512] = "";
  char line[512]   = "";
  char *fileStr = NULL;
  char *nullit  = NULL;
  FILE *fp      = NULL;

  strcpy(stream, &(fileName[9]));
  nullit = strstr(stream, "Stream");
  nullit[0] = '\0';
  fileStr = malloc(sizeof(char) * 1);
  if (!fileStr) {
    printf("This a very serious error... the kind that you can't even joke about. Malloc failed, man... it just failed.\n");
    exit(1);
  }
  fileStr[0] = '\0';

  if (!access(fileName, W_OK) && (fp = fopen(fileName, "r")) != NULL) {
    char usrSpaces[1024];
    strcpy(usrSpaces, username);
    strcat(usrSpaces, "   ");
    while (fgets(line, 512, fp)) {
      if (strstr(line, usrSpaces))
        foundUser = 1;
      else {
        nullit = (char*)realloc(fileStr, sizeof(char) * (strlen(fileStr) + strlen(line) +1));
        if (!nullit) {
          printf("This a very serious error... the kind that you can't even joke about. Malloc failed, man... it just failed.\n");
          free(fileStr);
          exit(1);
        }
        fileStr = nullit;
        strcat(fileStr, line);
      }
    }
    fclose(fp);
    fp = NULL;
  }
  else {
    printf("<p id=\"error\">Error! could not remove user:<br />    The \"%s\" stream does not exist.</p>", stream);
    free(fileStr);
    return;
  }

  if (foundUser) {
    fp = fopen(fileName, "w");
    if (!fp)
      printf("<p id=\"error\">By golly, this is odd... it seems that %s cannot be written to.</p>", fileName);
    else {
      fprintf(fp, "%s", fileStr);
      fclose(fp);
      fp = NULL;
      printf("<p id=\"success\">%s was successfully removed from \"%s\"</p>", username, stream);
    }
  }
  else
    printf("<p id=\"error\">Error! could not remove user:<br />    %s does not belong to the \"%s\" stream</p>", username, stream);
  free(fileStr);
}
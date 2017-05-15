#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "stream.h"

/*
 * Ben Turcotte
 * Bturcott - 0832217
 *
 * Assignment 2
 * CIS*2750
 */

class PostEntry {

  char* get_time_date() {
    
    time_t raw = time(NULL); 
    struct tm allTime = *localtime(&raw);
    char   zeroMth[3]; zeroMth[0] = '\0';
    char   zeroD[3];   zeroD[0]   = '\0';
    char   zeroH[3];   zeroH[0]   = '\0';
    char   zeroMin[3]; zeroMin[0] = '\0';
    char   zeroS[3];   zeroS[0]   = '\0';
    char   *dateTime = malloc(sizeof(char) * 64);
    if (!dateTime)
      exit(1);

    if (allTime.tm_mon+1 < 10)
      strcpy(zeroMth, "0");
    if (allTime.tm_mday < 10)
      strcpy(zeroD, "0");
    if (allTime.tm_hour < 10)
      strcpy(zeroH, "0");
    if (allTime.tm_min < 10)
      strcpy(zeroMin, "0");
    if (allTime.tm_sec < 10)
      strcpy(zeroS, "0");
    
    sprintf(dateTime, "%d%s%d%s%d%s%d%s%d%s%d",
            allTime.tm_year +1900,
            zeroMth, allTime.tm_mon +1,
            zeroD, allTime.tm_mday,
            zeroH, allTime.tm_hour,
            zeroMin, allTime.tm_min,
            zeroS, allTime.tm_sec);
    
    return dateTime;
  }

  UserPost* format_entry(char *un, char *sn, char *t) { 
    
    FILE *fp = NULL;
    UserPost *post = NULL;
    char BUFF[32768];
    int i = 0, k = 0;
    
    post = malloc(sizeof(UserPost));
    if (!post) {
      printf("memory allocation error!\n");
      exit(1);
    }

    strcpy(post->username, un);
    strcpy(post->streamname, sn);
    strcpy(post->date, get_time_date());

    for (i = 0; i < strlen(t); i++) {
      if (t[i] == '\n') {
        BUFF[k++] = '<';
        BUFF[k++] = 'b';
        BUFF[k++] = 'r';
        BUFF[k++] = ' ';
        BUFF[k++] = '/';
        BUFF[k] = '>';
      }
      else {
        BUFF[k] = t[i];
      }
      k++;
    }
    BUFF[k] = '\0';

    strcpy(post->text, BUFF);
    
    return post;
  }

  void submit_post(UserPost *post) {
    update_stream(post);
    free(post);
  }
};
/* ------------------------------------------------------------------------- */

int main(int argc, char *argv[]) {
  UserPost *post = NULL;
  if (argc == 4)
    post = format_entry(argv[1], argv[2], argv[3]);
  if (post)
    submit_post(post);
  return 0;
}
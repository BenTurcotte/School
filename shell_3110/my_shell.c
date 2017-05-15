/**
 * Ben Turcotte
 * bturcott - 0832217
 *
 * Assignment 1
 * CIS*3110
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <math.h>

extern char **getln();

/* prints number of arguments, then lists the arguments */
void print_strray_stats(char **strray) {  
  
  int i;
  char BUFF[2048] = "";

  for(i = 1; strray[i] != NULL; i++) {
    if(i > 1) strcat(BUFF, ", "); 
    strcat(BUFF, strray[i]);
  }
  printf("argc: %d, args: %s\n", i-1, BUFF);
}

/* generates all binary strings on length n in lexographic order */
void genbin(char *str, int i, int n) {
  if(i == n) printf("%s\n", str);
  else {
    str[i] = '0'; genbin(str, i+1, n);
    str[i] = '1'; genbin(str, i+1, n);
  }
}

/* returns index of found string,      *
 *  if string is not found, returns -1 */
int vector_contains_str(char **vec, char *str) {
  for(int i = 0; vec[i] != NULL; i++) {
      if( !strcmp(vec[i], str))
        return i;
  }
  return -1;
}

/* function to send to sigset */
void chill_til_done(int merp) { wait(NULL); }

int main() {
    
  FILE   *fpIn    = NULL;
  FILE   *fpOut   = NULL;
  char   **args   = NULL;
  pid_t  pid      = -1;
  int    ignoreMe = -1;
  int    i        = 0;
  int    waitPls  = 0;
  int    diffIn   = 0;
  double sum      = 0.0;
  
  while(1) {
      
    i        = 0;
    diffIn   = 0;
    waitPls  = 1;
    ignoreMe = -1;
    
    printf("my_shell: bturcott$ ");
    args = getln();

    /* no args left, re-prompt (back to top) */
    if(args[0] == NULL) continue;
    
    /* check if command is to be run in background */
    if(vector_contains_str(args, "&") != -1) {
      args[i] = NULL;
      waitPls = 0;
    }

    /* byebye */
    if( !strcmp(args[0], "exit") ) {
      printf("goodbye.\n");
      if(fpIn != NULL) fclose(fpIn);
      if(fpOut != NULL) fclose(fpOut);
      exit(0);
    }
    
    /* add */
    else if(!strcmp(args[0], "add")) {
      sum = 0;
      for(i = 1; args[i] != NULL; i++)
        sum += atof(args[i]);
      printf("Sum: %.0f\n", sum);
    }
    
    /* arg */
    else if(!strcmp(args[0], "arg")) {
      print_strray_stats(args);
    }
    
    /* print all binary strings of length n in lexographic order */
    else if( !strcmp(args[0], "genbin") ) {
      
      if(args[1] == NULL) {
        printf("\aError: invalid args for genbin\n");
        printf("\tvalid args: any integer >0 and <17");
        continue;
      }
      
      int n = (int)floor(atof(args[1]));
      char *str = malloc(sizeof(char) * (n+1));
      
      if(str == NULL) {
        printf("error: could not allocate memory for binary string.\n");
        exit(1);
      }
      
      str[n] = '\0';
      genbin(str, 0, n);
      free(str);
    }
    
    /* fork child process */
    else if((pid = fork()) < 0) { /* error */
      printf("ERROR: fork() failed.");
      if(fpIn != NULL) fclose(fpIn);
      if(fpOut != NULL) fclose(fpOut);
      exit(1);
    }
    
    /* is child process -- execute command */
    else if(pid == 0) {
      /* exec command */
      if(diffIn == 1 && execvp(args[0], NULL) < 0) {
        printf("ERROR: invalid command\n");
        if(fpIn != NULL) fclose(fpIn);
        if(fpOut != NULL) fclose(fpOut);
        exit(1);
      }
      else if(execvp(args[0], args) < 0) {
        printf("ERROR: invalid command\n");
        if(fpIn != NULL) fclose(fpIn);
        if(fpOut != NULL) fclose(fpOut);
        exit(1);
      }
    }
    
    /* is parent process -- hang tight until child process terminates */
    else {
      if(waitPls)
        while(wait(NULL) != pid);
      else
        sigset(SIGCHLD, &chill_til_done);
    }
  }
  return 0;
}

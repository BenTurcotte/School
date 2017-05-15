/******************************************************************************
 *        Name:  Ben Turcotte                                                 *
 *  Student ID:  Bturcott                                                     *
 *   Student #:  0832217                                                      *
 *       Email:  bturcott@mail.uoguelph.ca                                    *
 *       Class:  CIS*2750                                                     *
 *  Assignment:  3 - config_parser (used in succeeding assignments as well)   *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define seg printf("Progress: %s: %d\n", __FILE__, __LINE__);
#define bigErr(info)\
        {printf("\aERROR: %s\n\tFile: %s: %d\n", info, __FILE__, __LINE__);\
         exit(0);}

struct Node {
  char tok[2048];
  struct Node *n;
  struct Node *p;
};
typedef struct Node Node;


/**
 * LINKED LIST FUNCTIONS
 */
void free_list(Node *head) {
  Node *byebye;
  while (head) {
    byebye = head;
    head = head->n;
    free(byebye);
  }
}

Node * new_node(char BUFF[2048]) {
  Node *newguy;
  newguy = malloc(sizeof(Node));
  if (!newguy)
    bigErr("malloc failed.");
  newguy->n = NULL;
  newguy->p = NULL;
  strcpy(newguy->tok, BUFF);
  return newguy;
}

Node * push_b(Node *head, Node *pushMe) {
  if (!head)
    return pushMe;
  if (!pushMe) {
    printf("\aERROR: User tried to add null node to list.\n");
    return head;
  }
  Node *temp = head;
  while (temp->n)
    temp = temp->n;
  temp->n = pushMe;
  pushMe->p = temp;
  return head; /* for symmetry sake */
}

Node * delete_node(Node *head, Node *deleteMe) {
  
  if (!deleteMe) {
    printf("error: tried to remove a null node.\n");
  }
  else if (!head) {
    for (head = deleteMe; head->p; head = head->p);
  }
  else if (deleteMe == head) {
    head = head->n;
    free(deleteMe);
  }
  else if (!deleteMe->n) {
    deleteMe->p->n = NULL;
    free(deleteMe);
  }
  else {
    Node *temp = deleteMe->p;
    temp->n    = deleteMe->n;
    temp->n->p = temp;
    free(deleteMe);
  }

  return head;
}

void nullify(char *str, int len) {
  int i;
  for (i = 0; i < len; i++)
    str[i] = '\0';
}

/**
 * PARSING FUNCTIONS
 */
int is_element_tag(char c) {
  switch(c) {
    case 'b': case 'd': case 'e': case 'h': case 'i': case 'l': case 'p': case 'r': case 't':
      return 1;
  }
  return 0;
}

void remove_quotes(char *str) {
  int i = 0;
  for (i = 0; str[i +2] != '\0'; i++)
    str[i] = str[i +1];
  str[i] = '\0';
}

/**
 * MAIN
 */
int main (int argc, char *argv[]) {

  FILE *inputFp = NULL;
  Node *head = NULL;
  Node *this = NULL;
  char asdf  = '\0';
  char qwer  = '\0';
  char mark  = '\0';
  char inputFileName[512];
  char BUFF[2048] = "";
  int  i = 0;
  
  /* safety first, kids */
  if (argc != 2)
    bigErr("user must provide exactly 2 arguments.")

  /* copy input file name, generate output file name */
  strcpy(inputFileName, argv[1]);

  /* open file */
  if ( !(inputFp = fopen(inputFileName, "r")) )
    bigErr("Cannot open file.")
  
  /* parser loop */
  while ((asdf = fgetc(inputFp)) != EOF) {
    switch(asdf) {
    case ' ':
    case '\n':
    case '\t':
    case '\r':
      if (BUFF[0] != '\0')
        head = push_b(head, new_node(BUFF));
      i = 0;
      do {
        BUFF[i++] = asdf;
        qwer = asdf;
        asdf = fgetc(inputFp);
      } while (asdf == ' ' || asdf == '\n' || asdf == '\t'|| asdf == '\r');
      ungetc(asdf, inputFp);
      BUFF[i] = '\0';
      head = push_b(head, new_node(BUFF));
      nullify(BUFF, 2048);
      i = 0;
      break;

    /* symbols are each one token */
    case '(': case ')': case '[': case ']': case '{': case '}': case '#':
    case '<': case '>': case '+': case '-': case '*': case '/': case ';':
    case '&': case '|': case '!': case '=': case ',': case '.': case '\\':
      if (BUFF[0] != '\0')
        head = push_b(head, new_node(BUFF));
      BUFF[0]= asdf;
      BUFF[1]= '\0';
      head   = push_b(head, new_node(BUFF));
      nullify(BUFF, 2048);
      i = 0;
      break;

    case '\"':
    case '\'':
      if (BUFF[0] != '\0')
        head = push_b(head, new_node(BUFF));
      mark = asdf;
      i    = 0;
      do {
        BUFF[i++]= asdf;
        qwer   = asdf;
      } while ((asdf = fgetc(inputFp)) != mark || (asdf == mark && qwer == '\\'));
      BUFF[i++]= asdf;
      BUFF[i]  = '\0';
      head     = push_b(head, new_node(BUFF));
      BUFF[0]  = '\0';
      i = 0;
      break;

    default:
      BUFF[i++]= asdf;
      BUFF[i]  = '\0';
      break;
    }
    qwer = asdf;
  }
  fclose(inputFp);
  inputFp = NULL;

  /* turn wpml tags into properly-formatted html tags &print to stdout */
  printf("\n<START>\n");
  for (this = head; this; this = this->n) {
     
    if (this->tok[0] == '.' && strlen(this->tok) == 1
        && this->n          && strlen(this->n->tok) == 1 && is_element_tag(this->n->tok[0])
        && this->n->n       && this->n->n->tok[0] == '(') {
      
      char elem_tag = this->n->tok[0];
      head = delete_node(head, this->n); /* delete element tag */
      head = delete_node(head, this->n); /* delete '(' node */
       
      switch(elem_tag) {
 
        char name[128];
        char action[128];
        char cmd[128];
        char filenameOnly[128];
        char value[128];
        char size[128];
        char text[32768];
        char link[128];
        char width[128];
        char height[128];
        char *nullme = NULL;
        Node *temp = NULL;
        Node *printAfter = NULL;
         
        case 'd': /* horizontal line */
          printf("<hr />\n");
          this = this->n;
          while (this->tok[0] != ')') {
            printf("%s", this->tok);
          }
          break;

        case 'b': /* botton */
					this = this->n; /* skip the dot, 'this' now has label of first element property */
					name[0] = '\0';
          action[0] = '\0';
          while (this && this->tok[0] != ')') {
						if (name[0] == '\0' && !strcmp(this->tok, "name")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(name, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
						else if (link[0] == '\0' && !strcmp(this->tok, "link")) {
							while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(action, this->tok);
							this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
						else {
              printAfter = push_b(printAfter, new_node(this->tok));
              this = this->n;
            }
					}
          printf("\n<form action=%s method=\"post\">\n", action);
					for (temp = printAfter; temp; temp = temp->n) {
						printf("%s", temp->tok);
					}
          printf("\n  <input type=\"submit\" value=%s>\n", name);
					printf("\n</form>\n");
          if (printAfter)
            free_list(printAfter);
          printAfter = NULL;
          break;

        case 'e': /* executable */
          printAfter = NULL;
          this = this->n;
          cmd[0] = '\0';
					while (this && this->tok[0] != ')' && this->tok[0] != '\n') {
						if (!strcmp(this->tok, "exe")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(cmd, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
						else {
							printAfter = push_b(printAfter, new_node(this->tok));
              this = this->n;
						}
					}

					if(cmd[0] == '\"') {
						remove_quotes(cmd);
					}
					strcpy(filenameOnly, cmd);
					if ((nullme = strstr(filenameOnly, " "))) {
						nullme[0] = '\0';
					}

          /* printf("<p>cmd: %s |end</p>\n", cmd); */
					/* printf ("\necho \"cmd (not including dir): %s <br />\";\n", filename); */ /* for debugging */
					printf("\n<?php");
          printf("\n  $wpmloutput = NULL;");
					printf("\n  if (file_exists(\"%s\")) {", filenameOnly);
					printf("\n    exec(\"./%s\", $wpmloutput, $wpmlstatus);", cmd);
					printf("\n    if (!$wpmlstatus) {");
          /* printf("\n      echo \"SUCESSFUL EXECUTION\";"); */
					printf("\n      foreach ($wpmloutput as $wpmlline) {");
					printf("\n        echo $wpmlline;");
					printf("\n      }");
					printf("\n    }");
					printf("\n    else {");
					printf("\n      echo \"inner exec failed. (dir: ./)<br />cmd: ./%s<br />\";", cmd);
					printf("\n    }");
					printf("\n  }");
					printf("\n  elseif (file_exists(\"./bin/%s\")) {", filenameOnly);
					printf("\n    exec(\"./bin/%s\", $wpmloutput, $wpmlstatus);", cmd);
					printf("\n    if (!$wpmlstatus) {");
					printf("\n      foreach ($wpmloutput as $wpmlline) {");
					printf("\n        echo $wpmlline;");
					printf("\n      }");
					printf("\n    }");
					printf("\n    else {");
					printf("\n      echo \"inner exec failed. (dir: ./bin/)<br />cmd: ./bin/%s<br />\";", cmd);
					printf("\n    }");
					printf("\n  }");
					printf("\n  elseif (file_exists(\"/sys/bin/%s\")) {", filenameOnly);
					printf("\n    exec(\"/sys/bin/%s\", $wpmloutput, $wpmlstatus);", cmd);
					printf("\n    if (!$wpmlstatus) {");
					printf("\n      foreach ($wpmloutput as $wpmlline) {");
					printf("\n        echo $wpmlline;");
					printf("\n      }");
					printf("\n    }");
					printf("\n    else {");
					printf("\n      echo \"inner exec failed. (dir: /sys/bin/)<br />cmd: /sys/bin/%s<br />\";", cmd);
					printf("\n    }");
					printf("\n  }");
					printf("\n  else {");
					printf("\n    echo \"<h1>Failed to execute: %s </h1>\";", cmd);
					printf("\n  }");
					for (temp = printAfter; temp; temp = temp->n) {
						printf("%s", temp->tok);
					}
					printf("\n?>\n");
					free_list(printAfter);
					printAfter = NULL;
          strcpy(cmd, "");
					break;

        case 'h': /* header */
          printAfter = NULL;
          strcpy(size, "\"3\"");
					strcpy(text, "\"HEADING\"");
					this = this->n;
 
					while (this && this->tok[0] != ')') {
						if (!strcmp(this->tok, "size")) {
               
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(size, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
						else if (!strcmp(this->tok, "text")) {
               
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(text, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
						else {
							printAfter = push_b(printAfter, new_node(this->tok));
              this = this->n;
						}
					}
					remove_quotes(size);
					remove_quotes(text);
					printf("<h%s>%s", size, text);
					for (temp = printAfter; temp; temp = temp->n) {
						printf("%s", temp->tok);
					}
					printf("</h%s>\n", size);
					free_list(printAfter);
					printAfter = NULL;
					break;

        case 'i': /* input */
          printAfter = NULL;
          name[0] = '\0';
					text[0] = '\0';
					value[0] = '\0';
					this = this->n;
          
          while (this && this->tok[0] != ')') {
						if (!strcmp(this->tok, "action")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(action, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
							printf("<form action=%s method=\"post\">\n", action);
						}
						else if (text[0] == '\0' && !strcmp(this->tok, "text")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(text, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
						else if (name[0] == '\0' && !strcmp(this->tok, "name")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(name, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
						else if (value[0] == '\0' && !strcmp(this->tok, "value")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(value, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
            else if(this->tok[0] == '<') {
              char tagStr[512] = "";
              while (this->tok[0] != '>' && this->tok[0] != ')' && this->tok[0] != '\n') {
                strcat(tagStr, this->tok);
                this = this->n;
              }
              strcat(tagStr, this->tok);
              printAfter = push_b(printAfter, new_node(tagStr));
              this = this->n;
            }
						else {
							printAfter = push_b(printAfter, new_node(this->tok));
              this = this->n;
						}

						if (text[0] != '\0' && name[0] != '\0' && value[0] != '\0') {
              remove_quotes(text);
							printf("  %s <input type=\"text\" name=%s value=%s /><br />\n", text, name, value);
							text[0]  = '\0';
							name[0]  = '\0';
							value[0] = '\0';
						}
					}

					for (temp = printAfter; temp; temp = temp->n) {
						printf("%s", temp->tok);
					}
					printf("  <input type=\"submit\" value=\"Submit\" /><br />\n</form>\n");
          free_list(printAfter);
          break;

        case 'l': /* link */
          printAfter = NULL;
          this = this->n;
          strcpy(text, "link");

          while (this && this->tok[0] != ')') {
						if (!strcmp(this->tok, "text")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(text, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
						else if (!strcmp(this->tok, "link")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(link, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
						else {
							printAfter = push_b(printAfter, new_node(this->tok));
              this = this->n;
						}
					}

          printf("<a");
          for (temp = printAfter; temp; temp = temp->n) {
            printf("%s", temp->tok);
          }
          remove_quotes(text);
          printf("href=%s> %s</a>\n", link, text);
          break;

        case 'p': /* image */
          printAfter = NULL;
          this = this->n;
          strcpy(width, "100");
          strcpy(height, "100");
          strcpy(name, "sad_drake.gif");

          while (this && this->tok[0] != ')') {
						if (!strcmp(this->tok, "image")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(name, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
            }
            else if (!strcmp(this->tok, "size")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							remove_quotes(temp->tok);
              if ((nullme = strstr(temp->tok, "x"))) {
                nullme[0] = '\0';
                strcpy(width, temp->tok);
                strcpy(height, &(nullme[1]));
              }
						}
						else {
							printAfter = push_b(printAfter, new_node(this->tok));
              this = this->n;
						}
          }
          printf("<img ");
          for (temp = printAfter; temp; temp = temp->n) {
            printf("%s", temp->tok);
          }
          printf("src=\"%s\" width=\"%s\" height=\"%s\"><br />", name, width, height);
          free_list(printAfter);
          break;

        case 'r': /* radio button */
          printAfter = NULL;
          this = this->n;

          while (this && this->tok[0] != ')') {
            if (!strcmp(this->tok, "action")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(action, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
              printf("\n<form action=\"%s\" method=\"post\">\n", action);
						}
            else if (!strcmp(this->tok, "name")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(name, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
						}
						else if (!strcmp(this->tok, "value")) {
              while (this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							strcpy(value, this->tok);
              remove_quotes(value);
              printf("  <input type=\"radio\" name=\"%s\" value=\"%s\" /> %s <br />\n", name, value, value);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }

						}
            else {
							printAfter = push_b(printAfter, new_node(this->tok));
              this = this->n;
						}
          }
          for (temp = printAfter; temp; temp = temp->n) {
            printf("%s", temp->tok);
          }
          printf("<input type=\"submit\" value=\"submit\" />\n</form>\n");
          free_list(printAfter);
          printAfter = NULL;
          break;

        case 't': /* text as literal or from file */
          printAfter = NULL;
					this = this->n;
          filenameOnly[0] = '\0';
          text[0] = '\0';
          while (this && this->tok[0] != ')') {
						if (filenameOnly[0] == '\0' && text[0] == '\0' && !strcmp(this->tok, "file")) {
              while (this && this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							if (!this) break;
							strcpy(filenameOnly, this->tok);
							printf("\n<?php\n  include(%s);\n?>\n<br />\n", filenameOnly);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
							break;
						}
						else if (filenameOnly[0] == '\0' && text[0] == '\0' && !strcmp(this->tok, "text")) {
              while (this && this->tok[0] != '\"') {
                this = this->n; /* skip "name", skip "=" */
              }
							if (!this) break;
							strcpy(text, this->tok);
              this = this->n;
              if (this->tok[0] == ',') {
                this = this->n;
              }
              remove_quotes(text);
							printf("<p> %s </p>\n", text);
							break;
						}
						else {
							printAfter = push_b(printAfter, new_node(this->tok));
              this = this->n;
						}
					}

					for (temp = printAfter; temp; temp = temp->n) {
						printf("%s", temp->tok);
					}
          free_list(printAfter);
          printAfter = NULL;
          break;

        default:
          break;
      }
    }
    else printf("%s", this->tok);
  }

  free_list(head);
  return 0;
}
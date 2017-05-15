#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define seg printf("Progress: %s: %d\n", __FILE__, __LINE__);
struct Node {
  char tok[1024];
  struct Node *n;
  struct Node *p;
};
typedef struct Node Node;
void free_list(Node *head) {
  Node *byebye;
  while (head) {
    byebye = head;
    head = head->n;
    free(byebye);
  }
}
Node * new_node(char BUFF[1024]) {
  Node *newguy;
  newguy = malloc(sizeof(Node));
  if (!newguy) {
    printf("Error! %s: %d\n", __FILE__, __LINE__);
    return NULL;
  }
  newguy->n = NULL;
  newguy->p = NULL;
  strcpy(newguy->tok, BUFF);
  return newguy;
}
Node * push_b(Node *head, Node *pushMe) {
  if (!head)
    return pushMe;
  if (!pushMe) {
    free_list(head);
    return NULL;
  }
  Node *temp = head;
  while (temp->n)
    temp = temp->n;
  temp->n = pushMe;
  pushMe->p = temp;
  return head; /* for symmetry sake */
}
int is_class_dec(Node *list) {
  if (strstr(list->tok, "class")) {
    while (!strstr(list->tok, ";")) {
      if (strstr(list->tok, "{")
          || strstr(list->tok, "(")
          || strstr(list->tok, ")")
          || strstr(list->tok, "\""))
        return 0;
      list = list->n;
    }
    return 1;
  }
  return 0;
}
int is_class_def(Node *list) {
  if (list && strstr(list->tok, "class")) {
    for (list = list; list; list = list->n) {
      if (strstr(list->tok, ";")) return 0;
      if (strstr(list->tok, "{")) return 1;
    }
  }
  return 0;
}
int is_func_def(Node *list, char *searchMe) {
  if (list && strstr(searchMe, list->tok)) {
    for (list = list; list; list = list->n) {
      if (strstr(list->tok, ";")) return 0;
      if (strstr(list->tok, "{")) return 1;
    }
  }
  return 0;
}
int is_var_dec(Node *list, char *TYPES) {
  if (list && strstr(TYPES, list->tok)) {
    for (list = list; !strstr(list->tok, ";"); list = list->n) {
      if (strstr(list->tok, "(")) return 0;
      if (strstr(list->tok, ")")) return 0;
      if (strstr(list->tok, "{")) return 0;
      if (strstr(list->tok, "}")) return 0;
    }
    return 1;
  }
  return 0;
}
int is_class_func_call(Node *list) {
  if (!list || !list->n || !list->n->n || !list->n->n->n)
    return 0;
  if (strstr(list->n->tok, ".")
      && strstr(list->n->n->n->tok, "("))
    return 1;
  return 0;
}
void nullify(char *str, int len) {
  int i;
  for (i = 0; i < len; i++)
    str[i] = '\0';
}
int main (int argc, char *argv[]) {

  FILE *fp   = NULL;
  Node *head = NULL;
  Node *this = NULL;
  char asdf  = '\0';
  char qwer  = '\0';
  char mark  = '\0';
  char BUFF[1024] = "";
  char TYPES[47]  = "void char int float short long double UserPost";
  int  i   = 0;
  
  /* safety first, kids */
  if (argc != 2) {
    printf("off to a bad start.\n");
    return 1;
  }

  char fileName[512];
  for (i = 0; argv[1][i] != '.'; i++)
    fileName[i] = argv[1][i];
  fileName[i++] = '.';
  fileName[i++] = 'c';
  fileName[i++] = 'c';
  fileName[i++] = '\0';

  if ((fp = fopen(fileName, "r")) == NULL) {
    printf("Cannot open file.\n");
    return 1;
  }
  
  /* parser loop */
  while ((asdf = fgetc(fp)) != EOF) {
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
        asdf = fgetc(fp);
      } while (asdf == ' ' || asdf == '\n' || asdf == '\t'|| asdf == '\r');
      ungetc(asdf, fp);
      BUFF[i] = '\0';
      head = push_b(head, new_node(BUFF));
      nullify(BUFF, 1024);
      i = 0;
      break;
    case '/':
      asdf = fgetc(fp);
      if(asdf == '/') {
        BUFF[i++] = qwer;
        BUFF[i++] = '*';
        while ((asdf = fgetc(fp)) != EOF && asdf != '\n' && asdf != '\n')
          BUFF[i++] = asdf;
        BUFF[i++]= ' ';
        BUFF[i++]= '*';
        BUFF[i++]= '/';
        BUFF[i++]= asdf;
        BUFF[i]  = '\0';
      }
      else {
        /* push the '\' onto BUFF */
        ungetc(asdf, fp);
        BUFF[i++]= '/';
        BUFF[i]  = '\0';
      }
      break;
      /* else, don't break */
    case '*':
      if(qwer == '/') {
        do {
          BUFF[i++] = asdf;
          qwer = asdf;
          asdf = fgetc(fp);
        } while ( !(qwer == '*' && asdf == '/') );
        BUFF[i++]= asdf;
        BUFF[i]  = '\0';
        break;
      }
      /* else, don't break */
    /* symbols are each one token */
    case '#': case ';': case '&': case '|': case '(': case ')': case '[': case ']': case '{': case '}': case '\\': case '<': case '>': case '!': case '=': case '+': case '-': case ',': case '.':
      if (BUFF[0] != '\0')
        head = push_b(head, new_node(BUFF));
      BUFF[0]= asdf;
      BUFF[1]= '\0';
      head   = push_b(head, new_node(BUFF));
      nullify(BUFF, 1024);
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
      } while ((asdf = fgetc(fp)) != mark || (asdf == mark && qwer == '\\'));
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
  } /* end of while loop parser */

  /* move methods outside of classes */
  for (this = head; this; this = this->n) {
    if (is_class_dec(this)) {
      Node *temp = NULL;
      char constructorCall[2048];
      this = this->n->n;
      strcpy(constructorCall, "  ");
      strcat(constructorCall, "constructor_");
      strcat(constructorCall, this->tok);
      strcat(constructorCall, "(&");
      strcat(constructorCall, this->n->n->tok);
      strcat(constructorCall, ");");
      while (!strstr(this->tok, ";"))
        this = this->n;
      temp = this->n;
      this->n = new_node(constructorCall);
      this->n->p = this;
      this->n->n = temp;
      temp->p = this->n;
    }
    if (is_class_def(this)) {
      Node *temp     = NULL;
      Node *methods  = NULL;
      Node *methHead = NULL;
      Node *methTail = NULL;
      Node *funcptrs = NULL;
      int  class_bbf = 0;    /* bbf: bracket balance factor */
      int  meth_bbf  = 0;
      char className[512] = "\0";
      
      temp = this;
      while (strstr(temp->tok, " ")
          || strstr(temp->tok, "\n")
          || strstr(temp->tok, "\r")
          || strstr(temp->tok, "\t"))
        temp = temp->n;
      strcat(className, temp->n->n->tok); /* skip "class", skip " ", get tok */
      while (!strstr(this->tok, "{"))
        this = this->n;
      do {
        if (strstr(this->tok, "{")) class_bbf++;
        if (strstr(this->tok, "}")) class_bbf--;
        if (is_func_def(this, TYPES)) {
          char funcPtrLine[1024] = "";
          methHead = this;
          methTail = this;
          temp = this;
          this = this->p; /* points at tok just before start of func def */
          /* generate func ptr line & insert before 'this' */
          strcpy(funcPtrLine, "  ");
          strcat(funcPtrLine, temp->tok);
          while (!strcmp(temp->n->tok, "*") || !strcmp(temp->n->tok, " ")) {
            temp = temp->n;
            strcat(funcPtrLine, temp->tok);
          }
          strcat(funcPtrLine, "(*");
          while ((temp = temp->n) && !strstr(temp->tok, "("))
            strcat(funcPtrLine, temp->tok);
          strcat(funcPtrLine, ")");
          strcat(funcPtrLine, temp->tok);
          while ((temp = temp->n) && !strstr(temp->n->tok, "{"))
            strcat(funcPtrLine, temp->tok);
          if (!strstr(temp->tok, " "))
            strcat(funcPtrLine, temp->tok);
          strcat(funcPtrLine, ";\n");
          funcptrs = push_b(funcptrs, new_node(funcPtrLine));
          /* grab everything that belongs to the method */
          while (!strstr(methTail->tok, "("))
            methTail = methTail->n;
          while (!strstr(methTail->tok, "{"))
            methTail = methTail->n;
          do {
            if (strstr(methTail->tok, "{")) meth_bbf++;
            if (strstr(methTail->tok, "}")) meth_bbf--;
          } while (meth_bbf != 0 && (methTail = methTail->n)); /* only go to next if not at end */
          
          /* detach method def. from program, push onto list of methods */
          this->n = methTail->n;
          this->n->p = this;
          methHead->p = NULL;
          methTail->n = NULL;
          methods = push_b(methods, new_node("\n"));
          methods = push_b(methods, methHead);
        }
      } while (class_bbf != 0 && (this = this->n));

      /* insert func ptrs just before end of method & create constructor */
      if (funcptrs) {
        /* generate constructor function */
        char constructor[2048]= "\nvoid constructor_";
        char funcName[512]    = "\0";
        char *here = NULL;
        strcat(constructor, className);
        strcat(constructor, "(struct ");
        strcat(constructor, className);
        strcat(constructor, " *this) {\n");
        for (temp = funcptrs; temp; temp = temp->n) {
          /* add func ptr assignments to body of constructor */
          here = strstr(temp->tok, "(*");
          here = &(here[2]);
          strcpy(funcName, here);
          here = NULL;
          for (i = 0; funcName[i] != ' ' && funcName[i] != ')'; i++);
          funcName[i] = '\0';
          strcat(constructor, "\tthis->");
          strcat(constructor, funcName);
          strcat(constructor, " = &");
          strcat(constructor, funcName);
          strcat(constructor, ";\n");
        }
        strcat(constructor, "}\n");
        methods = push_b(methods, new_node(constructor));
        temp = this->p;
        for (temp->n = funcptrs; temp->n; temp = temp->n);
        temp->n = this;
        this->p = temp;
      }
      this = this->n;
      /* insert methods after class definition */
      if (methods) {
        temp = this->n;
        this->n = methods;
        methods->p = this;
        while (methods->n)
          methods = methods->n;
        methods->n = temp;
        temp->p = methods;
        this = methods; /* because "this = this->n" at top of loop */
      }
    }
  } /* end of moving methods outside of classes */

  /* change "class" to "struct" */
  for (this = head; this; this = this->n) {
    
    if (is_class_def(this)) {
      Node *temp = NULL;
      for (temp = this; !strstr(temp->tok, "{"); temp = temp->n);
      temp = temp->n;
      Node *destroy = temp;
      while (strstr(temp->tok, " ")
             || strstr(temp->tok, " ")
             || strstr(temp->tok, " "))
        temp = temp->n;
      destroy->p->n = temp;
      temp->p->n = NULL;
      temp->p = destroy->p;
      free_list(destroy);
    }

    if (!strcmp(this->tok, "class"))
      strcpy(this->tok, "struct");
  }

  

  printf("\n"); /* for some reason, this prevents a segmentation fault */
  fclose(fp);
  fp = NULL;
  fileName[strlen(fileName) -1] = '\0';
  fp = fopen(fileName, "w");

  /* print each token from list to output file */
  for (this = head; this; this = this->n)
    fprintf(fp, "%s", this->tok);
  
  /* clean up */
  fclose(fp);
  this = NULL;
  free_list(head);
  return 0;
}
/******************************************************************************
 *        Name:  Ben Turcotte                                                 *
 *  Student ID:  Bturcott                                                     *
 *   Student #:  0832217                                                      *
 *       Email:  bturcott@mail.uoguelph.ca                                    *
 *       Class:  CIS*2750                                                     *
 *  Assignment:  4 - db                                                       *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_QUERY 32768
#define HOSTNAME "dursley.socs.uoguelph.ca"
#define USERNAME "bturcott"
#define PASSWORD "0832217"
#define DATABASE "bturcott"

void error (char *msg, MYSQL *mysql) {
  printf("%s\n%s\n", msg, mysql_error(mysql));
  exit(1);
}
void clrstr(char *buf) {
  buf[0] = '\0';
}

int main(int argc, char *argv[]) {

  /* safety first */
  if (argc < 2) {
    printf("invalid cmd args.\n");
    exit(1);
  }

  char HELP_MSG[2048] = "+--------------------------------------------------------------------------+\n";
  strcat(HELP_MSG, "| List of valid command line flags & their behaviours:                     |\n");
  strcat(HELP_MSG, "+--------------------------------------------------------------------------+\n");
  strcat(HELP_MSG, "| From a4 spec:                                                            |\n");
  strcat(HELP_MSG, "| -streams : prints all stream names stores in database.                   |\n");
  strcat(HELP_MSG, "| -users   : prints all usernames stored in database.                      |\n");
  strcat(HELP_MSG, "| -posts   : prints all posts (messages) stored in database.               |\n");
  strcat(HELP_MSG, "| -clear   : deletes all records from every table in the database.         |\n");
  strcat(HELP_MSG, "| -reset   : drops all tables on the database.                             |\n");
  strcat(HELP_MSG, "+--------------------------------------------------------------------------+\n");
  strcat(HELP_MSG, "| Custom commands:                                                         |\n");
  strcat(HELP_MSG, "| -add     <username> <streamname1> <streaname2> ... (not comma separated) |\n");
  strcat(HELP_MSG, "| -remove  <username> <streamname1> <streaname2> ... (not comma separated) |\n");
  strcat(HELP_MSG, "| -post    <username> <streamname> \"<message>\"                             |\n");
  strcat(HELP_MSG, "+--------------------------------------------------------------------------+\n");

  /* var daclarations */
  MYSQL mysql;
  MYSQL_RES *res;
  MYSQL_ROW row;
  /*
  MYSQL_FIELD *field;
  */
  char query[MAX_QUERY];
  char err_msg[256];
  char post[32768];
  int i = 0;

  /* set up */
  mysql_init(&mysql);
  mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "mydb");
  if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) { 
    error("Could not connect to host,", &mysql);
  }
  clrstr(query);

  /* custom commands -------------------------------------------------------- */
  /* INIT */
  if (!strcmp(argv[1], "-init")) {
    /* build query for "messages" table */
    /*
      +----------+------------+---------+
      | username | streamname | message |
      +----------+------------+---------+
    */
    strcat(query, "create table messages (username char(32) not null,");
    strcat(query, "streamname char(32) not null,");
    strcat(query, "message varchar(32768) not null);");
    /* strcat(query, "PRIMARY KEY (username,streamname,message));"); */
    printf("creating messages table...\n");
    /* send query to mysql */
    if (mysql_query(&mysql, query))
      error("Could not create messages table.", &mysql);
    
    /*
      +----------+------------+-------------+
      | username | streamname | lastRead(#) |
      +----------+------------+-------------+
    */
    /* build query to make "users" table */
    strcpy(query, "create table users (username char(32) not null, ");
    strcat(query, "streamname char(32) not null, lastRead int, ");
    strcat(query, "PRIMARY KEY (username,streamname));");
    printf("creating users table...\n");
    /* send query to mysql */
    if (mysql_query(&mysql, query))
      error("Could not create users table.", &mysql);
  }

  /* POST */
  else if (!strcmp(argv[1], "-post")) {
    if (argc != 5) {
      printf("invalid command args. use -help flag for more info.\n");
      exit(0);
    }
    /*
      argv[2] - username
      argv[3] - streamname
      argv[4] - message
    */
    mysql_real_escape_string(&mysql, post, argv[4], strlen(argv[4]));
    /* add a new message to the messages table */
    sprintf(query, "insert into messages values ('%s', '%s', '%s');", argv[2], argv[3], post);
    if (mysql_query(&mysql, query)) {
      sprintf(err_msg, "Error! Could not post %s's post to the %s stream.\n", argv[2], argv[3]);
      error(err_msg, &mysql);
    }
    else printf("Success! %s's post was posted to the %s stream.\n", argv[2], argv[3]);
  }

  /* ADD */
  else if (!strcmp(argv[1], "-add")) {
    /*
      argv[2] - username
      argv[3, 4, ... , n] - streamname(s) (one per arg)
    */
    /* add row to users, change value of streams */
    for (i = 3; argv[i]; i++) {
      sprintf(query, "insert into users values ('%s', '%s', 0);", argv[2], argv[i]);
      if (mysql_query(&mysql, query)) {
        sprintf(err_msg, "Error! Could not add %s to the %s stream.\n", argv[2], argv[i]);
        error(err_msg, &mysql);
      }
      else printf("Success! %s was added to the %s stream.\n", argv[2], argv[i]);
    }
  }

  /* REMOVE */
  else if (!strcmp(argv[1], "-remove")) {
    /*
      argv[2] - username
      argv[3, 4, ... , n] - streamname(s) (one per arg)
    */
    /* add row to users, change value of streams */
    for (i = 3; argv[i]; i++) {
      sprintf(query, "delete from users where username = '%s' and streamname = '%s';", argv[2], argv[i]);
      if (mysql_query(&mysql, query)) {
        sprintf(err_msg, "Error! Could not remove %s from the %s stream.\n", argv[2], argv[i]);
        error(err_msg, &mysql);
      }
      else printf("Success! %s was removed from the %s stream.\n", argv[2], argv[i]);
    }
  }

  /* MARK READ */
  else if (!strcmp(argv[1], "-mark")) {
    /*
      argv[2] - username
      argv[3] - streamname
      argv[4] - "all" or "increment"
    */
    if (!strcmp(argv[4], "all")) {
      sprintf(query, "update users set lastRead = (select count(*) from messages where messages.streamname = '%s') where username = '%s' and streamname = '%s';", argv[3], argv[2], argv[3]);
      if (mysql_query(&mysql, query)) {
        sprintf(err_msg, "Error! Could not mark all posts from the %s stream as read.\n", argv[3]);
        error(err_msg, &mysql);
      }
      else printf("Success! All posts from the %s stream were marked as read.\n", argv[3]);
    }
    if (!strcmp(argv[4], "none")) {
      sprintf(query, "update users set lastRead = 0 where username = '%s' and streamname = '%s';", argv[2], argv[3]);
      if (mysql_query(&mysql, query)) {
        sprintf(err_msg, "Error! Could not mark all posts from the %s stream as unread.\n", argv[3]);
        error(err_msg, &mysql);
      }
      else printf("Success! All posts from the %s stream were marked as unread.\n", argv[3]);
    }
  }


  /* commands from assignment 4 spec ---------------------------------------- */
  /* HELP */
  else if (!strcmp(argv[1], "-help")) {
    printf("%s", HELP_MSG);
  }

  /* STREAMS */
  else if (!strcmp(argv[1], "-streams")) {
    if (argc == 2) { 
      strcpy(query, "SELECT DISTINCT streamname FROM users;");
      if (mysql_query(&mysql, query))
        error("Error! Could not retrieve streams.", &mysql);
      
      if (!(res = mysql_store_result(&mysql)))
        error("No existing streams yet.\n", &mysql);

      /* print streams list */
      int fetched = 0;
      while ((row = mysql_fetch_row(res))) {
        printf("%s\n", row[0]);
        fetched = 1;
      }
      if (!fetched) {
        printf("- no streams -\n");
      }
    }
    else { /* view streams a specific user belongs to */
      /*
        argv[2] - username
      */
      sprintf(query, "SELECT DISTINCT streamname FROM users where username = '%s';", argv[2]);
      if (mysql_query(&mysql, query))
        error("Error! Could not retrieve streams.", &mysql);
      
      if (!(res = mysql_store_result(&mysql)))
        error("- no streams -\n", &mysql);

      /* print streams list */
      int fetched = 0;
      while ((row = mysql_fetch_row(res))) {
        printf("%s\n", row[0]);
        fetched = 1;
      }
      if (!fetched) {
        printf("- no streams -\n");
      }
    }
  }

  /* USERS */
  else if (!strcmp(argv[1], "-users")) {
    strcpy(query, "SELECT DISTINCT username FROM users;");
    if (mysql_query(&mysql, query))
      error("Error! Could not retrieve streams.", &mysql);
    
    if (!(res = mysql_store_result(&mysql)))
      error("No existing users yet.", &mysql);

    /* print users list */
    int fetched = 0;
    while ((row = mysql_fetch_row(res))) {
      printf("%s\n", row[0]);
      fetched = 1;
    }
    if (!fetched) {
      printf("- no users yet -\n");
    }
  }

  /* POSTS */
  else if (!strcmp(argv[1], "-posts")) {
    if (argc == 2) { 
      strcpy(query, "SELECT DISTINCT message FROM messages;");
    }
    else if (argc == 4) { /* view posts for specific user */
      /*
        argv[2] - username
        argv[3] - streamname
      */
      if (!strcmp(argv[3], "all")) {
        sprintf(query, "select message from messages where streamname in (select distinct users.streamname from users where users.username = '%s');", argv[2]);
      }
      else {
        sprintf(query, "select message from messages where streamname = '%s'", argv[3]);
      }
    }
    else {
      printf("invalid command line args. use -help flag for more info.\n");
      exit(0);
    }
    if (mysql_query(&mysql, query))
      error("Error! Could not retrieve streams.", &mysql);
    
    if (!(res = mysql_store_result(&mysql)))
      error("- no posts yet -\n\t\t\t\n", &mysql);

    /* print posts */
    int fetched = 0;
    while ((row = mysql_fetch_row(res))) {
      printf("%s", row[0]);
      fetched = 1;
    }
    if (!fetched) {
      printf("- no posts yet -\n\t\t\t\n");
    }
  }

  /* RESET */
  else if (!strcmp(argv[1], "-reset")) {
    /* drop messages table */
    printf("dropping \'messages\' table...\n");
    if (mysql_query(&mysql, "drop table messages;"))
      error("Could not drop messages table.", &mysql);
    
    
    /* drop users table */
    printf("dropping \'users\' table...\n");
    if (mysql_query(&mysql, "drop table users;"))
      error("Could not drop users table.", &mysql);
    
  }
  
  /* CLEAR */
  else if (!strcmp(argv[1], "-clear")) {
    /* clear messages table */
    printf("clearing \'messages\' table...\n");
    if (mysql_query(&mysql, "delete from messages;"))
      error("Could not clear messages table.", &mysql);
    
    
    /* clear users table */
    printf("clearing \'users\' table...\n");
    if (mysql_query(&mysql, "delete from users;"))
      error("Could not clear users table.", &mysql);
    
  }
  
  /* INVALID */
  else {
    printf("invalid command.\n");
    printf("%s", HELP_MSG);
  }

  /* clean up */
  mysql_close(&mysql);
  return 0;
}
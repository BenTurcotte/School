/******************************************************************************
 *        Name:  Ben Turcotte                                                 *
 *  Student ID:  Bturcott                                                     *
 *   Student #:  0832217                                                      *
 *       Email:  bturcott@mail.uoguelph.ca                                    *
 *       Class:  CIS*2750                                                     *
 *  Assignment:  2 - stream header (used in succeeding assignments as well)   *
 ******************************************************************************/

#include <stdio.h>

struct UserPost {
 char username[64];
 char streamname[64];
 char date[64];
 char text[65536];
};
typedef struct UserPost UserPost;

/* my functions */
int  is_valid_char(char c);
void common_add_remove(char *username, char *list, int rFlag);

/* required functions */
void update_stream(UserPost *st);
void add_user(char *username, char *fileName);
void remove_user(char *username, char *fileName);
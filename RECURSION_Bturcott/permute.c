/**
 * @author  Ben Turcotte
 * @date    2016-09-26
 * @title   permute.c
 */
#include <stdio.h>
#include <string.h>

/**
 * swaps values of x & y
 * @param   int     x   first value to be swapped
 * @param   int     x   second value to be swapped
 * @return  void
 */
void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

/**
 * Prints all permutations of 'c' from index 'at' to index 'n'
 * @param   int     n   Length of string
 * @param   int     at  Current index of string
 * @param   char*   c   Points to beginning of string
 * @return  void
 * @err     at < 0          Print error message, return from function
 * @err     at > n          Print error message, return from function
 * @err     n >= strlen(c)  Print error message, return from function
 */
void permute(int n, int at, char* c) {

    if( at < 0 || at > n || n >= strlen(c) ) {
        printf("Error: invalid index values.");
        return;
    }
    
    if(at == n) printf("%s\n", c);
    else {
        for (int i = at; i <= n; i++) {
            swap((c+at), (c+i));
            permute(n, at+1, c);
            swap((c+at), (c+i));
        }
    }
}

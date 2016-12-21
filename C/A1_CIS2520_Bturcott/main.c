/**
 * Assignment 1
 * Class: CIS2520 F16
 * Student ID: bturcott - 0832217
 * @author Ben Turcotte
 * @date 2016-09-26
 * @title   main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void carbon();
int ackermann(int m, int n);
void newton(double x, double e);

/**
 * @param   int     argc    Number of arguments
 * @param   char**  argv    Array of char* that point to each argument string (char*)
 * @return  0   if success
 * @return  -1  if failure
 * @func    void carbon()
 * @func    int ackermann(int m, int n)
 * @func    void newton(double x, double e)
 * @err     Args are not formatted as expected, returns -1
 */
int main(int argc, char** argv) {
    
    if(argc < 2) permute(5, 0, "carbon");
    
    else if( !strcmp(argv[1], "ackermann") && argc == 4 )
        printf("Value of Ackerman's function:
            %d\n", ackermann( atoi(argv[2]), atoi(argv[3]) );
    
    else if( !strcmp(argv[1], "newton") && argc == 4 )
        int ans = newton( strtod(argv[2], NULL), strtod(argv[3], NULL) );
    
    else printf("Error: Incorrect input. Refer to readme.txt\n");
    return 0;
}
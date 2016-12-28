/**
 * @author  Ben Turcotte
 * @date    2016-09-26
 * @title   ackermann.c
 */

#include <stdio.h>

/**
 * Computes ackermann's value for the given m & n values
 * @param   int 	m
 * @param   int 	n
 * @func 	int 	ackermann(int m, int n) recursive
 * @return 	void
 * @err 	m < 0 	return -1
 * @err 	n < 0 	return -1
 */
int ackermann(int m, int n) {
    
    if(m == 0)              return n+1;
    else if(n == 0)         return ackermann(m-1, 1);
    else if(m  > 0 && n > 0)return ackermann(m-1, ackermann(m, n-1));
    return -1;
}

/**
 * 'm' & 'n' are sent to ackerman(int m, int n) which calculates
 *  Ackerman's value for the given 'm' & 'n' values
 * @param   int 	m
 * @param   int 	n
 * @func    int 	ackermann(int m, int n)
 * @return  void
 * @err     m < 0 	Print error message, end function
 * @err     n < 0 	Print error message, end function
 */
void ackermannGuard(int m, int n) {
    
    if(m < 0 || n < 0) printf("No negative integers please.\n");
    else printf("Value of Ackerman's function: %d\n", ackermann(m, n));
}

/**
 * Assignment 1
 * Class: CIS2520 F16
 * Student ID: bturcott - 0832217
 * @author Ben Turcotte
 * @date 2016-09-26
 */
#include <stdio.h>
#include <math.h>
#include <time.h>

/**
 * Computes Newton's square root approximation using recursion
 * @param   double  x   Number to find the root of
 * @param   double  e   Margin for error
 * @param   double  a   Proposed answer
 * @return  double  a   First answer that falls within x +/- e
 */
double recursiveNewton(double x, double e, double a) {
    
    double abs = a*a-x;
    if(abs < 0) abs = -1 * abs;

    if(abs <= e) return a;
    else         return recursiveNewton(x, e, (a + x/a)/2);
}

/**
 * Computes Newton's square root approximation using a loop
 * @param   double  x   Number to find the root of
 * @param   double  e   Margin for error
 * @param   double  a   Proposed answer
 * @return  double  a   First answer that falls within x +/- e
 */
double nonrecursiveNewton(double x, double e, double a) {

    do {
        abs = a*a-x;
        if(abs < 0) abs = -1 * abs;
        a = (a+x/a)/2;
    } while(abs > e);

    return a;
}

/**
 * @param   double  x   Number to find the root of
 * @param   double  e   Margin for error
 * @func    double recursiveNewton(double x, double e, double a)
 * @func    double nonrecursiveNewton(double x, double e, double a)
 * @return  int     ans Root of x +/- e
 */
void newton(double x, double e) {

    if(x < 0 || e < 0) {
        printf("Error: newton will only work with positive numbers (including 0)");
        return;
    }
    
    double timeRec, timeNon, ans;
    clock_t time1, time2;

    time1 = clock();
    ans = recursiveNewton(x, e, x/2);
    time2 = clock();
    // clock() gives cycles/s ... convert to cycles/ms
    timeRec = (double)(time2 - time1)/1000;

    time1 = clock();
    ans = nonrecursiveNewton(x, e, x/2);
    time2 = clock();
    timeNon = (double)(time2 - time1)/1000; // cyc/s --> cyc/ms

    // Print results
    printf("Answer: %f\n", ans);

    if(timeRec < timeNon) {
        double timeDiff = timeNon - timeRec;
        printf("The recursive function was executed
            %fms faster than the non-recursive function.\n", timeDiff);
    }
    else if(timeNon < timeRec) {
        double timeDiff = timeRec - timeNon;
        printf("The non-recursive function was executed
            %fms faster than the recursive function\n", timeDiff);
    }
    else printf("There was no difference in execution time
            between the recursive and the non-recursive function.\n");
}
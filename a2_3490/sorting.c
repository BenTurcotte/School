#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long lg(long n) { return log((int)n)/log(2); }

void merge(int *inversions, int l[], int r[], int home[], long bigLen) {
    
    int rindx = 0, lindx = 0;
    
    for(int i = 0; i < bigLen; i++) {
        if(lindx >= bigLen/2)
            home[i] = r[rindx++];
        else if( rindx >= bigLen/2 + bigLen%2 || r[rindx] > l[lindx])
            home[i] = l[lindx++];
        else {
            *inversions += bigLen/2 - lindx;
            home[i] = r[rindx++];
        }
    }
}

void merge_sort(int *inversions, int home[], long len) {
    
    int *l, *r;
    l = malloc(sizeof(int) * (len/2 +1));
    r = malloc(sizeof(int) * (len/2 + len%2 +1));
    
    for(int i  = 0; i < len; i++) {
        if(i < len/2) l[i] = home[i];
        else r[i - len/2] = home[i];
    }
    
    if(len/2 > 1)
        merge_sort(inversions, l, len/2);
    if(len/2 + len%2 > 1)
        merge_sort(inversions, r, len/2 + len%2);
    merge(inversions, l, r, home, len);
    
    free(l);
    free(r);
}

int main(int argc, char **argv) {
    
    int  i, j, count, a[100000];
    int  bruteTime, divideTime;
    long n = 0;
    clock_t time;
    FILE *fp = NULL;
    
    if(argc != 2) {
        printf("invalid command line arguments.\n");
        return 1;
    }
    else if((fp = fopen(argv[1], "r")) == NULL) {
        printf("could not open file.\n");
        return 1;
    }
    else {
        /* get data from file */
        for(n = 0; n < 50000 && fscanf(fp, "%d", &(a[n])) == 1; n++);
        if(n == 0) printf("no integer values were found in file.\n");
        else {
            
            printf("%ld integers were found.\n", n);

            /* brute force */
            time = clock();
            count = 0;
            for(i = 0; i < n-1; i++) {
                for(j = i+1; j < n; j++) {
                    if(a[i] > a[j])
                        count++;
                }
            }
            bruteTime = (clock() - time);
            printf("Brute Force count: ........ %d\n", count);

            /* divide & conquer */
            count = 0;
            time = clock();
            merge_sort(&count, a, n);
            divideTime = (clock() - time);
            printf("Divide & Conquer count: ... %d\n", count);

            /* print stats */
            printf("\n -- Brute force -----------------\n");
            printf("Time: %d cycles\n\n", bruteTime);
            printf(" -- Divide & Conquer ------------\n");
            printf("Time: %d cycles\n\n", divideTime);
        }
    }
    return 0;
}

/**
 * This program is written for CIS2520 F16 Assignment 3
 * Written by: Ben Turcotte
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Object {
    int key;
    int nums[7];
} Object;

Object* constructObject( char* infoStr ) {
    
    Object* newObject = malloc( sizeof( Object ));
    if( newObject == NULL ) return NULL;

    newObject->key = 0;

    int first, second, third, intCount;

    /**************************************************************************
     * Assign values from string 'infoStr' to the members of newObject
     * If sscanf does not scan exactly 10 integers, an error message will print
     * and the program will exit
     *************************************************************************/
    intCount = sscanf( infoStr,
            "%d %d %d %d %d %d %d %d %d %d",
            &first,
            &second,
            &third,
            &(newObject->nums[0]),
            &(newObject->nums[1]),
            &(newObject->nums[2]),
            &(newObject->nums[3]),
            &(newObject->nums[4]),
            &(newObject->nums[5]),
            &(newObject->nums[6])  );
    if( intCount != 10 ) {
        printf( "Incorrect file format.\n" );
        exit(1);
    }

    newObject->key = first + second + third;

    return newObject;
}

void makeObjectArray( FILE * fp, Object* objectArray[21] ) {

    /**************************************************************************
     * Assume that the file contains at leat 20 lines, all of which are
     *   formatted correctly
     * One line corresponds to one object
     * The 'i' in the for loop is used as an idex for our
     *  Object array
     * Each iteration of the loop constructs an object via the constructObject
     *   function then assigns the object pointer returned by constructObject
     *   to the 'i'th member of the objectArray
     *************************************************************************/
    for( int i = 1; i < 21; i++ ) {

        char* passStr = malloc( sizeof(char) * 255 );
        fgets(passStr , 255, fp);
        
        // Make sure fgets actually got a string
        if( passStr == NULL ) {
            printf( "Incorrect file format.\n" );
            exit(1);
        }

        // Construct object and add it to the array
        objectArray[i] = constructObject( passStr );

        if( objectArray[i] == NULL ) {
            printf( "Unable to allocate memory for Object.\n" );
            exit(1);
        }
    }
}

void printObjects( Object* heap[21] ) {
    
    for( int i = 1; i < 21; i++ ) {
        
        printf( "Key: %d", heap[i]->key );
        if( heap[i]->key < 100 ) printf(" "); // adjust allignment
        printf("  Info:  ");

        for( int j = 0; j < 7; j++) {
            printf( "%d", heap[i]->nums[j]);
            if( j < 6 ) printf("\t");
        }
        printf( "\n" );
    }
}

void swapObject( Object** x, Object** y ) {
    
    Object* temp = *x;
    *x = *y;
    *y = temp;
}

void arrayDownHeap( Object* heap[21], int i, int n ) {
    
    if( i*2 <= n ) {

        if( heap[i*2]->key > heap[i]->key ) {
            swapObject( &(heap[ i*2 ]), &(heap[i]) );
            arrayDownHeap( heap, i*2, n );
        }
        if( (i*2)+1 <= n ) {

            if( heap[ (i*2)+1 ]->key > heap[i]->key ) {
                swapObject( &(heap[ (i*2)+1 ]), &(heap[i]) );
                arrayDownHeap( heap, (i*2)+1, n);
            }
        }
    }
}

void arrayMaxHeapify( Object* heap[21], int n ) {
    
    for( int i = n/2; i > 0; i--)
        arrayDownHeap(heap, i, n);
}

int main(int argc, char **argv) {
    
    if(argc == 2) {

        FILE* fp;
        Object* heap[21];

        // Open file
        fp = fopen( argv[1], "r" );
        if ( fp == NULL ) {
            printf( "Failed to open file.\n" );
            return 1;
        }

        // Create array of object pointers
        makeObjectArray( fp, heap );

        // Heapify the array using the keys of each object
        arrayMaxHeapify( heap, 20 );

        // Print each object in order of appearance in array
        printObjects( heap );

        return 0;
    }
    else {
        printf("Error! invalid arguments.\n");
        return 1;
    }       
}
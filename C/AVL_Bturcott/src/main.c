/**
 * @author  Ben Turcotte
 * @date    2016-11-28
 * @title   main.c
 * @depend  avltree.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

/**
 * main
 * prints banner, runs a menu loop until user enters "7" to exit.
 * The tree is destroyed (memory is freed) before the program exits
 */
int main(int argc, char** argv) {
    
    // welcome banner
    printf("::::::::::::::::::::::::::::::::\n");
    printf("          Ben Turcotte\n");
    printf("       Bturcott - 0832217\n");
    printf("::::::::::::::::::::::::::::::::\n");

    int num;
    char dump;
    AVL avl;

    avl.root = NULL;
    avl.size = 0;

    // menu loop
    while(1)
    {
        // display menu
        printf("\n1. Initialization\n");
        printf("2. Find\n");
        printf("3. Insert\n");
        printf("4. Remove\n");
        printf("5. Check height & size\n");
        printf("6. Find all\n");
        printf("7. Exit\n");

        // prompt
        printf("avl/> ");

        char* userIn = malloc(sizeof(char)*20);
        if( userIn == NULL ) return 1;

        scanf("%s", userIn);

        if( strlen(userIn) != 1 ) {
            printf("Invalid entry.\n");
        }
        else {
            switch( userIn[0] ) {
                case '1':
                    printf("filename: ");
                    scanf("%s", userIn);
                    initialization(userIn, &avl);
                    break;

                case '2':
                    printf("find key: ");
                    scanf("%s", userIn);
                    find(userIn, avl.root);
                    break;

                case '3':
                    printf("insert key: ");
                    scanf("%s", userIn);
                    insertNode(userIn, &avl);
                    find(userIn, avl.root);
                    break;

                case '4':
                    printf("remove key: ");
                    scanf("%s", userIn);
                    removeNode(userIn, &avl);
                    break;

                case '5':
                    if( avl.size == 0 ) printf("Tree is empty.\n");
                    else {
                        printf("height: %d, size: %d\n", getNodeHeight(avl.root), avl.size);
                    }
                    break;

                case '6':
                    printf("frequency: ");
                    if( scanf("%d%c", &num, &dump) != 2 || dump != '\n' ) {
                        printf("invalid input. Enter a positive integer.\n");
                        break;
                    }
                    else {
                        if( !findAll(num, avl.root) ) printNode(NULL);
                    }
                    break;

                case '7':
                    if( avl.root ) destroyTree(avl.root);
                    if( userIn ) free(userIn);

                    return 0;

                default:
                    printf("%sInvalid entry.\n", userIn);
                    break;
            }
        }
    }
    return 0; // keep compiler happy
}

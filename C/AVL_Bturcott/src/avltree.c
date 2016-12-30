/**
 * @author  Ben Turcotte
 * @date    2016-11-28
 * @title   avltree.c
 *
 * Uses modified versions of some of the functions from Tony Thompson's avl.c
 *      link: https://gist.github.com/tonious/1377768#file-avl-c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

Node* newNode(char* newKey) {
    
    Node* n = malloc(sizeof(Node));
    if( n == NULL ) {
        printf("Error: malloc_failed");
        exit(1);
    }

    n->key = malloc( sizeof(newKey) + 1);
    if( n == NULL ) {
        printf("Error: malloc_failed");
        exit(1);
    }

    strcpy(n->key, newKey);

    n->freq = 1;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void printNode(Node* n) {
    
    if( n == NULL ) printf("no_such_key\n");
    else {  printf("key: %s, frequency: %d\n", n->key, n->freq);  }
}

Node* llRotate(Node* n) {

    Node* temp = n->left;
    n->left = temp->right;
    temp->right = n;

    return temp;
}

Node* rrRotate(Node* n) {

    Node* temp = n->right;
    n->right = temp->left;
    temp->left = n;

    return temp;
}

Node* lrRotate(Node* n) {

    n->left = rrRotate(n->left);
    return llRotate(n);
}

Node* rlRotate(Node* n) {

    n->right = llRotate(n->right);
    return rrRotate(n);
}

int getNodeHeight(Node* n) {
    
    int lh = 0;
    int rh = 0;

    if( n->left != NULL ) lh = getNodeHeight(n->left);
    if( n->right != NULL ) rh = getNodeHeight(n->right);

    if( rh > lh ) {
        return (rh + 1);
    }
    else {
        return (lh + 1);
    }
}

int getBalanceFactor(Node* n) {
    
    int bf = 0;

    if( n->left != NULL ) bf += getNodeHeight(n->left);
    if( n->right != NULL ) bf -= getNodeHeight(n->right);

    return bf;
}

Node* rebalanceAvl(Node* n) {

    int bf = getBalanceFactor(n);

    // too left-heavy for rotation
    if( bf > 2 ) n->left = rebalanceAvl(n->left);

    // too right-heavy for rotation
    else if ( bf < -2 ) n->right = rebalanceAvl(n->right);

    // left-heavy, time to rotate
    else if( bf == 2 ) {
        bf = getBalanceFactor(n->left);

        if( bf > 0 ) n = llRotate(n);
        if( bf < 0 ) n = lrRotate(n);
    }
    
    // right-heavy, time to rotate
    else if( bf == -2 ) {
        bf = getBalanceFactor(n->right);

        if( bf < 0 ) n = rrRotate(n);
        if( bf > 0 ) n = rlRotate(n);
    }

    return n;
}

void insertNode(char* key, AVL* avl) {

    Node *n = avl->root;
    Node *prev = NULL;

    if( avl->root == NULL ) {
        avl->root = newNode(key);
        n = avl->root;
    }

    else {

        while( n != NULL ) {
            
            if( strcmp(n->key, key) == 0 ) {
                n->freq++;
                return;
            }

            else if( strcmp(n->key, key) > 0 ) {
                prev = n;
                n = n->left;
            }

            else if( strcmp(n->key, key) < 0 ) {
                prev = n;
                n = n->right;
            }
        }

        n = newNode(key);

        if( strcmp(prev->key, n->key) > 0 ) prev->left = n;
        if( strcmp(prev->key, n->key) < 0 ) prev->right = n;

        avl->root = rebalanceAvl(avl->root);
    }

    avl->size++;
}

void initialization(char* fileName, AVL* avl) {

    char line[256];
    FILE *fp;

    fp = fopen(fileName, "r");
    if( fp == NULL ) {
        printf("Error: file_not_found\n");
        return;
    }

    while( fscanf(fp, "%s", line ) == 1 ) {
        insertNode(line, avl);
    }
}

void find(char* findMe, Node* n) {

    while( n != NULL ) {
        
        if( strcmp(n->key, findMe) == 0 ) break;
        if( strcmp(n->key, findMe) > 0 ) n = n->left;
        else if( strcmp(n->key, findMe) < 0 ) n = n->right;
    }
    printNode(n);
}

int findAll(int i, Node* n) {

    int foundHere = 0;
    int foundL = 0;
    int foundR = 0;
    
    if( n != NULL && n->freq >= i ) { 
        printNode(n);
        foundHere = 1;
    }
    if( n->left != NULL ) foundL = findAll(i, n->left);
    if( n->right != NULL ) foundR = findAll(i, n->right);

    if( foundHere ) return foundHere;
    if( foundL > foundR ) return foundL;
    return foundR;
}

Node* getParentOfSuccessor(Node* n) {

    if(n == NULL || n->right || n->right->left == NULL) return NULL;

    Node* prev = n;
    n = n->right;

    while(n->left != NULL) {
        prev = n;
        n = n->left;
    }

    return prev;
}

void swapNodes(Node* a, Node* b) {
    Node *t;
    t = a;
    a = b;
    b = t;
}

void removeNode(char* key, AVL* avl) {

    Node* n = avl->root;
    Node* parent = NULL;

    // while n is not NULL and the key is not found, traverse tree in search of match
    while( n && strcmp(n->key, key) ) {

        if( strcmp(n->key, key) > 0 ) {
            parent = n;
            n = n->left;
        }

        else if( strcmp(n->key, key) < 0 ) {
            parent = n;
            n = n->right;
        }
    }
    
    // n will not be NULL if a matching key was found
    if( n ) {

        if( n->freq > 1 ) {
            n->freq--;
            printNode(n);
        }

        else {
            // n->key matches key and n has two children
            if( n->left && n->right ) {
                
                Node* successorParent = getParentOfSuccessor(n);

                if( successorParent ) {
                    if( parent ) {

                        // n is parent's left child
                        if( strcmp(parent->key, key) > 0 ) {

                            parent->left = successorParent->left;
                            successorParent->left = NULL;
                            parent->left->right = n->right;
                            parent->left->left = n->left;
                        }

                        // n is parent's right child
                        else {

                            parent->right = successorParent->left;
                            successorParent->left = NULL;
                            parent->right->right = n->right;
                            parent->right->left = n->left;
                        }
                    }
                    // n is the root
                    else {
                        successorParent->left->left = n->left;
                        successorParent->left->right = n->right;
                        avl->root = successorParent->left;
                        successorParent->left = NULL;
                    }
                }
                else {
                    if( parent ) {
                        parent->left = n->right;
                        parent->left->left = n->left;
                    }
                    else {
                        avl->root = n->right;
                        avl->root->left = n->left;
                    }
                }
            }

            // n->key matches key and n only has left child
            else if( n->left ) {

                if( parent ) {
                    if( strcmp(parent->key, key) > 0 ) {
                        parent->left = n->left;
                    }
                    else {
                        parent->right = n->left;
                    }
                }
                else {
                    avl->root = n->left;
                }
            }

            // n->key matches key and n only has right child
            else if( n->right ) {

                if( parent ) {
                    if( strcmp(parent->key, key) > 0 ) {
                        parent->left = n->right;
                    }
                    else {
                        parent->right = n->right;
                    }
                }
                else {
                    avl->root = n->left;
                }
            }

            // matching node is a leaf node
            else {
                
                // n is left of parent
                if( parent && strcmp(parent->key, key) > 0 ) {
                    parent->left = NULL;
                }
                // n is right of parent
                else if( parent ) {
                    parent->right = NULL;
                }
                // if n doesn't have a parent, don't do anything
            }

            printf("key: %s, frequency: %d\n", n->key, (n->freq - 1) );

            free(n);
            n = NULL;

            if( avl->size > 1 ) avl->root = rebalanceAvl(avl->root);

            avl->size--;
        }
    }

    // matching key was not found
    else {
        printNode(NULL);
    }
}

void destroyTree(Node* n) {
    if(n->left) destroyTree(n->left);
    if(n->right)destroyTree(n->right);
    if(n->key)  free(n->key);
    if(n)       free(n);
}
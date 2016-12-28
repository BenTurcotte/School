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

// Struct declarations
typedef struct Node {
    struct Node* left;
    struct Node* right;
    int freq;
    char* key;
} Node;

typedef struct AVL {
    Node* root;
    int size;
} AVL;

/**
 * newNode
 * allocates memory for the node and the key memory can be freed using destroyTree
 *
 * @param   char*   newKey  is the key of the new node
 * @return  Node*   n       a pointer to the newly-created node
 */
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

/**
 * printNode
 * if the node exists (is not NULL), the function prints the key & frequency of a node
 * if the node deos not exist, the function prints "no_such_key"
 *
 * @param   Node*   n   points to the node to be printed
 * return   void
 */
void printNode(Node* n) {
    
    if( n == NULL ) printf("no_such_key\n");
    else {  printf("key: %s, frequency: %d\n", n->key, n->freq);  }
}

/**
 * llRotate
 * Rebalances a left-left-heavy subtree
 *
 * @param   Node*   n       root of (sub)tree to be rotated
 * @return  Node*   temp    a pointer to the new root
 */
Node* llRotate(Node* n) {

    Node* temp = n->left;
    n->left = temp->right;
    temp->right = n;

    return temp;
}

/**
 * rrRotate
 * Rebalances a right-right-heavy subtree
 *
 * @param   Node*   n       root of (sub)tree to be rotated
 * @return  Node*   temp    a pointer to the new root
 */
Node* rrRotate(Node* n) {

    Node* temp = n->right;
    n->right = temp->left;
    temp->left = n;

    return temp;
}

/**
 * lrRotate
 * Rebalances a left-right-heavy subtree
 *
 * @param   Node*   n       root of (sub)tree to be rotated
 * @func    Node*   rrRotate(Node* n)
 * @func    Node*   llRotate(Node* n)
 * @return  Node*   temp    a pointer to the new root
 */
Node* lrRotate(Node* n) {

    n->left = rrRotate(n->left);
    return llRotate(n);
}

/**
 * rlRotate
 * Rebalances a right-left-heavy subtree
 *
 * @param   Node*   n       root of (sub)tree to be rotated
 * @func    Node*   llRotate(Node* n)
 * @func    Node*   rrRotate(Node* n)
 * @return  Node*   temp    a pointer to the new root
 */
Node* rlRotate(Node* n) {

    n->right = llRotate(n->right);
    return rrRotate(n);
}

/**
 * getNodeHeight
 * heights start at 1 (external node)
 *
 * @param   Node*   n   node to get height of
 * @func    int     getNodeHeight(Node* n) recursive call
 * @return  int     h   integer value of height of the passed in node
 */
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

/**
 * getBalanceFactor
 * makes use of getNodeHeight to determine the balance factor of a given node
 *
 * @param   Node*   n   node to get balance factor of
 * @func    int     getNodeHeight(Node* n)
 * @return  int     bf  an integer value representing the balance factor of the node it was passed
 */
int getBalanceFactor(Node* n) {
    
    int bf = 0;

    if( n->left != NULL ) bf += getNodeHeight(n->left);
    if( n->right != NULL ) bf -= getNodeHeight(n->right);

    return bf;
}

/**
 * rebalanceAvl
 * makes use of getBalanceFactor & all four rotation functions (llRotate, rrRotate, lrRotate, & rlRotate)
 * rebalances a given subtree.
 *
 * @param   Node*   n   root of tree to be rebalanced
 * @func    int     getBalanceFactor(Node* n)
 * @func    Node*   rebalanceAvl(Node* n) recursive call
 * @func    Node*   llRotate(Node* n)
 * @func    Node*   lrRotate(Node* n)
 * @func    Node*   rrRotate(Node* n)
 * @func    Node*   rlRotate(Node* n)
 * @return  Node*   n   a pointer to the new root of the subtree
 */
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

/**
 * insertNode
 * If the new key is a duplicate of a pre-existing key, the frequency of that node is incremented by 1
 *  otherwise, a new node is created & it is inserted into the tree
 *
 * @param   char*   key     key of the to-be-inserted node
 * @param   AVL*    avl     pointer to an AVL struct which holds info about the whole tree
 * @func    Node*   newNode(char* newKey)
 * @func    Node*   rebalanceAvl(Node* n)
 * @return  void
 */
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

/**
 * initialization
 * reads keys from a file and adds them to the avl tree
 *
 * @param   char*   fileName    name of file to be read
 * @param   AVL*    avl         pointer to an AVL struct which holds info about the whole tree
 * @func    void insertNode(char* key, AVL* avl)
 * @return  void
 */
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

/**
 * find
 * searches tree for a given key, results are printed to the screen via printNode
 *
 * @param   char*   findMe  key that the function searches the tree for
 * @param   Node*   n       root of the tree to be searched
 * @func    void    printNode(Node* n)
 * @return  void
 */
void find(char* findMe, Node* n) {

    while( n != NULL ) {
        
        if( strcmp(n->key, findMe) == 0 ) break;
        if( strcmp(n->key, findMe) > 0 ) n = n->left;
        else if( strcmp(n->key, findMe) < 0 ) n = n->right;
    }
    printNode(n);
}

/**
 * findAll
 * recursively searces through entire tree
 * prints any nodes who's frequency is greater than or equal to i
 *
 * @param   int     i   number that the frequency of each node is compared to
 * @param   Node*   n   node in question
 * @func    void    printNode(Node* n)
 * @func    int     findAll(int i, Node* n) recursive call
 * @return  int     1   if at least 1 node was found
 * @return  int     0   if no nodes were found
 */
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

/**
 * getParentOfSuccessor
 * Searches through the tree to find the parent of the immediate successor of the passed-in node
 *
 * @param   Node*   n       node to find the parent of the immediate successor of
 * @return  Node*   n       if the parent of the immediate successor was found
 * @return  Node*   NULL    if no such parent of immediate successor excists
 */
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

/**
 * swapNodes
 * Simple swap function. Swaps pointer values so one points at the other & vice-versa
 *
 * @param   Node*   a   first node to be swapped
 * @param   Node*   b   second node to be swapped
 * @return  void
 */
void swapNodes(Node* a, Node* b) {
    Node *t;
    t = a;
    a = b;
    b = t;
}

/**
 * removeNode
 * searches the tree for a node with a key that matches the passed-in key
 * if found and the frequency is greater than 1, frequency is decremented
 * if found and the frequency is 1, the node is removed and the tree is rebalanced
 * if not found, the appropriate NO_SUCH_KEY message is printed to the screen
 *
 * @param   char*   key     key to search for
 * @param   AVL*    avl     contains info about the whole tree (including a pointer to the root)
 * @func    void    printNode(Node* n)
 * @func    Node* getParentOfSuccessor(Node* n)
 * @return  void
 */
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

/**
 * destroyTree
 * frees all memory that was dynamically allocated for the tree whose root is n
 * frees memory starting at the nodes that are furthest from the root
 *
 * @param   Node*   n   pointer to the root of the (sub)tree to be destroyed
 * @func    void    destroyTree(Node* n)
 * no return value
 */
void destroyTree(Node* n) {
    if(n->left) destroyTree(n->left);
    if(n->right)destroyTree(n->right);
    if(n->key)  free(n->key);
    if(n)       free(n);
}


/**
 * main
 * prints banner, runs a menu loop until user enters "7" to exit.
 * The tree is destroyed (memory is freed) before the program exits
 *
 * @param   int     argc    number of command line arguments provided (starts from 0)
 * @param   char**  argv    array of character arrays (strings) that are each command line argument
 * @func    void    initialization(char* fileName, AVL* avl)
 * @func    void    find(char* findMe, Node* n)
 * @func    void    insertNode(char* key, AVL* avl)
 * @func    void    removeNode(char* key, AVL* avl)
 * @func    int     getNodeHeight(Node* n) {
 * @func    int     findAll(int i, Node* n)
 * @func    void    destroyTree(Node* n)
 * @return  int     0 on success
 * @return  int     1 if any error occurs (most common: malloc error)
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

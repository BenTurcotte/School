/**
 * @author  Ben Turcotte
 * @date    2016-11-28
 * @title   avltree.h
 *
 * Uses modified versions of some of the functions from Tony Thompson's avl.c
 *      link: https://gist.github.com/tonious/1377768#file-avl-c
 *
 */

#ifndef __AVL_BTURCOTT__
#define __AVL_BTURCOTT__

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
Node* newNode(char* newKey);

/**
 * printNode
 * if the node exists (is not NULL), the function prints the key & frequency of a node
 * if the node deos not exist, the function prints "no_such_key"
 *
 * @param   Node*   n   points to the node to be printed
 * return   void
 */
void printNode(Node* n);

/**
 * llRotate
 * Rebalances a left-left-heavy subtree
 *
 * @param   Node*   n       root of (sub)tree to be rotated
 * @return  Node*   temp    a pointer to the new root
 */
Node* llRotate(Node* n);

/**
 * rrRotate
 * Rebalances a right-right-heavy subtree
 *
 * @param   Node*   n       root of (sub)tree to be rotated
 * @return  Node*   temp    a pointer to the new root
 */
Node* rrRotate(Node* n);

/**
 * lrRotate
 * Rebalances a left-right-heavy subtree
 *
 * @param   Node*   n       root of (sub)tree to be rotated
 * @func    Node*   rrRotate(Node* n)
 * @func    Node*   llRotate(Node* n)
 * @return  Node*   temp    a pointer to the new root
 */
Node* lrRotate(Node* n);

/**
 * rlRotate
 * Rebalances a right-left-heavy subtree
 *
 * @param   Node*   n       root of (sub)tree to be rotated
 * @func    Node*   llRotate(Node* n)
 * @func    Node*   rrRotate(Node* n)
 * @return  Node*   temp    a pointer to the new root
 */
Node* rlRotate(Node* n);

/**
 * getNodeHeight
 * heights start at 1 (external node)
 *
 * @param   Node*   n   node to get height of
 * @func    int     getNodeHeight(Node* n) recursive call
 * @return  int     h   integer value of height of the passed in node
 */
int getNodeHeight(Node* n);

/**
 * getBalanceFactor
 * makes use of getNodeHeight to determine the balance factor of a given node
 *
 * @param   Node*   n   node to get balance factor of
 * @func    int     getNodeHeight(Node* n)
 * @return  int     bf  an integer value representing the balance factor of the node it was passed
 */
int getBalanceFactor(Node* n);

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
Node* rebalanceAvl(Node* n);

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
void insertNode(char* key, AVL* avl);

/**
 * initialization
 * reads keys from a file and adds them to the avl tree
 *
 * @param   char*   fileName    name of file to be read
 * @param   AVL*    avl         pointer to an AVL struct which holds info about the whole tree
 * @func    void insertNode(char* key, AVL* avl)
 * @return  void
 */
void initialization(char* fileName, AVL* avl);

/**
 * find
 * searches tree for a given key, results are printed to the screen via printNode
 *
 * @param   char*   findMe  key that the function searches the tree for
 * @param   Node*   n       root of the tree to be searched
 * @func    void    printNode(Node* n)
 * @return  void
 */
void find(char* findMe, Node* n);

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
int findAll(int i, Node* n);

/**
 * getParentOfSuccessor
 * Searches through the tree to find the parent of the immediate successor of the passed-in node
 *
 * @param   Node*   n       node to find the parent of the immediate successor of
 * @return  Node*   n       if the parent of the immediate successor was found
 * @return  Node*   NULL    if no such parent of immediate successor excists
 */
Node* getParentOfSuccessor(Node* n);

/**
 * swapNodes
 * Simple swap function. Swaps pointer values so one points at the other & vice-versa
 *
 * @param   Node*   a   first node to be swapped
 * @param   Node*   b   second node to be swapped
 * @return  void
 */
void swapNodes(Node* a, Node* b);

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
void removeNode(char* key, AVL* avl);

/**
 * destroyTree
 * frees all memory that was dynamically allocated for the tree whose root is n
 * frees memory starting at the nodes that are furthest from the root
 *
 * @param   Node*   n   pointer to the root of the (sub)tree to be destroyed
 * @func    void    destroyTree(Node* n)
 * no return value
 */
void destroyTree(Node* n);

#endif /* __AVL_BTURCOTT__ */

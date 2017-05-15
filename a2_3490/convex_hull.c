/*
 POINTS FOUND USING BRUTE FORCE:
     1.1, 1705.6
     1.1, 891.5
     1.1, 331.7
     3.0, 2144.1
     3.2, 13.9
     137.8, 2146.6
     12.3, 2.4
     193.9, 2147.0
     547.7, 1.2
     438.8, 2147.5
     607.7, 1.2
     1298.6, 2147.3
     1962.2, 1.6
     1858.6, 2146.9
     2068.0, 1.9
     2111.1, 2146.7
     2110.5, 4.1
     2135.3, 2133.6
     2147.3, 7.4
     2143.7, 2115.4
     2147.4, 62.0
     2146.4, 2024.5
     2147.5, 165.4
     2147.1, 1826.1
     2147.3, 1603.2
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Node {
    double x;
    double y;
    int    v; /* visited flag */
    struct Node *n;
    struct Node *p;
} Node;

/* BRUTE FORCE FUNC.s */
int    visited_all    (Node *list);
int    is_in_list     (Node *list, Node *searchNode);
Node * copy_lowest_x  (Node *list);
Node * get_first_non_v(Node *list);
Node * brute_ch_set   (Node *list);

/* DIV. & CONQ. FUNC.s */
Node * quickhull(Node *list);

/* L.L. FUNC.s */
Node * new_node  (double x, double y);
Node * get_f     (Node *f);
Node * get_b     (Node *b);
Node * push_b    (Node *b, Node *a);
void   free_list (Node *f);

int main(int argc, char **argv) {
    
    if (argc == 2) {
        FILE *fp = NULL;
        if ((fp = fopen(argv[1], "r")) != NULL) {
            
            Node    *front = NULL, *CH = NULL, *printMe = NULL;
            clock_t time;
            int     n = 0;
            int     bruteTime, divideTime;
            double  x, y;
            
            /* parse file */
            for (front = NULL; fscanf(fp,"%lf%lf",&x,&y) == 2; front = push_b(front,new_node(x,y))) n++;
            printf("%d coordinates were found.\n", n);
            
            /* sort list based on x coord */
            for (Node *tempA = front; tempA; tempA = tempA->n) {
                for (Node *tempB = tempA; tempB; tempB = tempB->n) {
                    if (tempA->x > tempB->x) {
                        double temp_x = tempA->x;
                        double temp_y = tempA->y;
                        tempA->x = tempB->x;
                        tempA->y = tempB->y;
                        tempB->x = temp_x;
                        tempB->y = temp_y;
                    }
                }
            }
            
            /* brute force */
            time = clock();
            CH = brute_ch_set(front);
            bruteTime = clock() - time;
            
            /* print pts found using brute force */
            printf("Brute force found the following points:\n");
            for (printMe = CH; printMe; printMe = printMe->n)
                printf("%.1lf, %.1lf\n", printMe->x, printMe->y);
            free_list(CH);
            CH = NULL;
            
            /* divide & conquer */
            time = clock();
            // CH = quickhull(front);
            divideTime = clock() - time;
             
            /* print pts found using divide & conquer */
            printf("Quickhull found the following points:\n");
            for (printMe = CH; printMe; printMe = printMe->n)
                printf("%.1lf, %.1lf\n", printMe->x, printMe->y);
            
            /* print stats */
            printf("\n -- Brute force -----------------\n");
            printf("Time: %d cycles\n\n", bruteTime);
            printf(" -- Divide & Conquer ------------\n");
            printf("Time: %d cycles\n\n", divideTime);
            
            free_list(front);
        }
        else printf("Unable to open file.\n");
    }
    else printf("invalid command line arguments.\n");
    return 0;
}


/********************************************************
 *        DIVIDE & CONQUER CONVEX HULL FUNCTIONS        *
 ********************************************************/
Node * get_hull(Node *CH, Node *S, Node *A, Node *B) {

    printf("called get_hull.\n");
    
    if (S) {
        
        Node *far = S;
        double a = (A->y - B->y);
        double b = (B->x - A->x);
        double c = (B->x * A->y) - (B->y * A->x);
        double farDist = fabs(a * far->x + b * far->y + c) / sqrt(pow(a, 2) + pow(b, 2));

        
        /* get farthest point from line ptA-ptB */
        for (Node *temp = S; temp; temp = temp->n) {
            
            printf("looping inside get_hull\nx,y: %lf, %lf\n\n", temp->x, temp->y);
            
            double dist = fabs(a * temp->x + b * temp->y + c) / sqrt(pow(a, 2) + pow(b, 2));
             
            if (farDist < dist) {
                far = temp;
                farDist = dist;
            }
        }
        CH = push_b(CH, new_node(far->x, far->y));
        
        /* split S into 3 groups:
         g1: points on the outside of line ptA-far
         g2: points on the outside of line far-ptB
         g3: all remaining points
         get_hull(CH, g1, ptA, far);
         get_hull(CH, g2, far, ptB);
         */
        Node *g1 = NULL;
        Node *g2 = NULL;
        double A_c = (far->x * A->y) - (far->y * A->x);
        double B_c = (B->x * far->y) - (B->y * far->x);
        
        for (Node *temp = S; temp != NULL; temp = temp->n) {
            
            printf("looping inside get_hull\nx,y: %lf, %lf\n\n", temp->x, temp->y);
            
            double alt_c = a * temp->x + b * temp->y;
            
            if (alt_c > A_c)
                g1 = push_b(g1, new_node(temp->x, temp->y));
            
            else if (alt_c > B_c)
                g2 = push_b(g2, new_node(temp->x, temp->y));
        }
        CH = get_hull(CH, g1, A, far);
        CH = get_hull(CH, g2, far, B);
    }
    return CH;
}

Node * quickhull(Node *list) {
    
    printf("called quickhull.\n");
    
    Node *CH   = NULL;
    Node *temp = NULL;
    Node *ls   = NULL;
    Node *rs   = NULL;
    Node *minx = list;
    Node *maxx = get_b(list);
    double  a  = (maxx->y - minx->y);
    double  b  = (minx->x - maxx->x);
    double  c  = (minx->x * maxx->y) - (minx->y * maxx->x);
    
    for (temp = list; temp != NULL; temp = temp->n) {
        printf("looping.\nx,y: %lf, %lf\n\n", temp->x, temp->y);
        double alt_c = a * temp->x + b * temp->y;
        if (alt_c > c)
            ls = push_b(ls, new_node(temp->x, temp->y));
        else if (alt_c < c)
            rs = push_b(ls, new_node(temp->x, temp->y));
    }
    
    CH = push_b(CH, minx);
    CH = push_b(CH, maxx);
    CH = get_hull(CH, ls, minx, maxx);
    CH = get_hull(CH, rs, maxx, minx);
    
    if (ls) free(ls);
    if (rs) free(rs);
    return CH;
}


/***************************************************
 *        BRUTE FORCE CONVEX HULL FUNCTIONS        *
 ***************************************************/
int visited_all(Node *list) {
    while(list) {
        if(!list->v) return 0;
        list = list->n;
    }
    return 1;
}
int is_in_list(Node *list, Node *searchNode) {
    while(list && searchNode) {
        if(list->x == searchNode->x && list->y == searchNode->y)
            return 1;
        list = list->n;
    }
    return 0;
}
Node * copy_lowest_x(Node *list) {
    Node *low_x = new_node(9999999, 9999999);
    while(list) {
        if(list->x < low_x->x) {
            low_x->x = list->x;
            low_x->y = list->y;
        }
        list = list->n;
    }
    return low_x;
}
Node * get_first_non_v(Node *list) {
    while(list) {
        if(!list->v) return list;
        list = list->n;
    }
    return NULL;
}
Node * brute_ch_set(Node *list) {
    
    if (!list) return NULL;
    list = get_f(list);
    
    double a, b, c;
    int ls = 0, rs = 0;
    Node *ptA    = NULL;
    Node *ptTemp = NULL;
    Node *CH     = copy_lowest_x(list);
    Node *list_itr = list;
    
    while (!visited_all(CH)) {
        
        ptA = get_first_non_v(CH);
        ptA->v = 1;
        ptTemp = get_f(list);
        
        while (ptTemp) {
            
            a  = (ptTemp->y - ptA->y);
            b  = (ptA->x - ptTemp->x);
            c  = (ptA->x * ptTemp->y) - (ptA->y * ptTemp->x);
            ls = 0;
            rs = 0;
            list_itr = get_f(list);
            
            while (list_itr) {
                double alt_c = a * list_itr->x + b * list_itr->y;
                if (alt_c > c +0.005) ls = 1;
                if (alt_c < c -0.005) rs = 1;
                // if (ls + rs == 2) break; /* add this line in for some optimization */
                list_itr = list_itr->n;
            }
            
            if(ls + rs < 2 && !is_in_list(CH, ptTemp))
                CH = push_b(CH, new_node(ptTemp->x, ptTemp->y));
            
            ptTemp = ptTemp->n;
        }
    }
    
    return CH;
}

/******************************
 *   LINKED LIST FUNCTIONS    *
 * -------------------------- *
 * Note: _f = front           *
 *       _b = back            *
 ******************************/
Node * new_node(double x, double y) { /* returns ptr to init'd node */
    Node *a;
    if ((a = malloc(sizeof(Node)))) {
        a->x = x;
        a->y = y;
        a->v = 0;
        a->n = NULL;
        a->p = NULL;
    }
    return a;
}
Node * get_f(Node *f) { /* returns ptr to front of list */
    while (f && f->p) f = f->p;
    return f;
}
Node * get_b(Node *b) { /* returns ptr to back of list */
    while (b && b->n) b = b->n;
    return b;
}
Node * push_b(Node *b, Node *a) { /* returns ptr to front of list */
    if ((b = get_b(b))) {
        b->n = a;
        a->p = b;
    }
    return get_f(a);
}
void free_list(Node *f) {
    Node *t = f;
    while (t) {
        t = t->n;
        free(f);
        f = t;
    }
}

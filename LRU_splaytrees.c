#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 5

int TABLE_FILL = 0;
int LEAST_TURN;
int *reference_string;
typedef struct node 
{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
    int turn;
}node;

node *LRU;

typedef struct splay_tree 
{
    struct node *root;
}splay_tree;


node* new_node(int data) 
{
    node *n = malloc(sizeof(node));
    n->data = data;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    n->turn = 0;

    return n;
}

splay_tree* new_splay_tree() 
{
    splay_tree *t = malloc(sizeof(splay_tree));
    t->root = NULL;
    return t;
}

node* maximum(splay_tree *t, node *x) 
{
    while(x->right != NULL)
    {
        x = x->right;
    }
    return x;
}

void left_rotate(splay_tree *t, node *x) 
{
    node *y = x->right;
    x->right = y->left;
    if(y->left != NULL) 
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL) 
    { //x is root
        t->root = y;
    }
    else if(x == x->parent->left) 
    { //x is left child
        x->parent->left = y;
    }
    else 
    { //x is right child
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(splay_tree *t, node *x) 
{
    node *y = x->left;
    x->left = y->right;
    if(y->right != NULL) 
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL) 
    { //x is root
        t->root = y;
    }
    else if(x == x->parent->right) 
    { //x is left child
        x->parent->right = y;
    }
    else 
    { //x is right child
        x->parent->left = y;
    }   
    y->right = x;
    x->parent = y;
}

void splay(splay_tree *t, node *n) 
{
    while(n->parent != NULL) 
    { //node is not root
        if(n->parent == t->root) 
        { //node is child of root, one rotation
            if(n == n->parent->left) 
            {
                right_rotate(t, n->parent);
            }
            else 
            {
                left_rotate(t, n->parent);
            }
        }
        else 
        {
            node *p = n->parent;
            node *g;

            if(p->parent != NULL)
                g = p->parent; //grandparent

            if(n->parent->left == n && p->parent->left == p) 
            { //both are left children
                right_rotate(t, g);
                right_rotate(t, p);
            }
            else if(n->parent->right == n && p->parent->right == p) 
            { //both are right children
                left_rotate(t, g);
                left_rotate(t, p);
            }
            else if(n->parent->right == n && p->parent->left == p) 
            {
                left_rotate(t, p);
                right_rotate(t, g);
            }
            else if(n->parent->left == n && p->parent->right == p) 
            {
                right_rotate(t, p);
                left_rotate(t, g);
            }
        }
    }
}

void insert(splay_tree *t, node *n) 
{
    node *y = NULL;
    node *temp = t->root;
    while(temp != NULL) 
    {
        y = temp;
        if(n->data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    n->parent = y;

    if(y == NULL) //newly added node is root
        t->root = n;
    else if(n->data < y->data)
        y->left = n;
    else
        y->right = n;

    splay(t, n);
    TABLE_FILL++;
}

node* search(splay_tree *t, node *n, int x) 
{
    if(n == NULL)
    {
        return NULL;
    }
    if(x == n->data) 
    {
        splay(t, n);
        return n;
    }
    else if(x < n->data)
        return search(t, n->left, x);
    else if(x > n->data)
        return search(t, n->right, x);
    else
        return NULL;
}

void GET_LRU(splay_tree *t, node *n) 
{

    if( n != NULL)
    {
        if(n->turn <= LEAST_TURN)
        {
            LEAST_TURN = n->turn;
            LRU = n;
        }
        GET_LRU(t, n->left);
        GET_LRU(t, n->right);
    }
}

void delete(splay_tree *t, node *n) 
{
    splay(t, n);

    splay_tree *left_subtree = new_splay_tree();
    left_subtree->root = t->root->left;
    if(left_subtree->root != NULL)
        left_subtree->root->parent = NULL;

    splay_tree *right_subtree = new_splay_tree();
    right_subtree->root = t->root->right;
    if(right_subtree->root != NULL)
        right_subtree->root->parent = NULL;

    
    free(n);
    if(left_subtree->root != NULL) 
    {
        node *m = maximum(left_subtree, left_subtree->root);
        splay(left_subtree, m);
        left_subtree->root->right = right_subtree->root;
        if(right_subtree->root != NULL)
            right_subtree->root->parent = left_subtree->root;
        t->root = left_subtree->root;
    }
    else 
    {
        t->root = right_subtree->root;
    }
    TABLE_FILL--;
}


int GET_DEPTH(splay_tree *t,node *node)
{
    if (node == NULL)
        return -1;
    else {
        /* compute the depth of each subtree */
        int lDepth = GET_DEPTH(t, node->left);
        int rDepth = GET_DEPTH(t, node->right);
 
        /* use the larger one */
       if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

void PRINT_LEVEL(splay_tree *t,node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 0)
        printf("%d | %d\t\t", root->data, root->turn);
    else if (level > 0)
    {
        PRINT_LEVEL(t, root->left, level-1);
        PRINT_LEVEL(t, root->right, level-1);
    }
}
void show_table(splay_tree *t, node *node)
{
    for(int i=0; i<=GET_DEPTH(t, node); i++)
    {
        PRINT_LEVEL(t, node, i);
    }
}

void display(splay_tree *spl)
{
    printf("\n\n");
    printf("\n\n\t\t\t\t\t************************************************** CURRENT PAGE TABLE ***********************************************");
    printf("\n\n\n\t\t\t\t\t\t");
    for(int i=0; i<TABLE_SIZE;i++)
    {
       printf("%d | Freq\t", i);
    }
    printf("\n");
    printf("\t\t\t\t\t\t");
    for(int i=0; i<TABLE_SIZE;i++)
    {
        printf("--------\t");
    }
    printf("\n");
    printf("\t\t\t\t\t\t");
    show_table(spl, spl->root);
    printf("\n\t\t\t\t\t**********************************************************************************************************************");
}

void main()
{
    splay_tree *spl = new_splay_tree();

    char start;
    int ch, r_length, con = 1, page_fault = 0, hit = 0;
    printf("\n\n\n\nPress Enter to start...");
    scanf("%c", &start);
    while(con != 2)
    {
        printf("\n\nChoose an option from below:\n\n");
        printf("1. Generate a reference string\n2. Generate a random reference string\n\n");
        printf("Enter your choice below: ");
        scanf("%d",&ch);

        if(ch == 1)
        {
            printf("\nWhat should be the length of the reference string: ");
            scanf("%d", &r_length);

            reference_string = (int *)malloc(r_length*sizeof(int));

            printf("\n\nEnter reference string with spaces between numbers: ");
            for(int i=0; i<r_length; i++)
            {
                scanf("%d", &reference_string[i]);
            }
        }
        else if(ch == 2)
        {
            printf("\nWhat should be the length of the reference string: ");
            scanf("%d", &r_length);

            reference_string = (int *)malloc(r_length*sizeof(int));

            printf("\n\nGenerated reference string: ");

            for(int i=0; i<r_length; i++)
            {
                reference_string[i] = (rand() %(0 - 9 + 1)) + 0;
                printf("%d ", reference_string[i]);
            }
            printf("\n\n");
        }
        else
        {
            printf("\nWrong Input\n");

        }

        for(int i=0; i<r_length; i++)
        {
            printf("\nLooking for Page = %d", reference_string[i]);
            node *temp = search(spl, spl->root, reference_string[i]);
            
            if(temp == NULL)
            {
                page_fault++;
                printf("\nPage not found");
                if(TABLE_FILL < 5)
                {
                    printf("\nSpace available in the table");
                    node *nd = new_node(reference_string[i]);
                    nd->turn = nd->turn+1;
                    insert(spl, nd);
                    printf("\nPage inserted into the table");
                }
                else
                {
                    printf("\nNo free space available");
                    LEAST_TURN = spl->root->turn;

                    GET_LRU(spl, spl->root);
                    printf("\nDeleting page Least Recently Used\nPage = %d", LRU->data);
                    delete(spl, LRU);

                    //printf("\nRoot = %d\n", spl->root->data);

                    node *nd = new_node(reference_string[i]);
                    nd->turn = nd->turn+1;
                    insert(spl, nd);
                }
            }
            else
            {
                hit++;
                printf("\nPage Found\n");
                splay(spl, temp);
                temp->turn = temp->turn + 1;
            }
            display(spl);
        
            //sleep(0);
        }
        printf("\n\n\n\n=========================================================");
        printf("\n\nTotal Hits = %d", hit);
        printf("\nTotal Page Faults = %d", page_fault);
        printf("\n\n=========================================================");
        printf("\n\nWould you want to continue? 1-yes/2-no: ");
        scanf("%d", &con);
    }
}
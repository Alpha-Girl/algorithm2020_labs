#include <stdio.h>

#define BLACK 0
#define RED 1

typedef struct rbt_node
{
    int key;
    rbt_node *p;
    rbt_node *left;
    rbt_node *right;
    int color;
};

typedef struct RBT
{
    rbt_node *root;
    rbt_node *nil;
};

void left_rotate(RBT *T, rbt_node *x)
{
    rbt_node *y;
    y = x->right;
    x->right = y->right;
    if (y->left != T->nil)
        y->left->p = x;
    y->p = x->p;
    if (x->p == T->nil)
        T->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void right_rotate(RBT *T, rbt_node *x)
{
    rbt_node *y;
    y = x->left;
    x->left = y->left;
    if (y->right != T->nil)
        y->right->p = x;
    y->p = x->p;
    if (x->p == T->nil)
        T->root = y;
    else if (x == x->p->right)
        x->p->right = y;
    else
        x->p->left = y;
    y->right = x;
    x->p = y;
}
void rbt_insert_fixup(RBT *T, rbt_node *z){
    while (z->p->color==RED)
    {
        
    }
    
}
void rbt_insert(RBT *T, rbt_node *z)
{
    rbt_node *x, *y;
    y = T->nil;
    x = T->root;
    while (x != T->nil)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if (y == T->nil)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left =T->nil;
    z->right=T->nil;
    z->color=RED;
    rbt_insert_fixup(T,z);
}
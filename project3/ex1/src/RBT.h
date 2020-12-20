#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BLACK 0
#define RED 1

typedef struct rbt_node
{
    int key;
    struct rbt_node *p;
    struct rbt_node *left;
    struct rbt_node *right;
    int color;
} rbt_node;

typedef struct RBT
{
    struct rbt_node *root;
    struct rbt_node *nil;
} RBT;

typedef struct delete_list
{
    struct rbt_node *node;
    struct delete_list *next;
} delete_list;

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
void rbt_insert_fixup(RBT *T, rbt_node *z)
{
    rbt_node *y;
    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else if (z == z->p->right)
            {
                z = z->p;
                left_rotate(T, z);
            }
            z->p->color = BLACK;
            z->p->p->color = RED;
            right_rotate(T, z->p->p);
        }
        else
        {
            y = z->p->p->right;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else if (z == z->p->left)
            {
                z = z->p;
                right_rotate(T, z);
            }
            z->p->color = BLACK;
            z->p->p->color = RED;
            left_rotate(T, z->p->p);
        }
    }
    T->root->color = BLACK;
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
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;
    rbt_insert_fixup(T, z);
}

void rbt_transplant(RBT *T, rbt_node *u, rbt_node *v)
{
    if (u->p == T->nil)
        T->root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    v->p = u->p;
}

rbt_node *tree_minimum(rbt_node *x)
{
    while (x->left != NULL)
    {
        x = x->left;
    }
    return x;
}

rbt_node *tree_maximum(rbt_node *x)
{
    while (x->right != NULL)
    {
        x = x->right;
    }
    return x;
}

void rbt_delete_fixup(RBT *T, rbt_node *x)
{
    rbt_node *w;
    while (x != T->nil && x->color == BLACK)
    {
        if (x == x->p->left)
        {
            w = x->p->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(T, x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else if (w->right->color == BLACK)
            {
                w->left->color = BLACK;
                w->color = RED;
                right_rotate(T, w);
                w = x->p->right;
            }
            w->color = x->p->color;
            x->p->color = BLACK;
            w->right->color = BLACK;
            left_rotate(T, x->p);
            x = T->root;
        }
        else
        {
            w = x->p->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(T, x->p);
                w = x->p->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else if (w->left->color == BLACK)
            {
                w->right->color = BLACK;
                w->color = RED;
                left_rotate(T, w);
                w = x->p->left;
            }
            w->color = x->p->color;
            x->p->color = BLACK;
            w->left->color = BLACK;
            right_rotate(T, x->p);
            x = T->root;
        }
    }
    x->color = BLACK;
}
void rbt_delete(RBT *T, rbt_node *z)
{
    rbt_node *y = z;
    rbt_node *x;
    int y_original_color = y->color;
    if (z->left == T->nil)
    {
        x = z->right;
        rbt_transplant(T, z, z->right);
    }
    else if (z->right = T->nil)
    {
        x = z->left;
        rbt_transplant(T, z, z->left);
    }
    else
    {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->p == z)
            x->p = y;
        else
        {
            rbt_transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        rbt_transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK)
        rbt_delete_fixup(T, x);
}

void inorder(FILE *f, RBT *T, rbt_node *node)
{
    if (node == T->nil)
        return;
    inorder(f, T, node->left);
    fprintf(f, " %d ", node->key);
    inorder(f, T, node->right);
}
#include <stdio.h>

#define BLACK 0
#define RED 1



typedef struct rbt_node {
    int key;
    rbt_node* p;
    rbt_node* left;
    rbt_node* right;
    int color;
};

typedef struct RBT
{
    rbt_node *root;
    rbt_node *nil;
};

void left_rotate(RBT* T,rbt_node *x){
    rbt_node *y;
    y=x->right;
    x->right=y->right;
    if(y->left!=T->nil)
        y->left->p=x;
    y->p=x->p;
    if(x->p==T->nil)
        T->root=y;
    else if(x==x->p->left)
        x->p->left=y;
    else
        x->p->right=y;
    y->left=x;    
}
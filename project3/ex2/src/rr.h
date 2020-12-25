#define RED 0
#define BLACK 1

typedef struct rbt_node
{
    int color;
    int key;
    struct rbt_node *left;
    struct rbt_node *right;
    struct rbt_node *parent;
    int high;
    int max;
} rbt_node;

typedef struct RBT
{
    rbt_node *node;
} RBT;

typedef struct delete_list
{
    struct rbt_node *node;
    struct delete_list *next;
} delete_list;

#include <stdio.h>
#include <stdlib.h>



RBT *create_rbt()
{
    RBT *root = (RBT *)malloc(sizeof(RBT));
    root->node = NULL;
    return root;
}

void inorder(FILE *f, RBT *T, rbt_node *node)
{
    if (node == NULL)
        return;
    inorder(f, T, node->left);
    fprintf(f, " [%d,%d] %d\n", node->key, node->high, node->max);
    inorder(f, T, node->right);
}

rbt_node *minimum(rbt_node *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

rbt_node *maximum(rbt_node *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

void rbt_left_rotate(RBT *root, rbt_node *x)
{
    rbt_node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root->node = y;
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    y->max = x->max;
    if (x->left != NULL && (x->left->max > x->max))
        x->max = x->left->max;
    if (x->right != NULL && (x->right->max > x->max))
        x->max = x->right->max;
}

void rbt_right_rotate(RBT *root, rbt_node *y)
{
    rbt_node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        root->node = x;
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
    y->max = x->max;
    if (x->left != NULL && (x->left->max > x->max))
        x->max = x->left->max;
    if (x->right != NULL && (x->right->max > x->max))
        x->max = x->right->max;
}

static void rbt_insert_fixup(RBT *root, rbt_node *node)
{
    rbt_node *parent, *gparent;
    while ((parent = node->parent) && parent->color == RED)
    {
        gparent = parent->parent;
        if (parent == gparent->left)
        {
            {
                rbt_node *uncle = gparent->right;
                if (uncle && uncle->color == RED)
                {
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    gparent->color = RED;
                    node = gparent;
                    continue;
                }
            }
            if (parent->right == node)
            {
                rbt_node *tmp;
                rbt_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            parent->color = BLACK;
            gparent->color = RED;
            rbt_right_rotate(root, gparent);
        }
        else
        {
            {
                rbt_node *uncle = gparent->left;
                if (uncle && uncle->color == RED)
                {
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    gparent->color = RED;
                    node = gparent;
                    continue;
                }
            }
            if (parent->left == node)
            {
                rbt_node *tmp;
                rbt_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            parent->color = BLACK;
            gparent->color = RED;
            rbt_left_rotate(root, gparent);
        }
    }
    root->node->color = BLACK;
}

void rbt_insert(RBT *root, rbt_node *node)
{
    rbt_node *y = NULL;
    rbt_node *x = root->node;
    while (x != NULL)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    node->parent = y;
    if (y != NULL)
    {
        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }
    else
    {
        root->node = node;
    }
    node->color = RED;
    y = node;
    while (y != root->node)
    {
        if (y->max > y->parent->max)
            y->parent->max = y->max;
        y = y->parent;
    }

    rbt_insert_fixup(root, node);
}

rbt_node *create_rbt_node(int key, int h, rbt_node *parent, rbt_node *left, rbt_node *right)
{
    rbt_node *p;
    if ((p = (rbt_node *)malloc(sizeof(rbt_node))) == NULL)
        return NULL;
    p->key = key;
    p->high = h;
    p->max = h;
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK;
    return p;
}

rbt_node *insert_rbt(RBT *root, int key, int h)
{
    rbt_node *node;
    if ((node = create_rbt_node(key, h, NULL, NULL, NULL)) == NULL)
        return NULL;
    rbt_insert(root, node);
    return node;
}

void rbt_delete_fixup(RBT *root, rbt_node *node, rbt_node *parent)
{
    rbt_node *other;
    while ((!node || node->color == BLACK) && node != root->node)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (other->color == RED)
            {
                other->color = BLACK;
                parent->color = RED;
                rbt_left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || other->left->color == BLACK) &&
                (!other->right || other->right->color == BLACK))
            {
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->right || other->right->color == BLACK)
                {
                    other->left->color = BLACK;
                    ;
                    other->color = RED;
                    ;
                    rbt_right_rotate(root, other);
                    other = parent->right;
                }
                other->color = parent->color;
                parent->color = BLACK;
                other->right->color = BLACK;
                rbt_left_rotate(root, parent);
                node = root->node;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (other->color == RED)
            {
                other->color = BLACK;
                parent->color = RED;
                rbt_right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || other->left->color == BLACK) &&
                (!other->right || other->right->color == BLACK))
            {
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->left || other->left->color == BLACK)
                {
                    other->right->color = BLACK;
                    other->color = RED;
                    rbt_left_rotate(root, other);
                    other = parent->left;
                }
                other->color = parent->color;
                parent->color = BLACK;
                other->left->color = BLACK;
                rbt_right_rotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node)
        node->color = BLACK;
}

void rbt_delete(RBT *root, rbt_node *node)
{
    rbt_node *child, *parent;
    int color;
    if ((node->left != NULL) && (node->right != NULL))
    {
        rbt_node *replace = node;
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;
        if (node->parent)
        {
            if (node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        }
        else
            root->node = replace;
        child = replace->right;
        parent = replace->parent;
        color = replace->color;
        if (parent == node)
        {
            parent = replace;
        }
        else
        {
            if (child)
                child->parent = parent;
            parent->left = child;
            replace->right = node->right;
            node->right->parent = replace;
        }
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;
        if (color == BLACK)
            rbt_delete_fixup(root, child, parent);
        free(node);
        return;
    }
    if (node->left != NULL)
        child = node->left;
    else
        child = node->right;
    parent = node->parent;
    color = node->color;
    if (child)
        child->parent = parent;
    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root->node = child;

    if (color == BLACK)
        rbt_delete_fixup(root, child, parent);
    free(node);
}

void delete_rbt(RBT *root, int key)
{
    rbt_node *z, *node;
    rbt_delete(root, z);
}

void rbt_destroy(rbt_node *tree)
{
    if (tree == NULL)
        return;
    if (tree->left != NULL)
        rbt_destroy(tree->left);
    if (tree->right != NULL)
        rbt_destroy(tree->right);
    free(tree);
}

void destroy_rbt(RBT *root)
{
    if (root != NULL)
        rbt_destroy(root->node);
    free(root);
}

rbt_node *interval_search(RBT *T, rbt_node *i)
{
    rbt_node *x = T->node;
    while (x != NULL && (i->key > x->key || i->high < x->high))
    {
        if (x->left != NULL && x->left->max >= i->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

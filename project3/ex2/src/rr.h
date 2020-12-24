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

#define rb_parent(r) ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r) ((r)->color == RED)
#define rb_is_black(r) ((r)->color == BLACK)
#define rb_set_black(r)     \
    do                      \
    {                       \
        (r)->color = BLACK; \
    } while (0)
#define rb_set_red(r)     \
    do                    \
    {                     \
        (r)->color = RED; \
    } while (0)
#define rb_set_parent(r, p) \
    do                      \
    {                       \
        (r)->parent = (p);  \
    } while (0)
#define rb_set_color(r, c) \
    do                     \
    {                      \
        (r)->color = (c);  \
    } while (0)

/*
 * 创建红黑树，返回"红黑树的根"！
 */
RBT *create_rbtree()
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

void rbtree_left_rotate(RBT *root, rbt_node *x)
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

void rbtree_right_rotate(RBT *root, rbt_node *y)
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

static void rbtree_insert_fixup(RBT *root, rbt_node *node)
{
    rbt_node *parent, *gparent;
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);
        if (parent == gparent->left)
        {
            {
                rbt_node *uncle = gparent->right;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }
            if (parent->right == node)
            {
                rbt_node *tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_right_rotate(root, gparent);
        }
        else
        {
            {
                rbt_node *uncle = gparent->left;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }
            if (parent->left == node)
            {
                rbt_node *tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_left_rotate(root, gparent);
        }
    }
    rb_set_black(root->node);
}

void rbtree_insert(RBT *root, rbt_node *node)
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
    rb_parent(node) = y;
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

    rbtree_insert_fixup(root, node);
}

rbt_node *create_rbtree_node(int key, int h, rbt_node *parent, rbt_node *left, rbt_node *right)
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

rbt_node *insert_rbtree(RBT *root, int key, int h)
{
    rbt_node *node;
    if ((node = create_rbtree_node(key, h, NULL, NULL, NULL)) == NULL)
        return NULL;
    rbtree_insert(root, node);
    return node;
}

void rbtree_delete_fixup(RBT *root, rbt_node *node, rbt_node *parent)
{
    rbt_node *other;
    while ((!node || rb_is_black(node)) && node != root->node)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rbtree_right_rotate(root, other);
                    other = parent->right;
                }
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                rbtree_left_rotate(root, parent);
                node = root->node;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    rb_set_black(other->right);
                    rb_set_red(other);
                    rbtree_left_rotate(root, other);
                    other = parent->left;
                }
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rbtree_right_rotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}

void rbtree_delete(RBT *root, rbt_node *node)
{
    rbt_node *child, *parent;
    int color;
    if ((node->left != NULL) && (node->right != NULL))
    {
        rbt_node *replace = node;
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        }
        else
            root->node = replace;
        child = replace->right;
        parent = rb_parent(replace);
        color = rb_color(replace);
        if (parent == node)
        {
            parent = replace;
        }
        else
        {
            if (child)
                rb_set_parent(child, parent);
            parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right, replace);
        }
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;
        if (color == BLACK)
            rbtree_delete_fixup(root, child, parent);
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
        rbtree_delete_fixup(root, child, parent);
    free(node);
}

void delete_rbtree(RBT *root, int key)
{
    rbt_node *z, *node;
    rbtree_delete(root, z);
}

void rbtree_destroy(rbt_node *tree)
{
    if (tree == NULL)
        return;
    if (tree->left != NULL)
        rbtree_destroy(tree->left);
    if (tree->right != NULL)
        rbtree_destroy(tree->right);
    free(tree);
}

void destroy_rbtree(RBT *root)
{
    if (root != NULL)
        rbtree_destroy(root->node);
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

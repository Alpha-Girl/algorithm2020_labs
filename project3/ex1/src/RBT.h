#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1

typedef struct rbt_node
{
    int color;
    int key;
    struct rbt_node *left;
    struct rbt_node *right;
    struct rbt_node *parent;
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

/***********
函数名：create_rbt
函数功能描述：创建红黑树
输入参数的类型和意义：无
输出参数的类型和意义：RBT* 红黑树指针
************/
RBT *create_rbt()
{
    RBT *root = (RBT *)malloc(sizeof(RBT));
    root->node = NULL;
    return root;
}

/***********
函数名：inorder
函数功能描述：中序遍历红黑树
输入参数的类型和意义：FILE* 输出的文件指针，RBT* 红黑树指针, rbt_node* 当前输出的节点
输出参数的类型和意义：无
************/
void inorder(FILE *f, RBT *T, rbt_node *node)
{
    if (node == NULL)
        return;
    inorder(f, T, node->left);
    fprintf(f, " %d ", node->key);
    inorder(f, T, node->right);
}

/***********
函数名：minimum
函数功能描述：红黑树子树的最小值
输入参数的类型和意义：rbt_node* 子树的根
输出参数的类型和意义：rbt_node* 最小值节点对应的指针
************/
rbt_node *minimum(rbt_node *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

/***********
函数名：maximum
函数功能描述：红黑树子树的最大值
输入参数的类型和意义：rbt_node* 子树的根
输出参数的类型和意义：rbt_node* 最大值节点对应的指针
************/
rbt_node *maximum(rbt_node *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

/***********
函数名：rbt_left_rotate
函数功能描述：红黑树左旋
输入参数的类型和意义：RBT* 红黑树指针，rbt_node* 待左旋的节点
输出参数的类型和意义：无
************/
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
}

/***********
函数名：rbt_right_rotate
函数功能描述：红黑树右旋
输入参数的类型和意义：RBT* 红黑树指针，rbt_node* 待右旋的节点
输出参数的类型和意义：无
************/
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
}

/***********
函数名：rbt_insert_fixup
函数功能描述：红黑树插入调整
输入参数的类型和意义：RBT* 红黑树指针，rbt_node* 待调整的节点
输出参数的类型和意义：无
************/
void rbt_insert_fixup(RBT *root, rbt_node *node)
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

/***********
函数名：rbt_insert
函数功能描述：红黑树插入
输入参数的类型和意义：RBT* 红黑树指针，rbt_node* 待插入的节点
输出参数的类型和意义：无
************/
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
    rbt_insert_fixup(root, node);
}

/***********
函数名：create_rbt_node
函数功能描述：红黑树节点创建
输入参数的类型和意义：int key 关键字,  rbt_node *parent 父节点, rbt_node *left 左孩子, rbt_node *right右孩子
输出参数的类型和意义：rbt_node* 红黑树节点指针
************/
rbt_node *create_rbt_node(int key, rbt_node *parent, rbt_node *left, rbt_node *right)
{
    rbt_node *p;
    if ((p = (rbt_node *)malloc(sizeof(rbt_node))) == NULL)
        return NULL;
    p->key = key;
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK;
    return p;
}

/***********
函数名：insert_rbt
函数功能描述：红黑树节点插入
输入参数的类型和意义：RBT *root 红黑树根, int key 关键字
输出参数的类型和意义：rbt_node* 红黑树节点指针
************/
rbt_node *insert_rbt(RBT *root, int key)
{
    rbt_node *node;
    if ((node = create_rbt_node(key, NULL, NULL, NULL)) == NULL)
        return NULL;
    rbt_insert(root, node);
    return node;
}

/***********
函数名：rbt_delete_fixup
函数功能描述：红黑树节点删除调整
输入参数的类型和意义：RBT *root 红黑树根, rbt_node *node 待删除节点, rbt_node *parent 待删除节点的父亲
输出参数的类型和意义：无
************/
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
                    other->color = RED;
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

/***********
函数名：rbt_delete
函数功能描述：红黑树节点
输入参数的类型和意义：RBT *root 红黑树根, rbt_node *node 待删除节点
输出参数的类型和意义：无
************/
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

/***********
函数名：rbt_destroy
函数功能描述：红黑树节点销毁
输入参数的类型和意义：rbt_node *tree 待销毁节点
输出参数的类型和意义：无
************/
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

/***********
函数名：rbt_destroy
函数功能描述：红黑树销毁
输入参数的类型和意义：RBT *root 待销毁树指针
输出参数的类型和意义：无
************/
void destroy_rbt(RBT *root)
{
    if (root != NULL)
        rbt_destroy(root->node);
    free(root);
}

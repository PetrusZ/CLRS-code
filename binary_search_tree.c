/*
 * =====================================================================================
 *
 *       Filename:  tree.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月09日 10时38分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int     key;
    struct node    *left;
    struct node    *right;
    struct node    *p;
}NODE;


void
node_init(NODE *node)
{
    node->left = NULL;
    node->right = NULL;
    node->p = NULL;
    node->key = 0;
}

void
inorder_tree_walk(NODE *x)
{
    if (x != NULL) {
        inorder_tree_walk(x->left);
        printf("%d ", x->key);
        inorder_tree_walk(x->right);
    }
}

NODE *
tree_search(NODE *x, int k)
{
    if (x == NULL || k == x->key)
        return(x);
    if (k < x->key)
        return(tree_search(x->left, k));
    else
        return(tree_search(x->right, k));
}

NODE *
iterative_tree_search(NODE *x, int k)
{
    /*
     * 对于大多数计算机，采用while循环
     * 来展开递归，用一种迭代方式重新
     * 这个过程，运行的效率要比递归高
     * 的多。
     */
    while (x != NULL && k != x->key) {
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return(x);
}

NODE *
tree_minimum(NODE *x)
{
    /*
     * 二叉搜索树性质保证了tree_minimum是正确的
     */
    while (x->left != NULL)
        x = x->left;

    return(x);
}

NODE *
tree_maximum(NODE *x)
{
    /*
     * 与tree_minimum是对称的
     */
    while (x->right != NULL)
        x = x->right;

    return(x);
}

NODE *
tree_successor(NODE *x)
{
    /*
     * 查找一个节点的后继
     *
     * case1: 如果结点x的右子树非空，
     * 那么x的后继恰是x右子树中的最左结点。
     *
     * case2:如果结点x的右子树为空,并有一个后继y，
     * 那么y就是x的有左孩子的最底层祖先，并且它也是
     * x的一个祖先
     */
    NODE    *y;

    y = (NODE *)malloc(sizeof(NODE));
    node_init(y);

    if (x->right != NULL)
        return tree_minimum(x->right);

    y = x->p;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->p;
    }

    return(y);

}

NODE *
tree_predecessor(NODE *x)
{
    /*
     * 查找先驱，与tree_successor对称
     */
    NODE    *y;

    y = (NODE *)malloc(sizeof(NODE));
    node_init(y);

    if (x->left != NULL)
        return tree_maximum(x->left);

    y = x->p;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->p;
    }

    return(y);

}

void
tree_insert(NODE **root, int key)
{
    NODE    *x, *y, *z;

    y = NULL;
    z = (NODE *)malloc(sizeof(NODE));
    node_init(z);
    z->key = key;

    x = *root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y;
    if (y == NULL)
        *root = z;         //tree T was empty
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

void
transplant(NODE **root, NODE *u, NODE *v)
{
    /*
     * 用一颗以v为根的子树来替换一颗以u为根的子树时，
     * 结点u的双亲就变成了结点v的双亲。
     * 注意，transplant并没有处理v.left和v.right的更新，
     * 这些更新都是由transplant的调用者来负责。
     */
    if (u->p == NULL)
        *root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right =v;
    
    if (v != NULL)
        v->p = u->p;
}

void
tree_delete(NODE **root, NODE *z)
{
    /*
     * case1: 结点z没有左孩子
     * case2: 结点z没有右孩子
     * case3: 结点z有两个孩子
     */
    NODE    *y;
    
    y = (NODE *)malloc(sizeof(NODE));
    node_init(y);

    if (z->left == NULL)
        transplant(root, z, z->right);
    else if (z->right == NULL)
        transplant(root, z, z->left);
    else {
        y = tree_minimum(z->right);
        if (y->p != z) {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->p = y;
    }

}

int
main(void)
{
    NODE    *root;

    root = NULL;

    tree_insert(&root, 13);
    tree_insert(&root, 3);
    tree_insert(&root, 83);
    tree_insert(&root, 15);
    tree_insert(&root, 61);
    tree_insert(&root, 74);
    tree_insert(&root, 81);

    printf("after insert 7 elements:\n");
    inorder_tree_walk(root);
    printf("\n");

    tree_delete(&root, tree_search(root, 3));
    tree_delete(&root, iterative_tree_search(root, 83));

    printf("\nafter delete 3, 83:\n");
    inorder_tree_walk(root);
    printf("\n");

    printf("\nminimum: %d\n", tree_minimum(root)->key);
    printf("\nmaximum: %d\n", tree_maximum(root)->key);

    printf("\nsuccessor of 15: %d\n", tree_successor(iterative_tree_search(root, 15))->key);
    printf("\npredeccessor of 74: %d\n", tree_predecessor(iterative_tree_search(root, 74))->key);
}

#include "rr.h"
#include "malloc.h"
#include <windows.h>
int in[100];
int j[60];
FILE *f_in, *out1, *out3, *out2;
int main()
{
    f_in = fopen("../input/input.txt", "w");
    //播种随机数，存入input.txt
    srand(time(NULL));
    int i = 0;
    for (i = 0; i < 60; i++)
        j[i] = 0;
    i = 0;
    for (;;)
    {
        in[i] = rand() % 51;
        in[i + 1] = rand() % 51;
        if (in[i] > in[i + 1])
        {
            int tmp = in[i];
            in[i] = in[i + 1];
            in[i + 1] = tmp;
        }
        if ((in[i] < 30 && in[i + 1] > 25) || j[in[i]] == 1)
        {
        }
        else
        {
            fprintf(f_in, "%d %d\n", in[i], in[i + 1]);
            j[in[i]]++;
            i = i + 2;
        }
        if (i == 60)
            break;
    }
    fclose(f_in);
    printf("Finished 1.\n");
    out1 = fopen("../output/inorder.txt", "w");
    out3 = fopen("../output/search.txt", "w");
    out2 = fopen("../output/delete_data.txt", "w");
    RBT *T = create_rbtree();
    int choose = rand() % 15;
    int flag = 0;
    rbt_node *de1, *de2, *de3;
    for (i = 0; i < 30; i++)
    {
        rbt_node *x = insert_rbtree(T, in[2 * i], in[2 * i + 1]);
        if (i == choose)
            de1 = x;
        else if (i - 15 == choose)

            de2 = x;
        else if (flag == 0 && x->high <= 25)
        {
            de3 = x;
            flag = 1;
        }
    }
    printf("ok");
    inorder(out1, T, T->node);
    fclose(out1);
    fprintf(out2, "[%d,%d]\n", de1->key, de1->high);
    rbtree_delete(T, de1);
    fprintf(out2, "[%d,%d]\n", de2->key, de2->high);
    rbtree_delete(T, de2);
    fprintf(out2, "[%d,%d]\n", de3->key, de3->high);
    rbtree_delete(T, de3);
    inorder(out2, T, T->node);

    fclose(out2);
    int l, r;
    l = rand() % 3;
    r = rand() % 3;
    rbt_node *x;
    if (l < r)
    {
        x = interval_search(T, create_rbtree_node(l + 26, r + 26, NULL, NULL, NULL));
        if (x == NULL)
            fprintf(out3, "There is no interval overlaps [%d,%d].\n", l + 26, r + 26);
        else
            fprintf(out3, "There is [%d,%d] overlaps [%d,%d].\n", x->key, x->high, l + 26, r + 26);
    }
    else
    {
        x = interval_search(T, create_rbtree_node(r + 26, l + 26, NULL, NULL, NULL));
        if (x == NULL)
            fprintf(out3, "There is no interval overlaps [%d,%d].\n", r + 26, l + 26);
        else
            fprintf(out3, "There is [%d,%d] overlaps [%d,%d].\n", x->key, x->high, r + 26, l + 26);
    }
    for (i = 0; i < 2; i++)
    {
        l = rand() % 51;
        r = rand() % 51;
        if (l < r)
        {
            x = interval_search(T, create_rbtree_node(l, r, NULL, NULL, NULL));
            if (x == NULL)
                fprintf(out3, "There is no interval overlaps [%d,%d].\n", l, r);
            else
                fprintf(out3, "There is [%d,%d] overlaps [%d,%d].\n", x->key, x->high, l, r);
        }
        else
        {
            x = interval_search(T, create_rbtree_node(r, l, NULL, NULL, NULL));
            if (x == NULL)
                fprintf(out3, "There is no interval overlaps [%d,%d].\n", r, l);
            else
                fprintf(out3, "There is [%d,%d] overlaps [%d,%d].\n", x->key, x->high, r, l);
        }
    }

    fclose(out3);
}

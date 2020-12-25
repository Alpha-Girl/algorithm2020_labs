#include "interval.h"
#include "malloc.h"
#include <windows.h>
#include <time.h>
int in[100];
int j[60];
FILE *f_in, *out1, *out3, *out2;
int main()
{
    f_in = fopen("../input/input.txt", "w");
    //播种随机数
    srand(time(NULL));
    int i = 0;
    for (i = 0; i < 60; i++)
        j[i] = 0;
    i = 0;
    //生成30个[0,25]或[25,50]的区间，存入input.txt
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
            fprintf(f_in, "[%d,%d]\n", in[i], in[i + 1]);
            j[in[i]]++;
            i = i + 2;
        }
        if (i == 60)
            break;
    }
    fclose(f_in);

    out1 = fopen("../output/inorder.txt", "w");
    out3 = fopen("../output/search.txt", "w");
    out2 = fopen("../output/delete_data.txt", "w");
    //建树
    RBT *T = create_rbt();
    int choose = rand() % 15;
    int flag = 0;
    rbt_node *de1 = NULL, *de2 = NULL, *de3 = NULL;
    //插入，并选取待删除节点
    for (i = 0; i < 30; i++)
    {
        rbt_node *x = insert_rbt(T, in[2 * i], in[2 * i + 1]);
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
    //输出中序遍历序列到inorder.txt
    inorder(out1, T, T->node);
    fclose(out1);
    //输出待删除节点到delete_data.txt，并删除节点
    fprintf(out2, "[%d,%d]\n", de1->key, de1->high);
    rbt_delete(T, de1);
    fprintf(out2, "[%d,%d]\n", de2->key, de2->high);
    rbt_delete(T, de2);
    fprintf(out2, "[%d,%d]\n", de3->key, de3->high);
    rbt_delete(T, de3);
    //输出删除后的中序遍历序列到delete_data.txt
    inorder(out2, T, T->node);
    fclose(out2);
    //查找
    int l, r;
    l = rand() % 3;
    r = rand() % 3;
    rbt_node *x;
    //查找一个(25,30)的区间
    if (l < r)
    {
        x = interval_search(T, create_rbt_node(l + 26, r + 26, NULL, NULL, NULL));
        if (x == NULL)
            fprintf(out3, "There is no interval overlaps [%d,%d].\n", l + 26, r + 26);
        else
            fprintf(out3, "There is [%d,%d] overlaps [%d,%d].\n", x->key, x->high, l + 26, r + 26);
    }
    else
    {
        x = interval_search(T, create_rbt_node(r + 26, l + 26, NULL, NULL, NULL));
        if (x == NULL)
            fprintf(out3, "There is no interval overlaps [%d,%d].\n", r + 26, l + 26);
        else
            fprintf(out3, "There is [%d,%d] overlaps [%d,%d].\n", x->key, x->high, r + 26, l + 26);
    }
    //查找两个[0,50]的区间
    for (i = 0; i < 2; i++)
    {
        l = rand() % 51;
        r = rand() % 51;
        if (l < r)
        {
            x = interval_search(T, create_rbt_node(l, r, NULL, NULL, NULL));
            if (x == NULL)
                fprintf(out3, "There is no interval overlaps [%d,%d].\n", l, r);
            else
                fprintf(out3, "There is [%d,%d] overlaps [%d,%d].\n", x->key, x->high, l, r);
        }
        else
        {
            x = interval_search(T, create_rbt_node(r, l, NULL, NULL, NULL));
            if (x == NULL)
                fprintf(out3, "There is no interval overlaps [%d,%d].\n", r, l);
            else
                fprintf(out3, "There is [%d,%d] overlaps [%d,%d].\n", x->key, x->high, r, l);
        }
    }
    fclose(out3);
    system("PAUSE");
}

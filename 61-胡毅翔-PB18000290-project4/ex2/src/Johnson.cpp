#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#define N 30010
#define M 60010
#define INF 1000000000
using namespace std;
typedef pair<long long, int> data;
int n, m, head[N], cnt = 0, sum[N], father[N], use[N];
long long h[N], dis[N];
bool vis[N];
struct Edge
{
    int nxt, to, val;
} ed[M];

//生成随机数
int rand(int n) { return n ? rand() % n : 0; }

//加边
void add(int u, int v, int w)
{
    ed[++cnt].nxt = head[u];
    ed[cnt].to = v, ed[cnt].val = w;
    head[u] = cnt;
    return;
}

//计算新的w
void redefine_w()
{
    queue<int> q;
    memset(h, 63, sizeof(h));
    memset(vis, false, sizeof(vis));
    h[0] = 0, vis[0] = true;
    q.push(0);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (++sum[u] >= n)
        {
            printf("-1\n");
            exit(0);
        }
        vis[u] = false;
        for (int i = head[u]; i; i = ed[i].nxt)
        {
            int v = ed[i].to, w = ed[i].val;
            if (h[v] > h[u] + w)
            {
                h[v] = h[u] + w;
                if (!vis[v])
                    q.push(v), vis[v] = true;
            }
        }
    }
    return;
}

//反向输出最短路径
void print_way(int s, int t, FILE *out)
{
    if (s != t)
    {
        print_way(s, father[t], out);
        fprintf(out, ",%d", t);
    }
    else
    {
        fprintf(out, "(%d", s);
    }
}

//求最短路径并输出到result
void dijkstra(int s, FILE *out)
{
    priority_queue<data> q;
    for (int i = 1; i <= n; i++)
        dis[i] = INF;
    memset(vis, false, sizeof(vis));
    dis[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = ed[i].nxt)
        {
            int v = ed[i].to, w = ed[i].val;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                father[v] = u;
                if (!vis[v])
                    q.push(make_pair(-dis[v], v));
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (i == s)
            continue;
        if (dis[i] == INF)
            fprintf(out, "\nThere is no way from %d to %d.", s, i);
        else
        {
            fprintf(out, "\nThe weight of the shortest way from %d to %d is %d\n", s, i, dis[i]);
            print_way(s, i, out);
            fprintf(out, ")");
        }
    }
    return;
}

//返回运行时间
double test(int vn, int lo, FILE *in, FILE *out)
{
    n = vn;
    m = (int)(log(vn) / log(lo));
    int u, v, w;
    for (int j = 1; j <= n; j++)
    {
        for (int k = 1; k <= n; k++)
            use[k] = 0;
        for (int i = 1; i <= m; i++)
        {
            v = rand(n) + 1;
            if (use[v] == 0)
            {
                w = rand(50) + 1;
                add(j, v, w);
                fprintf(in, "( %d , %d ) %d\n", j, v, w);
            }
            else
            {
                i--;
            }
        }
    }

    double run_time;
    LARGE_INTEGER time_start; //开始时间
    LARGE_INTEGER time_over;  //结束时间
    double dqFreq;            //计时器频率
    LARGE_INTEGER f;          //计时器频率
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;
    QueryPerformanceCounter(&time_start); //计时开始
    for (int i = 1; i <= n; i++)
        add(0, i, 0);
    redefine_w();
    for (int u = 1; u <= n; u++)
        for (int j = head[u]; j; j = ed[j].nxt)
            ed[j].val += h[u] - h[ed[j].to];
    for (int i = 1; i <= n; i++)
    {
        dijkstra(i, out);
    }
    QueryPerformanceCounter(&time_over); //计时结束
    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    //乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
    return run_time;
}

int main()
{
    srand(time(NULL));
    double time[8];
    FILE *f1, *f2;
    f1 = fopen("../input/input11.txt", "w");
    f2 = fopen("../output/result11.txt", "w");
    time[0] = test(27, 5, f1, f2);
    fclose(f1);
    fclose(f2);

    f1 = fopen("../input/input12.txt", "w");
    f2 = fopen("../output/result12.txt", "w");
    time[1] = test(27, 7, f1, f2);
    fclose(f1);
    fclose(f2);

    f1 = fopen("../input/input21.txt", "w");
    f2 = fopen("../output/result21.txt", "w");
    time[2] = test(81, 5, f1, f2);
    fclose(f1);
    fclose(f2);

    f1 = fopen("../input/input22.txt", "w");
    f2 = fopen("../output/result22.txt", "w");
    time[3] = test(81, 7, f1, f2);
    fclose(f1);
    fclose(f2);

    f1 = fopen("../input/input31.txt", "w");
    f2 = fopen("../output/result31.txt", "w");
    time[4] = test(243, 5, f1, f2);
    fclose(f1);
    fclose(f2);

    f1 = fopen("../input/input32.txt", "w");
    f2 = fopen("../output/result32.txt", "w");
    time[5] = test(243, 7, f1, f2);
    fclose(f1);
    fclose(f2);

    f1 = fopen("../input/input41.txt", "w");
    f2 = fopen("../output/result41.txt", "w");
    time[6] = test(729, 5, f1, f2);
    fclose(f1);
    fclose(f2);

    f1 = fopen("../input/input42.txt", "w");
    f2 = fopen("../output/result42.txt", "w");
    time[7] = test(729, 7, f1, f2);
    fclose(f1);
    fclose(f2);

    f1 = fopen("../output/time.txt", "w");
    fprintf(f1, "N   log5N      log7N\n");
    fprintf(f1, "%d   %lf  %lf\n", 27, time[0], time[1]);
    fprintf(f1, "%d   %lf  %lf\n", 81, time[2], time[3]);
    fprintf(f1, "%d   %lf  %lf\n", 243, time[4], time[5]);
    fprintf(f1, "%d   %lf  %lf\n", 729, time[6], time[7]);
}
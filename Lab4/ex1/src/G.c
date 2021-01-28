#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <time.h>
#define INFINITY 100000
#define MAX_VERTEX_NUM 20
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1
#define GRAY -1
#define WHITE 0
#define BLACK 1
#define STACKINCREMET 10

typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind;
typedef struct ArcCell
{
    int adj;
    char *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
    int s[MAX_VERTEX_NUM * MAX_VERTEX_NUM + 1];
    int fst[MAX_VERTEX_NUM + 1];
    int lst[MAX_VERTEX_NUM + 1];
    int vexnum;
    int arcnum;
} SLGraph;

typedef struct
{
    int *queue;
    int front;
    int rear;
} SqQueue;

typedef int Status;

typedef struct
{
    int *base;
    int *top;
    int stacksize;
} int_stack;

typedef struct
{
    int vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum;
    int arcnum;
    int kind;
} MGraph;

typedef struct
{
    int adjvex;
    struct ArcNode *nextarc;
    int weight;
    char *info;
} ArcNode;

typedef struct VNode
{
    int data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList *vertices;
    int vexnum, arcnum;
    GraphKind kind;
} ALGraph;
int visited[MAX_VERTEX_NUM];
SqQueue *InitQueue()
{
    SqQueue *Q;
    Q = (SqQueue *)malloc(sizeof(SqQueue));
    Q->queue = (int *)malloc(sizeof(int) * 100);
    Q->front = 0;
    Q->rear = 0;
    return Q;
}
Status QueueEmpty(SqQueue *Q)
{
    int Length;
    Length = Q->rear - Q->front;
    return (Length != 0);
}
Status EmptyStack(int_stack *S)
{
    if (*(S->base) == *(S->top))
        return 1;
    else
        return 0;
}
void EnQueue(SqQueue *Q, int a)
{
    Q->queue[Q->rear] = a;
    Q->rear++;
}
int DeQueue(SqQueue *Q)
{
    Q->front++;
    return Q->queue[Q->front - 1];
}
int_stack *InitStack()
{
    int_stack *S;
    S = (int_stack *)malloc(sizeof(int_stack));
    S->base = (int *)malloc(100 * sizeof(int));
    if (!(S->base))
        exit(0);
    S->top = S->base;
    S->stacksize = 100;
    return S;
} //InitStack1
void Push(int_stack *S, int e)
{
    if (S->top - S->base >= S->stacksize)
    {
        S->base = (int *)realloc(S->base, (STACKINCREMET + 100) * sizeof(int));
        if (!S->base)
            exit(0);
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMET;
    }
    *S->top = e;
    S->top++;
    //printf("PUSH1 %d\n",e);
}
int GetTop(int_stack *S)
{
    int e;
    if (S->top == S->base)
        return ERROR;
    e = *(S->top - 1);
    return e;
}
int Pop(int_stack *S)
{
    int e;
    if (S->top == S->base)
    {
        printf("2");
        return ERROR;
    }
    S->top--;
    e = *(S->top);
    //printf("POP1 %d\n",e);
    return e;
} //Pop

Status CreateMGraph(MGraph *G)
{
    int a;
    printf("输入1-4，生成有向图/网、无向图/网：");
    scanf("%d", &a);
    switch (a)
    {
    case 1:
        return CreateMDG(G);
    case 2:
        return CreateMDN(G);
    case 3:
        return CreateMUDG(G);
    case 4:
        return CreateMUDN(G);
    default:
        return ERROR;
    }
} //CreateMGraph

Status CreateALGraph(ALGraph *G)
{
    int a;
    printf("输入1-4，生成有向图/网、无向图/网：");
    scanf("%d", &a);
    G->kind = a;
    switch (a)
    {
    case 1:
        return CreateALDG(G);
    case 2:
        return CreateALDN(G);
    case 3:
        return CreateALUDG(G);
    case 4:
        return CreateALUDN(G);
    default:
        return ERROR;
    }
} //CreateALGraph
Status CreateMDN(MGraph *G)
{
    int inf, i, j, k, w, u, v;
    scanf("%d,%d,%d", &G->vexnum, &G->arcnum, &inf);
    for (i = 0; i < G->vexnum; i++)
        scanf("%d", &G->vexs[i]);
    for (i = 0; i < G->vexnum; i++)
        for (j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].adj = INFINITY;
            G->arcs[i][j].info = NULL;
        }
    for (k = 0; k < G->arcnum; k++)
    {
        scanf("%d,%d,%d", u, v, w);
        G->arcs[u][v].adj = w;
        if (inf)
        {
            G->arcs[u][v].info = (char *)malloc(sizeof(char));
            scanf("%c", G->arcs[u][v].info);
        }
    }
    return OK;
} //CreateMDN

Status CreateALDN(ALGraph *G)
{
    int inf, i, j, k, w, u, v;
    ArcNode *p;
    scanf("%d,%d,%d", &G->vexnum, &G->arcnum, &inf);
    for (i = 0; i < G->vexnum; i++)
    {
        scanf("%d", &u);

        G->vertices[i]->data = u;
        G->vertices[i]->firstarc = NULL;
    }
    for (k = 0; k < G->arcnum; k++)
    {
        scanf("%d,%d,%d,%d", &u, &v, &w, &inf);
        for (p = G->vertices[u]->firstarc; p != NULL; p = p->nextarc)
        {
        }
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = v;
        p->nextarc = NULL;
        p->info = NULL;
        p->weight = w;
        if (inf)
        {
            p->info = (char *)malloc(sizeof(char));
            scanf("%c", p->info);
        }
    }
    return OK;
} //CreateALDN
Status CreateALDG(ALGraph *G)
{
    int inf, i, j, k, u, v;
    ArcNode *p;
    scanf("%d,%d,%d", &G->vexnum, &G->arcnum, &inf);
    for (i = 0; i < G->vexnum; i++)
    {
        scanf("%d", &u);

        G->vertices[i]->data = u;
        G->vertices[i]->firstarc = NULL;
    }
    for (k = 0; k < G->arcnum; k++)
    {
        scanf("%d,%d,%d", &u, &v, &inf);
        for (p = G->vertices[u]->firstarc; p != NULL; p = p->nextarc)
        {
        }
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = v;
        p->nextarc = NULL;
        p->info = NULL;
        p->weight = 1;
        if (inf)
        {
            p->info = (char *)malloc(sizeof(char));
            scanf("%c", p->info);
        }
    }
    return OK;
} //CreateALDG

Status CreateALUDG(ALGraph *G)
{
    int inf, i, j, k, u, v;
    ArcNode Arc;
    ArcNode *ww;
    VNode *q;
    printf("输入无向图的顶点数:");
    scanf("%d", &G->vexnum);
    printf("输入无向图的边数：");
    scanf("%d", &G->arcnum);
    for (i = 0; i < G->vexnum; i++)
    {
        printf("输入第%d个顶的序号：", i + 1);
        scanf("%d", &u);
        q = &(G->vertices[i]);
        q->data = u;
        q->firstarc = NULL;
    }
    for (k = 0; k < G->arcnum; k++)
    {
        printf("输入第%d条边的两顶序号（v，u，inf）：\n", k + 1);
        printf("输入第一个顶序号：");
        scanf("%d", &u);
        printf("输入第二个顶序号：");
        scanf("%d,", &v);
        printf("输入有无信息：");
        scanf("%d", &inf);
        q = &(G->vertices[u]);
        ww = NULL;
        ww = (ArcNode *)malloc(sizeof(ArcNode));
        if (!ww)
            printf("%p\n", ww);

        ww->adjvex = v;

        ww->nextarc = NULL;
        ww->info = NULL;
        ww->nextarc = q->firstarc;
        q->firstarc = ww;
        ww->weight = 1;
        if (inf)
        {
            ww->info = (char *)malloc(sizeof(char));
            scanf("%c", ww->info);
        }
        q = &(G->vertices[v]);
        ww = (ArcNode *)malloc(sizeof(ArcNode));
        ww->adjvex = u;
        ww->nextarc = NULL;
        ww->info = NULL;
        ww->nextarc = q->firstarc;
        q->firstarc = ww;
        ww->weight = 1;
        if (inf)
        {
            ww->info = (char *)malloc(sizeof(char));
            scanf("%c", ww->info);
        }
    }
    return OK;
} //CreateALUDG

Status CreateALUDN(ALGraph *G)
{
    int inf, i, j, w, k, u, v;
    ArcNode *p;
    VNode *q;
    scanf("%d,%d,%d", &G->vexnum, &G->arcnum, &inf);
    for (i = 0; i < G->vexnum; i++)
    {
        scanf("%d", &u);

        G->vertices[i]->data = u;
        G->vertices[i]->firstarc = NULL;
    }
    for (k = 0; k < G->arcnum; k++)
    {
        scanf("%d,%d,%d", &u, &v, &inf);
        for (p = G->vertices[u]->firstarc; p != NULL; p = p->nextarc)
        {
        }
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = v;
        p->nextarc = NULL;
        p->info = NULL;
        p->weight = w;
        if (inf)
        {
            p->info = (char *)malloc(sizeof(char));
            scanf("%c", p->info);
        }
        for (p = G->vertices[v]->firstarc; p != NULL; p = p->nextarc)
        {
        }
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = u;
        p->nextarc = NULL;
        p->info = NULL;
        p->weight = w;
        if (inf)
        {
            p->info = (char *)malloc(sizeof(char));
            scanf("%c", p->info);
        }
    }
    return OK;
} //CreateALDG
Status CreateMDG(MGraph *G)
{
    int inf, i, j, k, u, v;

    printf("输入有向图的顶点数:");
    scanf("%d", &i);
    G->vexnum = i;
    printf("输入有向图的边数：");
    scanf("%d", &i);
    G->arcnum = i;
    printf("输入有无信息：");
    scanf("%d", &inf);

    for (i = 0; i < G->vexnum; i++)
    {
        printf("输入第%d个顶的序号：", i + 1);
        scanf("%d", &G->vexs[i]);
    }
    for (i = 0; i < G->vexnum; i++)
        for (j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].adj = INFINITY;
            G->arcs[i][j].info = NULL;
        }
    for (k = 0; k < G->arcnum; k++)
    {
        printf("输入第%d条边的两顶序号：", k + 1);
        printf("输入第一个顶的序号：");
        scanf("%d", &v);
        printf("输入第二个顶的序号：");
        scanf("%d", &u);
        G->arcs[v][u].adj = 1;
        if (inf)
        {
            G->arcs[v][u].info = (char *)malloc(sizeof(char));
            scanf("%c", G->arcs[v][u].info);
        }
    }
    for (i = 0; i < G->vexnum; i++)
    {
        for (k = 0; k < G->vexnum; k++)
        {
            printf("%d ", G->arcs[i][k]);
        }
        printf("\n");
    }
    return OK;
} //CreateMDG

void MDGtoSLDG(MGraph *MG, SLGraph *SLG)
{
    int i, Cnt, j, cnt;
    SLG->arcnum = MG->arcnum;
    SLG->vexnum = MG->vexnum;
    for (i = 1; i < MG->vexnum + 1; i++)
    {
        SLG->lst[i] = -1;
        SLG->fst[i] = 0;
    }
    Cnt = 0;
    for (i = 0; i < MG->vexnum; i++)
    {
        cnt = 0;
        for (j = 0; j < MG->vexnum; j++)
        {
            if (MG->arcs[i][j].adj < INFINITY)
            {
                Cnt++;
                cnt++;
                SLG->s[Cnt] = j + 1;
                if (cnt == 1)
                    SLG->fst[i + 1] = Cnt;
            }
            SLG->lst[i + 1] = Cnt;
        }
    }
    for (i = 1; i < Cnt + 1; i++)
    {

        printf("%d ", SLG->s[i]);

        printf("\n");
    }
    for (i = 1; i < SLG->vexnum + 1; i++)
    {
        printf("%d %d", SLG->fst, SLG->lst);
    }
}

Status CreateMUDG(MGraph *G, int vn, int en)
{
    int inf, i, j, k, u, v;

    G->vexnum = vn;

    G->arcnum = vn * en;

    for (i = 0; i < G->vexnum; i++)
    {
        G->vexs[i] = i;
    }
    for (i = 0; i < G->vexnum; i++)
        for (j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].adj = INFINITY;
            G->arcs[i][j].info = NULL;
        }
    for (i = 0; i < G->vexnum; i++)
    {
    }
    for (k = 0; k < G->arcnum; k++)
    {
        printf("输入第%d条边的两顶序号：", k + 1);
        printf("输入第一个顶的序号：");
        scanf("%d", &v);
        printf("输入第二个顶的序号：");
        scanf("%d", &u);
        G->arcs[u][v].adj = 1;
        G->arcs[v][u] = G->arcs[u][v];
    }
    //for(i=0;i<G->vexnum;i++) {
    //for(k=0;k<G->vexnum;k++) {
    //         printf("%d ",G->arcs[i][k]);
    // }
    // printf("\n");
    // }
    return OK;
} //CreateMUDG

Status CreateMUDN(MGraph G, int vn, int en)
{
    int inf, i, j, k, w, u, v, sum, t;
    inf = 0;
    G.vexnum = vn;
    G.arcnum = 0;
    for (i = 0; i < G.vexnum; i++)
        G.vexs[i] = i;
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            if (i == j)
            {
                G.arcs[i][j].adj = 0;
            }
            else
            {
                G.arcs[i][j].adj = INFINITY;
            }

            G.arcs[i][j].info = NULL;
        }
    }

    srand(time(NULL));
    for (i = 0; i < G.vexnum; i++)
    {
        sum = 0;

        for (j = 0; j < G.vexnum; j++)
        {
            if (sum >= (vn / 2))
                break;
            if (rand() % 3 && G.arcs[i][j].adj == INFINITY && i != j)
            {
                G.arcs[i][j].adj = rand() % 20 + 1;
                G.arcs[j][i].adj = G.arcs[i][j].adj;
                sum++;
            }
        }
    }
    return OK;
} //CreateMUDN

void BFSTraverse(MGraph *G, Status (*Visit)(int u))
{

    int v, i, j, u;
    SqQueue *Q;
    printf("BFS:\n");
    for (v = 0; v < G->vexnum; ++v)
        visited[v] = FALSE;
    Q = InitQueue();
    for (v = 0; v < G->vexnum; ++v)
        if (!visited[v])
        {
            visited[v] = TRUE;
            Visit(v);
            EnQueue(Q, v);
            while (!QueueEmpty(Q))
            {
                u = DeQueue(Q);
                for (j = 0; j < G->vexnum; j++)
                {
                    if (G->arcs[u][j].adj == 1 && visited[j] == FALSE)
                    {
                        visited[j] = TRUE;
                        Visit(j);
                        EnQueue(Q, j);
                    } //if
                }
            } //while
        }     //if
} //BFSTraverse

void BFSTraverseAL(ALGraph *G, Status (*Visit)(int u))
{
    int v, i, j, u;
    ArcNode *p;
    SqQueue *Q;
    VNode *q;
    for (v = 0; v < G->vexnum; ++v)
        visited[v] = FALSE;
    printf("BFS：\n");
    Q = InitQueue();
    for (v = 0; v < G->vexnum; ++v)
        if (!visited[v])
        {
            visited[v] = TRUE;
            Visit(v);
            EnQueue(Q, v);
            while (!QueueEmpty(Q))
            {
                u = DeQueue(Q);
                q = G->vertices[u];
                for (p = q->firstarc; p; p = p->nextarc)
                {
                    if (visited[p->adjvex] == FALSE)
                    {
                        visited[p->adjvex] = TRUE;
                        Visit(p->adjvex);
                        EnQueue(Q, p->adjvex);
                    } //if
                }
            } //while
        }     //if
} //BFSTraverse
void DFSTraverse(MGraph *G, Status (*Visit)(int u))
{
    int v, i, j;

    int_stack *S;
    printf("DFS:\n");
    for (v = 0; v < G->vexnum; ++v)
        visited[v] = WHITE;
    S = InitStack();
    visited[0] = GRAY;
    Push(S, 0);
    while (!EmptyStack(S))
    {
        v = Pop(S);
        visited[v] = BLACK;
        Visit(v);
        for (j = 0; j < G->vexnum; j++)
        {
            if (G->arcs[v][j].adj == 1 && visited[j] == WHITE)
            {
                visited[j] = GRAY;
                Push(S, j);
            } //if
        }
    }
} //DFSTraverse

void DFSTraverseAL(ALGraph *G, Status (*Visit)(int u))
{
    int v, i, j;
    ArcNode *p;
    int_stack *S;
    for (v = 0; v < G->vexnum; ++v)
        visited[v] = WHITE;
    InitStack(S);
    visited[0] = GRAY;
    Push(S, 0);
    while (!EmptyStack(S))
    {
        v = Pop(S);
        visited[v] = BLACK;
        Visit(v);
        for (p = G->vertices[v]->firstarc; p; p = p->nextarc)
        {
            if (visited[p->adjvex] == FALSE)
            {
                visited[p->adjvex] = TRUE;
                Visit(p->adjvex);
                Push(S, p->adjvex);
            }
        }
    }
} //DFSTraverseAL
int Path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void BFS_Short_Path_M(MGraph *G, int v, int length)
{
    SqQueue *Q;
    int i, u, k;
    Q = InitQueue();
    for (k = 0; k < G->vexnum; k++)
    {
        if (G->arcs[v][k].adj == 1 && visited[k] == FALSE)
        {
            visited[k] = TRUE;

            printf("vex%d_ShortPath:", k);
            for (i = 0; i <= length; i++)
            {
                Path[k][i] = Path[v][i];
                printf("%d ", Path[v][i]);
            }
            Path[k][length + 1] = k;
            printf("%d\n", k);
            EnQueue(Q, k);
        }
    }
    while (QueueEmpty(Q))
    {
        u = DeQueue(Q);
        BFS_Short_Path_M(G, u, length + 1);
    }
}

void ShortestPath_M(MGraph *G, int v0)
{
    int v, u;
    for (v = 0; v < G->vexnum; v++)
    {
        visited[v] = FALSE;
        for (u = 0; u < G->vexnum; u++)
            Path[v][u] = v0;
    }
    visited[v0] = TRUE;
    BFS_Short_Path_M(G, v0, 0);
}

void BFS_Short_Path(ALGraph *G, int v, int length)
{
    SqQueue *Q;
    ArcNode *p;
    int i, u;
    Q = InitQueue();
    for (p = G->vertices[v]->firstarc; p; p = p->nextarc)
    {
        if (visited[p->adjvex] == FALSE)
        {
            visited[p->adjvex] = TRUE;

            printf("vex%d_ShortPath:", p->adjvex);
            for (i = 0; i <= length; i++)
            {
                Path[p->adjvex][i] = Path[v][i];
                printf("%d ", Path[v][i]);
            }
            printf("%d\n", p->adjvex);
            EnQueue(Q, p->adjvex);
        }
    }
    while (!QueueEmpty(Q))
    {
        u = DeQueue(Q);
        BFS_Short_Path(G, u, length + 1);
    }
}
Status ShortestPath(ALGraph *G, int v0)
{
    int v, u;
    for (v = 0; v < G->vexnum; v++)
    {
        visited[v] = FALSE;
        for (u = 0; u < G->vexnum; u++)
            Path[v][u] = v0;
    }
    visited[v0] = TRUE;
    BFS_Short_Path(G, v0, 0);
    return OK;
}

Status Visit(int a)
{
    printf("%d\n", a);
}
int count;
int low[MAX_VERTEX_NUM];
void FindArticul(ALGraph *G)
{
    int i, v;
    ArcNode *p;
    VNode *q;
    count = 1;
    visited[0] = 1;
    for (i = 1; i < G->vexnum; i++)
        visited[i] = 0;
    q = &G->vertices[0];
    p = q->firstarc;
    v = p->adjvex;
    DFSArticul(G, v);
    if (count < G->vexnum)
    {
        printf("Articul:%d\n", q->data);
        while (p->nextarc)
        {
            p = p->nextarc;
            v = p->adjvex;
            if (visited[v] == 0)
                DFSArticul(G, v);
        }
    }
}

void DFSArticul(ALGraph *G, int v0)
{
    int min, w;
    ArcNode *p;
    min = count++;
    visited[v0] = min;
    for (p = G->vertices[v0]->firstarc; p; p = p->nextarc)
    {
        w = p->adjvex;
        if (visited[w] == 0)
        {
            DFSArticul(G, w);
            if (low[w] < min)
                min = low[w];
            if (low[w] >= visited[v0])
                printf("Articul:%d\n", G->vertices[v0]->data);
        }
        else if (visited[w] < min)
            min = visited[w];
    }
    low[v0] = min;
}
/*
int main(){
    ALGraph *ALG;
    int order;
    MGraph *MG;
    MG=(MGraph *)malloc(sizeof(MGraph));
    ALG=(ALGraph *)malloc(sizeof(ALGraph));
    printf("***README***\n本程序第一次输入3，可建立邻接矩阵存储的无向图，并完成广度优先、深度优先遍历及求最短路径\n第二次输入3，可建立邻接表存储的无向图并完成广度优先遍历及求关节点\n有无信息输入0表示该边无信息\n\n");
    CreateMGraph(MG);
    BFSTraverse(MG,Visit);
    DFSTraverse(MG,Visit);
    ShortestPath_M(MG,0);

    CreateALGraph(ALG);
    BFSTraverseAL(ALG,Visit);
    FindArticul(ALG);

    return OK;
}
//
   // scanf("%d",&order);
*/
int main()
{
    MGraph *G;
    G = (MGraph *)malloc(sizeof(MGraph));
    CreateMUDG(G);
}

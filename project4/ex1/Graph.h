#include <stdio.h>
#include <limits.h>
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 100
//图的类型
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

typedef int Status;

//邻接矩阵表示的图
typedef struct
{
    int vexs[MAX_VERTEX_NUM]; //顶点
    AdjMatrix arcs;           //邻接矩阵
    int vexnum;               //顶点数
    int arcnum;               //边数
    int kind;                 //图的类型
} MGraph;

typedef struct
{
    int adjvex;              //顶点
    struct ArcNode *nextarc; //下一条边
    int weight;              //权重
    char *info;
} ArcNode;

typedef struct VNode
{
    int data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

//邻接表表示的图
typedef struct
{
    AdjList *vertices;
    int vexnum, arcnum;
    GraphKind kind;
} ALGraph;

int make()
{
    int M[512][512];
}

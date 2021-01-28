#pragma once
#include <iostream>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

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
	AdjMatrix arcs;			  //邻接矩阵
	int V_n;				  //顶点数
	int A_n;				  //边数
	int kind;				  //图的类型
} MGraph;

typedef struct
{
	int adjvex;				 //顶点
	struct ArcNode *nextarc; //下一条边
	int weight;				 //权重
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
	int V_n, A_n;
	GraphKind kind;
} ALGraph;

int rand(int n) { return n ? rand() % n : 0; }

#define INF 0x3f3f3f3f

typedef pair<int, int> data;
typedef pair<int, data> edge;
struct Graph
{
	vector<edge> edges;
	int V_n = 0, A_n = 0;
};

bool cmp(pair<int, data> e1, pair<int, data> e2)
{
	return e1.first < e2.first;
}

bool cmp1(pair<int, int> d1, pair<int, int> d2)
{
	return d1.first < d2.first;
}

//建图
void InitGraph(Graph &G, int V_n, ostream &os)
{
	G.V_n = V_n;
	int maxEdgeNum = V_n;
	int maxWeight = 20;
	for (int i = 0, RandNum = 0; i < V_n; i++)
	{
		RandNum = rand(maxEdgeNum - i - 1) + 1;
		for (int j = 0; j < RandNum; j++)
		{
			int k = rand(V_n - i) + i;
			int w = rand(maxWeight) + 1;
			G.edges.push_back(make_pair(rand(maxEdgeNum) + 1, make_pair(i, k)));
			os << i << ' ' << k << ' ' << w << endl;
		}
		G.A_n += RandNum;
	}
	sort(G.edges.begin(), G.edges.end(), cmp);
}

//调试用
void ShowGraph(Graph G)
{
	for (auto it = G.edges.begin(); it != G.edges.end(); ++it)
		cout << it->first << ' ' << it->second.first << ' ' << it->second.second << endl;
}

vector<data> Kruskal(Graph G, int &weight)
{
	int *uni = new int[G.V_n];
	vector<data> ans;
	for (int i = 0; i < G.V_n; ++i)
		uni[i] = i;
	for (auto it = G.edges.begin(); it != G.edges.end(); ++it)
	{
		if (uni[it->second.first] != uni[it->second.second])
		{
			ans.push_back(it->second);
			weight += it->first;
			int key = uni[it->second.second];
			for (int i = 0; i < G.V_n; ++i)
				if (uni[i] == key)
					uni[i] = uni[it->second.first];
		}
	}
	sort(ans.begin(), ans.end(), cmp1);
	return ans;
}
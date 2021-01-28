#pragma once
#include <iostream>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

int rand(int n)
{
	return n ? rand() % n : 0;
}

#define INF 0x3f3f3f3f

typedef pair<int, int> dat;
typedef pair<int, dat> edge;
struct Graph
{
	vector<edge> edges;
	int vexnum = 0, arcnum = 0;
};

bool cmp(pair<int, dat> e1, pair<int, dat> e2)
{
	return e1.first < e2.first;
}

bool cmp1(pair<int, int> d1, pair<int, int> d2)
{
	return d1.first < d2.first;
}

void InitGraph(Graph &G, int vexnum, ostream &os)
{
	G.vexnum = vexnum;
	int maxEdgeNum = vexnum;
	int maxWeight = 20;
	for (int i = 0, RandNum = 0; i < vexnum; i++)
	{
		RandNum = rand(maxEdgeNum - i - 1) + 1;
		for (int j = 0; j < RandNum; j++)
		{
			int k = rand(vexnum - i) + i;
			int w = rand(maxWeight) + 1;
			G.edges.push_back(make_pair(rand(maxEdgeNum) + 1, make_pair(i, k)));
			os << i << ' ' << k << ' ' << w << endl;
		}
		G.arcnum += RandNum;
	}
	sort(G.edges.begin(), G.edges.end(), cmp);
}

/*void ShowGraph(Graph G)
{
	for (auto it = G.edges.begin(); it != G.edges.end(); it++)
		cout << it->first << ' ' << it->second.first << ' ' << it->second.second << endl;
}*/

vector<dat> Kruskal(Graph G, int &weight)
{
	int *uni = new int[G.vexnum];
	vector<dat> ans;
	for (int i = 0; i < G.vexnum; ++i)
		uni[i] = i;
	for (vector<edge>::iterator it = G.edges.begin(); it != G.edges.end(); ++it)
	{
		if (uni[it->second.first] != uni[it->second.second])
		{
			ans.push_back(it->second);
			weight += it->first;
			int key = uni[it->second.second];
			for (int i = 0; i < G.vexnum; ++i)
				if (uni[i] == key)
					uni[i] = uni[it->second.first];
		}
	}
	sort(ans.begin(), ans.end(), cmp1);
	return ans;
}

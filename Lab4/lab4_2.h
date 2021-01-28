#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define U 65535
#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)
#define N 5

struct vertex
{
	int key;
	struct vtable *adj;
};

struct vtable
{
	int key;
	int w;
	struct vtable *next;
};

struct vassist
{
	int d;
	int p;
	int key;
};

int insert(struct vertex *, int, int, int, int);
int walk(struct vertex *, int, int);
struct vassist *initialize_ss(int, int);
int relaxd(int *, int, int, int);
int relaxb(struct vassist *, int, int, int);
int build_min_heap(struct vassist *, int);
int min_heapify(struct vassist *, int, int);
int heap_extract_min(struct vassist *, int);
int inheap(struct vassist *, int, int);
int heap_decrease(struct vassist *, int, int);
int dijkstra(struct vertex *, int, int, int **);
int bellman_ford(struct vertex *, int *, int, int);

int insert(struct vertex *p, int len, int i, int j, int w)
{
	struct vtable *q, *prev;
	q = p[i].adj;
	//printf("key:%d\n", p[i].key);
	prev = NULL;
	while (q != NULL)
	{
		if (q->key == j)
		{
			//printf("error: v %d to %d already exist.\n", i, j);
			return 0;
		}
		else
		{
			prev = q;
			q = q->next;
		}
	}
	q = (struct vtable *)malloc(sizeof(struct vtable));
	q->key = j;
	q->w = w;
	q->next = NULL;
	if (prev != NULL)
		prev->next = q;
	else
		p[i].adj = q;
	return 1;
}

int walk(struct vertex *p, int len, int i)
{
	struct vtable *q = p[i].adj;
	while (q != NULL)
	{
		//printf(" %d,w is %d\n", q->key, q->w);
		q = q->next;
	}
	printf("\n");
}

struct vassist *initialize_ss(int size, int s)
{
	int i;
	struct vassist *va;
	va = (struct vassist *)malloc(size * sizeof(struct vassist));
	for (i = 0; i < size; i++)
	{
		va[i].key = i;
		va[i].d = U;
		va[i].p = -1;
	}
	va[s].d = 0;
	return va;
}

//relax for dijkstra
int relaxd(int *p, int u, int v, int w)
{ //w=w(u,v)
	if (p[v] > p[u] + w)
	{
		p[v] = p[u] + w;
	}
	return 1;
}

//relax for beltman_ford
int relaxb(struct vassist *va, int u, int v, int w)
{ //w=w(u,v)
	if (va[v].d > va[u].d + w)
	{
		va[v].d = va[u].d + w;
		va[v].p = u;
	}
	return 1;
}

int bellman_ford(struct vertex *graph, int *h, int size, int s)
{
	int i, j;
	struct vtable *p;
	struct vassist *va;
	va = initialize_ss(size, s);
	for (i = 1; i < size; i++)
		for (j = 0; j < size - 1; j++)
		{
			p = graph[j].adj;
			while (p != NULL)
			{
				relaxb(va, j, p->key, p->w);
				p = p->next;
			}
		}

	printf("from %d,\n", s);
	for (j = 0; j < size; j++)
		printf("to %d: %d\n", j, va[j].d);

	for (j = 0; j < size; j++)
	{
		p = graph[j].adj;
		while (p != NULL)
		{
			if (va[p->key].d > va[j].d + p->w)
				return 0;
			p = p->next;
		}
	}
	for (j = 1; j <= size; j++)
		h[j] = va[j].d;
	free(va);
	h[0] = 0;
	return 1;
}

int build_min_heap(struct vassist *va, int size)
{
	int i;
	for (i = size / 2 - 1; i >= 0; i--)
		min_heapify(va, i, size);
	return 1;
}

int min_heapify(struct vassist *va, int i, int heap_size)
{
	int l, r, min;
	struct vassist temp;
	int tmin = U;
	l = LEFT(i);
	r = RIGHT(i);
	if ((l < heap_size) && (va[l].d < va[i].d))
	{
		min = l;
		tmin = va[l].d;
	}
	else
	{
		min = i;
		tmin = va[i].d;
	}
	if ((r < heap_size) && (va[r].d < va[min].d))
	{
		min = r;
		tmin = va[r].d;
	}
	if (!(min == i))
	{
		temp.d = va[min].d;
		temp.p = va[min].p;
		temp.key = va[min].key;

		va[min].d = va[i].d;
		va[min].p = va[i].p;
		va[min].key = va[i].key;

		va[i].d = temp.d;
		va[i].p = temp.p;
		va[i].key = temp.key;

		min_heapify(va, min, heap_size);
	}
	return 1;
}

int heap_extract_min(struct vassist *va, int heap_size)
{
	int min;
	if (heap_size < 1)
		return -1;
	min = va[0].key;
	va[0].p = va[heap_size - 1].p;
	va[0].d = va[heap_size - 1].d;
	va[0].key = va[heap_size - 1].key;
	heap_size = heap_size - 1;
	min_heapify(va, 0, heap_size);
	return min;
}

int inheap(struct vassist *va, int heap_size, int j)
{
	int i;
	for (i = 0; i < heap_size; i++)
		if (va[i].key == j)
			return i;
	return -1;
}

int heap_decrease(struct vassist *va, int i, int key_new)
{
	struct vassist temp;
	if (key_new > va[i].d)
		return 0;
	va[i].d = key_new;
	while ((i > 0) && (va[PARENT(i)].d > va[i].d))
	{
		temp.d = va[i].d;
		temp.p = va[i].p;
		temp.key = va[i].key;
		va[i].d = va[PARENT(i)].d;
		va[i].p = va[PARENT(i)].p;
		va[i].key = va[PARENT(i)].key;
		va[PARENT(i)].d = temp.d;
		va[PARENT(i)].p = temp.p;
		va[PARENT(i)].key = temp.key;
		i = PARENT(i);
	}
	return 1;
}

int dijkstra(struct vertex *graph, int len, int s, int **delta)
{
	int i, j, heap_size;
	struct vtable *q;
	struct vassist *va;
	int *p;
	p = (int *)malloc(len * sizeof(int));
	for (i = 0; i < len; i++)
		p[i] = U;
	p[s] = 0;
	heap_size = len;
	va = initialize_ss(len, s);
	build_min_heap(va, heap_size);
	while (heap_size > 0)
	{
		i = heap_extract_min(va, heap_size);
		//printf("node:%d\n", i);
		heap_size--;
		for (j = 0; j < heap_size; j++)
			//printf("key:%d,d:%d, in array:%d\n", va[j].key, va[j].d, p[va[j].key]);
		q = graph[i].adj;
		while (q != NULL)
		{
			j = inheap(va, heap_size, q->key);
			if (j >= 0)
				if (va[j].d > p[i] + q->w)
					heap_decrease(va, j, p[i] + q->w);
			relaxd(p, i, q->key, q->w);
			//printf("relax %d to %d ,w is %d\n", i, q->key, q->w);
			q = q->next;
		}
		for (j = 0; j < heap_size; j++)
			//printf("key:%d,d:%d, in array:%d\n", va[j].key, va[j].d, p[va[j].key]);
			;
	}
	for (i = 0; i < len; i++)
		//printf("from %d to %d, distance is %d\n", s, i, p[i]);

	free(va);

	for (i = 0; i < len; i++)
	{
		delta[s][i] = p[i];
	}
	free(p);
}

int **johnson(struct vertex *g, int n)
{
	int i, j;
	int *h, **delta, **d;
	struct vertex *gn;
	struct vtable *p;
	gn = (struct vertex *)malloc(n * sizeof(struct vertex));
	h = (int *)malloc(n * sizeof(int));
	delta = (int **)malloc(n * sizeof(int *));
	d = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
	{
		delta[i] = (int *)malloc(n * sizeof(int));
		d[i] = (int *)malloc(n * sizeof(int));
	}
	for (i = 0; i < n; i++)
		gn[i] = g[i];
	for (i = 1; i < n; i++)
		insert(gn, n, 0, i, 0);
	if (!bellman_ford(gn, h, n, 0))
	{
		printf("the input graph contains a negative-weight cycle.\n");
		return NULL;
	}
	for (i = 0; i < n; i++)
	{
		p = gn[i].adj;
		while (p != NULL)
		{
			p->w = p->w + h[i] - h[p->key];
			p = p->next;
		}
	}
	for (i = 0; i < n; i++)
		walk(gn, n, i);

	printf("before dijkstra\n");
	for (i = 1; i < n; i++)
	{
		dijkstra(gn, n, i, delta);
		for (j = 1; j < n; j++)
			d[i][j] = delta[i][j] + h[j] - h[i];
	}
	for (i = 1; i < n; i++)
	{
		for (j = 1; j < n; j++)
			printf("%d\t", d[i][j]);
		printf("\n");
	}
	return d;
}

int test(int vn, int en)
{
	int i, j;
	int **d;
	struct vertex vt[vn + 1];
	for (i = 0; i < vn + 1; i++)
	{
		vt[i].adj = NULL;
		vt[i].key = i;
	}
	int sum = 0;
	srand(time(NULL));
	for (i = 1; i < vn + 1; i++)
	{
		sum = 0;
		while (sum < en)
		{
			if (insert(vt, vn + 1, i, (rand() % vn) + 1, (rand() % 50) + 1))
				sum++;
		}
	}
	d = johnson(vt, vn + 1);

	return 1;
}

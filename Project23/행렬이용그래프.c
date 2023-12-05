#include <stdio.h>
#define Max_size 100

int visited[Max_size];

typedef struct {
	int n;
	int array[Max_size][Max_size];
}GraphType;

typedef struct {
	int queue[Max_size];
	int front, rear;
}QueueType;

void init_queue(QueueType* q)
{
	q->rear = q->front = 0;
}

void enqueue(QueueType* q, int data)
{
	q->queue[++q->rear] = data;
}

int dequeue(QueueType* q)
{
	int data = q->queue[++q->front];
	return data;
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

void init_graph(GraphType *g)
{
	g->n = 0;

	for (int i = 0; i < Max_size; i++)
	{
		for (int t = 0; t < Max_size; t++)
		{
			g->array[i][t] = 0;
		}
	}
}

int insert_vertex(GraphType* g)
{
	++g->n;
	if (g->n > Max_size) return 0;
}

void insert_edge(GraphType* g, int start, int end)
{
	if (start > g->n || end > g->n) printf("error");

	g->array[start][end] = 1;
	g->array[end][start] = 1;
}

void print_array(GraphType *g)
{
	for (int i = 0; i < g->n; i++)
	{
		for (int t = 0; t < g->n; t++)
		{
			printf(" %d ", g->array[i][t]);
		}
		printf("\n");
	}
}


void dfs_mat(GraphType* g, int v)
{
	visited[v] = 1;
	printf("정점 %d -> ", v);

	for (int i = 0; i < g->n; i++)
	{
		if (g->array[v][i] && !visited[i])
			dfs_mat(g, i);
	}
}

void bfs_mat(GraphType* g, int v)
{
	QueueType q;
	init_queue(&q);

	visited[v] = 1;
	printf("정점 %d -> ", v);
	enqueue(&q, v);

	while (!is_empty(&q))
	{
		int w = dequeue(&q);
		for (int i = 0; i < g->n; i++)
		{
			if (g->array[w][i] && !visited[i])
			{
				visited[i] = 1;
				printf("정점 %d -> ", i);
				enqueue(&q, i);
			}
		}
	}
}

int main(void)
{
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	for (int i = 0; i < Max_size; i++) visited[i] = 0;
	init_graph(g);

	for (int i = 0; i < 4; i++) insert_vertex(g);

	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);

	print_array(g);
	dfs_mat(g, 2);
	printf("\n");

	for (int i = 0; i < Max_size; i++) visited[i] = 0;
	bfs_mat(g, 0);
	printf("\n");

	free(g);
}
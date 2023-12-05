#include <stdio.h>
#define Max_size 100
int visited[Max_size];

typedef struct GraphNode{
	int data;
	struct GraphNode* link;
}GraphNode;

typedef struct {
	GraphNode* array[Max_size];
	int n;
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

void init_graph(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < Max_size; i++) g->array[i] = NULL;
}

void insert_vertex(GraphType* g)
{
	if (g->n + 1 > Max_size) exit(1);
	g->n++;
}

void insert_edge(GraphType* g, int start, int end)
{
	if (start > g->n || end > g->n) exit(1);

	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	node->data = end;
	node->link = g->array[start];
	g->array[start] = node;
}

void print_array(GraphType* g)
{
	for (int i = 0; i < g->n; i++)
	{
		GraphNode* n = g->array[i];
		for (; n != NULL; n = n->link)
		{
			printf(" %d ", n->data);
		}
		printf("\n");
	}
}

void dfs_list(GraphType* g, int v)
{
	visited[v] = 1;
	printf("정점 %d -> ", v);

	GraphNode* n = g->array[v];
	for (; n != NULL; n = n->link)
	{
		if (!visited[n->data]) dfs_list(g, n->data);
	}
}

void bfs_list(GraphType* g, int v)
{
	QueueType q;
	init_queue(&q);

	visited[v] = 1;
	printf("정점 %d -> ", v);
	enqueue(&q, v);

	while (!is_empty(&q))
	{
		int n = dequeue(&q);
		for (GraphNode* w = g->array[n]; w != NULL; w = w->link)
		{
			if (!visited[w->data])
			{
				visited[w->data] = 1;
				printf("정점 %d -> ", w->data);
				enqueue(&q, w->data);
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

	insert_edge(g, 0, 3); insert_edge(g, 1, 0);
	insert_edge(g, 0, 2); insert_edge(g, 2, 0);
	insert_edge(g, 0, 1); insert_edge(g, 3, 0);
	insert_edge(g, 1, 2); insert_edge(g, 2, 1);
	insert_edge(g, 2, 3); insert_edge(g, 3, 2);

	print_array(g);
	dfs_list(g, 3);
	printf("\n");

	for (int i = 0; i < Max_size; i++) visited[i] = 0;
	bfs_list(g, 3);
	printf("\n");

	free(g);
}

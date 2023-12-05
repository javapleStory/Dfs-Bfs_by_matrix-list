#include <stdio.h>
#define Max_size 100
int visited[Max_size];

typedef struct GraphNode {
	int data;
	struct GraphNode* link;
}GraphNode;

typedef struct {
	int n;
	int array[Max_size][Max_size];
}MatrixGraphType;

typedef struct {
	GraphNode* array[Max_size];
	int n;
}ListGraphType;

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

void init_list(ListGraphType* g)
{
	g->n = 0;
	for (int i = 0; i < Max_size; i++) g->array[i] = NULL;
}

void List_insert_vertex(ListGraphType* g)
{
	if (g->n + 1 > Max_size) exit(1);
	g->n++;
}

void List_insert_edge(ListGraphType* g, int start, int end)
{
	if (start > g->n || end > g->n) exit(1);

	GraphNode* node1 = (GraphNode*)malloc(sizeof(GraphNode));
	GraphNode* node2 = (GraphNode*)malloc(sizeof(GraphNode));
	
	node1->data = end;
	node1->link = g->array[start];
	g->array[start] = node1;
	
	node2->data = start;
	node2->link = g->array[end];
	g->array[end] = node2;
}

void print_list(ListGraphType* g)
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

void dfs_list(ListGraphType* g, int v)
{
	visited[v] = 1;
	printf("정점 %d -> ", v);

	GraphNode* n = g->array[v];
	for (; n != NULL; n = n->link)
	{
		if (!visited[n->data]) dfs_list(g, n->data);
	}
}

void bfs_list(ListGraphType* g, int v)
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

void free_list(ListGraphType* g)
{
	printf("< 전체 그래프 노드 삭제 >\n");
	for (int i = 0; i < g->n; i++)
	{
		GraphNode* n = g->array[i];
		printf("list %d : ", i);
		while (n != NULL)
		{
			GraphNode* temp = n;
			printf("%d -> ", n->data);
			n = n->link;
			free(temp);
		}
		g->array[i] = NULL;
		printf("\n");
	}
}



void init_matrix(MatrixGraphType* g)
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

int Matrix_insert_vertex(MatrixGraphType* g)
{
	++g->n;
	if (g->n > Max_size) return 0;
}

void Matrix_insert_edge(MatrixGraphType* g, int start, int end)
{
	if (start > g->n || end > g->n) printf("error");

	g->array[start][end] = 1;
	g->array[end][start] = 1;
}

void print_matrix(MatrixGraphType* g)
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


void dfs_mat(MatrixGraphType* g, int v)
{
	visited[v] = 1;
	printf("정점 %d -> ", v);

	for (int i = 0; i < g->n; i++)
	{
		if (g->array[v][i] && !visited[i])
			dfs_mat(g, i);
	}
}

void bfs_mat(MatrixGraphType* g, int v)
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
	MatrixGraphType* mg = (MatrixGraphType*)malloc(sizeof(MatrixGraphType));
	init_matrix(mg);
	for (int i = 0; i < 8; i++) Matrix_insert_vertex(mg);

	Matrix_insert_edge(mg, 0, 1); Matrix_insert_edge(mg, 1, 2);
	Matrix_insert_edge(mg, 1, 5); Matrix_insert_edge(mg, 2, 3);
	Matrix_insert_edge(mg, 2, 5); Matrix_insert_edge(mg, 3, 4);
	Matrix_insert_edge(mg, 4, 5); Matrix_insert_edge(mg, 4, 6);
	Matrix_insert_edge(mg, 4, 7); Matrix_insert_edge(mg, 5, 6);

	ListGraphType* lg = (ListGraphType*)malloc(sizeof(ListGraphType));
	init_list(lg);
	for (int i = 0; i < 8; i++) List_insert_vertex(lg);

	List_insert_edge(lg, 0, 1); List_insert_edge(lg, 1, 2);
	List_insert_edge(lg, 1, 5); List_insert_edge(lg, 2, 3);
	List_insert_edge(lg, 2, 5); List_insert_edge(lg, 3, 4);
	List_insert_edge(lg, 4, 5); List_insert_edge(lg, 4, 6);
	List_insert_edge(lg, 4, 7); List_insert_edge(lg, 5, 6);
	
	for (int i = 0; i < Max_size; i++) visited[i] = 0;
	printf("1) 깊이 우선 탐색(dfs_mat) \n");
	dfs_mat(mg, 4);
	printf("\n\n");

	for (int i = 0; i < Max_size; i++) visited[i] = 0;
	printf("2) 깊이 우선 탐색(dfs_list) \n");
	dfs_list(lg, 4);
	printf("\n\n");

	for (int i = 0; i < Max_size; i++) visited[i] = 0;
	printf("3) 너비 우선 탐색(bfs_mat) \n");
	bfs_mat(mg, 4);
	printf("\n\n");

	for (int i = 0; i < Max_size; i++) visited[i] = 0;
	printf("4) 너비 우선 탐색(bfs_list) \n");
	bfs_list(lg, 4);
	printf("\n\n");
	
	free_list(lg);
	
	free(lg);
	free(mg);
}

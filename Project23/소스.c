#include <stdio.h>
#define Max_size 200

typedef struct element {
	int key;
}element;

typedef struct {
	element heap[Max_size];
	int size;
}HeapType;

void init_Heap(HeapType * h)
{
	h->size = 0;
}

void insert_max_heap(HeapType* h, element data)
{
	int i = ++(h->size);
	while (i > 1 && data.key >= h->heap[i/2].key)
	{
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = data;
}

element delete_max_heap(HeapType* h)
{
	element data, temp;
	int parent, child;

	data = h ->heap[1];
	temp = h->heap[(h->size)--];

	parent = 1; child = 2;

	while (child <= h->size)
	{
		if (child < h->size && h->heap[child + 1].key > h->heap[child].key)
		{
			child = child + 1;
		}
		
		if (temp.key >= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child = 2 * child;
	}
	h->heap[parent] = temp;
	return data;
}

void HeapSort(element a[], int size)
{
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	init_Heap(h);

	for (int i = 0; i < size; i++)
	{
		insert_max_heap(h, a[i]);
	}
	for (int i = size - 1; i >= 0; i--)
	{
		a[i] = delete_max_heap(h);
	}
	for (int i = 0; i < size; i++)
	{
		printf("< %d > ", a[i].key);
	}
	printf("\n");
}

int main(void)
{
	element list[8] = { 23,56,11,9,56,99,27,34 };
	HeapSort(list, 8);

	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
	element e4, e5, e6;
	HeapType h;

	init_Heap(&h);
	insert_max_heap(&h, e1);
	insert_max_heap(&h, e2);
	insert_max_heap(&h, e3);
	
	e4 = delete_max_heap(&h);
	printf("< %d > ", e4.key);
	e5 = delete_max_heap(&h);
	printf("< %d > ", e5.key);
	e6 = delete_max_heap(&h);
	printf("< %d > ", e6.key);
	printf("\n");
}
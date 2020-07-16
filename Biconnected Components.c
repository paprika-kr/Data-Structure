#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 30
#define MIN2(x,y) ((x) < (y) ? (x) : (y))
short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
int num;
void init();
void bicon(int, int);
void add(int, int);
void delete(int*, int*);

typedef struct node *node_pointer;
typedef struct node {
	int vertex;
	node_pointer link;
}node;
node_pointer createNode(int);
node_pointer graph[MAX_VERTICES];

typedef struct Node {
	int u;
	int v;
	struct Node* next;
}Node;
Node* top;

int n;

void main()
{
	FILE* fp = fopen("input.txt", "r");
	node_pointer tail;
	int i, j, k, index, count = 0;
	int input[30];
	char c;
	fscanf(fp, "%d", &n);

	while (!feof(fp)) {
		for (i = 0; i < n; i++) {
			fscanf(fp, "%d", &index);
			for (j = 0;; j++) {
				node_pointer temp;
				fscanf_s(fp, "%d", &input[j]);
				temp = createNode(input[j]);
				if (j == 0) {
					graph[i] = temp;
					tail = temp;
				}
				else {
					for (k = 0; k < j; k++) {
						tail->link = temp;
					}
					tail = temp;
				}
				c = fgetc(fp);
				if (c == '\n') break;
				if (feof(fp)) break;
			}
			tail = NULL;
		}
	}

	init();
	bicon(3, -1);
}

node_pointer createNode(int n) {
	node_pointer newNode = (node_pointer)malloc(sizeof(node));
	newNode->vertex = n;
	newNode->link = NULL;
	return newNode;
}
void add(int a, int b) {
	Node* temp;
	temp = (Node*)malloc(sizeof(Node));
	temp->u = a;
	temp->v = b;
	temp->next = top;
	top = temp;
}
void delete(int* a, int* b) {
	Node* temp;
	temp = top;
	*a = temp->u;
	*b = temp->v;
	top = top->next;
	free(temp);
}
void init(void) {
	int i;
	for (i = 0; i < n; i++) {
		dfn[i] = low[i] = -1;
	}
	num = 0;
}

void bicon(int child, int parent) {
	node_pointer ptr;
	int w, x, y;
	dfn[child] = low[child] = num++;
	for (ptr = graph[child]; ptr; ptr = ptr->link) {
		w = ptr->vertex;
		if (parent != w && dfn[w] < dfn[child])
			add(child, w);
		if (dfn[w] < 0) {   
			bicon(w, child);
			low[child] = MIN2(low[child], low[w]);
			if (low[w] >= dfn[child]) {
				printf("New biconnected component: ");
				do {
					delete(&x, &y);
					printf("<%d, %d>", x, y);
				} while (!((x == child) && (y == w)));
				printf("\n");
			}
		}
		else if (w != parent) low[child] = MIN2(low[child], dfn[w]);
	}
}



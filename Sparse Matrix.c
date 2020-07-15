#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef enum { head, entry } tagfield;
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
} entry_node;

typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		struct entry_node entry;
	} u;
} matrix_node;

matrix_pointer hdnode[MAX_SIZE];
matrix_pointer mread(FILE*);
void mwrite(matrix_pointer);
void merase(matrix_pointer*);

void main() {

	matrix_pointer a, b;

	FILE *fa, *fb;

	fa = fopen("A.txt", "r");
	if (fa == NULL) {
		printf("A file open error!\n");
		return 0;
	}

	fb = fopen("B.txt", "r");
	if (fb == NULL) {
		printf("B file open error!\n");
		return 0;
	}

	a = mread(fa);
	b = mread(fb);
	mwrite(a);
	mwrite(b);
	merase(&a);
	merase(&b);
	mwrite(a);
	mwrite(b);

	fclose(fa);
	fclose(fb);
	
	return 0;
}

matrix_pointer mread(FILE *fp)
{
	int num_rows, num_cols, num_terms, num_heads, i;
	int row, col, value, current_row;
	matrix_pointer temp, last, node;

	fscanf(fp, "%d %d", &num_rows, &num_cols);
	num_heads = (num_rows > num_cols) ? num_rows : num_cols;
	node = (matrix_pointer)malloc(sizeof(matrix_node));
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;

	if (!num_heads)
		node->right = node;

	else {
		for (i = 0; i < num_heads; i++) {
			temp = (matrix_pointer)malloc(sizeof(matrix_node));
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		current_row = 0;
		last = hdnode[0];
		for (row = 0; row < num_rows; row++) {
			for (col = 0; col < num_cols; col++) {
				fscanf(fp, "%d", &value);
				if (value) {
					if (row > current_row)
					{
						last->right = hdnode[current_row];
						current_row = row;
						last = hdnode[row];
					}
					temp = (matrix_pointer)malloc(sizeof(matrix_node));
					temp->tag = entry;
					temp->u.entry.row = row;
					temp->u.entry.col = col;
					temp->u.entry.value = value;
					last->right = temp;
					last = temp;
					hdnode[col]->u.next->down = temp;
					hdnode[col]->u.next = temp;
				}
			}
		}
		last->right = hdnode[current_row];
		for (i = 0; i < num_cols; i++)
			hdnode[i]->u.next->down = hdnode[i];
		for (i = 0; i < num_heads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[num_heads - 1]->u.next = node;
		node->right = hdnode[0];
	}
	return node;
}
void mwrite(matrix_pointer node)
{
	matrix_pointer tmp;
	int last;

	if (node != NULL)
	{
		matrix_pointer head = node->right;
		for (int i = 0; i < node->u.entry.row; i++) {
			last = 0;
			for (tmp = head->right; tmp != head; tmp = tmp->right) {
				for (int j = last; j < tmp->u.entry.col; j++)
					printf("0 ");
				printf("%d ", tmp->u.entry.value);
				last = tmp->u.entry.col + 1;
			}
			for (int j = last; j < node->u.entry.col; j++)
				printf("0");
			head = head->u.next;
			printf("\n");
		}
	}

	else
		printf("No matrices\n");

	printf("\n");
}
void merase(matrix_pointer* node)
{
	int i;
	matrix_pointer x, y, head = (*node)->right;

	for (i = 0; i < (*node)->u.entry.row; i++) {
		y = head->right;
		while (y != head) {
			x = y;
			y = y->right;
			free(x);
		}
		x = head;
		head = head->u.next;
		free(x);
	}

	y = head;
	while (y != *node) {
		x = y;
		y = y->u.next;
		free(x);
	}
	free(*node);
	*node = NULL;
}

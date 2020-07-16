#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 100
#define IS_FULL(ptr) (!(ptr))
#include <stdlib.h>
#include <stdio.h>
typedef struct treeNode* treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	treePtr rchild;
}treeNode;
void inorder(treePtr);
void preorder(treePtr);
void insert(treePtr*, int);
treePtr modifiedSearch(treePtr, int);
void main()
{
	int i, n, A[MAX_TERMS];
	treePtr tree = NULL;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(fp, "%d", &A[i]);
	}

	for (i = 0; i < n; i++)
		insert(&tree, A[i]);

	inorder(tree);
	printf("\n");
	preorder(tree);
	printf("\n");
}
treePtr modifiedSearch(treePtr tree, int key) {

	/* return a pointer to the node that contains key.
	If there is no such node, return NULL. */
	while (tree) {
		if (key == tree->data) return NULL;
		if (key < tree->data) {

			if (!tree->lchild) {
				return tree;
			}
			else tree = tree->lchild;
		}
		else {
			if (!tree->rchild) {
				return tree;
			}
			else tree = tree->rchild;
		}
	}
	return NULL;
}
void insert(treePtr*node, int num)
{
	/* If numis in the tree pointed at by node do nothing;
	otherwise add a new node with data = num*/
	treePtr ptr, temp = modifiedSearch(*node, num);
	if (temp || !(*node)) {
		/* num is not in the tree */
		ptr = (treePtr)malloc(sizeof(treeNode));
		if (IS_FULL(ptr)) {
			fprintf(stdout, "The memory is full");
			exit(1);
		}
		ptr->data = num;
		ptr->lchild = ptr->rchild = NULL;
		if (*node) /* insert as child of temp */
			if (num < temp->data)
				temp->lchild = ptr;
			else temp->rchild = ptr;
		else *node = ptr;
	}
}

void inorder(treePtr ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
}
void preorder(treePtr ptr) {

	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}
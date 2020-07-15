#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0
typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
}threadedTree;

void construct_tree(threadedPointer tree);
threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void insertRight(threadedPointer s, threadedPointer r);
void insert(threadedPointer s, char data);

int main()
{
	threadedPointer head;
	head = (threadedPointer)malloc(sizeof(threadedTree));
	head->leftThread = head->rightThread = false;
	head->leftChild = head->rightChild = head;
	construct_tree(head);
	insert(head->leftChild->rightChild, 'E');
	insert(head->leftChild->leftChild->rightChild, 'F');
	insert(head->leftChild->leftChild, 'G');
	tinorder(head);
	getchar();
	return 0;
}

void construct_tree(threadedPointer tree)
{
	threadedPointer temp, temp_root;

	temp_root = tree;
	/* insert node 'A' to the left of the head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = true;
	temp->leftChild = temp->rightChild = temp;
	temp->data = 'A';

	temp_root->leftChild = temp;
	temp_root->leftThread = false;

	temp_root = tree->leftChild;
	/* insert node 'B' to the left of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->rightThread = temp->leftThread = true;
	temp->leftChild = tree;
	temp->rightChild = temp;
	temp->data = 'B';

	temp_root->leftChild = temp;
	temp_root->leftThread = false;

	/* insert node 'C' to the right of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = true;
	temp->leftChild = temp_root;
	temp->rightChild = tree;
	temp->data = 'C';

	temp_root->rightChild = temp;
	temp_root->rightThread = false;

	temp_root = temp_root->leftChild;
	/* insert node 'D' to the right of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = true;
	temp->leftChild = temp_root;
	temp->rightChild = tree->leftChild;
	temp->data = 'D';

	temp_root->rightChild = temp;
	temp_root->rightThread = false;
}

threadedPointer insucc(threadedPointer tree)
{
	threadedPointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread)
		while (!temp->leftThread)
			temp = temp->leftChild;
	return temp;
}

void tinorder(threadedPointer tree)
{
	threadedPointer temp = tree;
	for (; ;) {
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%3c", temp->data);
	}
}

void insert(threadedPointer s, char data)
{
	threadedPointer temp;
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->data = data;
	insertRight(s, temp);
}

void insertRight(threadedPointer s, threadedPointer r)
{
	threadedPointer temp;
	r->rightChild = s->rightChild;
	r->rightThread = s->rightThread;
	r->leftChild = s;
	r->leftThread = true;
	s->rightChild = r;
	s->rightThread = false;
	if (!r->rightThread) {
		temp = insucc(r);
		temp->leftChild = r;
	}
}
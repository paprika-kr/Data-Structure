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
treePtr modifiedSearch2(treePtr ptr, int key);
treePtr search_sublmax(treePtr ptr);
treePtr search_subrmin(treePtr ptr);
treePtr search_parent(treePtr root, int key, int *dir);
void delete(treePtr*, int);
void rangeSearch(treePtr, int, int);


void main()
{
	int i, j, n, m, A[MAX_TERMS], D[MAX_TERMS], k1, k2;
	treePtr tree = NULL;

	// �Է����� ������ ����� ������ n��, ���� ���� ������ m��, �����Ͽ�����
	//�������� A��, ������ �������� D��, ���� ����� ������ k1, k2 ����
		// ������� binary search tree�� ����

	FILE* fp = fopen("input2.txt", "r");
	fscanf(fp, "%d", &n);
	for (i = 0; i < n; i++) 
		fscanf(fp, "%d", &A[i]);

	fscanf(fp, "%d", &m);
	for (i = 0; i < m; i++)
		fscanf(fp, "%d", &D[i]);

	fscanf(fp, "%d", &k1);
	fscanf(fp, "%d", &k2);

	for (i = 0; i < n; i++)
		insert(&tree, A[i]);

	inorder(tree);
	printf("\n");
	preorder(tree);
	printf("\n");

	// ������ binary search tree�� inorder�� preorder�� ����Ͽ� �ùٸ��� Ʈ����
//�����Ǿ����� Ȯ��
	// delete�� �������� ������ binary search tree���� ������ ��, �ùٸ��� ������
//	������ Ȯ���ϱ� ���� inorder�� preorder�� ���

	for (i = 0; i < m; i++)
		delete(&tree, D[i]);

	inorder(tree);
	printf("\n");
	preorder(tree);
	printf("\n");

	rangeSearch(tree, k1, k2);
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

void insert(treePtr* node, int num)
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

treePtr modifiedSearch2(treePtr ptr, int key)
{
	if (!ptr) return NULL;
	if (key == ptr->data) return ptr;
	if (key < ptr->data)
		return modifiedSearch2(ptr->lchild, key);
	return modifiedSearch2(ptr->rchild, key);
}

void node_count(treePtr ptr, int* cnt) {

	if (ptr) {
		node_count(ptr->lchild, cnt);
		(*cnt)++;
		node_count(ptr->rchild, cnt);
	}
}

treePtr search_sublmax(treePtr ptr)
{
	treePtr temp;

	if (!ptr) return NULL;
	ptr = ptr->lchild;
	while (ptr->rchild)
		ptr = ptr->rchild;

	return ptr;
}

treePtr search_subrmin(treePtr ptr)
{
	treePtr temp;

	if (!ptr) return NULL;
	ptr = ptr->rchild;
	while (ptr->lchild)
		ptr = ptr->lchild;

	return ptr;
}

treePtr search_parent(treePtr root, int key, int *dir)
{
	treePtr temp;
	*dir = 0;

	if (key == root->data) return NULL;
	while (root) {
		if (key < root->data) {
			if (key == root->lchild->data) {
				*dir = -1;
				return root;
			}
			root = root->lchild;
		}
		else {
			if (key == root->rchild->data) {
				*dir = 1;
				return root;
			}
			root = root->rchild;
		}
	}
	return NULL;
}

void delete(treePtr* node, int num) {
	treePtr root, cnode, pnode = NULL, ptr, tlnode, ptlnode, temp;
	int dir, lcount=0, rcount=0;														// 1: right , -1 : left
	
	root = *node;
	cnode = modifiedSearch2(root, num);

	if (cnode) {
		if (cnode->lchild == NULL && cnode->rchild == NULL) { // case 1 : leaf node 
			pnode = search_parent(root, cnode->data, &dir);
			if (dir == -1)
				pnode->lchild = NULL;
			else if (dir == 1)
				pnode->rchild = NULL;

			free(cnode);
			if (pnode == NULL) *node = cnode;
		}

		else if (cnode->lchild == NULL || cnode->rchild == NULL) { // case 2 : non-leaf node with single child
			pnode = search_parent(root, cnode->data, &dir);

			if (pnode == NULL) {									// cnode�� root node
				if (cnode->lchild != NULL)
					*node = cnode->lchild;
				else
					*node = cnode->rchild;
				free(cnode);
			}

			else {
				if (dir == -1) { 
					if (cnode->lchild != NULL)				//�θ� ����� ���� �ڽ� = �ڽ� ����� ���� �ڽ�
						pnode->lchild = cnode->lchild;
					else
						pnode->lchild = cnode->rchild;		//�θ� ����� ���� �ڽ� = �ڽ� ����� ������ �ڽ�
				}
				else {
					if (cnode->lchild != NULL)				//�θ� ����� ������ �ڽ� = �ڽ� ����� ���� �ڽ�
						pnode->rchild = cnode->lchild;
					else
						pnode->rchild = cnode->rchild;		//�θ� ����� ������ �ڽ� = �ڽ� ����� ������ �ڽ�
				}
				free(cnode);
			}
		}

		else {												// case 3 : non-leaf node with double child
			node_count(cnode->lchild, &lcount);
			node_count(cnode->rchild, &rcount);

			if (lcount >= rcount) {
				tlnode = search_sublmax(cnode);
				ptlnode = search_parent(root, tlnode->data, &dir);
				pnode = search_parent(root, cnode->data, &dir);

				if (tlnode != cnode->lchild) {
					ptlnode->rchild = tlnode->lchild;
					tlnode->lchild = cnode->lchild;
				}
				tlnode->rchild = cnode->rchild;

				if (pnode == NULL)
					*node = tlnode;
				else {
					if (dir == -1)
						pnode->lchild = tlnode;
					else
						pnode->rchild = tlnode;
				}
				free(cnode);
			}

			else {
				tlnode = search_subrmin(cnode);
				ptlnode = search_parent(root, tlnode->data, &dir);
				pnode = search_parent(root, cnode->data, &dir);

				if (tlnode != cnode->rchild) {
					ptlnode->lchild = tlnode->lchild;
					tlnode->lchild = cnode->lchild;
				}
				tlnode->rchild = cnode->rchild;

				if (pnode == NULL)
					*node = tlnode;
				else {
					if (dir == -1)
						pnode->lchild = tlnode;
					else
						pnode->rchild = tlnode;
				}
				free(cnode);
			}
		}
	}

	else 
		printf("%d �� Ʈ���� �������� �ʽ��ϴ�.\n", num);
}

void rangeSearch(treePtr ptr, int k1, int k2) {

	if (ptr) {
		rangeSearch(ptr->lchild, k1, k2);
		if ((ptr->data >= k1) && (ptr->data <= k2))
			printf("%d ", ptr->data);
		rangeSearch(ptr->rchild, k1, k2);
	}
}


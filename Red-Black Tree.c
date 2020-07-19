#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum COLOR {RED,BLACK};
typedef enum COLOR COLOR;
typedef int 		DATA;

struct rbtree
{
	DATA 			key;
	COLOR			color;
	struct rbtree 	*left;
	struct rbtree 	*right;
	struct rbtree	*p;
};
typedef struct rbtree 	ELEM_RB;
typedef ELEM_RB 		*RBTREE;

RBTREE nil;

RBTREE left_rotate(RBTREE tree, RBTREE base)
{
	RBTREE y = base -> right;
	base -> right = y -> left;

	if (y -> left != nil)
		y -> left -> p = base;

	y -> p = base -> p;

	if (base -> p == nil)
		tree = y;
	else if (base == base -> p -> left)
		base -> p -> left = y;
	else
		base -> p -> right = y;

	y -> left = base;
	base -> p = y;

	return tree;
}

RBTREE right_rotate(RBTREE tree, RBTREE base)
{
	RBTREE y = base -> left;
	base -> left = y -> right;

	if (y -> right != nil)
		y -> right -> p = base;

	y ->p = base -> p;

	if (base -> p == nil)
		tree = y;
	else if (base == base -> p -> right)
		base -> p -> right = y;
	else
		base -> p -> left = y;

	y -> right = base;
	base -> p = y;

	return tree;
}


RBTREE RB_insert_fixup(RBTREE tree, RBTREE input)
{
	RBTREE y;
	
	while ( input -> p -> color == RED)
	{
		if( (input -> p) == (input -> p -> p -> left))
		{
			y = input -> p -> p -> right;
			if (y -> color == RED)
			{
				input -> p -> color = BLACK;
				y -> color = BLACK;
				input -> p -> p -> color = RED;
				input = input -> p -> p;
			}
			else 
			{
				if ( input == input -> p -> right)
				{
					input = input -> p;
					tree = left_rotate(tree,input);
				}
				input -> p -> color = BLACK;
				input -> p -> p -> color = RED;
				tree = right_rotate(tree,input->p->p);
			}
		}
		else
		{
			y = input -> p -> p -> left;
			if (y -> color == RED)
			{
				input -> p -> color = BLACK;
				y -> color = BLACK;
				input -> p -> p -> color = RED;
				input = input -> p -> p;
			}
			else 
			{
				if ( input == input -> p -> left)
				{
					input = input -> p;
					tree = right_rotate(tree,input);
				}
				input -> p -> color = BLACK;
				input -> p -> p -> color = RED;
				tree = left_rotate(tree,input->p->p);
			}
		}
	}
	tree -> color = BLACK;
	return tree;
}

RBTREE RB_insert(RBTREE tree, RBTREE input)
{
	RBTREE y = nil;
	RBTREE x = tree;

	while (x != nil)
	{
		y = x;
		if ((input -> key) < (x -> key))
			x = x -> left;
		else
			x = x -> right;
	}
	input -> p = y;

	if (y == nil)
		tree = input;
	else if ((input -> key) < (y -> key))
		y -> left = input;
	else
		y -> right = input;
	
	input -> left = nil;
	input -> right = nil;
	input -> color = RED;

	return RB_insert_fixup(tree,input);
}

RBTREE make_node(DATA input)
{
	RBTREE tmp;
	tmp =  (RBTREE)malloc(sizeof(ELEM_RB));
	tmp ->key = input;
	tmp ->left = nil;
	tmp -> right = nil;
	tmp ->p = nil;
	return tmp;
}
RBTREE make_nil()
{
	RBTREE tmp;
	tmp = (RBTREE)malloc(sizeof(ELEM_RB));
	tmp -> key = 0;
	tmp ->left = NULL;
	tmp -> right = NULL;
	tmp ->p = NULL;
	tmp ->color = BLACK;
	return tmp;
}

RBTREE tree_minimum(RBTREE root)
{
	RBTREE tmp = root;

	while (tmp -> left != nil)
	{
		tmp = tmp -> left;
	}
	return tmp;
}

RBTREE tree_successor(RBTREE root)
{
	RBTREE tmp;
	if (root -> right != nil)
		return tree_minimum(root -> right);
	
	tmp = root->p;
	
	while((tmp != nil) && (root == tmp->right))
	{
		root = tmp;
		tmp = tmp -> p;
	}
	return tmp;
}

RBTREE RB_delete_fixup(RBTREE tree, RBTREE put)
{
	RBTREE w;
	while((put != tree) &&(put -> color == BLACK))
	{
		if(put == put -> p -> left)
		{
			w = put -> p -> right;
			if (w -> color == RED)
			{
				w -> color = BLACK;
				put -> p -> color = RED;
				tree = left_rotate(tree,put->p);
				w = put -> p -> right;
			}
			if ((w->left->color == BLACK)&&(w->right->color == BLACK))
			{
				w -> color = RED;
				put = put -> p;
			}
			else 
			{
				if(w -> right -> color == BLACK)
				{
					w->left->color = BLACK;
					w-> color = RED;
					tree = right_rotate(tree,w);
					w = put->p->right;
				}
				w -> color = put -> p -> color;
				put -> p -> color = BLACK;
				w -> right -> color = BLACK;
				tree = left_rotate(tree,put->p);
				put = tree;
			}
		}
		else
		{
			w = put -> p -> left;
			if (w -> color == RED)
			{
				w -> color = BLACK;
				put -> p -> color = RED;
				tree = right_rotate(tree,put->p);
				w = put -> p -> left;
			}
			if ((w->right->color == BLACK)&&(w->left->color == BLACK))
			{
				w -> color = RED;
				put = put -> p;
			}
			else 
			{
				if(w -> left -> color == BLACK)
				{
					w->right->color = BLACK;
					w-> color = RED;
					tree = left_rotate(tree,w);
					w = put->p->left;
				}
				w -> color = put -> p -> color;
				put -> p -> color = BLACK;
				w -> left -> color = BLACK;
				tree = right_rotate(tree,put->p);
				put = tree;
			}
		}
	}
	put -> color = BLACK;
	return tree;
}

RBTREE RB_delete(RBTREE tree, RBTREE put)
{
	RBTREE y;
	RBTREE x;
	if ((put->left == nil) || (put->right == nil))
		y = put;
	else
		y = tree_successor(put);

	if (y->left != nil)
		x = y->left;
	else
		x = y->right;

	x->p = y->p;

	if (y->p == nil)
		tree = x;
	else
	{
		if (y == y->p->left)
			y->p->left = x;
		else
			y->p->right = x;
	}
	if (y != put)
		put->key = y->key;
	if (y->color == BLACK)
		tree = RB_delete_fixup(tree, x);

	return tree;
}

RBTREE tree_search(RBTREE tree, DATA d)
{
	RBTREE root;
	root = tree;
	
	while ((root != nil) && (d != root -> key))
	{
		if (d < root -> key)
			root = root -> left;
		else
			root = root -> right;
	}
	return root;
}

void delete_all(RBTREE tree)
{
	if(tree != nil)
	{
		delete_all(tree->left);
		delete_all(tree->right);
		free(tree);
	}
}

int main(int argc, char* argv[])
{
	clock_t start_time = clock();

	RBTREE tree;
	RBTREE val;
	char op;
	int n;
	char nul;

	FILE* fpi;
	FILE* fpo;
	fpi = fopen(argv[1], "r");
	fpo = fopen("db_result.txt", "w");

	nil = make_nil();
	tree = nil;

	while (!feof(fpi)) {
	fscanf(fpi,"%c %d\n",&op, &n);	

		if (op == 'i') {
			val = make_node(n); 
			tree = RB_insert(tree, val);

		}
		else if (op == 'd') {
			val = tree_search(tree, n);

			if (val != nil)
			{
				tree = RB_delete(tree, val);
			}
			else
				fprintf(fpo, "ignore\n");
		}
		else if (op == 's') {
			val = tree_search(tree, n);

			if (val != nil)
			{
				fprintf(fpo,"true\n");
			}
			else
				fprintf(fpo,"false\n");
		}
		else
			fprintf(fpo,"invalid operation.\n");
	}

	fclose(fpo);
	fclose(fpi);
	
	delete_all(tree);
	free(nil);

	printf("%lf\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
	return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EXPR_SIZE 100
typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand}
	precedence;
precedence *stack;
//int top = -1;
char expr[MAX_EXPR_SIZE];
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0}; // 교과서 3.6절 pp. 136 참고
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

typedef struct node* nodepointer;
typedef struct node {
	precedence token;
	nodepointer link;
}node;

nodepointer top;

precedence pop() {
	nodepointer temp = (nodepointer)malloc(sizeof(node));
	precedence element;
	temp = top;
	element = temp->token;
	top = temp->link;
	free(temp);
	return element;
}


void init(nodepointer a){
	a = (nodepointer)malloc(sizeof(node));
	a->link = NULL;
}

void push(precedence item) {
	nodepointer temp = (nodepointer)malloc(sizeof(node));
	temp->token = item;
	temp->link = top;
	top = temp;
}

precedence getToken(char* symbol, int* n) {
	/* get the next token, symbol is the character representation, which is returned, the
	token is represented by its enumerated value, which is returned in the function name */
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand; /* no error checking, default is operand */
	}
}

void printToken(precedence p) {
	char a;
	switch (p) {
	case lparen: a = '(';
		break;
	case rparen: a = ')';
		break;
	case plus: a = '+';
		break;
	case minus: a = '-';
		break;
	case times: a = '*';
		break;
	case divide: a = '/';
		break;
	case mod: a = '%';
		break;
	default: a = NULL;
	}
	printf(" %c", a);
}

void postfix() {
	char symbol;
	int n = 0;
	int count = 0;
	precedence token;
	nodepointer temp = (nodepointer)malloc(sizeof(node));
	temp->token = eos;
	temp->link = top;
	top = temp;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) 
			printf("%c", symbol);
		else if (token == rparen) {
			/* unstack tokens until left paranthesis */
			while (top->token != lparen) 
				printToken(pop());
			pop(); /* discard the left paranthesis */
		}
		else {
			/* remove and print symbols whose isp is greater
			than or equal to the current token’s icp */
			while (isp[top->token] >= icp[token]) 
				printToken(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos) 
		printToken(token);
	printf("\n");
}


void rExpr(FILE* fp, char* expr) {
	int count = 0;
	while (!(feof(fp))) 
		fscanf(fp, "%c", &expr[count++]);
}

void main()
{
	FILE* fp = fopen("expr.txt", "r");

	rExpr(fp, expr);
//	init(top);
	postfix();

	return 0;
}



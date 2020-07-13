#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element *stack;

typedef struct {
short int vert;
short int horiz;
} offsets;
offsets move[8];


int EXIT_ROW, EXIT_COL;
int top = -1;
int** maze;
int** mark;

void move_set() {

	move[0].vert = -1;
	move[0].horiz = 0;
	move[1].vert = -1;
	move[1].horiz = 1;
	move[2].vert = 0;
	move[2].horiz = 1;
	move[3].vert = 1;
	move[3].horiz = 1;
	move[4].vert = 1;
	move[4].horiz = 0;
	move[5].vert = 1;
	move[5].horiz = -1;
	move[6].vert = 0;
	move[6].horiz = -1;
	move[7].vert = -1;
	move[7].horiz = -1;
}

void push(element item)
{
	if (top >= (EXIT_COL*EXIT_ROW) / 2 - 1)
	printf("stack FULL !\n");
	stack[++top] = item;
}

element pop()
{

	if (top == -1)
		printf("stack EMPTY !\n");
	return stack[top--];
}

void path(void)
{
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (top > -1 && !found) {
		position = pop();
		row = position.row; col = position.col, dir = position.dir;
		while (dir < 8 && !found) {

			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
				found = TRUE;

			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;
		}
	}
	if (found) {
		printf("The path is : \n");
		printf(" row col \n");
		for (i = 0; i <= top; i++)
			printf(" (%d, %d)\n", stack[i].row, stack[i].col);
		printf(" (%d, %d)\n", row, col);
		printf(" (%d, %d)\n", EXIT_ROW, EXIT_COL);
	}
	else printf("The maze does not have a path \n");
}

int main() {
	int i, j;
	int tmp;

	FILE* fp;
	fp = fopen("maze.txt", "r");
	fscanf(fp, "%d %d", &EXIT_ROW, &EXIT_COL);

	stack = (element*)malloc(sizeof(element) * (EXIT_COL*EXIT_ROW) / 2);

	maze = (int**)malloc(sizeof(int*) * (EXIT_ROW + 2));
	for (i = 0; i < EXIT_ROW + 2; i++) {
		maze[i] = (int*)malloc(sizeof(int) * (EXIT_COL + 2));
	}

	mark = (int**)malloc(sizeof(int*) * (EXIT_ROW + 2));
	for (i = 0; i < EXIT_ROW + 2; i++) {
		mark[i] = (int*)malloc(sizeof(int) * (EXIT_COL + 2));
	}

	move_set();

	i = 1;
	j = 1;

	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp);
		maze[i][j] = tmp;
		mark[i][j] = 0;
		j++;
		if (j > EXIT_COL) {
			j = 1;
			i++;
		}
	}
	
	for (i = 0; i < EXIT_ROW+2; i++) {
		maze[i][0] = 1;
		maze[i][EXIT_COL + 1] = 1;
	}

	for (i = 0; i <= EXIT_COL+2; i++) {
		maze[0][i] = 1;
		maze[EXIT_ROW + 1][i] = 1;
	}

	path();

	

	for (i = 0; i < EXIT_ROW + 2; i++) {
		free(mark[i]);
	}
	free(mark);

	free(stack);

	fclose(fp);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
int backtracking(int n, int q_col[]) {
	int i;

	for (i = 1; i < n; i++) {
		if (q_col[i] == q_col[n] || abs(q_col[i] - q_col[n]) == abs(i - n)) 
			return 0;	
	}
	return 1;
}

int searching(int n, int i, int q_col[]) {
	int j = 0;
	int flag = 0;

	if (!backtracking(i, q_col))
		return;

	if (i == n) {
		for (j = 1; j <= n; j++)
			printf("%d ", q_col[j] - 1);
		flag = 1;
	}

	else {
		
		for (j = 1; j < n + 1; j++) {
			q_col[i + 1] = j;
			flag = searching(n, i + 1, q_col);
			if (flag)
				return;
		}
	}

	return flag;
}

int main() {

	int* q_col;

	int n, i, result;
	i = 0;
	result = 0;
	printf("Input N : ");
	scanf("%d", &n);

	q_col = (int*)malloc(sizeof(int) * n + 5);
	
	result = searching(n, i, q_col);

	if (!result)
		printf("No solution");
	free(q_col);
	return 0;
}
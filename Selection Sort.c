#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void s_sort(int list[], int n);
void swap(int *x, int *y);

int main() {
	int n;
	long rep = 0;
	double duration;
	int *ary;

	while (1) { // 여러번 반복하며 데이터 수집을 용이하게 하기 위해 무조건반복 설정
		printf("n ? "); 
		scanf("%d", &n);
		
		clock_t time_s = clock();

		ary = (int*)malloc(sizeof(int)*n); // 동적할당
		rep = 0; //반복 횟수 초기화

		do {
			rep++; 
			for (int i = 0; i < n; i++)
				ary[i] = n - i; // worst-case 설정을 위한 ary 배열의 초기화

			s_sort(ary, n); // 선택정렬
		} while (clock() - time_s < 1000); // 정해진 시간동안 같은 갯수의 원소의 선택 정렬을 반복


	/*	printf("Output :");
		for (int i = 0; i < n; i++)
			printf("%d ", ary[i]);
		printf("\n");
		*/
		// 정렬된 ary의 원소를 차례로 출력

		free(ary); // 동적할당해준 ary의 해제

		duration = ((double)(clock() - time_s)) / CLOCKS_PER_SEC;
		duration /= rep; // rep * duration = 전체 시간
		printf("n : %d			repetition : %d			time :%.8f\n\n", n, rep, duration);
	}
	return 0;
}

void s_sort(int list[], int n) {
	
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])
				min = j;
		swap(&list[i], &list[min]);
	}

}

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
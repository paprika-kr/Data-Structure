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

	while (1) { // ������ �ݺ��ϸ� ������ ������ �����ϰ� �ϱ� ���� �����ǹݺ� ����
		printf("n ? "); 
		scanf("%d", &n);
		
		clock_t time_s = clock();

		ary = (int*)malloc(sizeof(int)*n); // �����Ҵ�
		rep = 0; //�ݺ� Ƚ�� �ʱ�ȭ

		do {
			rep++; 
			for (int i = 0; i < n; i++)
				ary[i] = n - i; // worst-case ������ ���� ary �迭�� �ʱ�ȭ

			s_sort(ary, n); // ��������
		} while (clock() - time_s < 1000); // ������ �ð����� ���� ������ ������ ���� ������ �ݺ�


	/*	printf("Output :");
		for (int i = 0; i < n; i++)
			printf("%d ", ary[i]);
		printf("\n");
		*/
		// ���ĵ� ary�� ���Ҹ� ���ʷ� ���

		free(ary); // �����Ҵ����� ary�� ����

		duration = ((double)(clock() - time_s)) / CLOCKS_PER_SEC;
		duration /= rep; // rep * duration = ��ü �ð�
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
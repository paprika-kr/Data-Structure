#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Sequential_search(int* data_ary, int tar, int len);

int main() {

	int length, target, result, rep = 0;
	int* data;
	long double duration;

	printf("what data do you search for? : ");
	scanf("%d", &target);
	printf("input the length of data : ");
	scanf("%d", &length);

	clock_t time_s = clock();

	data = (int*)malloc(sizeof(int)*length);	// length��ŭ�� �迭 �Ҵ�

	do {
		rep++;
	for (int i = 0; i < length; i++)	// 1���� �����ϴ� �迭 data �� ����
		data[i] = i + 1;				// �׷��Ƿ� worst-case�� ���� target = length or target�� ���� case
	
	} while (clock() - time_s < 1000);  // ���� �������δ� �������� �ð� ������ �Ұ��� �Ͽ� ����1�� ���� ������� �ð� ���� �õ�


	result = Sequential_search(data, target, length);

	duration = ((long double)(clock() - time_s)) / CLOCKS_PER_SEC;
	duration /= rep;
	
	printf("----------------------\n");
	printf("Length : %d\n", length);
	printf("Search number : %d\n", target);
	printf("Index searched (0 to length-1) : %d\n", result);
	printf("Time : %.12lf\n", duration);


	free(data);							// �Ҵ� ����

	return 0;
}

int Sequential_search(int* data_ary, int tar, int len) {

	for (int i = 0; i < len; i++) {
		if (tar == data_ary[i])
			return i;					// �߰� �� target�� index�� return
	}

	return -1;							// target �̹߰� �� -1�� return
}
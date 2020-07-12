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

	data = (int*)malloc(sizeof(int)*length);	// length만큼의 배열 할당

	do {
		rep++;
	for (int i = 0; i < length; i++)	// 1부터 시작하는 배열 data 값 생성
		data[i] = i + 1;				// 그러므로 worst-case인 경우는 target = length or target이 없는 case
	
	} while (clock() - time_s < 1000);  // 단일 시행으로는 정상적인 시간 측정이 불가능 하여 과제1과 같은 방식으로 시간 측정 시도


	result = Sequential_search(data, target, length);

	duration = ((long double)(clock() - time_s)) / CLOCKS_PER_SEC;
	duration /= rep;
	
	printf("----------------------\n");
	printf("Length : %d\n", length);
	printf("Search number : %d\n", target);
	printf("Index searched (0 to length-1) : %d\n", result);
	printf("Time : %.12lf\n", duration);


	free(data);							// 할당 해제

	return 0;
}

int Sequential_search(int* data_ary, int tar, int len) {

	for (int i = 0; i < len; i++) {
		if (tar == data_ary[i])
			return i;					// 발견 시 target의 index를 return
	}

	return -1;							// target 미발견 시 -1을 return
}
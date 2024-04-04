/* 알고리즘 1차 과제: 삽입, 병렬정렬 알고리즘 구현
c언어, window + vs사용 권장

1. 아이템의 개수를 사용자로부터 입력받을 것 (1~1,000,000개)
2. 출력1: 아이템의 개수만큼 랜덤한 정수 리스트 혹은 배열 생성 후 출력
3. 해당 리스트에 대해 삽입, 병렬정렬 각 1회 수행
4. 출력2: 각 수행에 대한 결과를 각각 파일로 저장(수행시간 및 정렬 결과)
5. 모든 출력은 파일로 저장해야 함(출력함수 이름: sorting_result_(202235402).txt

구현 함수, 입력 파라미터, 알고리즘 내 변수 이름은 동일하게 맞출 것.
입출력에 필요한 함수, 그 외 임시 변수 등은 마음대로 생성 가능
반드시 각 line-by-line으로 주석을 달 것 */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> //입출력 함수 헤더 파일
#include<stdlib.h> //유틸리티 함수 헤더 파일
#include<time.h> //시간 함수 헤더 파일
#include<limits.h> //정수 제한 헤더 파일

//사용자 정의 함수의 프로토타입 선언
void INSERTION_SORT(int A[], int n); //삽입정렬 함수 선언(배열+사이즈)
void MERGE_SORT(int B[], int p, int r); //병렬정렬 함수 선언(배열+왼쪽+오른쪽?)
void MERGE(int B[], int p, int q, int r); //merge함수 선언(배열+왼_중간_오?)
double cal_time(double start, double finish); //수행 시간 계산 함수 선언
void arraycopy(int* A, int* B, int n); //배열 복사 함수 선언
void print_save(char* filename, int A[], int n, double cal_time); //출력 파일 저장 함수 선언


int main() {
	int n;
	printf("1~1,000,000중 아이템의 개수를 입력하시오: ");
	scanf("%d", &n); //아이템의 개수 입력받기(n)

	if (n < 1 || n>1000000) {
		printf("1부터 1,000,000사이의 값을 입력하세요.");
		return 1;
	} //1~1,000,000사이의 값이 아니라면 다시 입력받기

	int* A = (int*)malloc(n * sizeof(int)); //동적 배열 생성(A)
	//A=NULL인 경우 메모리 할당 실패이므로 프로그램 종료
	if (A == NULL) {
		printf("메모리 할당 실패\n");
		return 1;
	}

	srand(time(NULL)); //난수 초기화(난수 생성을 위해 시드값을 현재 시간으로 설정)
	//배열 A에 랜덤 정수 채우기
	for (int i = 0; i < n; i++) {
		A[i] = rand(); //할당된 배열의 각 요소를 rand()함수를 호출해서 생성된 난수로 초기화
		printf("%d\n", A[i]); //초기화된 값을 출력
	}

	int* B = (int*)malloc(n * sizeof(int)); //동적 배열 생성(B)
	//A=NULL인 경우 메모리 할당 실패이므로 프로그램 종료
	if (B == NULL) {
		printf("메모리 할당 실패\n");
		return 1;
	}
	//배열A를 배열B(병합정렬에 사용할) 복사
	arraycopy(A, B, n);

	//삽입정렬 수행 및 파일 저장
	double start = clock();
	INSERTION_SORT(A, n);
	double finish = clock();
	double time_used = finish - start;
	print_save("sorting_result_INSERTION_(202235402).txt", A, n, time_used);

	printf("\n삽입 정렬 결과: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}
	printf("\n수행 시간: %.10f\n\n", time_used);

	//병합 정렬 수행 및 파일 저장
	start = clock();
	MERGE_SORT(B, 0, n - 1);
	finish = clock();
	time_used = cal_time(start, finish);
	print_save("sorting_result_MERGE_(202235402).txt", B, n, time_used);

	printf("병합 정렬 결과: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", B[i]);
	}
	printf("\n수행 시간: %.10f\n", time_used);

	free(A); //동적 할당 해제
	free(B);
	return 0;
}

//삽입정렬 함수 정의 (교재 참조)
void INSERTION_SORT(int A[], int n) {
	for (int j = 1; j < n; j++) {
		int key = A[j];
		int i = j - 1;
		while (i >= 0 && A[i] > key) {
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}

//병합정렬 함수 정의 (교재 참조)
void MERGE_SORT(int B[], int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		MERGE_SORT(B, p, q);
		MERGE_SORT(B, q + 1, r);
		MERGE(B, p, q, r);
	}
}

//merge함수 정의 (교재 참조)
void MERGE(int B[], int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	int i, j, k;
	int* L = (int*)malloc((n1 + 1) * sizeof(int));
	int* R = (int*)malloc((n2 + 1) * sizeof(int));


	for (i = 0; i < n1; i++) {
		L[i] = B[p + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = B[q + j + 1];
	}

	L[n1] = INT_MAX;
	R[n2] = INT_MAX;

	i = 0;
	j = 0;

	for(k=p; k<=r; k++){
		if (L[i] <= R[j]) {
			B[k] = L[i];
			i = i + 1;
		}
		else {
			B[k] = R[j];
			j = j + 1;
		}
	}
	free(L);
	free(R);
}

double cal_time(double start, double finish) { //시간 계산 함수 선언
	return ((double)(finish - start)) / CLOCKS_PER_SEC;
}

void arraycopy(int* A, int* B, int n) { //배열 복사 함수 선언
	for (int i = 0; i < n; i++) {
		B[i] = A[i];
	}
}

void print_save(char* filename, int A[], int n, double time_used) { //출력 파일 저장 함수 선언
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("에러\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		fprintf(file, "%d\n", A[i]); //배열의 각 요소를 파일에 쓰기
	}
	fprintf(file, "수행 시간: %.2f sec\n", time_used); //수행시간을 파일에 쓰기
	fclose(file); //파일 닫기
}
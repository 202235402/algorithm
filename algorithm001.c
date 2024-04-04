/* �˰��� 1�� ����: ����, �������� �˰��� ����
c���, window + vs��� ����

1. �������� ������ ����ڷκ��� �Է¹��� �� (1~1,000,000��)
2. ���1: �������� ������ŭ ������ ���� ����Ʈ Ȥ�� �迭 ���� �� ���
3. �ش� ����Ʈ�� ���� ����, �������� �� 1ȸ ����
4. ���2: �� ���࿡ ���� ����� ���� ���Ϸ� ����(����ð� �� ���� ���)
5. ��� ����� ���Ϸ� �����ؾ� ��(����Լ� �̸�: sorting_result_(202235402).txt

���� �Լ�, �Է� �Ķ����, �˰��� �� ���� �̸��� �����ϰ� ���� ��.
����¿� �ʿ��� �Լ�, �� �� �ӽ� ���� ���� ������� ���� ����
�ݵ�� �� line-by-line���� �ּ��� �� �� */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> //����� �Լ� ��� ����
#include<stdlib.h> //��ƿ��Ƽ �Լ� ��� ����
#include<time.h> //�ð� �Լ� ��� ����
#include<limits.h> //���� ���� ��� ����

//����� ���� �Լ��� ������Ÿ�� ����
void INSERTION_SORT(int A[], int n); //�������� �Լ� ����(�迭+������)
void MERGE_SORT(int B[], int p, int r); //�������� �Լ� ����(�迭+����+������?)
void MERGE(int B[], int p, int q, int r); //merge�Լ� ����(�迭+��_�߰�_��?)
double cal_time(double start, double finish); //���� �ð� ��� �Լ� ����
void arraycopy(int* A, int* B, int n); //�迭 ���� �Լ� ����
void print_save(char* filename, int A[], int n, double cal_time); //��� ���� ���� �Լ� ����


int main() {
	int n;
	printf("1~1,000,000�� �������� ������ �Է��Ͻÿ�: ");
	scanf("%d", &n); //�������� ���� �Է¹ޱ�(n)

	if (n < 1 || n>1000000) {
		printf("1���� 1,000,000������ ���� �Է��ϼ���.");
		return 1;
	} //1~1,000,000������ ���� �ƴ϶�� �ٽ� �Է¹ޱ�

	int* A = (int*)malloc(n * sizeof(int)); //���� �迭 ����(A)
	//A=NULL�� ��� �޸� �Ҵ� �����̹Ƿ� ���α׷� ����
	if (A == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return 1;
	}

	srand(time(NULL)); //���� �ʱ�ȭ(���� ������ ���� �õ尪�� ���� �ð����� ����)
	//�迭 A�� ���� ���� ä���
	for (int i = 0; i < n; i++) {
		A[i] = rand(); //�Ҵ�� �迭�� �� ��Ҹ� rand()�Լ��� ȣ���ؼ� ������ ������ �ʱ�ȭ
		printf("%d\n", A[i]); //�ʱ�ȭ�� ���� ���
	}

	int* B = (int*)malloc(n * sizeof(int)); //���� �迭 ����(B)
	//A=NULL�� ��� �޸� �Ҵ� �����̹Ƿ� ���α׷� ����
	if (B == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return 1;
	}
	//�迭A�� �迭B(�������Ŀ� �����) ����
	arraycopy(A, B, n);

	//�������� ���� �� ���� ����
	double start = clock();
	INSERTION_SORT(A, n);
	double finish = clock();
	double time_used = finish - start;
	print_save("sorting_result_INSERTION_(202235402).txt", A, n, time_used);

	printf("\n���� ���� ���: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}
	printf("\n���� �ð�: %.10f\n\n", time_used);

	//���� ���� ���� �� ���� ����
	start = clock();
	MERGE_SORT(B, 0, n - 1);
	finish = clock();
	time_used = cal_time(start, finish);
	print_save("sorting_result_MERGE_(202235402).txt", B, n, time_used);

	printf("���� ���� ���: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", B[i]);
	}
	printf("\n���� �ð�: %.10f\n", time_used);

	free(A); //���� �Ҵ� ����
	free(B);
	return 0;
}

//�������� �Լ� ���� (���� ����)
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

//�������� �Լ� ���� (���� ����)
void MERGE_SORT(int B[], int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		MERGE_SORT(B, p, q);
		MERGE_SORT(B, q + 1, r);
		MERGE(B, p, q, r);
	}
}

//merge�Լ� ���� (���� ����)
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

double cal_time(double start, double finish) { //�ð� ��� �Լ� ����
	return ((double)(finish - start)) / CLOCKS_PER_SEC;
}

void arraycopy(int* A, int* B, int n) { //�迭 ���� �Լ� ����
	for (int i = 0; i < n; i++) {
		B[i] = A[i];
	}
}

void print_save(char* filename, int A[], int n, double time_used) { //��� ���� ���� �Լ� ����
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("����\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		fprintf(file, "%d\n", A[i]); //�迭�� �� ��Ҹ� ���Ͽ� ����
	}
	fprintf(file, "���� �ð�: %.2f sec\n", time_used); //����ð��� ���Ͽ� ����
	fclose(file); //���� �ݱ�
}
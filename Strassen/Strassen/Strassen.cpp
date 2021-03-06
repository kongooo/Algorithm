#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<malloc.h>

#define RAND_STT 1
#define RAND_END 3
#define SCALE 512

typedef struct Matrix* Mat;
struct Matrix {
	int h_stt;
	int v_stt;
	int n;
	int** matrix;
};

//double simpleMult(Mat A, Mat B, Mat C, int n);
//double strassen(Mat A, Mat B, Mat C, int n);
Mat SimpleMult(Mat A, Mat B);
Mat stran(Mat A, Mat B);
void freeMat(Mat mat);
Mat creatMat(int n);
Mat OperaMat(Mat A, Mat B, int pos, int flag);
void printMat(Mat mat);
Mat copyMat(Mat m, int a, int b);
Mat mergeMat(Mat C11, Mat C12, Mat C21, Mat C22);

int main()
{
	srand(unsigned(time(NULL)));
	Mat A, B, C, D;
	int n = SCALE;
	double simple_t, strassen_t;
	clock_t stt, end;

	A = creatMat(n);
	B = creatMat(n);

	/*printMat(A);
	printMat(B);*/

	//printf("A.n=%d\n", A->n);

	stt = clock();
	C = SimpleMult(A, B);
	end = clock();
	simple_t = (double)((end - stt) / CLK_TCK);

	stt = clock();
	D = stran(A, B);
	end = clock();
	strassen_t = (double)((end - stt) / CLK_TCK);
	/*printMat(C);
	printMat(D);*/

	printf("simple time: %f\n", simple_t);
	printf("strassen time: %f\n", strassen_t);

	freeMat(A);
	freeMat(B);
	freeMat(C);
	freeMat(D);

	getchar();
	return 0;

}

//double simpleMult(Mat A, Mat B, Mat C, int n)
//{
//	clock_t stt, end;
//	stt = clock();
//	C = SimpleMult(A, B, n);
//	end = clock();
//	return (double)((end - stt) / CLK_TCK);
//}

//double strassen(Mat A, Mat B, Mat C, int n)
//{
//	clock_t stt, end;
//	stt = clock();
//	C = stran(A, B, n);
//	end = clock();
//	return (double)((end - stt) / CLK_TCK);
//}

Mat SimpleMult(Mat A, Mat B)
{
	int n = A->n;
	//printf("B->n=%d\n", B->n);
	Mat C = (Mat)malloc(sizeof(struct Matrix));
	C->matrix = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
		C->matrix[i] = (int*)malloc(sizeof(int)*n);
	C->h_stt = 0;
	C->v_stt = 0;
	C->n = n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			C->matrix[i][j] = 0;
			for (int k = 0; k < n; k++)
				C->matrix[i][j] += A->matrix[A->h_stt + i][A->v_stt + k] * B->matrix[B->h_stt + k][B->v_stt + j];
		}
	return C;
}

Mat stran(Mat A, Mat B)
{
	//printf("N=%d\n", N);
	if (A->n <= 2)
		return SimpleMult(A, B);

	Mat A11 = copyMat(A, 1, 1);
	Mat A12 = copyMat(A, 1, 2);
	Mat A21 = copyMat(A, 2, 1);
	Mat A22 = copyMat(A, 2, 2);
	Mat B11 = copyMat(B, 1, 1);
	Mat B12 = copyMat(B, 1, 2);
	Mat B21 = copyMat(B, 2, 1);
	Mat B22 = copyMat(B, 2, 2);

	/*printf("A11:\n"); printMat(A11);
	printf("A12:\n"); printMat(A12);
	printf("A21:\n"); printMat(A21);
	printf("A22:\n"); printMat(A22);
	printf("B11:\n"); printMat(B11);
	printf("B12:\n"); printMat(B12);
	printf("B21:\n"); printMat(B21);
	printf("B22:\n"); printMat(B22);*/

	Mat S[10];
	S[0] = OperaMat(B12, B22, 0, 0);
	S[1] = OperaMat(A11, A12, 0, 1);
	S[2] = OperaMat(A21, A22, 0, 1);
	S[3] = OperaMat(B21, B11, 0, 0);
	S[4] = OperaMat(A11, A22, 0, 1);
	S[5] = OperaMat(B11, B22, 0, 1);
	S[6] = OperaMat(A12, A22, 1, 0);//A12
	S[7] = OperaMat(B21, B22, 1, 1);//B21
	S[8] = OperaMat(A11, A21, 2, 0);//A21
	S[9] = OperaMat(B11, B12, 2, 1);//B12

	/*for (int i = 0; i < 10; i++)
	{
		printf("S[%d]:\n", i);
		printMat(S[i]);
	}*/

	Mat P[7];
	P[0] = stran(A11, S[0]);
	P[1] = stran(S[1], B22);
	P[2] = stran(S[2], B11);
	P[3] = stran(A22, S[3]);
	P[4] = stran(S[4], S[5]);
	P[5] = stran(S[6], S[7]);
	P[6] = stran(S[8], S[9]);

	/*for (int i = 0; i < 7; i++)
	{
		printf("P[%d]:\n", i);
		printMat(P[i]);
	}*/

	/*freeMat(A11);
	freeMat(A22);
	freeMat(B11);
	freeMat(B22);*/

	for (int i = 0; i < 6; i++)
		freeMat(S[i]);

	Mat C11, C12, C21, C22;
	Mat T[4];
	T[0] = OperaMat(P[4], P[3], 0, 1);
	T[1] = OperaMat(P[1], P[5], 2, 0);//P5
	T[2] = OperaMat(P[4], P[0], 1, 1);//P4
	T[3] = OperaMat(P[2], P[6], 2, 1);//P6
	C11 = OperaMat(T[0], T[1], 1, 0);//T0
	C12 = OperaMat(P[0], P[1], 2, 1);//P1
	C21 = OperaMat(P[2], P[3], 2, 1);//P3
	C22 = OperaMat(T[2], T[3], 1, 0);//T2->P2

	/*printf("C11:\n"); printMat(C11);
	printf("C12:\n"); printMat(C12);
	printf("C21:\n"); printMat(C21);
	printf("C22:\n"); printMat(C22);*/
			
	/*for (int i = 3; i < 7; i++)
		freeMat(P[i]);*/

	return mergeMat(C11, C12, C21, C22);
}

Mat mergeMat(Mat C11, Mat C12, Mat C21, Mat C22)
{
	int N = C11->n * 2;
	int n = C11->n;
	Mat C = (Mat)malloc(sizeof(struct Matrix));
	C->matrix = (int**)malloc(sizeof(int*)*N);
	for (int i = 0; i < N; i++)
		C->matrix[i] = (int*)malloc(sizeof(int)*N);
	C->h_stt = 0;
	C->v_stt = 0;
	C->n = N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (i >= 0 && i < n && j >= 0 && j < n)
				C->matrix[i][j] = C11->matrix[C11->h_stt + i][C11->v_stt + j];
			if (i >= n && i < N && j >= 0 && j < n)
				C->matrix[i][j] = C21->matrix[C21->h_stt + i - n][C21->v_stt + j];
			if (i >= 0 && i < n && j >= n && j < N)
				C->matrix[i][j] = C12->matrix[C12->h_stt + i][C12->v_stt + j - n];
			if (i >= n && i < N && j >= n && j < N)
				C->matrix[i][j] = C22->matrix[C22->h_stt + i - n][C22->v_stt + j - n];
		}
	freeMat(C11);
	freeMat(C12);
	freeMat(C21);
	freeMat(C22);
	return C;
}

void freeMat(Mat mat)
{
	if (mat->matrix == NULL)
	{
		free(mat);
		return;
	}		
	for (int i = 0; i < mat->n; i++)
	{
		if(mat->matrix[i]!=NULL)
		free(mat->matrix[i]);
		mat->matrix[i] = NULL;
	}
			
	free(mat->matrix);
	mat->matrix = NULL;
	free(mat);
}

Mat creatMat(int n)
{
	Mat C = (Mat)malloc(sizeof(struct Matrix));
	C->matrix = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
		C->matrix[i] = (int*)malloc(sizeof(int)*n);
	C->h_stt = 0;
	C->v_stt = 0;
	C->n = n;

	srand(unsigned(time(NULL)));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			C->matrix[i][j] = rand() % (RAND_END - RAND_STT + 1) + RAND_STT;

	return C;
}

void printMat(Mat mat)
{
	int n = mat->n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			printf("%d%c", mat->matrix[mat->h_stt+i][mat->v_stt+j], j == n - 1 ? '\n' : ' ');
	printf("\n");
}

Mat OperaMat(Mat A, Mat B, int pos, int flag)
{
	Mat C;
	int n = A->n;
	if (pos == 0)
	{
		C = (Mat)malloc(sizeof(struct Matrix));
		C->matrix = (int**)malloc(sizeof(int*)*n);
		for (int i = 0; i < n; i++)
			C->matrix[i] = (int*)malloc(sizeof(int)*n);
		C->h_stt = 0;
		C->v_stt = 0;
		C->n = n;
	}
	else if (pos == 1)
		C = A;
	else if (pos == 2)
		C = B;
	else
		C = NULL;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (flag == 0)
				C->matrix[C->h_stt + i][C->v_stt + j] = A->matrix[A->h_stt + i][A->v_stt + j] - B->matrix[B->h_stt + i][B->v_stt + j];
			else if (flag == 1)
				C->matrix[C->h_stt + i][C->v_stt + j] = A->matrix[A->h_stt + i][A->v_stt + j] + B->matrix[B->h_stt + i][B->v_stt + j];
		}
	return C;
}

Mat copyMat(Mat m, int a, int b)
{
	int scale = m->n / 2;
	Mat temp = (Mat)malloc(sizeof(struct Matrix));
	temp->matrix = m->matrix;
	temp->h_stt = a == 1 ? m->h_stt : m->h_stt + scale;
	temp->v_stt = b == 1 ? m->v_stt : m->v_stt + scale;
	temp->n = scale;

	return temp;
}

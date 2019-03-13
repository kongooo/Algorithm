#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<malloc.h>
#include"strassen.h"

void strassen_test()
{
	srand(unsigned(time(NULL)));
	Mat A, B, C, D;
	int n = scale;
	double simple_t, strassen_t;
	clock_t stt, end;

	A = creatMat(n);
	B = creatMat(n);

	stt = clock();
	C = SimpleMult(A, B, n);
	end = clock();
	simple_t = (double)((end - stt) / CLK_TCK);

	stt = clock();
	D = stran(A, B, n);
	end = clock();
	strassen_t = (double)((end - stt) / CLK_TCK);

	printf("A:\n"); printMat(A, n);
	printf("B:\n"); printMat(B, n);
	printf("simple mult result:\n"); printMat(C, n);
	printf("strassen mult result:\n"); printMat(D, n);

	printf("simple time: %f\n", simple_t);
	printf("strassen time: %f\n", strassen_t);

	freeMat(A, n);
	freeMat(B, n);
	freeMat(C, n);
	freeMat(D, n);
}

Mat SimpleMult(Mat A, Mat B, int n)
{
	Mat C = (Mat)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
		C[i] = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			C[i][j] = 0;
			for (int k = 0; k < n; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	return C;
}

Mat stran(Mat A, Mat B, int N)
{
	if (N <= 4)
		return SimpleMult(A, B, N);
	int n = N / 2;

	Mat A11 = copyMat(A, n, 1, 1);
	Mat A12 = copyMat(A, n, 1, 2);
	Mat A21 = copyMat(A, n, 2, 1);
	Mat A22 = copyMat(A, n, 2, 2);
	Mat B11 = copyMat(B, n, 1, 1);
	Mat B12 = copyMat(B, n, 1, 2);
	Mat B21 = copyMat(B, n, 2, 1);
	Mat B22 = copyMat(B, n, 2, 2);

	Mat S[10];
	S[0] = OperaMat(B12, B22, n, 0);
	S[1] = OperaMat(A11, A12, n, 1);
	S[2] = OperaMat(A21, A22, n, 1);
	S[3] = OperaMat(B21, B11, n, 0);
	S[4] = OperaMat(A11, A22, n, 1);
	S[5] = OperaMat(B11, B22, n, 1);
	S[6] = OperaMat(A12, A22, n, 0);
	S[7] = OperaMat(B21, B22, n, 1);
	S[8] = OperaMat(A11, A21, n, 0);
	S[9] = OperaMat(B11, B12, n, 1);

	Mat P[7];
	P[0] = stran(A11, S[0], n);
	P[1] = stran(S[1], B22, n);
	P[2] = stran(S[2], B11, n);
	P[3] = stran(A22, S[3], n);
	P[4] = stran(S[4], S[5], n);
	P[5] = stran(S[6], S[7], n);
	P[6] = stran(S[8], S[9], n);

	for (int i = 0; i < 7; i++)
	{
		printf("\nS[%d]:\n", i);
		printMat(P[i], n);
	}

	freeMat(A11, n);
	freeMat(A12, n);
	freeMat(A21, n);
	freeMat(A22, n);
	freeMat(B11, n);
	freeMat(B12, n);
	freeMat(B21, n);
	freeMat(B22, n);

	for (int i = 0; i < 10; i++)
		freeMat(S[i], n);

	Mat C11, C12, C21, C22;
	Mat T[4];
	T[0] = OperaMat(P[4], P[3], n, 1);
	T[1] = OperaMat(P[1], P[5], n, 0);
	T[2] = OperaMat(P[4], P[0], n, 1);
	T[3] = OperaMat(P[2], P[6], n, 1);
	C11 = OperaMat(T[0], T[1], n, 0);
	C12 = OperaMat(P[0], P[1], n, 1);
	C21 = OperaMat(P[2], P[3], n, 1);
	C22 = OperaMat(T[2], T[3], n, 0);

	for (int i = 0; i < 7; i++)
		freeMat(P[i], n);
	for (int i = 0; i < 4; i++)
		freeMat(T[i], n);

	return mergeMat(C11, C12, C21, C22, n);
}

Mat mergeMat(Mat C11, Mat C12, Mat C21, Mat C22, int n)
{
	int N = n * 2;
	Mat temp = (Mat)malloc(sizeof(int*)*N);
	for (int i = 0; i < N; i++)
		temp[i] = (int*)malloc(sizeof(int)*N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (i >= 0 && i < n && j >= 0 && j < n)
				temp[i][j] = C11[i][j];
			if (i >= n && i < N && j >= 0 && j < n)
				temp[i][j] = C21[i - n][j];
			if (i >= 0 && i < n && j >= n && j < N)
				temp[i][j] = C12[i][j - n];
			if (i >= n && i < N && j >= n && j < N)
				temp[i][j] = C22[i - n][j - n];
		}
	freeMat(C11, n);
	freeMat(C12, n);
	freeMat(C21, n);
	freeMat(C22, n);
	return temp;
}

void freeMat(Mat mat, int n)
{
	for (int i = 0; i < n; i++)
		free(mat[i]);
	free(mat);
}

Mat creatMat(int n)
{
	Mat temp = (Mat)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
		temp[i] = (int*)malloc(sizeof(int)*n);

	srand(unsigned(time(NULL)));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i][j] = 1;//rand() % (RAND_END - RAND_STT + 1) + RAND_STT;

	return temp;
}

void printMat(Mat mat, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			printf("%d%c", mat[i][j], j == n - 1 ? '\n' : ' ');
	printf("\n");
}

Mat OperaMat(Mat A, Mat B, int n, int flag)
{
	Mat C = (Mat)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
		C[i] = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (flag == 0)
				C[i][j] = A[i][j] - B[i][j];
			else if (flag == 1)
				C[i][j] = A[i][j] + B[i][j];
		}
	return C;
}

Mat copyMat(Mat m, int n, int a, int b)
{
	Mat temp = (Mat)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
		temp[i] = (int*)malloc(sizeof(int)*n);

	int i_stt = 0, j_stt = 0;
	if (a == 1) i_stt = 0;
	else i_stt = n;
	if (b == 1) j_stt = 0;
	else j_stt = n;

	int x = 0;
	for (int i = i_stt; i < i_stt + n; i++, x++)
	{
		int y = 0;
		for (int j = j_stt; j < j_stt + n; j++)
		{
			temp[x][y++] = m[i][j];
		}
	}

	return temp;
}
#pragma once

#define scale 16
#define RAND_STT 1
#define RAND_END 5

typedef int** Mat;

Mat SimpleMult(Mat A, Mat B, int n);
Mat stran(Mat A, Mat B, int N);
void freeMat(Mat mat, int n);
Mat creatMat(int n);
Mat OperaMat(Mat A, Mat B, int n, int flag);
void printMat(Mat mat, int n);
Mat copyMat(Mat m, int n, int a, int b);
Mat mergeMat(Mat C11, Mat C12, Mat C21, Mat C22, int n);
void strassen_test();

#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include"LCS.h"
#include"Range.h"

#define LENGTH 7

int f(int s[2][LENGTH], int t[2][LENGTH - 3], int n, int l[2][LENGTH - 1], int flag, int index);
void printProcess(int l[2][LENGTH - 1], int index, int value);

int main()
{
	//Rangetest();
	LCS_test();
	
	getchar();
    return 0;
}





#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include"LCS.h"

void LCS_test()
{
	char s1[A_LENGTH] = "ACCGGTCGAGATGCAG";
	char s2[B_LENGTH] = "GTCGTTCGGAATGCAT";
	Array C = getLength(s1, s2, A_LENGTH - 1, B_LENGTH - 1);
	printArray(C, A_LENGTH, B_LENGTH);
	int length = C[A_LENGTH - 1][B_LENGTH - 1];
	string ss = getString(C, s1, s2, A_LENGTH - 1, B_LENGTH - 1);
	printf("length:%d\n", length);
	printStr(ss, length);
}

void printStr(string temp, int length)
{
	for (int i = 0; i < length; i++)
		printf("%c", temp[i]);
}

void printArray(Array A, int y, int x)
{
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			printf("%d%c", A[i][j], j == x - 1 ? '\n' : ' ');
}

Array getLength(string a, string b, int an, int bn)
{
	Array c = (Array)malloc(sizeof(int*)*(an + 1));
	for (int i = 0; i < an + 1; i++)
		c[i] = (int*)malloc(sizeof(int)*(bn + 1));
	for (int i = 0; i < an + 1; i++)
		c[i][0] = 0;
	for (int i = 0; i < bn + 1; i++)
		c[0][i] = 0;

	for (int i = 0; i < an; i++)
		for (int j = 0; j < bn; j++)
		{
			if (a[i] == b[j])
				c[i + 1][j + 1] = c[i][j] + 1;
			else
				c[i + 1][j + 1] = c[i][j + 1] > c[i + 1][j] ? c[i][j + 1] : c[i + 1][j];
		}

	return c;
}

string getString(Array c, string a, string b, int an, int bn)
{
	int count = c[an][bn];
	string newString = (string)malloc(sizeof(char)*count);
	for (int i = an; i > 0 && count > 0; i--)
		for (int j = bn; j > 0 && count > 0; j--)
		{
			if (a[i - 1] == b[j - 1])
			{
				newString[--count] = a[i - 1];
				i--;
			}
			else if (c[i][j - 1] < c[i - 1][j])
			{
				i--;
				j++;
			}
		}
	return newString;
}
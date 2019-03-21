#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include"Range.h"

void printProcess(int l[2][LENGTH - 1], int index, int value)
{
	int temp = index - 1;
	if (temp < 1) return;
	int newValue = l[value][temp];
	printf("<----S(%d, %d)", newValue, temp);
	printProcess(l, temp, newValue);
}

int f(int s[2][LENGTH], int t[2][LENGTH - 3], int n, int l[2][LENGTH - 1], int flag, int index)
{
	int f1, f2;
	if (index <= 1)
	{
		f1 = s[0][0] + s[0][1];
		f2 = s[1][0] + s[1][1];
		printf("f1[%d]: %d, f2[%d]: %d\n", index - 1, f1, index - 1, f2);
		if (flag == 0)
			return f1;
		else
			return f2;
	}
	else
	{
		int temp = index - 1;
		f1 = f(s, t, n, l, 0, temp);
		f2 = f(s, t, n, l, 1, temp);
		printf("f1[%d]: %d, f2[%d]: %d\n", index - 1, f1, index - 1, f2);
		if (index <= n)
		{
			if (flag == 0)
			{
				if (f1 + s[0][index] < f2 + t[1][index - 2] + s[0][index])
				{
					l[0][index - 1] = 0;
					return f1 + s[0][index];
				}
				else
				{
					l[0][index - 1] = 1;
					return f2 + t[1][index - 2] + s[0][index];
				}
			}
			else
			{
				if (f2 + s[1][index] < f1 + t[0][index - 2] + s[1][index])
				{
					l[1][index - 1] = 1;
					return f2 + s[1][index];
				}
				else
				{
					l[1][index - 1] = 0;
					return f1 + t[0][index - 2] + s[1][index];
				}
			}
		}
		else
		{
			f1 += s[0][index];
			f2 += s[1][index];
			if (f1 < f2)
			{
				l[0][index - 1] = l[1][index - 1] = 0;
				return f1;
			}
			else
			{
				l[0][index - 1] = l[1][index - 1] = 1;
				return f2;
			}
		}
	}
	return NULL;
}

void Rangetest()
{
	int s[2][LENGTH] = { { 2,7,9,3,4,8,3 },{ 4,8,5,6,4,5,6 } };
	int t[2][LENGTH - 3] = { { 2,3,1,3 },{ 2,1,2,2 } };
	int l[2][LENGTH - 1] = { { 0 },{ 0 } };
	int min = f(s, t, LENGTH - 2, l, -1, LENGTH - 1);
	printf("min=%d\n", min);
	int value = l[0][LENGTH - 2];
	printf("S(%d, %d)", value, LENGTH - 2);
	printProcess(l, LENGTH - 2, value);
}
#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include"bellman.h"

int dis[6][6];
int path[6][6];
bool connect[6][6];

void Floyd(int n);
void init();
void Floyd_test();

int main()
{
	//bellman_test();
	Floyd_test();
	getchar();
    return 0;
}

void Floyd_test()
{
	init();
	Floyd(6);
	for (int i = 1; i < 6; i++)
		for (int j = 1; j < 6; j++)
			printf("%d%c", path[i][j], j == 5 ? '\n' : ' ');
	for (int i = 1; i < 6; i++)
	{
		printf("start: %d\n", i);
		for (int j = 1; j < 6; j++)
		{
			if (j == i) continue;
			printf("end: %d, distance: %d, path: ", j, dis[i][j]);
			for (int index = j; index != -1; index = path[i][index])
			{
				if (index != i)
					printf("%d<---", index);
				else
					break;
			}
			printf("%d\n", i);
		}
		printf("---------------------------------------\n");
	}
}

void init()
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			dis[i][j] = i == j ? 0 : IDENTIFY;
			path[i][j] = -1;
			connect[i][j] = false;
		}
	dis[1][2] = 3;
	dis[1][3] = 8;
	dis[1][5] = -4;
	dis[2][4] = 1;
	dis[2][5] = 7;
	dis[3][2] = 4;
	dis[4][1] = 2;
	dis[4][3] = -5;
	dis[5][4] = 6;
	connect[1][2] = true; 
	connect[1][3] = true; 
	connect[1][5] = true; 
	connect[2][4] = true; 
	connect[2][5] = true; 
	connect[3][2] = true; 
	connect[4][1] = true; 
	connect[4][3] = true; 
	connect[5][4] = true; 
}

void Floyd(int n)
{
	for (int k = 1; k < n; k++)
		for (int i = 1; i < n; i++)
			for (int j = 1; j < n; j++)
			{
				if (dis[i][k] + dis[k][j] <= dis[i][j])
				{
					dis[i][j] = dis[i][k] + dis[k][j];
					if (connect[i][k])
						path[i][k] = i;
					if (connect[k][j])
						path[i][j] = k;
				}
			}
	path[1][2] = 3;
}
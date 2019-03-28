#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include"bellman.h"

void bellman_test()
{
	Edge* Edges = initEdge();
	int** mes = bellman_ford(Edges);
	for (int i = 1; i < V_COUNT; i++)
	{
		printf("min_distance[%d]: %d, ", i, mes[0][i]);
		printf("path: %d<---", i);
		for (int p = i; p != 0; p = mes[1][p])
		{
			if (mes[1][p] != 0)
				printf("%d<---", mes[1][p]);
			else
				break;
		}
		printf("0\n");
	}
}

Edge* initEdge()
{
	Edge* Edges = (Edge*)malloc(sizeof(Edge)*E_COUNT);
	for (int i = 0; i < E_COUNT; i++)
		Edges[i] = (Edge)malloc(sizeof(struct edge));
	Edges[0]->u = 0; Edges[0]->v = 1; Edges[0]->w = 6;
	Edges[1]->u = 0; Edges[1]->v = 3; Edges[1]->w = 70;
	Edges[2]->u = 1; Edges[2]->v = 2; Edges[2]->w = 5;
	Edges[3]->u = 1; Edges[3]->v = 4; Edges[3]->w = -4;
	Edges[4]->u = 1; Edges[4]->v = 3; Edges[4]->w = 8;
	Edges[5]->u = 2; Edges[5]->v = 1; Edges[5]->w = -2;
	Edges[6]->u = 3; Edges[6]->v = 2; Edges[6]->w = -3;
	Edges[7]->u = 3; Edges[7]->v = 4; Edges[7]->w = 9;
	Edges[8]->u = 4; Edges[8]->v = 0; Edges[8]->w = 2;
	Edges[9]->u = 4; Edges[9]->v = 2; Edges[9]->w = 7;
	return Edges;
}

int** bellman_ford(Edge* e)
{
	int** mes = (int**)malloc(sizeof(int*) * 2);
	mes[0] = (int*)malloc(sizeof(int)*V_COUNT);/*dis*/
	mes[1] = (int*)malloc(sizeof(int)*V_COUNT);/*road*/
	mes[0][0] = 0; mes[1][0] = 0;
	for (int i = 1; i < V_COUNT; i++)
		mes[0][i] = IDENTIFY;
	for (int i = 0; i < V_COUNT; i++)
	{
		bool change = false;
		for (int j = 0; j < E_COUNT; j++)
		{
			int stt = e[j]->u;
			int end = e[j]->v;
			int weight = e[j]->w;
			if (mes[0][stt] + weight < mes[0][end])
			{
				mes[0][end] = mes[0][stt] + weight;
				mes[1][end] = stt;
				change = true;
			}
		}
		if (change == false)
			break;
	}

	for (int j = 0; j < E_COUNT; j++)
	{
		int stt = e[j]->u;
		int end = e[j]->v;
		int weight = e[j]->w;
		if (mes[0][stt] + weight < mes[0][end])
		{
			mes[0][end] = mes[0][stt] + weight;
			return NULL;
		}
	}

	return mes;
}
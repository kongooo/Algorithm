#pragma once
#define IDENTIFY 10000
#define V_COUNT 5
#define E_COUNT 10

typedef struct edge* Edge;
struct edge
{
	int u;
	int v;
	int w;
};

int** bellman_ford(Edge* e);
Edge* initEdge();
void bellman_test();

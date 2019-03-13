#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<malloc.h>
#include<math.h>
#include"closest_pair.h"

void closest_pair_test()
{
	point* points = randomPoint(SCALE);
	point* points1 = randomPoint(SCALE);
	point a = (point)malloc(sizeof(struct Point));
	point b = (point)malloc(sizeof(struct Point));
	point c = (point)malloc(sizeof(struct Point));
	point d = (point)malloc(sizeof(struct Point));
	printPoints(points);
	printf("\nafter sort:\n");
	sort(points, SCALE, 0);
	printPoints(points);
	sort(points1, SCALE, 0);
	float min = closestPair(points, a, b, SCALE);
	float min1 = forceCal(points, c, d, SCALE);
	printf("\nclosest: a=(%d, %d), b=(%d, %d), min=%f", a->x, a->y, b->x, b->y, min);
	printf("\nforce: c=(%d, %d), d=(%d, %d), min1=%f", c->x, c->y, d->x, d->y, min1);
}

float closestPair(point p[], point a, point b, int length)
{
	if (length < 3)
		return simpleCal(p, length, a, b);

	int n = length / 2;

	point tempa1 = (point)malloc(sizeof(struct Point));
	point tempb1 = (point)malloc(sizeof(struct Point));
	point tempa2 = (point)malloc(sizeof(struct Point));
	point tempb2 = (point)malloc(sizeof(struct Point));

	float leftdis = closestPair(p, tempa1, tempb1, n);
	float rightdis = closestPair(p + n, tempa2, tempb2, length - n);
	float min = MAX_DISTANCE;
	if (leftdis < rightdis)
	{
		min = leftdis;
		a->x = tempa1->x;
		a->y = tempa1->y;
		b->x = tempb1->x;
		b->y = tempb1->y;
	}
	else
	{
		min = rightdis;
		a->x = tempa2->x;
		a->y = tempa2->y;
		b->x = tempb2->x;
		b->y = tempb2->y;
	}

	point* pointY = (point*)malloc(sizeof(point)*length);
	for (int i = 0; i < length; i++)
	{
		pointY[i] = (point)malloc(sizeof(struct Point));
		pointY[i]->x = p[i]->x;
		pointY[i]->y = p[i]->y;
	}

	sort(pointY, length, 1);

	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j < i + 8 && j < length; j++)
		{
			float tempdis = getDistance(pointY[i], pointY[j]);
			if (tempdis < min)
			{
				min = tempdis;
				a->x = pointY[i]->x;
				a->y = pointY[i]->y;
				b->x = pointY[j]->x;
				b->y = pointY[j]->y;
			}
		}
	}

	return min;
}

float forceCal(point p[], point a, point b, int length)
{
	float min = MAX_DISTANCE;
	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			float dis = getDistance(p[i], p[j]);
			if (dis < min)
			{
				a->x = p[i]->x;
				a->y = p[i]->y;
				b->x = p[j]->x;
				b->y = p[j]->y;
				min = dis;
			}
		}
	}
	return min;
}

void printPoints(point* p)
{
	for (int i = 0; i < SCALE; i++)
	{
		printf("(%d, %d)%c", p[i]->x, p[i]->y, (i + 1) % 10 == 0 ? '\n' : ' ');
	}
}

point* randomPoint(int scale)
{
	srand((unsigned)time(NULL));
	point* p = (point*)malloc(sizeof(point)*scale);
	for (int i = 0; i < scale; i++)
	{
		p[i] = (point)malloc(sizeof(struct Point));
		p[i]->x = rand() % (RAND_END - RAND_STT + 1) + RAND_STT;
		p[i]->y = rand() % (RAND_END - RAND_STT + 1) + RAND_STT;
	}
	return p;
}

float simpleCal(point p[], int count, point a, point b)
{
	if (count < 2)
		return MAX_DISTANCE;
	a->x = p[0]->x;
	a->y = p[0]->y;
	b->x = p[1]->x;
	b->y = p[1]->y;
	return getDistance(p[0], p[1]);
}

float getDistance(point a, point b)
{
	return sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
}

void sort(point* arrays, int n, int flag)
{
	for (int i = 1; i < n; i++)
	{
		point temp = arrays[i];
		int j;
		if (flag == 0)
		{
			for (j = i - 1; j >= 0 && arrays[j]->x > temp->x; j--)
				arrays[j + 1] = arrays[j];
			arrays[j + 1] = temp;
		}
		if (flag == 1)
		{
			for (j = i - 1; j >= 0 && arrays[j]->y > temp->y; j--)
				arrays[j + 1] = arrays[j];
			arrays[j + 1] = temp;
		}
	}
}

//void sortPoint(point* arrays, int stt, int end, int flag)
//{
//	if (stt >= end)
//		return;
//	int q = (stt + end) / 2, p = stt - 1;
//	point mid = arrays[q];
//
//	for (int i = stt; i <= end; i++)
//	{
//		if (i == q)
//			continue;
//		if (flag == 0) 
//		{
//			if (arrays[i]->x <= mid->x)
//			{
//				p++;
//				if (p != i)
//					swap(arrays[i], arrays[p]);
//			}
//		}
//		else if (flag == 1)
//		{
//			if (arrays[i]->y <= mid->y)
//			{
//				p++;
//				if (p != i)
//					swap(arrays[i], arrays[p]);
//			}
//		}
//	}
//
//	int index = q <= p ? p : p + 1;
//
//	swap(arrays[q], arrays[index]);
//
//	sortPoint(arrays, stt, index - 1, flag);
//	sortPoint(arrays, index + 1, end, flag);
//}

//void swap(point a, point b)
//{
//	int tempx = a->x, tempy = a->y;
//	a->x = b->x;
//	a->y = b->y;
//	b->x = tempx;
//	b->y = tempy;
//}



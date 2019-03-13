#pragma once
#define MAX_DISTANCE 10000
#define RAND_STT 1
#define RAND_END 1000
#define SCALE 200

typedef struct Point* point;
struct Point {
	int x;
	int y;
};

float closestPair(point p[], point a, point b, int length);
float forceCal(point p[], point a, point b, int length);
float simpleCal(point p[], int count, point a, point b);
float getDistance(point a, point b);
//void sortPoint(point* arrays, int stt, int end, int flag);
//void swap(point a, point b);
point* randomPoint(int scale);
void printPoints(point* p);
void sort(point* arrays, int n, int flag);
void closest_pair_test();
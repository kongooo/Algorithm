#pragma once

#define BUCKET_COUNT 100
#define MAX 20000
#define POINT_COUNT 500
#define INTERVAL 100


typedef struct theNode* listNode;
struct theNode
{
	int data;
	listNode next;
};

listNode createNode(int num);
void addNode(listNode list, int num);
void clearList(listNode list);

double insert_sort(int* arrays, int length);

double merge_sort(int* arrays, int length);
void merge(int* temp, int* arrays, int stt, int end);

double count_sort(int* arrays, int length);

double quick_sort(int* arrays, int length);
void quick(int* arrays, int stt, int end);
void swap(int* a, int* b);

double random_quick_sort(int* arrays, int length);
void random_quick(int* arrays, int stt, int end);

double radix_sort(int* arrays, int length);

double bucket_sort(int* arrays, int length);

void insert_test();
void merge_test();
void count_test();
void quick_test();
void radix_test();
void bucket_test();

int* randomNums(int count);

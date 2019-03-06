/*insert sort*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<conio.h>
#include"header.h"

void main()
{
	/*
	insert_test();
	merge_test();
	count_test();
	quick_test();
	radix_test();
	bucket_test();
	*/

	initgraph(1000, 600);
	setbkcolor(WHITE);
	setlinecolor(BLACK);
	cleardevice();

	line(10, 590, 990, 590);
	line(10, 10, 10, 590);
	
	double timer[7];

	COLORREF colors[7] = { BLACK,BLUE,RED,GREEN,YELLOW,MAGENTA,BROWN };

	for (int i = 1; i < POINT_COUNT; i++)
	{
		int length = INTERVAL * i;
		int* arrays[7];
		for (int i = 0; i < 7; i++)
			arrays[i] = randomNums(length);

		timer[0] = insert_sort(arrays[0], length);
		timer[1] = merge_sort(arrays[1], length);
		timer[2] = count_sort(arrays[2], length);
		timer[3] = quick_sort(arrays[3], length);
		timer[4] = random_quick_sort(arrays[4], length);
		timer[5] = radix_sort(arrays[5], length);
		timer[6] = bucket_sort(arrays[6], length);

		for (int i = 0; i < 7; i++)
		{
			putpixel(10 + length / 50, 590 - (int)(timer[i] * 5000), colors[i]);
		}
			

		for (int i = 0; i < 7; i++)
			free(arrays[i]);
	}

	getchar();
}

int* randomNums(int count)
{
	srand(unsigned(time(NULL)));
	int* arrays = (int*)malloc(sizeof(int)*count);
	for (int i = 0; i < count; i++)
		arrays[i] = rand() % (MAX - 1 + 1) + 1;
	return arrays;
}

void insert_test()
{
	int test[10] = { 2,9,100,30,11,89,66,22,5 };
	insert_sort(test, 10);
	printf("insert sort result:\n");
	for (int i = 0; i < 10; i++)
		printf("%d ", test[i]);
	printf("\n---------------------------------------------------\n");
}

void merge_test()
{
	int test1[10] = { 88,9,20,1,67,14,22,23,90,77 };
	int test2[11] = { 69,3,45,99,13,12,7,81,33,25,66 };
	merge_sort(test1, 10);
	merge_sort(test2, 11);
	printf("merge sort result:\n");
	printf("input even count numbers' result:\n");
	for (int i = 0; i < 10; i++)
		printf("%d ", test1[i]);
	printf("\ninput odd count numbers' result:\n");
	for (int i = 0; i < 11; i++)
		printf("%d ", test2[i]);
	printf("\n---------------------------------------------------\n");
}

void count_test()
{
	int test[10] = { 88,29,100,90,77,23,99,34,56,78 };
	count_sort(test, 10);
	printf("count sort result:\n");
	for (int i = 0; i < 10; i++)
		printf("%d ", test[i]);
	printf("\n---------------------------------------------------\n");
}

void quick_test()
{
	int test[10] = { 66,8,90,33,23,41,69,300,91,8 };
	int test1[10] = { 66,8,90,33,23,41,69,300,91,8 };
	quick_sort(test, 10);
	printf("quick sort result:\n");
	for (int i = 0; i < 10; i++)
		printf("%d ", test[i]);
	printf("\n---------------------------------------------------\n");
	random_quick_sort(test1, 10);
	printf("\nrandom quick sort result:\n");
	for (int i = 0; i < 10; i++)
		printf("%d ", test1[i]);
	printf("\n---------------------------------------------------\n");
}

void radix_test()
{
	int test[10] = { 332,897,432,567,325,13,67,889,223,225 };
	radix_sort(test, 10);
	printf("radix sort result:\n");
	for (int i = 0; i < 10; i++)
		printf("%d ", test[i]);
	printf("\n---------------------------------------------------\n");
}

void bucket_test()
{
	int test[20] = { 238,711,899,13,90,676,233,563,432,278,356,654,786,998,478,111,901,342,654,489 };
	bucket_sort(test, 20);
	printf("bucket sort result:\n");
	for (int i = 0; i < 20; i++)
		printf("%d ", test[i]);
	printf("\n---------------------------------------------------\n");
}

double insert_sort(int* arrays, int length)
{
	clock_t start, end;
	start = clock();
	for (int i = 1; i < length; i++)
	{
		int temp = arrays[i];
		int j;
		for (j = i - 1; j >= 0 && arrays[j] > temp; j--)
			arrays[j + 1] = arrays[j];
		arrays[j + 1] = temp;
	}
	end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}

double merge_sort(int* arrays, int length)
{
	clock_t start, end;
	start = clock();
	int* temp = (int*)malloc(sizeof(int)*length);
	merge(temp, arrays, 0, length - 1);
	free(temp);
	end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}

void merge(int* temp, int* arrays, int stt, int end)
{
	if (stt >= end)
		return;
	int len = (end - stt) / 2;
	int stt1 = stt, end1 = stt1 + len, stt2 = end1 + 1, end2 = end;

	merge(temp, arrays, stt1, end1);
	merge(temp, arrays, stt2, end2);

	int n = stt;
	while (stt1 <= end1 && stt2 <= end2)
		temp[n++] = arrays[stt1] < arrays[stt2] ? arrays[stt1++] : arrays[stt2++];
	while (stt1 <= end1)
		temp[n++] = arrays[stt1++];
	while (stt2 <= end2)
		temp[n++] = arrays[stt2++];

	for (int i = stt; i <= end; i++)
		arrays[i] = temp[i];
}

double count_sort(int * arrays, int length)
{
	clock_t start, end;
	start = clock();
	int* sorted_array = (int*)malloc(sizeof(int)*length);
	int max = arrays[0];
	for (int i = 1; i < length; i++)
		if (arrays[i] > max) max = arrays[i];
	int *count_arr = (int*)malloc(sizeof(int) * (max + 1));
	for (int i = 0; i < (max + 1); i++)
		count_arr[i] = 0;
	for (int i = 0; i < length; i++)
	{
		count_arr[arrays[i]]++;
		sorted_array[i] = 0;
	}		
	for (int i = 1; i < max; i++)
		count_arr[i] += count_arr[i - 1];
	for (int j = length; j > 0; j--)
		sorted_array[--count_arr[arrays[j - 1]]] = arrays[j - 1];
	for (int i = 0; i < length; i++)
		arrays[i] = sorted_array[i];
	free(count_arr);
	free(sorted_array);
	end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}

double quick_sort(int* arrays, int length)
{
	clock_t start, end;
	start = clock();
	quick(arrays, 0, length - 1);
	end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}

void quick(int* arrays, int stt, int end)
{
	if (stt >= end)
		return;
	int q = (stt + end) / 2, mid = arrays[q], p = stt-1;
	
	for (int i = stt; i <= end; i++)
	{
		if (i == q)
			continue;
		if (arrays[i] <= mid)
		{
			p++;
			if (p != i)
				swap(&arrays[i], &arrays[p]);
		}
	}

	int index = q <= p ? p : p + 1;

	swap(&arrays[q], &arrays[index]);

	quick(arrays, stt, index - 1);
	quick(arrays, index + 1, end);
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

double random_quick_sort(int * arrays, int length)
{
	clock_t start, end;
	start = clock();
	random_quick(arrays, 0, length - 1);
	end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}

void random_quick(int* arrays, int stt, int end)
{
	if (stt >= end)
		return;
	srand((unsigned)time(NULL));
	int q = rand() % (end - stt + 1) + stt, mid = arrays[q], p = stt - 1;

	for (int i = stt; i <= end; i++)
	{
		if (i == q)
			continue;
		if (arrays[i] <= mid)
		{
			p++;
			if (p != i)
				swap(&arrays[i], &arrays[p]);
		}
	}

	int index = q <= p ? p : p + 1;

	swap(&arrays[q], &arrays[index]);

	quick(arrays, stt, index - 1);
	quick(arrays, index + 1, end);
}

double radix_sort(int* arrays, int length)
{
	clock_t start, end;
	start = clock();
	int* temp = (int*)malloc(sizeof(int)*length);
	int exp = 1, max = arrays[0], bucket[10] = { 0 };
	temp[0] = 0;
	
	for (int i = 1; i < length; i++)
	{
		if (arrays[i] > max)
			max = arrays[i];
		temp[i] = 0;
	}
		
	while (max / exp > 0)
	{
		for (int i = 0; i < length; i++)
			bucket[(arrays[i] / exp) % 10]++;
		for (int i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];
		for (int i = length - 1; i >= 0; i--)
			temp[--bucket[(arrays[i] / exp) % 10]] = arrays[i];
		for (int i = 0; i < length; i++)
			arrays[i] = temp[i];
		for (int i = 0; i < 10; i++)
			bucket[i] = 0;
		exp *= 10;
	}
	free(temp);
	end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}

double bucket_sort(int* arrays, int length)
{
	clock_t start, end;
	start = clock();
	listNode bucket[BUCKET_COUNT];
	for (int i = 0; i < BUCKET_COUNT; i++)
		bucket[i] = createNode(0);
	int max = arrays[0];
	for (int i = 1; i < length; i++)
		if (arrays[i] > max) max = arrays[i];
	for (int i = 0; i < length; i++)
	{
		int index = arrays[i] / (max / (BUCKET_COUNT - 1));
		listNode temp = bucket[index];
		if (temp->next == NULL)
			temp->next = createNode(arrays[i]);
		else
		{
			while (temp->next != NULL && temp->next->data < arrays[i])
				temp = temp->next;
			addNode(temp, arrays[i]);
		}
	}
	int count = 0;
	for (int i = 0; i < BUCKET_COUNT; i++)
	{
		listNode tmp = bucket[i];
		while (tmp->next!=NULL)
		{
			arrays[count++] = tmp->next->data;
			tmp = tmp->next;
		}
		clearList(bucket[i]);
	}
	end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}


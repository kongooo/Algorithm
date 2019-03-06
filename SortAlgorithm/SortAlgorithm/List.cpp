#include<stdio.h>
#include<malloc.h>
#include"header.h"

listNode createNode(int num)
{
	listNode node = (listNode)malloc(sizeof(struct theNode));
	node->data = num;
	node->next = NULL;
	return node;
}

void addNode(listNode list, int num)
{
	listNode newNode = (listNode)malloc(sizeof(struct theNode));
	newNode->data = num;
	listNode nextNode = list->next;
	list->next = newNode;
	newNode->next = nextNode;
}

void clearList(listNode list)
{
	while (list->next!=NULL)
	{
		listNode temp = list;
		list = list->next;
		free(temp);
	}
}
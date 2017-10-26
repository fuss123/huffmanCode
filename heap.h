#ifndef HEAP_H
#define HEAP_H

#include "data.h"

typedef struct TreeNode {
	Data data;
	char code[20];
	struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;
typedef struct Element {
	TreeNode *root;
	int frequency;
}Element;
typedef struct MinHeap {
	Element *element;
	int heapSize;
}MinHeap;

void initHeap(MinHeap *heap);
void preorderTraversal(TreeNode *root);
TreeNode *huffmanTree(Data *dataArr, int *totalNumOfData);
void compareMemUsageFixedLen(TreeNode *root, int *totalNumOfData);
void encoding(TreeNode *root, char *buff, char character);

#endif
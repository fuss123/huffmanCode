#include "heap.h"

void initHeap(MinHeap *heap) 
{
	heap->heapSize = 0;
}

void pushDataToHeap(MinHeap *heap, Element *item) {
	int index = ++(heap->heapSize);

	while ((index != 1) && item->frequency < heap->element[index / 2].frequency)
	{
		heap->element[index] = heap->element[index / 2];
		index /= 2;
	}

	heap->element[index] = *item;
}

Element popDataFromHeap(MinHeap *heap) 
{
	int parent = 1, child = 2;
	Element item = heap->element[1];
	Element tmp = heap->element[(heap->heapSize)--];
	
	while (child <= heap->heapSize) 
	{
		if ((child < heap->heapSize) && heap->element[child].frequency > heap->element[child + 1].frequency)
			child++;
		if (tmp.frequency <= heap->element[child].frequency)
			break;

		heap->element[parent] = heap->element[child];
		parent = child;
		child *= 2;
	}

	heap->element[parent] = tmp;
	return item;
}

TreeNode *makeTree(TreeNode *left, TreeNode *right) 
{
	TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (newNode == NULL) { fprintf(stderr, "memory allocation failure!"); exit(-1); }

	newNode->left = left;
	newNode->right = right;
	myStringCopy(newNode->code, "");

	return newNode;
}

void castIntegerToString(char *tmp, int integer) 
{
	int intArr[10] = { 0 }, endIndex = 0, i = 0;
	
	while (integer) 
	{
		intArr[endIndex++] = integer % 10;
		integer /= 10;
	}

	for (i = endIndex - 1; i >= 0; i--) 
	{
		switch (intArr[i]) 
		{
		case 0: myStringCat(tmp, "0"); break;   
		case 1: myStringCat(tmp, "1"); break;
		case 2: myStringCat(tmp, "2"); break;
		case 3: myStringCat(tmp, "3"); break;
		case 4: myStringCat(tmp, "4"); break;
		case 5: myStringCat(tmp, "5"); break;
		case 6: myStringCat(tmp, "6"); break;
		case 7: myStringCat(tmp, "7"); break;
		case 8: myStringCat(tmp, "8"); break;
		case 9: myStringCat(tmp, "9"); 
		}
	}
}

void make_Wshape_DataWord(char *tmp, int *index) 
{
	myStringCopy(tmp, "W-");
	castIntegerToString(tmp, *index);
}

void addCodeData(TreeNode *root)
{
	if (root->left)
	{
		myStringCat(root->left->code, myStringCat_returnNewStringVer(root->code, "1"));
		addCodeData(root->left);
	}

	if (root->right)
	{
		myStringCat(root->right->code, myStringCat_returnNewStringVer(root->code, "0"));
		addCodeData(root->right);
	}

	if (root->left == NULL && root->right == NULL) return;
}

void printHeap(MinHeap *heap) 
{
	int i = 0;

	for (i = 1; i <= heap->heapSize; i++) 
		fprintf_s(stdout, "%s ", heap->element[i].root->data.word);

	fputs("\n", stdout);
}

void preorderTraversal(TreeNode *root)
{
	if (root == NULL) return;

	fprintf_s(stdout, "data->%-4s    count->%-3d    newCode->%-s\n", root->data.word, root->data.frequency, root->code);

	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

TreeNode *huffmanTree(Data *dataArr, int *totalNumOfData) 
{
	TreeNode *node = NULL, *sumNode = NULL;
	Element tmp = { 0 }, min1 = { 0 }, min2 = { 0 };
	MinHeap heap;
	int i = 0;
	char buff[10] = { 0 };

	initHeap(&heap);
	heap.element = (Element*)malloc(sizeof(Element) * *totalNumOfData);
	heap.element[0].root = NULL;
	heap.element[0].frequency = 0;
	
	for (i = 0; i < *totalNumOfData; i++) 
	{
		node = makeTree(NULL, NULL);
		node->data = dataArr[i];
		tmp.frequency = node->data.frequency;
		tmp.root = node;

		pushDataToHeap(&heap, &tmp);
		printHeap(&heap);
	}

	for (i = 1; i < *totalNumOfData; i++) 
	{
		min1 = popDataFromHeap(&heap);
		min2 = popDataFromHeap(&heap);
		
		sumNode = makeTree(min1.root, min2.root);
		sumNode->data.frequency = min1.frequency + min2.frequency;
		make_Wshape_DataWord(buff, &i);
		myStringCopy(sumNode->data.word, buff);

		tmp.frequency = sumNode->data.frequency;
		tmp.root = sumNode;
		pushDataToHeap(&heap, &tmp);
		printHeap(&heap);
	}

	tmp = popDataFromHeap(&heap);
	addCodeData(tmp.root);
	return tmp.root;
}

void memoryUsageOfHuffmanCode(TreeNode *root, int *res) 
{
	if (root == NULL) return;

	if (root->data.word[0] != 'W' && root->data.word[1] != '-') 
	{
		fprintf_s(stdout, "%s -> %s\n", root->data.word, root->code);
		*res = *res + root->data.frequency * myStringLength(root->code);
	}

	memoryUsageOfHuffmanCode(root->left, res);
	memoryUsageOfHuffmanCode(root->right, res);
}

void compareMemUsageFixedLen(TreeNode *root, int *totalNumOfData) 
{
	int fixedLength = 0, res = 0;
	
	memoryUsageOfHuffmanCode(root, &res);
	fprintf_s(stdout, "\nMemory usage of huffman code -> %-4d bit\n", res);

	res = 1;
	for (fixedLength = 1; ; fixedLength++) 
	{
		res *= 2;
		if (res >= *totalNumOfData)
			break;
	}
	
	fprintf_s(stdout, "Memory usage of fixed-length code -> %-4d bit\n", fixedLength * root->data.frequency);
}

void encoding(TreeNode *root, char *buff, char character) 
{
	if (root == NULL) return;

	if (root->data.word[1] != '-' && character == root->data.word[0]) 
	{
		myStringCat(buff, root->code);
		return;
	}

	encoding(root->left, buff, character);
	encoding(root->right, buff, character);
}
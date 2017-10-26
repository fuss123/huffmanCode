#include "fileIO.h"

int main(void) 
{
	FILE *input = NULL, *output = NULL;
	Data *dataArr = NULL;
	TreeNode *root = NULL;
	int totalNumOfData = 0;

	dataArr = loadingDataFromFile(input, &totalNumOfData);

	fputs("\n********** Data is being inserted and deleted from the heap...\n\n", stdout);
	root = huffmanTree(dataArr, &totalNumOfData);

	fputs("\n********** Huffman Tree\n\n", stdout);
	preorderTraversal(root);

	fputs("\n********** Huffman Code\n\n", stdout);
	compareMemUsageFixedLen(root, &totalNumOfData);

	huffmanEncoding(input, output, root);
	huffmanDecoding(input, output, root);

	free(dataArr);
	return 0;
}
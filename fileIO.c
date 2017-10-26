#include "fileIO.h"

int getTotalNumOfData(FILE *input) 
{
	int totalNumOfData = 0;

	fputs("Enter the total number of data -> ", stdout);
	fscanf_s(input, " %d", &totalNumOfData);
	fprintf_s(stdout, "%d\n\n", totalNumOfData);
	
	return totalNumOfData;
}

boolean checkCharacterOverlapping(Data *dataArr, Data *item, int *index) 
{
	int i = 0;

	for (i = 0; i < *index; i++) 
	{
		if (myStringCompare(item->word, dataArr[i].word) == TRUE)
			return TRUE;
	}

	return FALSE;
}

void getData(FILE *input, Data *dataArr, int *totalNumOfData) 
{
	Data item = { 0 };
	int i = 0;
	
	for (i = 0; i < *totalNumOfData; i++) 
	{
		fputs("Enter character data -> ", stdout);
		fscanf_s(input, " %s", item.word, sizeof(item.word));
		fprintf_s(stdout, "%s\n", item.word);

		fputs("Enter frequency data -> ", stdout);
		fscanf_s(input, " %d", &item.frequency);
		fprintf_s(stdout, "%d\n", item.frequency);

		if (checkCharacterOverlapping(dataArr, &item, &i) == FALSE)
			dataArr[i] = item;
		else
			(*totalNumOfData)--;
	}
}

Data *loadingDataFromFile(FILE *input, int *totalNumOfData) 
{
	Data *dataArr = NULL;

	fputs("********** Huffman Code Generator\n\n", stdout);
	fopen_s(&input, "word list.txt", "rt");
	if (input == NULL) { fprintf(stderr, "file open failure!"); exit(-1); }

	*totalNumOfData = getTotalNumOfData(input);
	dataArr = (Data*)malloc(sizeof(Data) * *totalNumOfData);
	getData(input, dataArr, totalNumOfData);

	fclose(input);
	return dataArr;
}

void huffmanEncoding(FILE *input, FILE *output, TreeNode *root) 
{
	char txt[1024] = { 0 };
	char buff[1024] = { 0 };
	int i = 0;

	fopen_s(&input, "text.txt", "rt");
	if (input == NULL) { fprintf(stderr, "file open failure!"); exit(-1); }

	fputs("\n***** The string contained in \"text.txt\" -> Huffman encoding to save \"code.txt\"\n", stdout);
	fscanf_s(input, " %s", txt, sizeof(txt));
	fclose(input);

	fopen_s(&output, "code.txt", "wt");
	if (output == NULL) { fprintf(stderr, "file open failure!"); exit(-1); }

	for (i = 0; i < myStringLength(txt); i++)
		encoding(root, buff, txt[i]);
	fprintf_s(output, "%s", buff);
	
	fprintf_s(stdout, "-> %s\n-> %s\n", txt, buff);
	fclose(output);
}

void huffmanDecoding(FILE *input, FILE *output, TreeNode *root) 
{
	TreeNode *p = root;
	char code[1024] = { 0 };
	char buff[1024] = { 0 };
	int i = 0;

	fopen_s(&input, "code.txt", "rt");
	if (input == NULL) { fprintf(stderr, "file open failure!"); exit(-1); }

	fputs("\n***** The string contained in \"code.txt\" -> Huffman encoding to save \"text.txt\"\n", stdout);
	fscanf_s(input, " %s", code, sizeof(code));
	fclose(input);

	fopen_s(&output, "text.txt", "wt");
	if (output == NULL) { fprintf(stderr, "file open failure!"); exit(-1); }

	for (i = 0; i < myStringLength(code); i++) 
	{
		if (code[i] == '1') p = p->left;
		else if (code[i] == '0') p = p->right;

		if (p->left == NULL && p->right == NULL) 
		{
			myStringCat(buff, p->data.word);
			p = root;
		}
	}

	fprintf_s(output, "%s", buff);
	fprintf_s(stdout, "-> %s\n-> %s\n\n", code, buff);
	fclose(output);
}
#ifndef FILE_IO_H
#define FILE_IO_H

#include "heap.h"

Data *loadingDataFromFile(FILE *input, int *totalNumOfData);
void huffmanEncoding(FILE *input, FILE *output, TreeNode *root);

#endif
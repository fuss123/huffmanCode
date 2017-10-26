#include "stringFunc.h"

int myStringLength(char *string) 
{
	int len = 0;

	while (*(string + len))
		len++;

	return len;
}

boolean myStringCompare(char *first, char *second) 
{
	while (*first == *second) 
	{
		if (*first == '\0' || *second == '\0')
			break;

		first++;
		second++;
	}

	return (*first == '\0' && *second == '\0') ? TRUE : FALSE;
}

void myStringCopy(char *target, char *source) 
{
	while (*source) 
	{
		*target = *source;
		source++;
		target++;
	}

	*target = '\0';
}

void myStringCat(char *original, char *add)
{
	while (*original)
		original++;

	while (*add)
	{
		*original = *add;
		add++;
		original++;
	}

	*original = '\0';
}

char *myStringCat_returnNewStringVer(char *orignal, char *add) 
{
	char buff[1024] = { 0 };

	myStringCopy(buff, orignal);
	myStringCat(buff, add);

	return buff;
}
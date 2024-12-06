#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getArray(unsigned char *buffer, unsigned char *arr, unsigned char *length)
{
	const char delimeter[] = " ";
	char *token;
	char i = 0;
	
	token = strtok(buffer, delimeter); 
	while (token != NULL) 
	{ 
		sscanf(token, "%d", &(arr[i++]));
		token = strtok(NULL, delimeter);
	}
	*length = i;
}

char isIncreasingOrDecreasing(unsigned char *arr, unsigned char length, char isIncreasing)
{
	char i;
	// we will get length - 1
	for (i = 0; i < length - 1; i++)
	{
		if (arr[i] == arr[i + 1])
			return 0;
		if (!isIncreasing)
		{
			if (arr[i] < arr[i + 1])
			{
				return 0; // false/unsafe
			}
		}
		else
		{
			if (arr[i] > arr[i + 1])
			{
				return 0; // false/unsafe
			}
		}
	}
	return 1; // true/safe
}

char isSafeRow(unsigned char *arr, unsigned char length)
{
	char isIncreasing = isIncreasingOrDecreasing(arr, length, 1);
	char isDecreasing = isIncreasingOrDecreasing(arr, length, 0);
	
	// if they are both set it will will be false, true otherwise
	if (isIncreasing ^ isDecreasing)
	{
		char i;
		for (i = 0; i<length-1; i++)
		{
			unsigned short difference = abs(arr[i] - arr[i+1]);
			if (!(difference >= 1 && difference <= 3))
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

int main()
{
	FILE *filePtr = fopen("C:/Users/jacob/Desktop/AoC2024/adventOfCode2024/2/input.txt", "r");
	if (filePtr == NULL)
		return -1;
	unsigned char bufferLength = 25; 
	char buffer[bufferLength];
	unsigned char *arr = (unsigned char *)malloc(bufferLength * sizeof(unsigned char)); 
	int count = 0;
	unsigned char length = 0;
	while(fgets(buffer, bufferLength, filePtr))
	{
		getArray(buffer, arr, &length);
		if (isSafeRow(arr, length))
			count++;		
	}
	
	printf("%d", count);					
	free(arr);
	return 0;
}

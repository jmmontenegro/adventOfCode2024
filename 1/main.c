#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getArrays(char *buffer, unsigned int lineCount, unsigned int *arr1, unsigned int *arr2)
{
	const char delimeter[] = " ";
	char *token1, *token2;
	
	token1 = strtok(buffer, delimeter);
	token2 = strtok(NULL, delimeter);
	
	sscanf(token1, "%d", &(arr1[lineCount]));
	sscanf(token2, "%d", &(arr2[lineCount]));	
}

void merge(unsigned int *arr, unsigned int left, unsigned int mid, unsigned int right)
{
	unsigned int size1 = mid - left + 1;
	unsigned int size2 = right - mid;
	
	unsigned int tempL[size1], tempR[size2];
	
	unsigned int i, j, k = left;
	
	for (i = 0; i < size1; i++)
		tempL[i] = arr[left + i];
	for (j = 0; j < size2; j++)
		tempR[j] = arr[mid + 1 + j];
	
	
	i = 0, j = 0;	
	while(i < size1 && j < size2)
	{
		if (tempL[i] <= tempR[j])
		{
			arr[k] = tempL[i];
			i++;
		} 
		else 
		{
			arr[k] = tempR[j];
			j++;
		}
		k++;
	}
	
	while(i < size1)
	{
		arr[k] = tempL[i];
		i++;
		k++;
	}
	
	while(j < size2)
	{
		arr[k] = tempR[j];
		j++;
		k++;
	}
}

void mergeSort(unsigned int *arr, unsigned int left, unsigned int right)
{
	if (left < right) 
	{
		unsigned int mid = left + (right - left) / 2;
		
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

unsigned int getSimilarityScore(unsigned int number, unsigned int *arr)
{
	unsigned int i, occurences = 0;
	
	for (i = 0; i < 1000; i++)
	{	
		if (number == *(arr+i))
			occurences++;
	}
	return number * occurences;
}

int main()
{
	FILE *filePtr = fopen("//vdi-ntfile01/UserProfiles/JacobM/Desktop/AoC_2024/1/input.txt", "r");
	if (filePtr == NULL)
		return -1;
	unsigned char bufferLength = 255; 
	char buffer[bufferLength];
	unsigned int capacity = 1000, lineCount = 0;
	unsigned int *arr1 = (unsigned int *)malloc(capacity * sizeof(unsigned int)); 
	unsigned int *arr2 = (unsigned int *)malloc(capacity * sizeof(unsigned int));
	
	// get arrays
	while(fgets(buffer, bufferLength, filePtr))
	{
		getArrays(buffer, lineCount, arr1, arr2);
		lineCount++;
	}
	
	// sort arrays
	mergeSort(arr1, 0, capacity - 1);
	mergeSort(arr2, 0, capacity - 1);
	
	// PART 1: get total distance
	int i, difference;
	unsigned int totalDistance = 0;
	
	for (i = 0; i < capacity; i++)
	{	
		
		difference = abs(*(arr1 + i) - *(arr2 + i));
		totalDistance += difference;
	}
	printf("%d\n", totalDistance);
	
	// PART 2: get similarity score	
	unsigned int totalSimilarityScore = 0;
	
	for (i = 0; i < capacity; i++)
	{	
		totalSimilarityScore += getSimilarityScore(*(arr1 + i), arr2);
	}
	
	printf("%d\n", totalSimilarityScore);
	
	// clean up
	free(arr1);
	free(arr2);
    return 0;
}



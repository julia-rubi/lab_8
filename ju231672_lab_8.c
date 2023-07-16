// Julianna Diaz
// COP 3502
// Professor Torosdalgi
// 15 July 2023


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Function to swap the values in heapify
void swap(int *a, int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

// Function to merge arrays together
void merge_function(int arr[], int left, int middle, int right){

  // Creates sizes for the left and right arrays
  int size_1 = middle - left + 1;
  int size_2 = right - middle;

  // Creates temp arrays to hold values
  int *left_arr = (int*)malloc(size_1*sizeof(int));
  int *right_arr = (int*)malloc(size_2*sizeof(int));

  // For loop to copy data into left temp array
  for(int i = 0; i < size_1; i++){
    left_arr[i] = arr[left + 1];
  }
  // For loop to copy data into right temp array
  for(int j = 0; j < size_2;j++){
    right_arr[j] = arr[middle + 1 + j];
  }

  // Counter variables used for indexes
  int i = 0;
  int j = 0;
  // Variable that holds first index of merged array
  int k = left;

  // While loop to merge arrays together
  while(i<size_1 && j < size_2){

    // Runs if element 1 is in its correct place
    if(left_arr[i] <= right_arr[j])
      arr[k++] = left_arr[i++];
    else
      arr[k++] = right_arr[j++];
  }
  // While loop to update left array and continue adding
  while(i < size_1)
    arr[k++] = left_arr[i++];

  // While loop to update right array and continue adding
  while(j < size_2)
    arr[k++] = right_arr[j++];

  // Frees space from temp arrays
  free(left_arr);
  free(right_arr);  
}

// Function that heapifys the array
void heapify(int arr[], int n, int i){

  // Initalizes counter variables
  int largest, left, right;
  // Makes largest equal to the root 
  largest = i;
  // Finds the left and right 
  left = 2 * i + 1;
  right = 2 * i + 2;

  // Checks to see if the left is larger than the root
  if(left < n && arr[left] > arr[largest])
    largest = left;
  // Checks if the right is larger than the root
  else if(right < n && arr[right] > arr[largest])
    largest = right;
  // Checks if the largest number is not equal to the root
  else if(largest != i){
    swap(&arr[i], &arr[largest]);
    heapify(arr, n, largest);
  }
  
}
// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
  // For loop that builds the max heap
  for(int i = n/2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  // For loop that swaps the array contents and heapifys root element
  for(int i = n -1; i > 0; i--){
    swap(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  }
  
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
  // Initalizes middle variable
  int middle;
  // Runs if the left is smaller than the right
  if(l < r){
    // Calculates the middle of the array
    middle = l + (r-l)/2;
    // Sorts the array by splitting them in half
    mergeSort(pData, l, middle);
    mergeSort(pData, middle + 1, r);
    merge_function(pData, l, middle, r);
  }
  // runs if right is larger than left
  else
    return;
}
// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");

    int* extraMemoryAllocated = (int*)malloc(sizeof(dataSz-1)*sizeof(int));
    
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",(dataSz-1)*sizeof(int));
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",(dataSz-1)*sizeof(int));
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
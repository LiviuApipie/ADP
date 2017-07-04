#include <io.h>
#include <malloc.h>
#include <cuda.h>
#include <stdlib.h>
#include <stdio.h>
#include <cuda_runtime.h>

#define n 10

__global__ void quickSort(int arr[], int left, int right);

int main(){

	int index;
	int size;
	size = n * sizeof(int);
	// Allocate input vector h_arr in host memory

	int* h_arr = (int*)malloc(size); 
	
	//// Allocate vector d_arr in device memory
	int* d_arr;
	cudaMalloc(&d_arr, size); 

	for(index=0;index<n;index++){
		printf("enter the %d number from arr",index);
		scanf("%d",&h_arr[index]);
	}

		// Copy vector from host memory to device memory

	cudaMemcpy(d_arr, h_arr, size, cudaMemcpyHostToDevice); 

	//// Kernel invocation with one block of N * N * 1 threads
	//and modifying the host code by replacing the <<<...>>> syntax introduced in Kernels 

	// Invoke kernel
	quickSort <<< 1, n >>>(d_arr, 0, n-1);
	 
	// Copy result from device memory to host memory // h_C contains the result in host memory
    //<<<blocksPerGrid, threadsPerBlock>>>
	cudaMemcpy(h_arr, d_arr, size, cudaMemcpyDeviceToHost);

	 // Free device memory
	cudaFree(d_arr);

}


 __global__ void quickSort(int arr[], int left, int right) {
	 
if (left >= right || left < 0 || right >= n) {
			return;
		}
if (right - left < n) {
	for (int i = left; i <= right; i++) {
		int tmp = arr[i];
		int j = i;
		for (; j > 0 && tmp < arr[j - 1]; j--)
			arr[j]= arr[j - 1];
			arr[j] = tmp;
			
		}
		return;
	}
	int pivotIdx = (right + left) / 2;
	int pivot = arr[pivotIdx];
	int i = left;
	int j = right;

	while (i < j) {
		while (arr[i] < pivot)
			i++;
			while (arr[j] > pivot)
				j--;
			if (i >= j)
				break;
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			
		}
		quickSort<<< 1, n >>>(arr, left, i - 1);
		
		quickSort<<< 1, n >>>(arr, i + 1, right);
		
}

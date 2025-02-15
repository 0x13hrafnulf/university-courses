/*******************************************************************************
*
*   This is the code from Chapter 3 of CUDA by Example illustrating how
*   vector addition is accomplished by the GPU.
*
*   compile with:
*     > nvcc vectorAdd_gpu.cu
*
*******************************************************************************/
#include <stdio.h>

/******************************************************************************/
// KERNEL TO RUN ON THE GPU:
__global__ void addGPU(int *a, int *b, int *c, int vecSize)
{
  int tid = blockIdx.x;         // get thread ID (tid) from the kernel
  if (tid < vecSize){           // only process memory that has been allocated
    c[tid] = a[tid] + b[tid];   // do addition based on memory location
  }
}

/******************************************************************************/
int main(void)
{

  int vecSize = 10; // set size of vectors to add (play with this)
  int intSize = sizeof(int); // get size in bytes of an int on this system

  // allocate memory on CPU (host) for three arrays
  int a[vecSize], b[vecSize], c[vecSize];

  // fill the host memory with numbers
  for (int i = 0; i < vecSize; i++) {
      a[i] = -i;
      b[i] = i * i;
      c[i] = 0;
  }

  // print what is stored in host memory
  printf("before GPU processing:\n");
  for (int i=0; i<vecSize; i++) {
    printf( "%d + %d = %d\n", a[i], b[i], c[i] );
  }

  // allocate memory on the GPU (device)
  int *dev_a, *dev_b, *dev_c;
  cudaMalloc((void**)&dev_a, intSize*vecSize);
  cudaMalloc((void**)&dev_b, intSize*vecSize);
  cudaMalloc((void**)&dev_c, intSize*vecSize);

  // copy vector a and vector b from host (CPU) memory to device (GPU) memory
  cudaMemcpy(dev_a, a, intSize*vecSize, cudaMemcpyHostToDevice);
  cudaMemcpy(dev_b, b, intSize*vecSize, cudaMemcpyHostToDevice);

  // launch needed number of threads on the GPU, each doing vector addition
  int numBlocks = vecSize;
  int threadsPerBlock = 1;
  addGPU <<< numBlocks, threadsPerBlock >>> (dev_a, dev_b, dev_c, vecSize);

  // copy thre result from device (GPU) memory to host (CPU) memory
  cudaMemcpy(c, dev_c, intSize*vecSize, cudaMemcpyDeviceToHost);

  // be a good citizen and release allocated memory on the device (GPU)
  cudaFree(dev_a);
  cudaFree(dev_b);
  cudaFree(dev_c);

  // print what is now stored in host memory
  printf("\nafter GPU processing:\n");
  for (int i=0; i<vecSize; i++) {
    printf( "%d + %d = %d\n", a[i], b[i], c[i] );
  }

return 0;
}

/******************************************************************************/

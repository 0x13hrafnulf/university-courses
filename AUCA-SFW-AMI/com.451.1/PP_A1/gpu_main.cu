/**************************************************************************
*
*  NOTES ABOUT PROGRAM GO HERE
*
**************************************************************************/

#include <cuda.h>
#include <stdio.h>
#include "gpu_main.h"

/*************************************************************************/
void FuncGPU(int *a, float *b, unsigned long vecSize){
  int intSize = sizeof(int);
  int floatSize = sizeof(float);

  int *dev_a;
  float *dev_b;
  cudaMalloc((void**)&dev_a, intSize*vecSize);
  cudaMalloc((void**)&dev_b, floatSize*vecSize);

  // copy vector a and vector b from host (CPU) memory to device (GPU) memory
  cudaMemcpy(dev_a, a, intSize*vecSize, cudaMemcpyHostToDevice);
  cudaMemcpy(dev_b, b, floatSize*vecSize, cudaMemcpyHostToDevice);
  // launch needed number of threads on the GPU, each doing vector addition
  int numBlocks = vecSize;
  int threadsPerBlock = 1;
  func <<< numBlocks, threadsPerBlock >>> (dev_a, dev_b, vecSize);

  // copy thre result from device (GPU) memory to host (CPU) memory
  cudaMemcpy(b, dev_b, floatSize*vecSize, cudaMemcpyDeviceToHost);

  // be a good citizen and release allocated memory on the device (GPU)
  cudaFree(dev_a);
  cudaFree(dev_b);

  // print what is now stored in host memory
}
__global__ void func(int *a, float *b, unsigned long vecSize)
{
	int tid = blockIdx.x;
	for(int N = 1; N <= a[tid]; ++N)
	{
		if(N % 2 == 0) b[tid] *= N;
		else b[tid] /= N;
	}
}

void GPUinfo()
{
	int deviceCount = 0;
	cudaGetDeviceCount(&deviceCount);
	if(deviceCount == 0)
	{
		printf("There are no available device(s) supporting CUDA");
	}
	else
	{
		printf("Detected %d CUDA capable device(s)\n", deviceCount);
	}
	for(int dev = 0; dev < deviceCount; ++dev){

		int driverVersion = 0, runtimeVersion = 0;

		cudaSetDevice(dev);
		cudaDeviceProp deviceProp;
		cudaGetDeviceProperties(&deviceProp, dev);
		printf("Device %d: \"%s\"\n", dev, deviceProp.name);

		cudaDriverGetVersion(&driverVersion);
		cudaRuntimeGetVersion(&runtimeVersion);
		printf(" CUDA Driver Version / Runtime Version %d.%d / %d.%d\n",
			driverVersion/1000, (driverVersion%100)/10,
			runtimeVersion/1000, (runtimeVersion%100)/10);
		printf(" CUDA Capability Major/Minor version number: %d.%d\n",
			deviceProp.major, deviceProp.minor);
		printf(" Total amount of global memory: %.2f MBytes (%llu bytes)\n",
			(float)deviceProp.totalGlobalMem/(pow(1024.0,3)),
			(unsigned long long) deviceProp.totalGlobalMem);
		printf(" GPU Clock rate: %.0f MHz (%0.2f GHz)\n",
			deviceProp.clockRate * 1e-3f, deviceProp.clockRate * 1e-6f);
		printf(" Memory Clock rate: %.0f Mhz\n",
			deviceProp.memoryClockRate * 1e-3f);
		printf(" Memory Bus Width: %d-bit\n",
			deviceProp.memoryBusWidth);
		if (deviceProp.l2CacheSize) {
			printf(" L2 Cache Size: %d bytes\n", deviceProp.l2CacheSize);
		}
		printf(" Max Texture Dimension Size (x,y,z)		"
			"	1D=(%d), 2D=(%d,%d), 3D=(%d,%d,%d)\n",
			deviceProp.maxTexture1D, deviceProp.maxTexture2D[0],
		deviceProp.maxTexture2D[1], deviceProp.maxTexture3D[0],
       		deviceProp.maxTexture3D[1], deviceProp.maxTexture3D[2]);

		printf(" Max Layered Texture Size (dim) x layers	1D=(%d) x %d, 2D=(%d,%d) x %d\n",
			deviceProp.maxTexture1DLayered[0], deviceProp.maxTexture1DLayered[1],
			deviceProp.maxTexture2DLayered[0], deviceProp.maxTexture2DLayered[1],
			deviceProp.maxTexture2DLayered[2]);

		printf(" Total amount of constant memory:	%lu bytes\n",
				deviceProp.totalConstMem);
		printf(" Total amount of shared memory per block: 	%lu bytes\n",
				deviceProp.sharedMemPerBlock);
		printf(" Total number of registers available per block:		%d\n",
			       	deviceProp.regsPerBlock);
		printf(" Warp size:	%d\n", deviceProp.warpSize);
		printf(" Maximum number of threads per multiprocessor:	%d\n",
		deviceProp.maxThreadsPerMultiProcessor);
		printf(" Maximum number of threads per block:	%d\n",
			deviceProp.maxThreadsPerBlock);
		printf(" Maximum sizes of each dimension of a block:	%d x %d x %d\n",
			deviceProp.maxThreadsDim[0],
			deviceProp.maxThreadsDim[1],
			deviceProp.maxThreadsDim[2]);
		printf(" Maximum sizes of each dimension of a grid:	%d x %d x %d\n",
			deviceProp.maxGridSize[0],
			deviceProp.maxGridSize[1],
			deviceProp.maxGridSize[2]);
		printf(" Maximum memory pitch:	%lu bytes\n", deviceProp.memPitch);
		printf("\n");
	}
}
	/*************************************************************************/

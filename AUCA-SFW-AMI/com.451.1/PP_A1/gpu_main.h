#ifndef GPULib
#define GPULib

#include <cuda.h>
#include <curand.h>                 // includes random num stuff
#include <curand_kernel.h>       	// more rand stuff
#include <cuda_texture_types.h>
#include <stdio.h>
#include <cuda_runtime.h>

// regular CPU function
void FuncGPU(int* a, float* b, unsigned long vecSize);

void GPUinfo();
// GPU kernel function
__global__ void func(int* a, float* b, unsigned long vecSize);


#endif  // GPULib

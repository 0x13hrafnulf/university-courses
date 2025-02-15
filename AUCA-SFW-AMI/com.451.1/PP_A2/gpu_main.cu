/**************************************************************************
*
*
*
**************************************************************************/

#include <cuda.h>

#include <stdio.h>
#include "gpu_main.h"
#include "params.h"
#include <math.h>

texture<float,2> texture_blue;

/*************************************************************************/
__global__ void updateReds(float* red, curandState* states)
{
  int x = threadIdx.x + (blockIdx.x * blockDim.x);
  int y = threadIdx.y + (blockIdx.y * blockDim.y);
  int vecIdx = x + (y * blockDim.x * gridDim.x);

  curandState randState = states[vecIdx];
  float rndNumber = curand_uniform(&randState);
  states[vecIdx] = randState;

  red[vecIdx] = (red[vecIdx] + rndNumber) / 2.0f;
}
__global__ void setup_random(curandState* states, long seed)
{
  int x = threadIdx.x + (blockIdx.x * blockDim.x);
  int y = threadIdx.y + (blockIdx.y * blockDim.y);
  int vecIdx = x + (y * blockDim.x * gridDim.x);

  curand_init(seed, vecIdx, 0, &states[vecIdx]);
}
/*************************************************************************/
__global__ void updateGreens(float* green, float sinV)
{
  int x = threadIdx.x + (blockIdx.x * blockDim.x);
  int y = threadIdx.y + (blockIdx.y * blockDim.y);
  int vecIdx = x + (y * blockDim.x * gridDim.x);


  green[vecIdx] = sinV;//(PI/180) * time --- mb use that one for test
}
/*************************************************************************/
__global__ void updateBlues(float* blue)//neighbors means 10x10 area? or just vertical and horizontal ones
{
  int x = threadIdx.x + (blockIdx.x * blockDim.x);
  int y = threadIdx.y + (blockIdx.y * blockDim.y);
  int vecIdx = x + (y * blockDim.x * gridDim.x);

  /*float sum = tex2D(texture_blue, x, y);;
  int count = 1;
  for(int i = 1; i <= 5; ++i)
  {
    sum += tex2D(texture_blue, x, y - i);//top
    sum += tex2D(texture_blue, x, y + i);//bottom
    sum += tex2D(texture_blue, x - i, y);//left
    sum += tex2D(texture_blue, x + i, y);//right
    //diagonals
    sum += tex2D(texture_blue, x - i, y - i);//
    sum += tex2D(texture_blue, x + i, y + i);//
    sum += tex2D(texture_blue, x - i, y + i);//
    sum += tex2D(texture_blue, x + i, y - i);//
    count += 8;
  }
  */
  float sum = 0.0f;
  for(int i = -5; i <= 5; ++i)
  {
    for(int j = -5; j <= 5; ++j)
    {
      if(i == 0 && j == 0) continue;
      sum += tex2D(texture_blue, x + i, y + i);
    }
  }

  blue[vecIdx] = sum / 120;
}

/*************************************************************************/
int updatePalette(GPU_Palette* P, int mode, float t){

//  do something <<< P->gBlocks, P->gThreads >>> (P->red);
  if(mode == 1)
  {
      //copy_const_kernel <<< P->gBlocks, P->gThreads >>> (P->blue);

      updateBlues <<< P->gBlocks, P->gThreads >>> (P->blue);
  }
  else if(mode == 2)
  {

    updateReds <<< P->gBlocks, P->gThreads >>> (P->red, P->theRand);
  }
  else if(mode == 3)
  {
      float sinValue = sin(t);
      updateGreens <<< P->gBlocks, P->gThreads >>> (P->green, sinValue);
  }
  return 0;
}

/*************************************************************************/
GPU_Palette initGPUPalette(AParams* PARAMS){

  // load
  GPU_Palette P;

  P.gTPB = 32;      // threads per block
  //P.gDIM = ((PARAMS->height) * (PARAMS->width)) / (32 * 32);     // assumes the image is 800x800
  P.gDIMy = PARAMS->height;
  P.gDIMx = PARAMS->width;
  // 800x800 palette = 25x25 grid of 32x32 threadblocks
  P.gSize = (P.gDIMy * P.gDIMx) * sizeof(float);// Area * float size
  long gRandSize = (P.gDIMy * P.gDIMx) * sizeof(curandState);
  P.gThreads.x = P.gTPB;
  P.gThreads.y = P.gTPB;
  P.gThreads.z = 1;         // 3D of threads allowed
  P.gBlocks.x = P.gDIMx/P.gTPB;
  P.gBlocks.y = P.gDIMy/P.gTPB;
  P.gBlocks.z = 1;          // only 2D of blocks allowed

  // allocate memory for the palette
  cudaMalloc((void**) &P.gray, P.gSize);    // black and white (avg of rgb)
  cudaMalloc((void**) &P.red, P.gSize);   // r
  cudaMalloc((void**) &P.green, P.gSize); // g
  cudaMalloc((void**) &P.blue, P.gSize);  // b

  //task 1 creating const data point to update based on time step
  cudaChannelFormatDesc desc = cudaCreateChannelDesc<float>();
  cudaBindTexture2D(NULL, texture_blue, P.blue, desc, P.gDIMx, P.gDIMy, sizeof(float) * P.gDIMx);
  //task 2, update red = avg(red + randomValueOfThread)
  cudaMalloc((void**) &P.theRand, gRandSize);
  setup_random <<<P.gBlocks, P.gThreads>>> (P.theRand, time(NULL));
  //task 3, green = sin(t)

  return P;
}


/*************************************************************************/
int freeGPUPalette(GPU_Palette* P) {

  cudaUnbindTexture(texture_blue);
  cudaFree(P->blue);
  cudaFree(P->red);
  cudaFree(P->green);
  cudaFree(P->gray);
  cudaFree(P->theRand);
  return 0;
}

/*************************************************************************/

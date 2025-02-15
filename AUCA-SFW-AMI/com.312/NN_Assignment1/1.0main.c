/**************************************************************************
*
*   SOME STARTER CODE FOR WORKING WITH NMIST, © MICHAEL BRADY 2018
*
**************************************************************************/
#include <stdio.h>
#include "randlib.h" 
#include "mnist/mnist.h"
#include <math.h>

#define imageSize 785
#define N 10

void updateWeights(float** weights)
{

}

int main(int argc, char* argv[])
{                
    // --- an example for working with random numbers
    seed_randoms();
    float sampNoise = rand_frac()/2.0; // sets default sampNoise
        
    // --- a simple example of how to set params from the command line
    if(argc == 2){ // if an argument is provided, it is SampleNoise
        sampNoise = atof(argv[1]);
        if (sampNoise < 0 || sampNoise > .5){
            printf("Error: sample noise should be between 0.0 and 0.5\n");
            return 0;
        }
    }             
        
    // --- an example for how to work with the included mnist library:
    mnist_data *zData;      // each image is 28x28 pixels
    unsigned int sizeData; // depends on loadType
    int loadType = 2; // loadType may be: 0, 1, or 2
    if (mnistLoad(&zData, &sizeData, loadType)){
        printf("something went wrong loading data set\n");
        return -1;
    } 
    
    // loadType = 0, 60k training images
    // loadType = 1, 10k testing images
    // loadType = 2, 10 specific images from training set
    printf("number of training patterns = %d\n", sizeData);

    // inspect the training samples we will work with:
    int inputVec[imageSize]; //(28*28)+1 = 785
    
    int weightSize = imageSize * N; //should be 784 * 10?? since "+1" is bias which is first element of array
    float weightVec[weightSize];

    for(int i = 0; i < weightSize; ++i)
    {
	weightVec[i] = rand_weight();    
    }
    
    float rate = 0.1f;
    float output[N];
    float Error[N];
for(int epoch = 0; epoch < 10; ++epoch){
    printf("Learning cycle: %d\n", epoch);
    for (int i = 0; i < N; i++){
	output[i] = 0.0f;
    	for(int j = 0; j < 10; j++){
        	get_input(inputVec, zData, j, sampNoise);
		//draw_input(inputVec, zData[j].label);
		for(int k = 0; k < imageSize; ++k){
			output[i] += inputVec[k] * weightVec[k*N + i];//getting output??
		}
		//squash the output using and finding error
		output[i] = (1.0/(1.0 + exp(-1.0f * output[i])));	
		Error[zData[j].label] = i == zData[j].label ? 1.0f - output[i] : 0.0f - output[i];
		printf("Number = %d\n", zData[j].label);
		for(int k = 0; k < imageSize; ++k){
			weightVec[k*N + i] += rate * inputVec[k] * Error[zData[j].label];	
		}
		printf("output[%d] = %f, error[%d] = %f\n", i, output[i], zData[j].label, Error[zData[j].label]);	
	}
	
    }
}
    free(zData);
    return 0;
}


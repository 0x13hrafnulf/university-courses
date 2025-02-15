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
#define outputSize 1 
#define NLayers 393
#define bias 1.0f
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
		int loadType = 0; // loadType may be: 0, 1, or 2
		if (mnistLoad(&zData, &sizeData, loadType)){
				printf("something went wrong loading data set\n");
				return -1;
		}

		// loadType = 0, 60k training images
		// loadType = 1, 10k testing images
		// loadType = 2, 10 specific images from training set
		printf("number of training patterns = %d\n", sizeData);

		// inspect the training samples we will work with:
		int inputVec[imageSize]; //(28*28)= 784
		float layers[NLayers];
		float WinputToLayers[NLayers * imageSize];
		float WlayersToOutput[NLayers * outputSize];//there are 785 output nodes

		float output[outputSize];
		float errorOutput[outputSize];
		float errorLayer[NLayers];


		for(int i = 0; i < NLayers * outputSize; ++i)
		{
			WinputToLayers[i] = rand_weight();
			WlayersToOutput[i] = rand_weight();
		}

		float rate = 0.1f;
		for(int epoch = 0; epoch < 10; ++epoch){
			for(int j = 0; j < sizeData; j++){//based on the size of the data loaded from minst
				get_input(inputVec, zData, j, sampNoise);//input
				//check which number
				//---Layer Nodes update from input to Layers--------------------------
				for (int i = 0; i < NLayers; i++){
					layers[i] = 0.0f;// added bias right away
					for(int k = 0; k < imageSize; ++k){//784 pixels
						layers[i] += inputVec[k] * WinputToLayers[k*NLayers + i];//getting output??
					}
					layers[i] = (1.0f/(1.0f + exp(-1.0f * (layers[i]))));//squash
				}
				layers[0] = 1.0f;//bias should be one
				//----------------------------------------------------------------------

				//---Output Nodes update from input to Layers---------------------------
				for(int i = 0; i < outputSize; ++i)//785
				{
					output[i] = 0.0f;// added bias right away
					for(int k = 0; k < NLayers; ++k){//784 pixels
						output[i] += layers[k] * WlayersToOutput[k*outputSize + i];//getting output??
					}
					output[i] = (1.0f/(1.0f + exp(-1.0f * (output[i]))));//squash
				}
				//----------------------------------------------------------------------

				//BACKPROPAGATION, ERROR--------------------------------------------------------------
				float target = zData[j].label % 2 == 0 ? 0.0f : 1.0f;
				errorOutput[0] = (target - output[0]) * output[0] * (1.0f - output[0]);
				for(int i = 1; i < outputSize; ++i)
				{
					errorOutput[i] = (inputVec[i] - output[i]) * output[i] * (1.0f - output[i]);
				}
				for(int i = 0; i < NLayers; ++i)
				{
					float sum = 0.0f;
					for(int k = 0; k < outputSize; ++k)
					{
							sum += errorOutput[k]*WlayersToOutput[i*outputSize + k];
					}
					errorLayer[i] = layers[i]*(1.0f - layers[i])*sum;
				}
				//WeightUpdate-----------------------------------------------------------------------------------
				for (int i = 0; i < NLayers; i++){
					for(int k = 0; k < outputSize; ++k){//784 pixels
						WlayersToOutput[i*outputSize + k] += rate * layers[i] * errorOutput[k];//getting output??
					}
				}

				for (int i = 0; i < imageSize; i++){
					for(int k = 0; k < NLayers; ++k){//784 pixels
						WinputToLayers[i*NLayers + k] += rate * inputVec[i] * errorLayer[k];//getting output??
					}
				}
			}
		}

		mnistLoad(&zData, &sizeData, 1);

			for(int j = 0; j < sizeData; j++){//based on the size of the data loaded from minst
				get_input(inputVec, zData, j, sampNoise);//input
				//check which number
				//---Layer Nodes update from input to Layers--------------------------
				for (int i = 0; i < NLayers; i++){
					layers[i] = 0.0f;// added bias right away
					for(int k = 0; k < imageSize; ++k){//784 pixels
						layers[i] += inputVec[k] * WinputToLayers[k*NLayers + i];//getting output??
					}
					layers[i] =  (1.0f/(1.0f + exp(-1.0f * (layers[i]))));//squash
				}
				layers[0] = 1.0f;
				//bias should be one
				//----------------------------------------------------------------------

				//---Output Nodes update from input to Layers---------------------------
				for(int i = 0; i < outputSize; ++i)//785
				{
					output[i] = 0.0f;// added bias right away
					for(int k = 0; k < NLayers; ++k){//784 pixels
						output[i] += layers[k] * WlayersToOutput[k*outputSize + i];//getting output??
					}
					output[i] = (1.0f/(1.0f + exp(-1.0f * (output[i]))));//squash
				}
				//----------------------------------------------------------------------
				printf("Number = %d\n", zData[j].label);
				printf("Output = %0.5f\n", output[0]);

			}


		free(zData);
		return 0;
}

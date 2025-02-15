/**************************************************************************
*
*           COMP 193
*           GPU programming
*           Exercise 2 template
*
**************************************************************************/
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <time.h>

#include "interface.h"
#include "gpu_main.h"
#include "params.h"
#include "animate.h"

// these needed to 'crack' the command line
int		arg_index = 0;
char	*arg_option;
char	*pvcon = NULL;


/*************************************************************************/
int main(int argc, char *argv[]){

	unsigned char ch;
  clock_t start, end;
	AParams PARAMS;

  setDefaults(&PARAMS);

  // -- get parameters that differ from defaults from command line:
  if(argc<2){usage(); return 1;} // must be at least one arg (fileName)
	while((ch = crack(argc, argv, "r|s|", 0)) != NULL) {
	  switch(ch){
    	case 'r' : PARAMS.runMode = atoi(arg_option); break;
      case 's' : PARAMS.speed = atoi(arg_option); break;
      default  : usage(); return(0);
    }
  }

  // filename of image.bmp should be last arg on command line:
  char* fileName = argv[arg_index];

  // initialize memory on the gpu

  //
	GPU_Palette P1;
  // read in the image file, write the data to the gpu:
	int err = openBMP(&PARAMS, &P1, fileName);

  // -- run the system depending on runMode
  switch(PARAMS.runMode){
      case 0: // add the numbers on the CPU
          printf("\n -- default picture in runmode 0 -- \n");
          start = clock();
          runIt(&P1, &PARAMS);
          end = clock();
          break;
			case 1: // update blue
          printf("\n -- updating blue pixels in runmode 1 -- \n");
          start = clock();
              // add some other function here...
					runIt(&P1, &PARAMS);
          end = clock();
          break;
      case 2: // update red
          printf("\n -- updating red pixels in runmode 2 -- \n");
          start = clock();
              // add some other function here...
					runIt(&P1, &PARAMS);
          end = clock();
          break;
			case 3: // update green
					printf("\n -- updating green pixels in runmode 3 -- \n");
          start = clock();
              // add some other function here...
					runIt(&P1, &PARAMS);
          end = clock();
          break;

      default: printf("no valid run mode selected\n") ;
  }

  // print the time used
  printf("time used: %.2f\n", ((double)(end - start))/ CLOCKS_PER_SEC);

return 0;
}


/**************************************************************************
                       PROGRAM FUNCTIONS
**************************************************************************/
int runIt(GPU_Palette* P1, AParams* PARAMS){

	clock_t curTime, lastTime, dtime;
	lastTime = clock();
	//time(&lastTime);
	CPUAnimBitmap animation(P1->gDIMx, P1->gDIMy, P1);
  cudaMalloc((void**) &animation.dev_bitmap, animation.image_size());
  animation.initAnimation();

	float t = 0.0f;
	float drawSpeed = 1.0f/(PARAMS->speed);
  while(1){
		//time(&curTime);
		curTime = clock();
		dtime = curTime - lastTime;
		printf("%.10f\n", dtime);

		if(dtime > drawSpeed){
			if(PARAMS->runMode > 0) int err = updatePalette(P1, PARAMS->runMode, t);//mb add speed??
    	animation.drawPalette(P1->gDIMx, P1->gDIMy, P1->gTPB);
			t += 0.1f;
			lastTime = curTime;
		}
  }

  return(0);
}

/**************************************************************************
                       PROGRAM FUNCTIONS
**************************************************************************/
// this function loads in the initial picture to process
int openBMP(AParams* PARAMS, GPU_Palette* P1, char* fileName){

// open the file
FILE *infp;
if((infp = fopen(fileName, "r+b")) == NULL){
	printf("can't open image of filename: %s\n", fileName);
  return 0;
}

// read in the 54-byte header
unsigned char header[54];
fread(header, sizeof(unsigned char), 54, infp);
PARAMS->width = *(int*)&header[18];
PARAMS->height = *(int*)&header[22];
PARAMS->size = 3 * (PARAMS->width) * (PARAMS->height);
//init GPU
*P1 = initGPUPalette(PARAMS);
// read in the data
unsigned char data[PARAMS->size];
fread(data, sizeof(unsigned char), PARAMS->size, infp);
fclose(infp);

float* graymap = (float*) malloc(P1->gSize);
float* redmap = (float*) malloc(P1->gSize);
float* greenmap = (float*) malloc(P1->gSize);
float* bluemap = (float*) malloc(P1->gSize);

for(int i = 0; i < PARAMS->size; i += 3)
{
  // flip bgr to rgb (red - green - blue)
  unsigned char temp = data[i];
  data[i] = data[i+2];
  data[i+2] = temp;

  // segregate data as floats between 0 - 1 to be written to gpu
  unsigned int graymapIdx = (int) floor(i/3.0);
  graymap[graymapIdx]   = (float) (data[i]+data[i+1]+data[i+2])/(255.0*3.0);
  redmap[graymapIdx]    = (float) data[i]/255.0;
  greenmap[graymapIdx]  = (float) data[i+1]/255.0;
  bluemap[graymapIdx]   = (float) data[i+2]/255.0;
}

// write image data to the GPU
cudaMemcpy(P1->gray, graymap, P1->gSize, cH2D);
cudaMemcpy(P1->red, redmap, P1->gSize, cH2D);
cudaMemcpy(P1->green, greenmap, P1->gSize, cH2D);
cudaMemcpy(P1->blue, bluemap, P1->gSize, cH2D);

// free CPU memory
free(graymap);
free(redmap);
free(greenmap);
free(bluemap);

return 0;
}




/**************************************************************************
                       INTERFACE HELPER FUNCTIONS
**************************************************************************/
int setDefaults(AParams *PARAMS){

    PARAMS->speed      		  = 1;
    PARAMS->runMode         = 0;

    PARAMS->height     = 800;
    PARAMS->width      = 800;
    PARAMS->size      = 800*800*3; // 800x800 pixels x 3 colors

    return 0;
}

/*************************************************************************/
int usage()
{
	printf("USAGE:\n");
	printf("-r[val] -s[val] filename\n\n");
  printf("e.g.> ex2 -r1 -s1 imagename.bmp\n");
  printf("s  speed mode, higher value -> increases speed\n");
  printf("r  run mode (0:default picture, 1:update_blue, 2:update_red, 3:update_green)\n");

  return(0);
}

/*************************************************************************/
int viewParams(const AParams *PARAMS){

    printf("--- PARAMETERS: ---\n");

    printf("run mode: %d\n", PARAMS->runMode);
		printf("processing speed: %d\n", PARAMS->speed);
    printf("image height: %d\n", PARAMS->height);
    printf("image width: %d\n", PARAMS->width);
    printf("data size: %d\n", PARAMS->size);

    return 0;
}

/*************************************************************************/
char crack(int argc, char** argv, char* flags, int ignore_unknowns)
{
    char *pv, *flgp;

    while ((arg_index) < argc){
        if (pvcon != NULL)
            pv = pvcon;
        else{
            if (++arg_index >= argc) return(NULL);
            pv = argv[arg_index];
            if (*pv != '-')
                return(NULL);
            }
        pv++;

        if (*pv != NULL){
            if ((flgp=strchr(flags,*pv)) != NULL){
                pvcon = pv;
                if (*(flgp+1) == '|') { arg_option = pv+1; pvcon = NULL; }
                return(*pv);
                }
            else
                if (!ignore_unknowns){
                    fprintf(stderr, "%s: no such flag: %s\n", argv[0], pv);
                    return(EOF);
                    }
                else pvcon = NULL;
	    	}
            pvcon = NULL;
            }
    return(NULL);
}

/*************************************************************************/

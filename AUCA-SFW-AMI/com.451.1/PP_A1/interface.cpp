/**************************************************************************
*
*
**************************************************************************/
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <time.h>
#include <thread>

#include "interface.h"
#include "gpu_main.h"

#include "crack.h"


/*************************************************************************/
int main(int argc, char *argv[]){

  unsigned char ch;
  clock_t start, end;
  AParams PARAMS;

  setDefaults(&PARAMS);

  // -- get parameters that differ from defaults from command line:
  while((ch = crack(argc, argv, "r|v|", 0)) != NULL) {
	switch(ch){
    case 'r' : PARAMS.runMode = atoi(arg_option); break;
    case 'v' : PARAMS.verbosity = atoi(arg_option); break;
    default  : usage(); return(0);
    }
  }

  // if detailed verbosity:
  if (PARAMS.verbosity == 2) viewParams(&PARAMS);

  // allocate memory on CPU for three arrays
  int a[PARAMS.vecSize];
  float b[PARAMS.vecSize];

  // fill the cpu arrays with numbers
  for (int i = 0; i < PARAMS.vecSize; i++) {
      a[i] = i+1;
      b[i] = 1.0f;
  }

  // -- run the system depending on runMode
  switch(PARAMS.runMode){
	case 0:  //Hardware information
		  if(PARAMS.verbosity)
                  	printf("\n -- GPU information -- \n");
		  GPUinfo();
      		  break;

	case 1: // add the numbers on the CPU
          	if (PARAMS.verbosity)
              		printf("\n -- running on CPU -- \n");
          	start = clock();
          	FuncCPU(a, b, PARAMS.vecSize);
          	end = clock();
          	break;
	case 2: // run GPU version
          	if (PARAMS.verbosity)
              		printf("\n -- running on GPU -- \n");
          	start = clock();
          	FuncGPU(a, b, PARAMS.vecSize);
          	end = clock();
          	break;
	case 3://multiple CPU mode
          	if (PARAMS.verbosity)
              		printf("\n -- running on multiple CPUs -- \n");
          	start = clock();
          	FuncMultiCPU(a, b, PARAMS.vecSize);
          	end = clock();
          	break;
	default: printf("no valid run mode selected\n");
  }
  if(PARAMS.runMode == 0) return 0;
  // print the time used
  printf("time used: %.2f\n", ((double)(end - start))/ CLOCKS_PER_SEC);

  // print the result if in verbose mode
  if (PARAMS.verbosity)
    for (int i=0; i<PARAMS.vecSize; i++) {
      printf( "My_Function(%d) = %.2f\n", a[i], b[i]);
    }

return 0;
}



/**************************************************************************
                       PROGRAM FUNCTIONS
**************************************************************************/
void FuncCPU(int* a, float* b, unsigned long vecSize){
	for(int i = 0; i < vecSize; ++i)
	{
		for(int N = 1; N <= a[i]; ++N)
		{
			if(N % 2 == 0) b[i] *= N;
			else b[i] /= N;
		}
	}
}

void FuncMultiCPU(int* a, float* b, unsigned long vecSize)
{
	//unsigned long const num_threads = std::thread::hardware_concurrency();
	unsigned long bound = vecSize / 4;
	std::thread t1(FuncCPU, a, b, bound);
	std::thread t2(FuncCPU, &(a[bound]), &(b[bound]), bound);
	std::thread t3(FuncCPU, &(a[bound*2]), &(b[bound*2]), bound);
	std::thread t4(FuncCPU, &(a[bound*3]), &(b[bound*3]), bound);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}
/**************************************************************************
                       INTERFACE HELPER FUNCTIONS
**************************************************************************/
int setDefaults(AParams *PARAMS){

    PARAMS->verbosity   = 1;
    PARAMS->runMode     = 1;
    PARAMS->vecSize     = 10000; // hundred thousand

    return 0;
}

/*************************************************************************/
int usage()
{
  printf("USAGE:\n");
  printf("-r[val] -v[val] \n\n");
  printf("e.g.> ex1 -r1 -v1\n");
  printf("v  verbose mode (0:none, 1:normal, 2:detailed)\n");
  printf("r  run mode (0:GPUinfo, 1:CPU, 2:GPU, 3:MultiCPU)\n");

  return(0);
}

/*************************************************************************/
int viewParams(const AParams *PARAMS){

    printf("--- PARAMETERS: ---\n");

    // verbose mode = 2 to have gotten here

    printf("run mode: %d\n", PARAMS->runMode);
    printf("vec size: %lu\n", PARAMS->vecSize);

    return 0;
}
/*************************************************************************/

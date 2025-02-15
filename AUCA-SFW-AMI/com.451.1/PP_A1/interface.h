#ifndef hInterfaceLib
#define hInterfaceLib

class AParams {
public:

  int             verbosity;
  int             runMode;
  unsigned long   vecSize;

};

void FuncCPU(int *a, float *b, unsigned long vecSize);
void FuncMultiCPU(int* a, float* b, unsigned long vecSize);

int setDefaults(AParams *PARAMS);
int usage();
int viewParams(const AParams *PARAMS);
char crack(int argc, char** argv, char* flags, int ignore_unknowns);


#endif

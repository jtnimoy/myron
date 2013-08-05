#include <stdlib.h>
#include <stdio.h>

#include "ezcam.h"

#define DLLAPI extern "C" __declspec(dllexport) 

DLLAPI int test(){
  return 69;
}

DLLAPI int ezcam_new(){
  return myron_ezcam_new();
}


DLLAPI int ezcam_findCamera(){
  return myron_ezcam_findCamera();
}


DLLAPI int ezcam_run(int w,int h){
  return myron_ezcam_run(w,h);
}


DLLAPI unsigned char*ezcam_getFrame(int w,int h){
  return myron_ezcam_getFrame();
}


DLLAPI int ezcam_stop(){
  return myron_ezcam_stop();
}



/**
   ezcam deals with cross platform differences between PortVideo and
   Linux DC1394 in order to provide a transparent and consistent
   interface to users of the myron_ezcam API across the board.
   
   @author jtnimoy
   
*/

#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h> <--- no threads for macromedia xtra yet.


#if defined(WIN32) || defined(__CYGWIN__) || defined(_WINDLL)
  #include "dslibCamera.h"
  #define PLAT_SPECIFIC_CAM dslibCamera
  #define EXPORT extern "C" __declspec(dllexport)
#elif defined(__APPLE__) || defined(__MWERKS__)
  #include "macsgCamera.h"
  #define PLAT_SPECIFIC_CAM macsgCamera
  #define EXPORT extern "C"
  
  //multi threaded CFM apps require additional configurations.
  #if defined(__MWERKS__)
  	#define _MSL_THREADSAFE 1
  //	#include <critical_regions.pthreads.h>
  #endif
  
#else
  #include "dc1394Camera.h"
  #define PLAT_SPECIFIC_CAM dc1394Camera
  #define EXPORT extern "C"
#endif

static PLAT_SPECIFIC_CAM *cam;


static int requested_width = 0;
static int requested_height = 0;

// static pthread_t threadFrames_thread_ptr;

EXPORT int myron_ezcam_new(){
  cam = new PLAT_SPECIFIC_CAM();

  if(cam==NULL){
    return 0;
  }
  
#if defined(WIN32)
  //i just wanna disable the settings popup in the beginning.
  cam->xml_config = "<?xml version='1.0' encoding='UTF-8'?> <dsvl_input> <camera show_format_dialog='false'><pixel_format><RGB24/></pixel_format></camera></dsvl_input>";
#endif
  
  return 1;
}


/**
   tell user how many cameras are attached to the machine.
*/
EXPORT int myron_ezcam_count(){
  int r = PLAT_SPECIFIC_CAM::countCameras();
  return r;
}





EXPORT int myron_ezcam_findCamera(){
  if(!cam->findCamera()){
    delete cam;
    return 0;
  }
  return 1;
}


EXPORT int myron_ezcam_getForcedWidth(){
  return cam->getWidth();
}

EXPORT int myron_ezcam_getForcedHeight(){
  return cam->getHeight();
}

EXPORT int myron_ezcam_run(int w,int h){
  
  requested_width = w;
  requested_height = h;
  
  if(!cam->initCamera(w,h,1)){
    fprintf(stderr,"myron_ezcam_run() failed at cam->initCamera()\n",0);
    delete cam;
    return 0;
  }

  if(!cam->startCamera()){
    fprintf(stderr,"myron_ezcam_run() failed at cam->startCamera()\n",0);
    delete cam;
    return 0;    
  }
  return 1;
}


EXPORT unsigned char *myron_ezcam_getFrame(){
  return cam->getFrame();
}


/**
   used by myron_ezcam_threadFrames()
*/
void *myron_ezcam_threadFrames_internal_thread_func(void*t){
  
  while(true){
    printf("i'm in another thread\n",0);
  }
}



void do_something()
{
printf("Thread 1!\n",0);
}



/**
   starts an internal seperate thread for calls to
   myron_ezcam_getFrame() 
*/
EXPORT void myron_ezcam_threadFrames(){
  //start a new thread
  /*
  int thread_create_result = pthread_create(
		     &threadFrames_thread_ptr,
		     NULL,
		     myron_ezcam_threadFrames_internal_thread_func,
		     NULL //void* anything you wanna pass to it.)
		     );
  printf("thread result: %i\n",thread_create_result);
  */

	//thread t1(do_something);
	
}



EXPORT void myron_ezcam_settings(){
  cam->showSettingsDialog();
}


EXPORT int myron_ezcam_stop(){
  if(!cam->stopCamera()){
    delete cam;
    return 0;
  }
  if(!cam->closeCamera()){
    delete cam;
    return 0;
  }
  return 1;
}


#include <stdlib.h>
#include <stdio.h>

#include "ezcam.h"

int main(int argc , char*argv[]){

 
  //test the entire sequence many times.
  for(int ii=0;ii<10;ii++){
    
    if(!myron_ezcam_new()){
      return -1;
    }
    
    printf("camera count : %i\n",myron_ezcam_count());
    
    
    
    printf("finding camera\n",0);
    
    if(!myron_ezcam_findCamera()){
      return -2;
    }
    
    printf("initing  camera\n",0);
    if(!myron_ezcam_run(320,240)){
      return -3;
    }

    printf("camera forced Width and Forced Height : %i x %i\n",myron_ezcam_getForcedWidth(),myron_ezcam_getForcedHeight());
    
    for(int i=0;i<50;i++){
      unsigned char *b = myron_ezcam_getFrame();
      if(b!=NULL)printf("%i %i %i\n",b[0],b[1],b[2]);
      else printf("null\n",0);
      
    }
    
    printf("stopping camera\n",0);
    myron_ezcam_stop();
    
  }
  
  return 0;
  
}

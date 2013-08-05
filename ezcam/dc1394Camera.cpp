#include <dc1394/dc1394_control.h>
#include <dc1394/dc1394_conversions.h>
#include <dc1394/dc1394_utils.h>
#include <stdio.h>
#include <pthread.h>
#include <Magick++.h>
#include "dc1394Camera.h"

dc1394Camera::dc1394Camera(){
  cam = NULL;
  camcount = 0;
  camID = 0;
  frameBytes = NULL;
}

dc1394Camera::~dc1394Camera(){
  delete [] frameBuf;
}

/**
   static function for counting the cameras on the machine.
*/
unsigned int dc1394Camera::countCameras(){
  dc1394camera_t **c;
  unsigned int n;
  dc1394_find_cameras(&c,&n);
  return n;
}

bool dc1394Camera::findCamera(){
  dc1394error_t err = dc1394_find_cameras(&cam,&camcount);
  if(err==DC1394_NO_CAMERA){
    fprintf(stderr,"no cameras\n",0);
    return false;
  }else if(err!=0){
    fprintf(stderr,"error finding cameras (%i)\nDo you have permissions for /dev/raw1394 and /dev/video1394*?\n\n",err);
    return false;
  }
  camID = 0;//just choose the first camera on the list.
  return true;
}


bool dc1394Camera::initCamera(int expected_width,int expected_height,bool colour){
  //actually, colour is just a dummy variable to complete the API
  dc1394error_t err;
  dc1394_cleanup_iso_channels_and_bandwidth(cam[camID]);
  dc1394_reset_camera(cam[camID]);
  dc1394speed_t speed;
  dc1394framerate_t frame_rate;
  dc1394color_coding_t color_coding;
  
  dc1394video_mode_t closest_fit_mode;
  
  getClosestMatchingVideoMode( cam[camID],&closest_fit_mode,
			       expected_width,expected_height );
  
  dc1394_video_get_iso_speed(cam[camID],&speed);
  dc1394_video_get_framerate(cam[camID],&frame_rate);
  dc1394_format7_get_color_coding(cam[camID], closest_fit_mode, &color_coding);
  err =  dc1394_video_specify_iso_channel(cam[camID],camID);
  
  if(err!=0){
    fprintf(stderr,"channel err: %i\n",err);
    return false;
  }
  
    err = dc1394_dma_setup_capture(cam[camID],closest_fit_mode,
					   speed,frame_rate,
					   5,1);
    

    if(err==DC1394_NO_ISO_CHANNEL){
      fprintf(stderr,"setup err: DC1394_NO_ISO_CHANNEL\n",err);
      return false;
    }else if(err==DC1394_NO_BANDWIDTH){
      fprintf(stderr,"setup err: DC1394_NO_BANDWIDTH\n",err);
      return false;
    }else if(err!=0){
      fprintf(stderr,"setup err: %i\n",err);
      return false;
    }
    frameBytes = NULL;
    return true;
}
  

bool dc1394Camera::startCamera(){
  dc1394error_t err;
  err = dc1394_video_set_transmission(cam[camID],DC1394_ON);
  if(err==0)return true;
  else return false;
}

bool dc1394Camera::stopCamera(){
  dc1394error_t err;
  err = dc1394_video_set_transmission(cam[camID],DC1394_OFF);
  if(err==0)return true;
  else return false;
}

bool dc1394Camera::closeCamera(){
  dc1394_cleanup_iso_channels_and_bandwidth(cam[camID]);
  return true;
}

/**
   rotate the ring buf, fill the current space, then return it.
*/
unsigned char*dc1394Camera::getFrame(){
  dc1394error_t err;

  if(frameBytes!=NULL){
    dc1394_dma_done_with_buffer(cam[camID]);  
  }
  
  err = dc1394_dma_capture(&cam[camID],1,DC1394_VIDEO1394_WAIT);
  if(err!=0)return 0;
  
  frameBytes = dc1394_video_get_buffer(cam[camID]);
  
  //convert to RGB8 if needed
  dc1394video_mode_t video_mode;
  err = dc1394_video_get_mode(cam[camID], &video_mode);
  unsigned int w;
  unsigned int h;
  float bpp;
  dc1394color_coding_t cc;
  getVideoModeString(video_mode,&w,&h,&cc);
  err = dc1394_get_bytes_per_pixel(cc,&bpp);
  
  if(frameBuf==NULL){
    int newlen = 24*w*h;
    frameBuf = new uchar_t[newlen];
  }  
  if(cc!=DC1394_COLOR_CODING_RGB8){
    //go from YUV to RGB - THANK YOU DC1394 api !!!!!!
    err = dc1394_convert_to_RGB8(
				 frameBytes,//src
				 frameBuf,//dst
				 w,h,
				 NULL,//byte order? how do I retrieve that?
				 cc,//coding
				 8   //bits
				 );
    
    if(err!=0)return NULL;
    return frameBuf;//return RGB converted pixels.
  }else{
    return frameBytes;
  }
}


void dc1394Camera::showSettingsDialog(){
  //todo: check if coriander is installed, then launch it.
}




void dc1394Camera::getVideoModeString(dc1394video_mode_t vm, uint_t *width, uint_t *height, dc1394color_coding_t *mode){
  (*width) = 0;
  (*height) = 0;
  (*mode) = (dc1394color_coding_t)0;
  
  dc1394error_t err;
  err = dc1394_get_image_size_from_video_mode(cam[camID],vm,width,height);
  err = dc1394_get_color_coding_from_video_mode(cam[camID],vm, mode);
  
}








/**
 * finds a matching video mode for the given requested width and height.
 */
void dc1394Camera::getClosestMatchingVideoMode(
					       dc1394camera_t *cam, 
					       dc1394video_mode_t *ret_mode,
					       int requested_w,
					       int requested_h
					       ){
  dc1394video_modes_t video_modes;
  dc1394_video_get_supported_modes(cam,&video_modes);
  uint_t w;
  uint_t h;
  dc1394color_coding_t m;
  for(int i=0;i<video_modes.num;i++){
    getVideoModeString(video_modes.modes[i] , &w, &h, &m);
    if(w>=requested_w && h>=requested_h){
      (*ret_mode) = video_modes.modes[i];
      return;
    }
  }
  (*ret_mode) = video_modes.modes[0];
  return;
}


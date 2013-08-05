#ifndef _dc1394Camera_H_
#define _dc1394Camera_H_

#include <dc1394/dc1394_control.h>

class dc1394Camera {
 public:
  dc1394Camera();
  ~dc1394Camera();
  bool findCamera();
  bool initCamera(int w,int h,bool colour);
  bool startCamera();
  unsigned char*getFrame();
  void showSettingsDialog();
  bool stopCamera();
  bool closeCamera();
  static unsigned int countCameras();
 private:
  unsigned char*frameBytes;//ptr into dc1394 ring buffer
  unsigned char*frameBuf;//personal pixel conversion scratch space.
  dc1394camera_t **cam;
  unsigned int camcount;
  unsigned int camID;
  

/**
 *   decodes a standard color mode into descriptive pieces.
 */
void getVideoModeString(dc1394video_mode_t vm, 
			uint_t *width, 
			uint_t *height, 
			dc1394color_coding_t *mode
			);

/**
 * finds a matching video mode for the given requested width and height.
 */
void  getClosestMatchingVideoMode(dc1394camera_t *cam,
				  dc1394video_mode_t *ret_mode,
				  int requested_w,
				  int requested_h
				  );




};



#endif

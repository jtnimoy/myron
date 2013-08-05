/*

Myron
open source vision object initiated by Josh Nimoy in March 2004
adapted from WebCamXtra

*/
 
#ifndef _MYRON_H_
#define _MYRON_H_

#if defined(__DARWIN__)
#elif defined(linux)
#else
//windows
#endif 

#define R_DIFFERENCEIMAGE(x,y) (this->differencePixels[y*3*this->imageWidth+x*3+0])								
#define G_DIFFERENCEIMAGE(x,y) (this->differencePixels[y*3*this->imageWidth+x*3+1])
#define B_DIFFERENCEIMAGE(x,y) (this->differencePixels[y*3*this->imageWidth+x*3+2])


#if defined(__DARWIN__)
  #if defined(__APPLE_CC__)
    //project builder
    #include <QuickTime/QuickTimeComponents.h>      
    #include <CoreFoundation/CFPreferences.h>     
  #else
    //codewarrior
    #include <QuickTimeComponents.h>      
    #include <CFPreferences.h>
  #endif
#else
  //windows visual studio . net
  using namespace std;//added for ofstream
//#include <windows.h>
#endif
	#include <stdio.h>
	#include <stdlib.h>

using namespace std;

struct MyronPoint{
  int x;
  int y;
};

class Myron{
 public:
  Myron();
  ~Myron();
  void start(int w,int h);
  void stop();
  void update();
  void updateCameraInSeperateThread();
  void settings();
  unsigned char* version();
  void findGlobs(int state);
  unsigned char *globsImage();
  void sensitivity(float val);
  void minDensity(int val);
  void maxDensity(int val);
  unsigned char *cameraImage();
  unsigned char *image();
  int *globBoxes();
  int globCount();
  int *globCenters();
  int *globPixels();
  int globPixelsCount();
  int globEdgePoints(int segmentLength);
  int *globEdgePointsResult();
  int *globQuads(float minSideLength, float maxSideLength);
  void trackColor(int red, int green, int blue, int tolerance);
  void trackNotColor(int red, int green, int blue, int tolerance);
  void average(int left,int top,int right,int bottom, unsigned char *colorbuff);
  void average(int left,int top,int right,int bottom, unsigned char *colorbuff,int skip);
  void averageFloat(int left,int top,int right,int bottom, float *colorbuff,int skip);
  unsigned char *retinaImage();
  void adaptivity(float val);
  void adapt();
  unsigned char *differenceImage();
  void hijackRGB(int w,int h,unsigned char * newimage);
  void hijackRGBMemCopy(int len,unsigned char * newimage);  
  void hijackARGB(int w,int h,unsigned char * newimage);
  void hijackARGBInvert(int w,int h,unsigned char * newimage);
  int width();
  int height();
  int getForcedWidth();
  int getForcedHeight();
  
 private:
  //private functions
  void stackFriendlyRecursiveGlobFind(int x,int y, int curGlobID);
  float getTriangleArea(float x0,float y0,float x1,float y1,float x2,float y2);
  int isEdge(int x,int y);
  
  //OSErr SaveSettingsPreference(UserData inUserData);
  //OSErr GetSettingsPreference(UserData *outUserData);
  void ProcessGlobIDs();
  
  //private variables
  int               imageWidth;                                        
  int               imageHeight;  
  int				findGlobs_state; 
  unsigned char 	*globPixelList;
  unsigned char		*cameraPixels;
  
  float		*retinaPixels;
  unsigned char  *retinaPixelsAsUnsignedChars;
  
  unsigned char 	*differencePixels;
  unsigned char 	*hijackPixels;
  int 	            *globIDs;
  int 				*stackX;
  int 				*stackY;
  
  int 				*thisGlobXs;
  int 				*thisGlobYs;
  int 				thisGlobCount;
  int 				minDensity_state;
  int 				maxDensity_state;
  
  int 				*globBoxList;
  int 				*globQuadList;
  int 				globBoxListCount;
  
  int 				*globPixelLists;
  int 				*globCenterPoints;
  int               *globEdgePointList;
  int               globEdgePointListCount;
  int 				globPixelListsCount;
  
  int				trackColorRed;
  int				trackColorGreen;
  int				trackColorBlue;
  int				trackNot;
  float 			sensitivity_state;
  
  
  /**
  	controls the retina image's environmental adapting speed.
  */
  float 			adaptivity_state;
  
  
  int 				hijackNext;
 
};

#endif


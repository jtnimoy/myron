/*
 *  mac_jni_projjnilib.c
 *  mac_jni_proj
 *
 *  Created by Josh Nimoy on Fri Mar 12 2004.
 *  Copyright (c) 2004 __MyCompanyName__. All rights reserved. 
 *
 */ 

#include "JMyron_JMyron.h"
#include "myron.h"

static Myron *myron;


#define COLOR_24BIT 0
#define COLOR_1BIT 1

/**
   a helper function that generates dynamic java color-int arrays on the fly from rgb triplets.
*/
jintArray convertToJavaArray(JNIEnv *env,unsigned char*p,int color_depth){
  int w = myron->width();
  int h = myron->height();
  jintArray returnArray = env->NewIntArray(w*h);
  jint *arrayStart = env->GetIntArrayElements(returnArray, 0);
  int a = 255 << 24;
  unsigned int r;
  unsigned int g;
  unsigned int b;
  
  if(color_depth==COLOR_24BIT){
    int i3;
    for(int i=0;i<w*h;i++){
      i3 = i*3;
      r = ((int)p[i3])<<16;
      g = ((int)p[i3+1])<<8;
      b = ((int)p[i3+2])<<0;
      arrayStart[i] = a|r|g|b;
    }
  }else{
    for(int i=0;i<w*h;i++){
      r = ((int)p[i])<<16;
      g = ((int)p[i])<<8;
      b = ((int)p[i])<<0;
      arrayStart[i] = a|r|g|b;
    }
  }
  
  env->ReleaseIntArrayElements(returnArray, arrayStart, 0);
  return returnArray;
}




/**
   another helper function that generates dynamic java color-int arrays on the fly from rgb triplets.
*/
void convertToJavaArrayCopy(JNIEnv *env,unsigned char*p,jintArray returnArray,int color_depth){
  int w = myron->width();
  int h = myron->height();
  jint *arrayStart = env->GetIntArrayElements(returnArray, 0);
  int a = 255 << 24;
  unsigned int r;
  unsigned int g;
  unsigned int b;
  
  if(color_depth==COLOR_24BIT){
    int i3;
    for(int i=0;i<w*h;i++){
      i3 = i*3;
      r = ((int)p[i3])<<16;
      g = ((int)p[i3+1])<<8;
      b = ((int)p[i3+2])<<0;
      arrayStart[i] = a|r|g|b;
    }

  }else{
    for(int i=0;i<w*h;i++){
      r = ((int)p[i])<<16;
      g = ((int)p[i])<<8;
      b = ((int)p[i])<<0;
      arrayStart[i] = a|r|g|b;
    }
  }
  env->ReleaseIntArrayElements(returnArray, arrayStart, 0);
}






JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1start(JNIEnv *env, jobject ths,jint width, jint height) {
  myron = new Myron();
  myron->start(width,height);
}

JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1stop(JNIEnv *env, jobject ths) {
    myron->stop();
    delete myron;
    myron = 0;       
}

JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1update(JNIEnv *env, jobject ths) {
    myron->update();
}


JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1settings(JNIEnv *env, jobject ths){
    myron->settings(); 
}

JNIEXPORT jstring JNICALL Java_JMyron_JMyron_native_1version(JNIEnv *env, jobject ths){
    return env-> NewStringUTF((const char*)myron->version()); 
}
JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1findGlobs(JNIEnv *env, jobject ths, jint val){
    myron->findGlobs(val);
}






JNIEXPORT jintArray JNICALL Java_JMyron_JMyron_native_1retinaImage(JNIEnv *env,jobject ths){
  return convertToJavaArray(env,myron->retinaImage(),COLOR_24BIT);
}


JNIEXPORT jintArray JNICALL Java_JMyron_JMyron_native_1differenceImage(JNIEnv *env,jobject ths){
  return convertToJavaArray(env,myron->differenceImage(),COLOR_24BIT);
}


JNIEXPORT jintArray JNICALL Java_JMyron_JMyron_native_1image(JNIEnv *env, jobject ths){
  return convertToJavaArray(env,myron->image(),COLOR_24BIT);
}

JNIEXPORT jintArray JNICALL Java_JMyron_JMyron_native_1globsImage(JNIEnv *env,jobject ths){
  return convertToJavaArray(env,myron->globsImage(),COLOR_1BIT);
}


JNIEXPORT jintArray JNICALL Java_JMyron_JMyron_native_1cameraImage(JNIEnv *env,jobject ths){
  return convertToJavaArray(env,myron->cameraImage(),COLOR_24BIT);
}    





JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1retinaImageCopy(JNIEnv *env,jobject ths,jintArray dst){
  convertToJavaArrayCopy(env,myron->retinaImage(),dst,COLOR_24BIT);
}


JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1differenceImageCopy(JNIEnv *env,jobject ths,jintArray dst){
   convertToJavaArrayCopy(env,myron->differenceImage(),dst,COLOR_24BIT);
}


JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1imageCopy(JNIEnv *env, jobject ths,jintArray dst){
   convertToJavaArrayCopy(env,myron->image(),dst,COLOR_24BIT);
}

JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1globsImageCopy(JNIEnv *env,jobject ths,jintArray dst){
   convertToJavaArrayCopy(env,myron->globsImage(),dst,COLOR_1BIT);
}


JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1cameraImageCopy(JNIEnv *env,jobject ths,jintArray dst){
   convertToJavaArrayCopy(env,myron->cameraImage(),dst,COLOR_24BIT);
}    








JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1sensitivity(JNIEnv *env,jobject ths,jfloat val){
  myron->sensitivity(val);
}

JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1minDensity(JNIEnv *env,jobject ths,jint val){
  myron->minDensity(val);
}

JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1maxDensity(JNIEnv *env,jobject ths,jint val){
  myron->maxDensity(val);
}


JNIEXPORT jintArray JNICALL Java_JMyron_JMyron_native_1globBoxes(JNIEnv *env,jobject ths){
  int *b =  myron->globBoxes();
  int count = myron->globCount();
  
  jintArray returnArray = env->NewIntArray(count*4);

  jint *arrayStart = env->GetIntArrayElements(returnArray, 0);
  for(int i=0;i<count*4;i++){
    arrayStart[i] = b[i];
  }
  env->ReleaseIntArrayElements(returnArray, arrayStart, 0);
  
  return returnArray;
  
}

JNIEXPORT jintArray JNICALL Java_JMyron_JMyron_native_1globCenters(JNIEnv *env,jobject ths){
  int *b =  myron->globCenters();
  int count = myron->globCount();
  
  jintArray returnArray = env->NewIntArray(count*3);
  
  jint *arrayStart = env->GetIntArrayElements(returnArray, 0);
  for(int i=0;i<count*3;i++){
    arrayStart[i] = b[i];
  }
  env->ReleaseIntArrayElements(returnArray, arrayStart, 0);
  
  return returnArray;


}

JNIEXPORT jintArray JNICALL Java_JMyron_JMyron_native_1globPixels(JNIEnv *env,jobject ths){
  int *b =  myron->globPixels();
  int count = myron->globPixelsCount();
  
  jintArray returnArray = env->NewIntArray(count*3);

  jint *arrayStart = env->GetIntArrayElements(returnArray, 0);
  for(int i=0;i<count*3;i++){
    arrayStart[i] = b[i];
  }
  env->ReleaseIntArrayElements(returnArray, arrayStart, 0);
  
  return returnArray;
}

JNIEXPORT jintArray JNICALL Java_JMyron_JMyron_native_1globEdgePoints(JNIEnv *env,jobject ths,jint segmentLength){
  int count = myron->globEdgePoints(segmentLength);
  int *b =  myron->globEdgePointsResult();
  
  jintArray returnArray = env->NewIntArray(count*3);
  
  jint *arrayStart = env->GetIntArrayElements(returnArray, 0);
  for(int i=0;i<count*3;i++){
    arrayStart[i] = b[i];
  }
  env->ReleaseIntArrayElements(returnArray, arrayStart, 0);
  
  return returnArray;

  
}

JNIEXPORT jintArray JNICALL Java_JMyron_JMyron_native_1globQuads(JNIEnv *env,jobject ths,jfloat minSideLength, jfloat maxSideLength){
 

  int *b =  myron->globQuads(minSideLength,maxSideLength);
  int count = myron->globCount();
  
  jintArray returnArray = env->NewIntArray(count*8);
  
  jint *arrayStart = env->GetIntArrayElements(returnArray, 0);
  for(int i=0;i<count*8;i++){
    arrayStart[i] = b[i];
  }
  env->ReleaseIntArrayElements(returnArray, arrayStart, 0);
  
  return returnArray;

}

JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1trackColor(JNIEnv *env,jobject ths,jint red, jint green, jint blue, jint tolerance){
  myron->trackColor(red,green,blue,tolerance);
}

JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1trackNotColor(JNIEnv *env,jobject ths,jint red, jint green, jint blue, jint tolerance){
  myron->trackNotColor(red,green,blue,tolerance);
}

JNIEXPORT jint JNICALL Java_JMyron_JMyron_native_1average(JNIEnv *env,jobject ths,jint left,jint top,jint right,jint bottom){
  unsigned char ret[3];
  myron->average(left,top,right,bottom,ret);
  return (ret[0]<<16)|(ret[1]<<8)|(ret[2]);
}


JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1adaptivity(JNIEnv *env,jobject ths,jfloat val){
  myron->adaptivity(val);
}

JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1adapt(JNIEnv *env,jobject ths){
  myron->adapt();
}

JNIEXPORT void JNICALL Java_JMyron_JMyron_native_1hijack(JNIEnv *env,jobject ths,jint w,jint h,jintArray newimage){
  
  unsigned char *fixedArray = new unsigned char[w*h*3];
  jint *arrayStart = env->GetIntArrayElements(newimage, 0);
  for(int i=0;i<w*h;i++){
    fixedArray[i*3+0] = (arrayStart[i]>>16)&0x000000FF;
    fixedArray[i*3+1] = (arrayStart[i]>>8 )&0x000000FF;
    fixedArray[i*3+2] = (arrayStart[i]    )&0x000000FF;
  }
  env->ReleaseIntArrayElements(newimage, arrayStart, 0);
  myron->hijackRGB(w,h,fixedArray);
  delete [] fixedArray;
}

JNIEXPORT jint JNICALL Java_JMyron_JMyron_native_1width(JNIEnv *env,jobject ths){
  return myron->width();
}

JNIEXPORT jint JNICALL Java_JMyron_JMyron_native_1height(JNIEnv *env,jobject ths){
  return myron->height();
}


JNIEXPORT jint JNICALL Java_JMyron_JMyron_native_1getForcedWidth(JNIEnv *env,jobject ths){
  return myron->getForcedWidth();
}

JNIEXPORT jint JNICALL Java_JMyron_JMyron_native_1getForcedHeight(JNIEnv *env,jobject ths){
  return myron->getForcedHeight();
}





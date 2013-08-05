//
//  Myron.java
//
//  Created by Josh Nimoy on Fri Mar 12 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//
package JMyron;
 
import java.util.*;

public class JMyron {
    static {
        // Ensure native JNI library is loaded
        System.loadLibrary("JMyron");
    }
    
    public static void main (String args[]) {
    }


    public JMyron() {
    }
    
    native void native_start(int width,int height);
    native void native_stop();
    native void native_update();
    native void native_settings();
    native String native_version();
    native void native_findGlobs(int val);
    native void native_sensitivity(float val);
    native void native_minDensity(int val);
    native void native_maxDensity(int val);

    native int[] native_cameraImage();
    native int[] native_globsImage();
    native int[] native_image();
    native int[] native_differenceImage();
    native int[] native_retinaImage();


    native void native_cameraImageCopy(int[]dst);
    native void native_globsImageCopy(int[]dst);
    native void native_imageCopy(int[]dst);
    native void native_differenceImageCopy(int[]dst);
    native void native_retinaImageCopy(int[]dst);



    native int[] native_globBoxes();
    native int native_globCount();
    native int[] native_globCenters();
    native int[] native_globPixels();
    native int[] native_globEdgePoints(int segmentLength);
    native int[] native_globQuads(float minSideLength, float maxSideLength);
    native void native_trackColor(int red, int green, int blue, int tolerance);
    native void native_trackNotColor(int red, int green, int blue, int tolerance);
    native int native_average(int left,int top,int right,int bottom);

    native void native_adaptivity(float val);
    native void native_adapt();

    native void native_hijack(int w,int h,int[] newimage);
    native int native_width();
    native int native_height();

    native int native_getForcedWidth();
    native int native_getForcedHeight();




    /**
       image functions 
    */

    public int[] retinaImage(){
	return native_retinaImage();
    }

    public int[] differenceImage(){
	return native_differenceImage();
    }
    

    public int[] globsImage(){
	return native_globsImage();
    }


    public int[] image(){
	return native_image();
    }
    
    public int[] cameraImage(){
	return native_cameraImage();
    }    


    public void retinaImageCopy(int[]dst){
	 native_retinaImageCopy(dst);
    }

    public void differenceImageCopy(int[]dst){
	 native_differenceImageCopy(dst);
    }
    

    public void globsImageCopy(int[]dst){
	 native_globsImageCopy(dst);
    }


    public void imageCopy(int[]dst){
	 native_imageCopy(dst);
    }
    
    public void cameraImageCopy(int[]dst){
	 native_cameraImageCopy(dst);
    }    








    
    public void start(int w,int h){
        native_start(w,h);
    }
    
    public void stop(){
        native_stop();
    }
    
    
    public void update(){
        native_update();
    }
    
    
    public void settings(){
	native_settings();
    }
    
    public String version(){
        return native_version();//m.native_version();
    }
    
    
    public int globCount(){
        return native_globCount();//m.native_version();
    }

    public void findGlobs(int val){
        native_findGlobs(val);//m.native_version();
    }

    
    public void sensitivity(float val){
	native_sensitivity(val);
    }
    
    public void minDensity(int val){
	native_minDensity(val);
    }
    
    public void maxDensity(int val){
	native_maxDensity(val);
    }
    

    public int[][] globBoxes(){
        int b[] = native_globBoxes();
        int returnArray[][] = new int[b.length/4][4];
        for(int i=0;i<b.length/4;i++){
            returnArray[i][0] = b[i*4+0];
            returnArray[i][1] = b[i*4+1];
            returnArray[i][2] = b[i*4+2]-b[i*4+0];
            returnArray[i][3] = b[i*4+3]-b[i*4+1];
        }
        return returnArray;
    }
    
    public int[][] globCenters(){
       int b[] = native_globCenters();
        int returnArray[][] = new int[b.length/2][2];
        for(int i=0;i<b.length/2-1;i++){
            returnArray[i][0] = b[i*2  ];
            returnArray[i][1] = b[i*2+1];
        }
        return returnArray;
    }
    
    public int[][][] globPixels(){
        int w = native_width();
        int h = native_height();
        
        int b[] = native_globPixels();
        int count = ((native_globCenters()).length)/2;
        int returnArray[][][] = new int[count][][];
        int[][] curArray = new int[w*h][];
        int arraycx=0;
        int edgecount=0;
        for(int i=0;i<b.length/3;i++){
            int tag = b[i*3+2];
            int x = b[i*3+0];
            int y = b[i*3+1];
            if(tag==1){
                edgecount = 0;
            }
            
            int point[] = {x,y};
            curArray[edgecount] = point;
            edgecount++;
            
            if(tag==2){
                returnArray[arraycx] = new int[edgecount][2];
                for(int ii=0;ii<edgecount;ii++){
                    returnArray[arraycx][ii][0] = curArray[ii][0];
                    returnArray[arraycx][ii][1] = curArray[ii][1];
                }
                arraycx++;
            }

        }
        return returnArray;

    }
    
    public int[][][] globEdgePoints(int segmentLength){
        int w = native_width();
        int h = native_height();
        
        int b[] = native_globEdgePoints(segmentLength);
        int count = ((native_globCenters()).length)/2;
        int returnArray[][][] = new int[count][][];
        int[][] curArray = new int[w*h][];
        int arraycx=0;
        int edgecount=0;
        for(int i=0;i<b.length/3;i++){
            int tag = b[i*3];
            int x = b[i*3+1];
            int y = b[i*3+2];
            if(tag==1){
                edgecount = 0;
            }
            
            int point[] = {x,y};
            curArray[edgecount] = point;
            edgecount++;
            
            if(tag==2){
                returnArray[arraycx] = new int[edgecount][2];
                for(int ii=0;ii<edgecount;ii++){
                    returnArray[arraycx][ii][0] = curArray[ii][0];
                    returnArray[arraycx][ii][1] = curArray[ii][1];
                }
                arraycx++;
            }

        }
        return returnArray;
    }
    
    public int[][] globQuads(float minSideLength, float maxSideLength){
       int b[] = native_globQuads(minSideLength,maxSideLength);
        int returnArray[][] = new int[b.length/8][8];
        for(int i=0;i<b.length/8;i++){
            returnArray[i][0] = b[i*8  ];
            returnArray[i][1] = b[i*8+1];
            returnArray[i][2] = b[i*8+2];
            returnArray[i][3] = b[i*8+3];
            returnArray[i][4] = b[i*8+4];
            returnArray[i][5] = b[i*8+5];
            returnArray[i][6] = b[i*8+6];
            returnArray[i][7] = b[i*8+7];
        }
        return returnArray;
    }
    
    public void trackColor(int red, int green, int blue, int tolerance){
	native_trackColor(red,green,blue,tolerance);
    }
    
    public void trackNotColor(int red, int green, int blue, int tolerance){
	native_trackNotColor(red,green,blue,tolerance);
    }
    
    public int average(int left,int top,int right,int bottom){
	return native_average(left,top,right,bottom);
    }
    
    
    public void adaptivity(float val){
	native_adaptivity(val);
    }
    
    public void adapt(){
	native_adapt();
    }
    

    public void hijack(int w,int h,int[] newimage){
	native_hijack(w,h,newimage);
    }
    
    public int width(){
	return native_width();
    }
    
    public int height(){
	return native_height();
    }
    

    public int getForcedWidth(){
	return native_getForcedWidth();
    }
    
    public int getForcedHeight(){
	return native_getForcedHeight();
    }
    


}



#include "myron.h"
#include <math.h>
#include "ezcam.h"

Myron::Myron(){
  if(!myron_ezcam_new()){
    fprintf(stderr,"Myron: myron_ezcam_new() failed\n",0);
  }

}

Myron::~Myron(){
}


//-----------------------------------------------------------------------------

void Myron::start(int w,int h){

	this->imageWidth = w;                                                            
	this->imageHeight = h;                     

	this->findGlobs_state = 1; //make a default

	this->thisGlobCount=0;
	this->minDensity_state = 100;
	this->maxDensity_state = 0;
	this->globBoxListCount = 0;

	this->globPixelList 	= new unsigned char[w*h];
#if defined(WIN32)
	this->cameraPixels = new unsigned char[w*h*3];
#endif
	this->retinaPixels = new float[w*h*3];
	this->retinaPixelsAsUnsignedChars = new unsigned char[w*h*3];

	this->differencePixels = new unsigned char[w*h*3];
	this->hijackPixels = new unsigned char[w*h*3];

	
	this->globIDs 		= new int[w*h];
	this->stackX 		= new int[w*h];
	this->stackY 		= new int[w*h];

	this->thisGlobXs 	= new int[w*h];
	this->thisGlobYs 	= new int[w*h];

	this->globBoxList	= new int[w*h*4];
	this->globCenterPoints = new int[w*h*2];
	this->globEdgePointList  = new int[w*h*3];

	this->globQuadList  = new int[w*h*8];
	this->globEdgePointListCount = 0;



	this->globPixelLists = new int[w*h*3];
	this->globPixelListsCount = 0;

	this->trackColorRed = 0;
	this->trackColorGreen = 0;
	this->trackColorBlue = 0;
	this->sensitivity_state = 10;
	this->trackNot = 0;
	this->adaptivity_state = 0.0;
	this->hijackNext = 0;


	if(!myron_ezcam_findCamera()){
	  fprintf(stderr,"Myron: myron_ezcam_findCamera() failed\n",0);
	}
	
	if(!myron_ezcam_run(w,h)){
	  fprintf(stderr,"Myron: myron_ezcam_run() failed\n",0);
	}

}

//-----------------------------------------------------------------------------

void Myron::stop(){

  myron_ezcam_stop();
  

  delete [] this->globPixelList;
#if defined(WIN32)
  delete [] this->cameraPixels;
#endif
  delete [] this->retinaPixels;
  delete [] this->retinaPixelsAsUnsignedChars;
  delete [] this->differencePixels;
  delete [] this->hijackPixels;
  delete [] this->globIDs;
  delete [] this->stackX;
  delete [] this->stackY;
  delete [] this->thisGlobXs;
  delete [] this->thisGlobYs;
  
  delete [] this->globBoxList;
  delete [] this->globCenterPoints;
  delete [] this->globPixelLists;
  delete [] this->globEdgePointList;
  delete [] this->globQuadList;


}

//-----------------------------------------------------------------------------

void Myron::updateCameraInSeperateThread(){
  //myron_ezcam_threadFrames();
}	


//-----------------------------------------------------------------------------


void Myron::update(){
  long y;
  unsigned char*videoBaseAddress;

  if(!this->hijackNext){
    //don't update the camera if you ain't gonna use it.
    videoBaseAddress = myron_ezcam_getFrame();
  }

  if(this->hijackNext){
    this->hijackNext = 0;
    this->cameraPixels = this->hijackPixels;
  }else{

#if defined(WIN32)

	  /*
		looks like only the windows version
		is returning NULL pixel arrays. Don't
		slow down the other platforms.

		another windows-only issue is the forced
		width and height that needs scaling.
	*/

	  if(videoBaseAddress!=NULL){

		double srcW = myron_ezcam_getForcedWidth();
		double srcH = myron_ezcam_getForcedHeight();
		double dstW = this->width();
		double dstH = this->height();
		double ratioW = dstW / srcW;
		double ratioH = dstH / srcH;

		int iy;//holder for per-row calculated inverted Y value.
		int srcPos; //holder for pre-calculated X array position for source array
		int dstPos; //holder for pre-calculated X array position for dest array
		int srcRow; //holder for pre-calculated row offset for source array
		int dstRow; //holder for pre-calculated row offset for dest array
		int x;//pre-declaring the inner loop inc var in hopes to optimise speed.
		
		if(srcW!=dstW || srcH!=dstH){
			for(int y=0;y<dstH;y++){
				iy = dstH - y - 1;
				srcRow = ((int)(y/ratioH))*srcW;
				dstRow= (int)(iy*dstW);
				for(x=0;x<dstW;x++){
					srcPos = (srcRow + ((int)(x/ratioW)))*3;
					dstPos = (dstRow + x)*3;
					this->cameraPixels[dstPos + 2] = videoBaseAddress[srcPos    ];
					this->cameraPixels[dstPos + 1] = videoBaseAddress[srcPos + 1];
					this->cameraPixels[dstPos    ] = videoBaseAddress[srcPos + 2];
				}
			}
		}else{ //removed some multiplication operators for the non-scaling copy.
			for(int y=0;y<dstH;y++){
				iy = dstH - y - 1;
				srcRow = y*srcW;
				dstRow = (int)(iy*dstW);
				for(x=0;x<dstW;x++){
					srcPos = (srcRow + x)*3;
					dstPos = (dstRow + x)*3;
					this->cameraPixels[dstPos + 2] = videoBaseAddress[srcPos    ];
					this->cameraPixels[dstPos + 1] = videoBaseAddress[srcPos + 1];
					this->cameraPixels[dstPos    ] = videoBaseAddress[srcPos + 2];
				}
			}
		}

	  }
#else
    this->cameraPixels = videoBaseAddress; 
#endif
  }



  //construct the retinaImage by linear catch-up to zero-delta  

  //if this feature is not disabled
  if(this->adaptivity_state!=0){
  
  	//for all the pixels in this image
    for(int i=0;i<this->imageWidth*this->imageHeight*3;i++){
    
      //move a step closer to zero-delta from either direction
      if(fabs(this->retinaPixels[i]-this->cameraPixels[i])>this->adaptivity_state){
		if(this->retinaPixels[i]<this->cameraPixels[i]){
			this->retinaPixels[i] += this->adaptivity_state;
		}
		if(this->retinaPixels[i]>this->cameraPixels[i]){
		  this->retinaPixels[i] -= this->adaptivity_state;
		}
      }

      
      //update the char-mirror as well
      this->retinaPixelsAsUnsignedChars[i]=this->retinaPixels[i];

      
    }
  }
  
  //construct the differenceImage
  {
	  int i;
	  int max = this->imageWidth*this->imageHeight*3;
	  for(i=0;i<max;i++)this->differencePixels[i] = abs( this->cameraPixels[i] - this->retinaPixels[i] );
  }


  
  if(this->findGlobs_state==1){ 		//do all the crazy analysis on it
	  
	  /*
	  	generate the glob image using thresholding
	  	against a color with a sensitivity - for process glob ids.
	  	
	  	DOES THIS NEED TO BE OUTSIDE THE findGlobs_state CONDITIONAL?
	  */
	  
	  for(y=0;y<this->imageHeight;y++){
	    for(int x=0;x<this->imageWidth;x++){
	      unsigned char r = (unsigned char)(this->differencePixels[y*3*this->imageWidth+x*3+0]);
	      unsigned char g = (unsigned char)(this->differencePixels[y*3*this->imageWidth+x*3+1]);
	      unsigned char b = (unsigned char)(this->differencePixels[y*3*this->imageWidth+x*3+2]);
	      unsigned char tr = this->trackColorRed;
	      unsigned char tg = this->trackColorGreen;
	      unsigned char tb = this->trackColorBlue;
	      float rd = (float)abs(tr-r);
	      float gd = (float)abs(tg-g);
	      float bd = (float)abs(tb-b);
	      int result = rd+gd+bd < this->sensitivity_state;
	      if(this->trackNot){
		result = !result;
	      }
	      if(result) {
		this->globPixelList[y*this->imageWidth+x] = 0;
	      } else {
		this->globPixelList[y*this->imageWidth+x] = 255;
	      }
	      
	    }//end for x
	  }//end for y
	    
    ProcessGlobIDs();	

  }
  
}

//-----------------------------------------------------------------------------
void Myron::settings(){
  myron_ezcam_settings();
}

//-----------------------------------------------------------------------------
unsigned char *Myron::version(){
  return (unsigned char*)"26";
}
//-----------------------------------------------------------------------------
void Myron::findGlobs(int state){
  this->findGlobs_state = state;
}
//-----------------------------------------------------------------------------
unsigned char *Myron::globsImage(){
  return this->globPixelList;
}

//-----------------------------------------------------------------------------

void Myron::sensitivity(float val){
  this->sensitivity_state = val;
} 
//-----------------------------------------------------------------------------
void Myron::minDensity(int val){
  this->minDensity_state = val;
}
//-----------------------------------------------------------------------------

void Myron::maxDensity(int val){
	this->maxDensity_state = val;
}
//-----------------------------------------------------------------------------
unsigned char *Myron::cameraImage(){
  return this->cameraPixels;
}
//-----------------------------------------------------------------------------
unsigned char *Myron::image(){
  return this->cameraPixels;
}
//-----------------------------------------------------------------------------

int *Myron::globBoxes(){
  return this->globBoxList;
}
//-----------------------------------------------------------------------------

int Myron::globCount(){
  return this->globBoxListCount;
}
//-----------------------------------------------------------------------------


int *Myron::globCenters(){
  return this->globCenterPoints;
}

//-----------------------------------------------------------------------------

int *Myron::globPixels(){
  return this->globPixelLists;
}

int Myron::globPixelsCount(){
  return this->globPixelListsCount;
}


//-----------------------------------------------------------------------------

int Myron::globEdgePoints(int segmentLength){
  this->globEdgePointListCount = 0;
  
  int w = this->imageWidth;
  int h = this->imageHeight;
  
  MyronPoint p;
  MyronPoint  middle;
  int tag;
  int accumCount=0;
  //float xd;
  //float yd;
  float *samples = new float[w*h*3];
  int samplesCount = 0;
  float *ordered_samples = new float[w*h*3];
  int ordered_samplesCount = 0;
  
  
  #if defined(_MACINTOSH)
  #else
  int addition_accumX = 0;
  int addition_accumY = 0;
  
  
  float centerX = 0;
  float centerY = 0;
  #endif
  
  for(int i=0;i<this->globPixelListsCount;i++){

    tag = this->globPixelLists[i*3+2];
    p.x = this->globPixelLists[i*3+0];
    p.y = this->globPixelLists[i*3+1];
    
    
    //this->pValueInterface->PointToValue(&p,&newval);
    
    if(tag==1){//beginning a glob
      middle.x = (this->globBoxList[accumCount*4+0]+this->globBoxList[accumCount*4+2])/2;
      middle.y = (this->globBoxList[accumCount*4+1]+this->globBoxList[accumCount*4+3])/2;
      samplesCount = 0;
    }
    int foundOne = 0;
    // add a distance entry ONLY if this pixel is an edge.
    if( (p.x-1<0||p.y-1<0||p.x+1>=w||p.y+1>=h) ){//if this pixel is on the edge of the board then it is an edge.
      foundOne = 1;
    } else {
      //amongst the pixels off the edge of the image, there are more edge pixels for the glob.
      if( this->globPixelList[(p.y+1)*w+(p.x)]==0 || this->globPixelList[(p.y)*w+(p.x+1)]==0 ||
	  this->globPixelList[(p.y-1)*w+(p.x)]==0 || this->globPixelList[(p.y)*w+(p.x-1)]==0 ){ //if ANY of the neighbors is 0
	foundOne = 1;
      }
    }
    if(foundOne){	//so add it to the list. (only for edge pixels, that's why the foundOne)
			//xd = p.x-middle.x;
			//yd = p.y-middle.y;
      samples[samplesCount*2+0] = (float)p.x;//(float)i;
      samples[samplesCount*2+1] = (float)p.y;//atan2(yd,xd);
      samplesCount++;
    }
    
    if(tag==2){//ending a glob
      //MyronPoint pp;
      
      
      if(segmentLength<1)segmentLength=1;
      //this->pMmList->NewListValue(&newval);
      for(int ii=0;ii<samplesCount-segmentLength;ii+=segmentLength){
	    if(ii==0){
	      this->globEdgePointList[this->globEdgePointListCount*3+0] = 1;
	    }else{
	      this->globEdgePointList[this->globEdgePointListCount*3+0] = 0;
	    }
	
		this->globEdgePointList[this->globEdgePointListCount*3+1] = (int)samples[ii*2+0];
		this->globEdgePointList[this->globEdgePointListCount*3+2] = (int)samples[ii*2+1];
		this->globEdgePointListCount++;
		//this->pValueInterface->PointToValue(&pp,&newpointval);
		//this->pMmList->AppendValueToList(&newval,&newpointval);
      }
      this->globEdgePointList[(this->globEdgePointListCount-1)*3+0] = 2;
	  
      //this->globEdgePointList[(this->globEdgePointListCount-1)*3+0] = 2; //set the last item to end tag.
      ordered_samplesCount = 0;
      samplesCount = 0;
      
      accumCount++;
    }
  }
  delete [] samples;
  delete [] ordered_samples;
  
  return this->globEdgePointListCount;
}
//-----------------------------------------------------------------------------
int *Myron::globEdgePointsResult(){
  return this->globEdgePointList;
}
//-----------------------------------------------------------------------------
int *Myron::globQuads(float minSideLength,float maxSideLength){
  int i;
  float rads[4];
  int w,h;
  MyronPoint p;
  MyronPoint  middle;
  int tag;
  int accumCount=0;
  float xd;
  float yd;
  float *samples;
  int samplesCount = 0;
  int ii;


  
  w = this->imageWidth;
  h = this->imageHeight;
  

  unsigned char *globPixelListsCopy = new unsigned char[w*h];
  
#if defined(_MACINTOSH) || defined(__CYGWIN__)
	for(int memcpycx=0;memcpycx<w*h;memcpycx++){
		globPixelListsCopy[memcpycx]=globPixelLists[memcpycx];
	}
#else
  memcpy(globPixelListsCopy,globPixelLists,w*h);
#endif

  samples = new float[w*h*3];
  for(i=0;i<this->globPixelListsCount;i++){

    tag = this->globPixelLists[i*3+2];
    p.x = this->globPixelLists[i*3+0];
    p.y = this->globPixelLists[i*3+1];
    
    
    //this->pValueInterface->PointToValue(&p,&newval);
    
    if(tag==1){//beginning a glob
      //this->pMmList->NewListValue(&thisList);
      middle.x = (this->globBoxList[accumCount*4+0]+this->globBoxList[accumCount*4+2])/2;
      middle.y = (this->globBoxList[accumCount*4+1]+this->globBoxList[accumCount*4+3])/2;
      samplesCount = 0;
    }
    int foundOne = 0;
    // add a distance entry ONLY if this pixel is an edge.
    if( (p.x-1<0||p.y-1<0||p.x+1>=w||p.y+1>=h) ){//if this pixel is on the edge of the board then it is an edge.
      foundOne = 1;
    } else {
      //amongst the pixels off the edge of the image, there are more edge pixels for the glob.
      if( this->globPixelList[(p.y+1)*w+(p.x)]==0 || this->globPixelList[(p.y)*w+(p.x+1)]==0 ||
	  this->globPixelList[(p.y-1)*w+(p.x)]==0 || this->globPixelList[(p.y)*w+(p.x-1)]==0 ){ //if ANY of the neighbors is 0
	foundOne = 1;
      }
    }
    if(foundOne){	//so add it to the list.
      xd = (float)p.x-(float)middle.x;
      yd = (float)p.y-(float)middle.y;
      samples[samplesCount*2+0] = (float)i;
      samples[samplesCount*2+1] = (float)sqrt(xd*xd+yd*yd);
      samplesCount++;
    }
    
    //this->pMmList->AppendValueToList(&thisList,&newval);
    if(tag==2){//ending a glob
      MyronPoint pp;
      MyronPoint pp2;
      float dist;
      float dist2;
      float ftmp;
      int itmp;
      //bubble sort them.
      
      int foundOne = 1;
      while(foundOne){
	foundOne = 0;
	for(ii=0;ii<samplesCount-1;ii++){
	  pp.x = this->globPixelLists[(int)samples[ii*2+0]*3+0];
	  pp.y = this->globPixelLists[(int)samples[ii*2+0]*3+1];
	  pp2.x = this->globPixelLists[(int)samples[(ii+1)*2+0]*3+0];
	  pp2.y = this->globPixelLists[(int)samples[(ii+1)*2+0]*3+1];
	  dist = samples[ii*2+1];	
	  dist2 = samples[(ii+1)*2+1];
	  if(dist2>dist){
	    //swap
	    ftmp = dist;
	    samples[ii*2+1] = dist2;
	    samples[(ii+1)*2+1] = ftmp;
	    
	    itmp = pp.x;
	    this->globPixelLists[(int)samples[ii*2+0]*3+0] = pp2.x;
	    this->globPixelLists[(int)samples[(ii+1)*2+0]*3+0] = itmp;
	    
	    itmp = pp.y;
	    this->globPixelLists[(int)samples[ii*2+0]*3+1] = pp2.y;
	    this->globPixelLists[(int)samples[(ii+1)*2+0]*3+1] = itmp;
	    
	    foundOne = 1;
	  }
	}
      }
      
      int quadPoints[4*2];
      int ga_quadPoints[4*2];
      float ga=0;
      for(int ci=(int)minSideLength;ci<maxSideLength;ci++){
	//now start at the top of the stack and choose 4 points that are far enough apart.
	
	for(int qci=0;qci<4;qci++){
	  quadPoints[qci*2+0] = middle.x;
	  quadPoints[qci*2+1] = middle.y;
	}
	int quadPointsCount = 0;
	for(ii=0;ii<samplesCount;ii++){
	  pp.x = this->globPixelLists[(int)samples[ii*2+0]*3+0];
	  pp.y = this->globPixelLists[(int)samples[ii*2+0]*3+1];
	  dist = samples[ii*2+1];
	  if(quadPointsCount==0){
	    //immediately add this first point.
	    quadPoints[0] = pp.x;
	    quadPoints[1] = pp.y;
	    quadPointsCount++;
	  } else if(quadPointsCount>3) {
	    break;
	  } else {//this is the middle, so compare to all of them
	    int violated = 0;
	    for(int iii=0;iii<quadPointsCount;iii++){
	      float xd = (float)quadPoints[iii*2+0] - pp.x;
	      float yd =(float) quadPoints[iii*2+1] - pp.y;
	      float d = (float)sqrt(xd*xd+yd*yd);
	      //if(d<=minSideLength){
	      if(d<=ci){
		violated = 1;
	      }
	    }
	    if(violated==0){//then we found one that is away from all the others.
	      quadPoints[quadPointsCount*2+0] = pp.x;
	      quadPoints[quadPointsCount*2+1] = pp.y;
	      quadPointsCount++;
	    }
	  }
	}
	
	//now that we have all the magic 4, rotate around and order them
	
	for(ii=0;ii<4;ii++){
	  rads[ii] = (float)atan2((float)quadPoints[ii*2+1]-middle.y,(float)quadPoints[ii*2+0]-middle.x);
	}
	
	//now bubble sort.
	foundOne = 1;
	while(foundOne){
	  foundOne = 0;
	  for(int ii=0;ii<3;ii++){
	    if(rads[ii]<rads[ii+1]){
	      float tmp = rads[ii];
	      rads[ii] = rads[ii+1];
	      rads[ii+1] = tmp;
	      
	      tmp = (float)quadPoints[ii*2+0];
	      quadPoints[ii*2+0]=quadPoints[(ii+1)*2+0];
	      quadPoints[(ii+1)*2+0]=(int)tmp;
	      
	      tmp = (float)quadPoints[ii*2+1];
	      quadPoints[ii*2+1]=quadPoints[(ii+1)*2+1];
	      quadPoints[(ii+1)*2+1]=(int)tmp;
	      
	      foundOne = 1;
	    }
	  }
	}
	
	//now calculate the area of this quad.
	float area = getTriangleArea( (float)quadPoints[0],(float)quadPoints[1],
				      (float)quadPoints[2],(float)quadPoints[3],
				      (float)quadPoints[4],(float)quadPoints[5]   );
	area +=      getTriangleArea( (float)quadPoints[4],(float)quadPoints[5],
				      (float)quadPoints[6],(float)quadPoints[7],
				      (float)quadPoints[0],(float)quadPoints[1]   );
	
	//could this area be the biggest?
	if(area>ga){
	  //if so, copy to the thrown
	  ga=area;
	  for(int gi=0;gi<4*2;gi++){
	    ga_quadPoints[gi] = quadPoints[gi];
	  }
	}
	
	
      }//end looping through the area sampling phase.
      
      
      //	MAKE A LIST OF 4 THEN APPEND IT TO RESULT LIST.
      
      //this->pMmList->NewListValue(&newval);
      for(int ica=0;ica<8;ica++){
	     this->globQuadList[accumCount*8+ica] = ga_quadPoints[ica];
      }
      
      
      accumCount++;
    }
  }
  delete samples;
  
#if defined(_MACINTOSH) || defined(__CYGWIN__)
	for(int memcpycx=0;memcpycx<w*h;memcpycx++){
		globPixelLists[memcpycx]=globPixelListsCopy[memcpycx];
	}
#else
  memcpy(globPixelLists,globPixelListsCopy,w*h);
#endif

 delete globPixelListsCopy;

  return this->globQuadList;
  
}

//-----------------------------------------------------------------------------

void Myron::trackColor(int red,int green,int blue,int tolerance){
  this->trackColorRed = red;
  this->trackColorGreen = green;
  this->trackColorBlue = blue;
  this->sensitivity_state = (float)tolerance;
  this->trackNot = 0;
}

//-----------------------------------------------------------------------------

void Myron::trackNotColor(int red,int green,int blue,int tolerance){
  this->trackColorRed = red;
  this->trackColorGreen = green;
  this->trackColorBlue = blue;
  this->sensitivity_state = (float)tolerance;
  this->trackNot = 1;
}

//-----------------------------------------------------------------------------
void Myron::average(int region_left,int region_top,
				int region_right, int region_bottom, unsigned char *buff){
	average(region_left,region_top,region_right,region_bottom,buff,1);
}

//-----------------------------------------------------------------------------
void Myron::average(int region_left,int region_top,
				int region_right, int region_bottom, unsigned char *buff,int skip){
  //safety clipping.
  if(region_top < 0)region_top = 0;
  if(region_left < 0)region_left = 0;
  if(region_bottom >= this->imageHeight )region_bottom = this->imageHeight-1;
  if(region_right >= this->imageWidth )region_right = this->imageWidth-1;

  //it seems arbitrary that i am hardwiring this to look at the camera image.
  long r=0;
  long g=0;
  long b=0;
  long counter=0;
  for(int y=region_top;y<region_bottom;y+=skip){
    for(int x=region_left;x<region_right;x+=skip){
      r+=this->differencePixels[y*this->imageWidth*3+x*3+0];
      g+=this->differencePixels[y*this->imageWidth*3+x*3+1];
      b+=this->differencePixels[y*this->imageWidth*3+x*3+2];
      counter++;
    }
  }
  //MessageBox(0,"3","",0);
  if(counter!=0){
	  buff[0] = (unsigned char)(r/counter);
	  buff[1] = (unsigned char)(g/counter);
	  buff[2] = (unsigned char)(b/counter);
  }else{
	  buff[0] = 0;
	  buff[1] = 0;
	  buff[2] = 0;
  }

  
}

//-----------------------------------------------------------------------------
void Myron::averageFloat(int region_left,int region_top,
				int region_right, int region_bottom, float *buff,int skip){
  //safety clipping.
  if(region_top < 0)region_top = 0;
  if(region_left < 0)region_left = 0;
  if(region_bottom >= this->imageHeight )region_bottom = this->imageHeight-1;
  if(region_right >= this->imageWidth )region_right = this->imageWidth-1;

  //it seems arbitrary that i am hardwiring this to look at the camera image.
  float r=0;
  float g=0;
  float b=0;
  long counter=0;
  for(int y=region_top;y<region_bottom;y+=skip){
    for(int x=region_left;x<region_right;x+=skip){
      r+=this->differencePixels[y*this->imageWidth*3+x*3+0];
      g+=this->differencePixels[y*this->imageWidth*3+x*3+1];
      b+=this->differencePixels[y*this->imageWidth*3+x*3+2];
      counter++;
    }
  }
  //MessageBox(0,"3","",0);
  if(counter!=0){
	  buff[0] = r/counter;
	  buff[1] = g/counter;
	  buff[2] = b/counter;
  }else{
	  buff[0] = 0;
	  buff[1] = 0;
	  buff[2] = 0;
  }

  
}

//-----------------------------------------------------------------------------

unsigned char *Myron::retinaImage(){
  return this->retinaPixelsAsUnsignedChars;
}

//-----------------------------------------------------------------------------


void Myron::adaptivity(float val){
  this->adaptivity_state = val;
}
//-----------------------------------------------------------------------------

void Myron::adapt(){
  for(int y=0;y<this->imageHeight;y++)for(int x=0;x<this->imageWidth;x++){
    this->retinaPixels[y*(this->imageWidth)*3+x*3  ]=this->cameraPixels[y*(this->imageWidth)*3+x*3  ];
    this->retinaPixels[y*(this->imageWidth)*3+x*3+1]=this->cameraPixels[y*(this->imageWidth)*3+x*3+1];
    this->retinaPixels[y*(this->imageWidth)*3+x*3+2]=this->cameraPixels[y*(this->imageWidth)*3+x*3+2];

	//update the char-mirror as well
    this->retinaPixelsAsUnsignedChars[y*(this->imageWidth)*3+x*3  ]=this->retinaPixels[y*(this->imageWidth)*3+x*3  ];
    this->retinaPixelsAsUnsignedChars[y*(this->imageWidth)*3+x*3+1]=this->retinaPixels[y*(this->imageWidth)*3+x*3+1];
    this->retinaPixelsAsUnsignedChars[y*(this->imageWidth)*3+x*3+2]=this->retinaPixels[y*(this->imageWidth)*3+x*3+2];


  }
}
//-----------------------------------------------------------------------------
unsigned char* Myron::differenceImage(){
  return this->differencePixels;
}
//-----------------------------------------------------------------------------
void Myron::hijackRGB(int w,int h,unsigned char * newimage){
  
  for(int y=0;y<this->imageHeight;y++)for(int x=0;x<this->imageWidth;x++){
    if(y>=h||x>=w){
      this->hijackPixels[y*(this->imageWidth)*3+x*3+0] = 0;//blanking out the areas that fall outside.
      this->hijackPixels[y*(this->imageWidth)*3+x*3+1] = 0;
      this->hijackPixels[y*(this->imageWidth)*3+x*3+2] = 0;
    }else{	
      this->hijackPixels[y*(this->imageWidth)*3+x*3+0] = newimage[y*3*w+x*3+0];
      this->hijackPixels[y*(this->imageWidth)*3+x*3+1] = newimage[y*3*w+x*3+1];
      this->hijackPixels[y*(this->imageWidth)*3+x*3+2] = newimage[y*3*w+x*3+2];
    }
  }
  this->hijackNext = 1;
}
//-----------------------------------------------------------------------------
void Myron::hijackRGBMemCopy(int len,unsigned char * newimage){
	//BlockMoveData(this->hijackPixels , newimage , len);

	FILE *memfile;
	memfile = fopen("ramdrive1:videomem.raw","rb");
	int ret = fread(this->hijackPixels , 1 , len , memfile);
	if(ferror(memfile)){
		for(int i=0;i<len;i++){
			this->hijackPixels[i] = 0;
		}
	}
	fclose(memfile);
  /*
  for(int y=0;y<this->imageWidth*this->imageHeight;y++)for(int x=0;x<this->imageWidth;x++){
    if(y>=h||x>=w){
      this->hijackPixels[y*(this->imageWidth)*3+x*3+0] = 0;//blanking out the areas that fall outside.
      this->hijackPixels[y*(this->imageWidth)*3+x*3+1] = 0;
      this->hijackPixels[y*(this->imageWidth)*3+x*3+2] = 0;
    }else{	
      this->hijackPixels[y*(this->imageWidth)*3+x*3+0] = newimage[y*3*w+x*3+0];
      this->hijackPixels[y*(this->imageWidth)*3+x*3+1] = newimage[y*3*w+x*3+1];
      this->hijackPixels[y*(this->imageWidth)*3+x*3+2] = newimage[y*3*w+x*3+2];
    }
  }
  */
  this->hijackNext = 1;
}
//-----------------------------------------------------------------------------
void Myron::hijackARGB(int w,int h,unsigned char * newimage){
  
  for(int y=0;y<this->imageHeight;y++)for(int x=0;x<this->imageWidth;x++){
    if(y>=h||x>=w){
      this->hijackPixels[y*(this->imageWidth)*3+x*3+0] = 0;//blanking out the areas that fall outside.
      this->hijackPixels[y*(this->imageWidth)*3+x*3+1] = 0;
      this->hijackPixels[y*(this->imageWidth)*3+x*3+2] = 0;
    }else{	
      this->hijackPixels[y*(this->imageWidth)*3+x*3+0] = newimage[y*4*w+x*4+1];
      this->hijackPixels[y*(this->imageWidth)*3+x*3+1] = newimage[y*4*w+x*4+2];
      this->hijackPixels[y*(this->imageWidth)*3+x*3+2] = newimage[y*4*w+x*4+3];
    }
  }
  this->hijackNext = 1;
}//-----------------------------------------------------------------------------
void Myron::hijackARGBInvert(int w,int h,unsigned char * newimage){
  
  for(int y=0;y<this->imageHeight;y++)for(int x=0;x<this->imageWidth;x++){
    if(y>=h||x>=w){
      this->hijackPixels[y*(this->imageWidth)*3+x*3+0] = 0;//blanking out the areas that fall outside.
      this->hijackPixels[y*(this->imageWidth)*3+x*3+1] = 0;
      this->hijackPixels[y*(this->imageWidth)*3+x*3+2] = 0;
    }else{	
      this->hijackPixels[y*(this->imageWidth)*3+x*3+0] = newimage[((this->imageHeight-1)-y)*4*w+x*4+2];
      this->hijackPixels[y*(this->imageWidth)*3+x*3+1] = newimage[((this->imageHeight-1)-y)*4*w+x*4+1];
      this->hijackPixels[y*(this->imageWidth)*3+x*3+2] = newimage[((this->imageHeight-1)-y)*4*w+x*4+0];
    }
  }
  this->hijackNext = 1;
}
//-----------------------------------------------------------------------------
int Myron::isEdge(int x,int y){
	if(!((y-1<0)||(y+1>=this->imageHeight)||(x-1<0)||(x+1>=this->imageWidth))){	
	  int pu = this->globPixelList[this->imageWidth*(y-1)+(x  )];//up
	  int pd = this->globPixelList[this->imageWidth*(y+1)+(x  )];//down
	  int pl = this->globPixelList[this->imageWidth*(y  )+(x-1)];//left
	  int pr = this->globPixelList[this->imageWidth*(y  )+(x+1)];//right
  
	  int pul = this->globPixelList[this->imageWidth*(y-1)+(x-1)];//up left
	  int pur = this->globPixelList[this->imageWidth*(y-1)+(x+1)];//up right
	  int pdl = this->globPixelList[this->imageWidth*(y+1)+(x-1)];//down left
	  int pdr = this->globPixelList[this->imageWidth*(y+1)+(x+1)];//down right
  
	  int ps = this->globPixelList[this->imageWidth*(y  )+(x  )];
	  return ((ps!=pu)||(ps!=pd)||(ps!=pl)||(ps!=pr)||
		  (ps!=pul)||(ps!=pur)||(ps!=pdl)||(ps!=pdr));
	}else{
		return 1;
	}

}

//-----------------------------------------------------------------------------
void Myron::stackFriendlyRecursiveGlobFind(int x,int y, int curGlobID){
  // i am proud of myself for writing this without using recursive function calling
  // because that was crashing on Mac OS X - the os having a (defaultly) small stack.
  // i bet linux is the same.
  // -josh
  

  
  this->thisGlobCount = 1;	//clear the current glob data
  int stackCount = 1;	//clear the parsing stack
  this->stackX[0] = x;
  this->stackY[0] = y;
  this->globIDs[y*this->imageWidth+x] = curGlobID;
  this->thisGlobXs[0] = x;
  this->thisGlobYs[0] = y;
  //i just added the stack's first item.
  
  //do all the neighbors of this guy to see if we can start a stack.
  int t;
  int xx;
  int yy;
  



  while(stackCount>0){
    //pop one off.
    xx = this->stackX[stackCount-1];
    yy = this->stackY[stackCount-1];
    stackCount--;
    
    //then check the neighbors if they need to be dealt with later as well.
    
    //left
    if(xx-1>=0){
      t = yy*this->imageWidth+(xx-1);
      if(	this->globIDs[t] == 0 && this->globPixelList[t] == 255 && isEdge(xx,yy) ){
	this->stackX[stackCount] = xx-1;
	this->stackY[stackCount] = yy;
	this->globIDs[t] = curGlobID;
	this->thisGlobXs[this->thisGlobCount] = xx-1;
	this->thisGlobYs[this->thisGlobCount] = yy;
	this->thisGlobCount++;
	stackCount++;
      }
    }
    
    //top
    if(yy-1>=0){
      t = (yy-1)*this->imageWidth+(xx);
      if(	this->globIDs[t] == 0 && this->globPixelList[t] == 255 && isEdge(xx,yy) ){
	this->stackX[stackCount] = xx;
	this->stackY[stackCount] = yy-1;
	this->globIDs[t] = curGlobID;
	this->thisGlobXs[this->thisGlobCount] = xx;
	this->thisGlobYs[this->thisGlobCount] = yy-1;
	this->thisGlobCount++;
	stackCount++;
      }
    }
    
    //bottom
    if(yy+1<this->imageHeight){
      t = (yy+1)*this->imageWidth+(xx);
      if(	this->globIDs[t] == 0 && this->globPixelList[t] == 255 && isEdge(xx,yy) ){
	this->stackX[stackCount] = xx;
	this->stackY[stackCount] = yy+1;
	this->globIDs[t] = curGlobID;
	this->thisGlobXs[this->thisGlobCount] = xx;
	this->thisGlobYs[this->thisGlobCount] = yy+1;
	this->thisGlobCount++;
	stackCount++;
      }
    }
    
    //right
    if(xx+1<this->imageWidth){
      t = (yy)*this->imageWidth+(xx+1);
      if(	this->globIDs[t] == 0 && this->globPixelList[t] == 255 && isEdge(xx,yy) ){
	this->stackX[stackCount] = xx+1;
	this->stackY[stackCount] = yy;
	this->globIDs[t] = curGlobID;
	this->thisGlobXs[this->thisGlobCount] = xx+1;
	this->thisGlobYs[this->thisGlobCount] = yy;
	this->thisGlobCount++;
	stackCount++;
      }
    }
    
  }
}
//-----------------------------------------------------------------------------
void Myron::ProcessGlobIDs(){
  
  //reset the globID buffer.
  
  for(int i=0;i<this->imageWidth*this->imageHeight;i++){
    this->globIDs[i] = 0;
  }

  //erase the global globbox accum buffer.
  this->globBoxListCount = 0;
  this->globPixelListsCount = 0;
  //reset the working glob counter.
  int curGlobID = 0;


  //loop through all the pixels and call the recursive function on them
  for(int y=0;y<this->imageHeight;y++){

    for(int x=0;x<this->imageWidth;x++){
	  
      int t =y*this->imageWidth+x;
  

	  int r1 = isEdge(x,y);
		int r2 = (this->globIDs[t] == 0);
		int r3 = (this->globPixelList[t] == 255);
	
	  if(r2 && r3 && r1 ){
	curGlobID++;

	//found one. so find all the neighbors too.
	stackFriendlyRecursiveGlobFind(x,y,curGlobID);
	
	//now erase the globs below minDensity
	
	int logicaccum = 0;
	if(this->maxDensity_state>this->minDensity_state){//is max density NOT infinite?
	  logicaccum = (this->thisGlobCount>this->maxDensity_state);//then also check for upper bound
	}
	if(this->thisGlobCount<this->minDensity_state||logicaccum){
	  //kill this glob
	  for(int i=0;i<this->thisGlobCount;i++){
	    //turn that pixel black and erase its ID.
	    this->globPixelList[this->thisGlobYs[i]*this->imageWidth+this->thisGlobXs[i]] = 0;
	    this->globIDs   [this->thisGlobYs[i]*this->imageWidth+this->thisGlobXs[i]] = 0;
	  }//end for
	} else {
	  
	  //store the weirdly ordered pixel list for later use
	  for(int i=0;i<this->thisGlobCount;i++){
	    this->globPixelLists[this->globPixelListsCount*3+0] = this->thisGlobXs[i];
	    this->globPixelLists[this->globPixelListsCount*3+1] = this->thisGlobYs[i];
	    //now record whether this is a head or a tail.
	    if(i==0){
	      this->globPixelLists[this->globPixelListsCount*3+2] = 1;
	    }else if(i==this->thisGlobCount-1){
	      this->globPixelLists[this->globPixelListsCount*3+2] = 2;
	    }else{
	      this->globPixelLists[this->globPixelListsCount*3+2] = 0;
	    }
	    this->globPixelListsCount++;
	  }//end for
	  
	   //do further analysis on it.
	   //1. find the bounding box of it.
	  int topmost = 10000000;
	  int bottommost = -1000000;
	  int leftmost = 10000000;
	  int rightmost = -100000000;
	  int i;
	  for(i=0;i<this->thisGlobCount;i++){
	    if(this->thisGlobXs[i]<leftmost)leftmost=this->thisGlobXs[i];
	    if(this->thisGlobXs[i]>rightmost)rightmost=this->thisGlobXs[i];
	    if(this->thisGlobYs[i]<topmost)topmost=this->thisGlobYs[i];
	    if(this->thisGlobYs[i]>bottommost)bottommost=this->thisGlobYs[i];						
	  }
	  //store this data.
	  this->globBoxList[this->globBoxListCount*4+0] = leftmost;
	  this->globBoxList[this->globBoxListCount*4+1] = topmost;
	  this->globBoxList[this->globBoxListCount*4+2] = rightmost;
	  this->globBoxList[this->globBoxListCount*4+3] = bottommost;
	  this->globBoxListCount++;
	}//end if				
	
      }//end if
    }//end for
  }//end for

  int i;
  //calculate centerpoints
  for(i=0;i<this->globBoxListCount;i++){
    this->globCenterPoints[i*2+0] = (this->globBoxList[i*4+0]+this->globBoxList[i*4+2])/2;
    this->globCenterPoints[i*2+1] = (this->globBoxList[i*4+1]+this->globBoxList[i*4+3])/2;
  }

}
//-----------------------------------------------------------------------------

float Myron::getTriangleArea(float x0,float y0,float x1,float y1,float x2,float y2){
#define DISTANCE(x,y,xx,yy) (sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy)))
  double a = DISTANCE(x0,y0,x1,y1);
  double b = DISTANCE(x1,y1,x2,y2);
  double c = DISTANCE(x2,y2,x0,y0);
  double s = 0.5*(a+b+c);
  return (float)sqrt(s*(s-a)*(s-b)*(s-c));
}



/**
   returns the image pixel width
*/
int Myron::width(){
  return this->imageWidth;
  
}



/**
   returns the image pixel height
*/
int Myron::height(){
  return this->imageHeight;
}







/**
   returns the forced image pixel width from myron_ezcam
*/
int Myron::getForcedWidth(){
  return myron_ezcam_getForcedWidth();
  
}



/**
   returns the forced image pixel height from myron_ezcam
*/
int Myron::getForcedHeight(){
  return myron_ezcam_getForcedHeight();
}



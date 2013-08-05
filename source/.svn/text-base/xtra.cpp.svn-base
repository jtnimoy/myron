#define INITGUID 1
 
#include "xtra.h"

#define myron pObj->myron

static char versionInfo[] = "xtra webcamxtra -- version 2.4 ; %s.%s.%s\n";
static char msgTable[] = { 
  "new object me\n"  /* standard first handler entry in all message tables */
  //"* globalHandler -- prints global handler message\n"
  //"+ parentHandler  object xtraRef -- prints parent handler message\n" 
  //"childHandler object me, integer number -- prints child handler message, returns a number\n"
  "start object me, integer width,integer height\n"
  "stop object me\n"
  "update object me\n"
  "settings object me\n"
  "version object me\n"
  "findGlobs object me, integer state\n"
  "globsImage object me\n"
  "sensitivity object me, float value --changes the trackColor tolerance\n"
  "minDensity object me, integer value\n"
  "maxDensity object me, integer value\n"
  "cameraImage object me\n"
  "cameraImageCopy object me,image destination\n"
  "image object me\n"
  "imageCopy object me,image destination\n"
  "globBoxes object me\n"
  "globCenters object me\n"
  "globPixels object me\n"
  "globEdgePoints object me, integer segmentLength\n"
  "globQuads object me, float minSideLength, float maxSideLength\n"
  "trackColor object me, integer red, integer green, integer blue, integer tolerance\n"
  "trackNotColor object me, integer red, integer green, integer blue, integer tolerance\n"
  "average object me, integer left, integer top, integer right, integer bottom,integer skip\n"
  "averageFloat object me, integer left, integer top, integer right, integer bottom,integer skip\n"
  "retinaImage object me\n"
  "adaptivity object me, float value\n"
  "adapt object me\n"
  "differenceImage object me\n"
  "hitCheck object me, any pointList --added by parmendil, - not in myron core\n"
  "hijack object me, image newimage\n"
  "width object me\n"
  "height object me\n"
  "getForcedWidth object me\n"
  "getForcedHeight object me\n"
  "setDifferenceMaskThreshold object me, integer thresh\n"
  "setDifferenceMaskMatteColor object me, integer r,integer g,integer b\n"
  "setDifferenceMaskReduceNoise object me, radius\n"
  "setAnalysisDownSampleSteps object me, integer steps\n"
  "setDifferenceMaskHoleFillMaxSize object me, integer pixelcount\n"
  "setDifferenceMaskEdgeContract object me, integer pixelwidth\n"
  "updateCameraInSeperateThread object me\n"
  "hijackFromFileRaw object me,string filename"
  /*
   * ---> insert additional handler(s) MUST MATCH WITH ENUMS BELOW -->
   */ 
};

	
/* 	This is the enumerated scripting method list. This list should
 *	directly correspond to the msgTable defined above. It is used
 *	to dispatch method calls via the methodSelector. The 'm_XXXX' method must
 *	be last.
 */

enum 
{
	m_new = 0, /* standard first entry */
	//m_globalHandler,						
	//m_parentHandler,
	//m_childHandler,
	webcamxtra_start,
	webcamxtra_stop,
	webcamxtra_update,
	webcamxtra_settings,
	webcamxtra_version,
	webcamxtra_findGlobs,
	webcamxtra_globsImage,
	webcamxtra_sensitivity,
	webcamxtra_minDensity,
	webcamxtra_maxDensity,
	webcamxtra_cameraImage,
	webcamxtra_cameraImageCopy,
	webcamxtra_image,
	webcamxtra_imageCopy,
	
	webcamxtra_globBoxes,
	webcamxtra_globCenters,
	webcamxtra_globPixels,
	webcamxtra_globEdgePoints,
	webcamxtra_globQuads,
	webcamxtra_trackColor,
	webcamxtra_trackNotColor,
	webcamxtra_average,
	webcamxtra_averageFloat,
	webcamxtra_retinaImage,
	webcamxtra_adaptivity,
	webcamxtra_adapt,
	webcamxtra_differenceImage,
	webcamxtra_hitcheck,
	webcamxtra_hijack,
	
	webcamxtra_width,
	webcamxtra_height,
	
	webcamxtra_getForcedWidth,
	webcamxtra_getForcedHeight,
	webcamxtra_setDifferenceMaskThreshold,
	webcamxtra_setDifferenceMaskMatteColor,
	webcamxtra_setDifferenceMaskReduceNoise,
	webcamxtra_setAnalysisDownSampleSteps,
	webcamxtra_setDifferenceMaskHoleFillMaxSize,
	webcamxtra_setDifferenceMaskEdgeContract,
	webcamxtra_updateCameraInSeperateThread,
	webcamxtra_hijackFromFileRaw,
		/*
		 * ---> insert additional names(s) MUST MATCH MESSAGE TABLE ABOVE -->
		 */ 
	m_XXXX
};


/* ============================================================================= */
/* Xtra Glue Stuff */
/* ============================================================================= */

#define XTRA_VERSION_NUMBER XTRA_CLASS_VERSION

BEGIN_XTRA
BEGIN_XTRA_DEFINES_CLASS(TStdXtra, XTRA_CLASS_VERSION)
  CLASS_DEFINES_INTERFACE(TStdXtra, IMoaRegister, XTRA_VERSION_NUMBER)
  CLASS_DEFINES_INTERFACE(TStdXtra, IMoaMmXScript, XTRA_VERSION_NUMBER)
  /*
   * ---> insert additional interface(s) -->
   */ 
  END_XTRA_DEFINES_CLASS
END_XTRA


/* ============================================================================= */
/* Create/Destroy for class TStdXtra */
/* ============================================================================= */


STDMETHODIMP_(MoaError) MoaCreate_TStdXtra (TStdXtra FAR * This) {
  moa_try
    
    ThrowErr (This->pCallback->QueryInterface(&IID_IMoaMmValue, (PPMoaVoid) &This->pValueInterface));
    ThrowErr (This->pCallback->QueryInterface(&IID_IMoaMmUtils2, (PPMoaVoid) &This->pMoaUtils));
    ThrowErr (This->pCallback->QueryInterface(&IID_IMoaMmImage,			(PPMoaVoid)&This->pMmImage));
    ThrowErr (This->pCallback->QueryInterface(&IID_IMoaMmList,			(PPMoaVoid)&This->pMmList));
    ThrowErr (This->pCallback->QueryInterface(&IID_IMoaMmColor,			(PPMoaVoid)&This->pMmColor));
    
	This->diffmaskthresh = -1;
	This->diffmaskMatteR = 0;	
	This->diffmaskMatteG = 255;	
	This->diffmaskMatteB = 0;	
	This->diffmasknoiseradius = 0;
	This->analysisDownSampleSteps = 1;
	This->diffmaskHoleFillMaxSize = 0;
	This->diffmaskEdgeContract = 0;



moa_catch
moa_catch_end
moa_try_end
}



STDMETHODIMP_(void) MoaDestroy_TStdXtra(TStdXtra FAR * This) {
moa_try

	if (This->pValueInterface != NULL) 
		ThrowErr (This->pValueInterface->Release());
		
	if (This->pMoaUtils != NULL) 
		ThrowErr (This->pMoaUtils->Release());
		
	if (This->pMmImage != NULL){
		This->pMmImage->Release();
		This->pMmImage = NULL;
	}
		
	if (This->pMmList != NULL){
		This->pMmList->Release();
		This->pMmList = NULL;
	}
		
	if (This->pMmColor != NULL){
		This->pMmColor->Release();
		This->pMmColor = NULL;
	}



moa_catch
moa_catch_end
moa_try_end_void
}


/* ============================================================================= */
/* Methods in TStdXtra_IMoaRegister */
/* ============================================================================= */

/*****************************************************************************
 *  Data needed for Registering
 *	---------------------------
 *	Specific code needed to register different types of Xtras.  The skeleton
 *	source files include minimal implementations appropriate for each Xtra
 *	type.  Current necessary actions:
 *
 *	Scripting Xtra:				Add the Scripting Xtra Message Table
 *	Sprite Asset Xtra:			Nothing
 *	Tool Xtra:					Nothing
 *	Transition Asset Xtra		Nothing
 *
 *  ****optional: Register as Safe for Shockwave!
 *****************************************************************************/ 

STD_INTERFACE_CREATE_DESTROY(TStdXtra, IMoaRegister)

BEGIN_DEFINE_CLASS_INTERFACE(TStdXtra, IMoaRegister)
END_DEFINE_CLASS_INTERFACE

/* ----------------------------------------------------------------------------- */
STDMETHODIMP TStdXtra_IMoaRegister::Register(
	PIMoaCache pCache, 
	PIMoaXtraEntryDict pXtraDict
)
{	
moa_try
	PIMoaRegistryEntryDict		pReg;
	MoaBool						bItsSafe = TRUE;
	char versionStr[256];
	PMoaVoid pMemStr = NULL;

	/* Register the lingo xtra */
	ThrowErr(pCache->AddRegistryEntry(pXtraDict, &CLSID_TStdXtra, &IID_IMoaMmXScript, &pReg));

	/* Register the method table */
	sprintf(versionStr, versionInfo, VER_MAJORVERSION_STRING, VER_MINORVERSION_STRING, VER_BUGFIXVERSION_STRING);
	pMemStr = pObj->pCalloc->NRAlloc(sizeof(msgTable) + sizeof(versionStr));
	ThrowNull(pMemStr);

	strcpy((char *)pMemStr, versionStr);
	strcat((char *)pMemStr, msgTable);

	ThrowErr(pReg->Put(kMoaDrDictType_MessageTable, pMemStr, 0, kMoaDrDictKey_MessageTable));

	/* Mark xtra as safe for shockwave - but only if it IS safe ! */
	ThrowErr(pReg->Put(kMoaMmDictType_SafeForShockwave, &bItsSafe, sizeof(bItsSafe), kMoaMmDictKey_SafeForShockwave));
	

moa_catch
moa_catch_end
	if (pMemStr)
		pObj->pCalloc->NRFree(pMemStr);
moa_try_end
}



/* ============================================================================= */
/*  Methods in TStdXtra_IMoaMmXScript */
/* ============================================================================= */

BEGIN_DEFINE_CLASS_INTERFACE(TStdXtra, IMoaMmXScript)
END_DEFINE_CLASS_INTERFACE

//******************************************************************************
TStdXtra_IMoaMmXScript::TStdXtra_IMoaMmXScript(MoaError FAR * pError)
//------------------------------------------------------------------------------
{


	*pError = kMoaErr_NoErr;
}	

//******************************************************************************
TStdXtra_IMoaMmXScript::~TStdXtra_IMoaMmXScript()
//------------------------------------------------------------------------------
{


}

/* ----------------------------------------------------------------------------- */
STDMETHODIMP TStdXtra_IMoaMmXScript::Call (PMoaDrCallInfo callPtr)
{
moa_try

	//validate myron's existence before calling its members
	if(myron==NULL)myron = new Myron();

	switch	( callPtr->methodSelector ) 
	{
		case m_new:
			{
			/* Setup any instance vars for you Xtra here. new() is
			called via Lingo when creating a new instance. */
			/*
			 * --> insert additional code -->
		 	 */
			}
			break;
					
		/* Here is where new methods are added to the switch statement. Each
		   method should be defined in the msgTable defined in and have a 
		   constant defined in the associated enum. 
		*/  
             /*
		case m_globalHandler:
			ThrowErr(XScrpGlobalHandler(callPtr));
			break;

		case m_parentHandler:
			ThrowErr(XScrpParentHandler(callPtr));
			break;

		case m_childHandler:
			ThrowErr(XScrpChildHandler(callPtr));
			break;
			*/
			
		case webcamxtra_start:
			ThrowErr(XScrp_webcamxtra_start(callPtr));
			break;

		case webcamxtra_stop:
			ThrowErr(XScrp_webcamxtra_stop(callPtr));
			break;

		case webcamxtra_update:
			ThrowErr(XScrp_webcamxtra_update(callPtr));
			break;

		case webcamxtra_settings:
			ThrowErr(XScrp_webcamxtra_settings(callPtr));
			break;
			
		case webcamxtra_version:
			ThrowErr(XScrp_webcamxtra_version(callPtr));
			break;
			
		case webcamxtra_findGlobs:
			ThrowErr(XScrp_webcamxtra_findGlobs(callPtr));
			break;
			
		case webcamxtra_globsImage:
			ThrowErr(XScrp_webcamxtra_globsImage(callPtr));
			break;
			
		case webcamxtra_sensitivity:
			ThrowErr(XScrp_webcamxtra_sensitivity(callPtr));
			break;
			
		case webcamxtra_minDensity:
			ThrowErr(XScrp_webcamxtra_minDensity(callPtr));
			break;


		case webcamxtra_maxDensity:
			ThrowErr(XScrp_webcamxtra_maxDensity(callPtr));
			break;
			
		case webcamxtra_cameraImage:
			ThrowErr(XScrp_webcamxtra_cameraImage(callPtr));
			break;


		case webcamxtra_cameraImageCopy:
			ThrowErr(XScrp_webcamxtra_cameraImageCopy(callPtr));
			break;
			
		case webcamxtra_image://note, this points to cameraImage - that's not a typo.
			ThrowErr(XScrp_webcamxtra_cameraImage(callPtr));
			break;

		case webcamxtra_imageCopy://note, this points to cameraImage - that's not a typo.
			ThrowErr(XScrp_webcamxtra_cameraImageCopy(callPtr));
			break;
			
		case webcamxtra_globBoxes:
			ThrowErr(XScrp_webcamxtra_globBoxes(callPtr));
			break;

		case webcamxtra_globCenters:
			ThrowErr(XScrp_webcamxtra_globCenters(callPtr));
			break;
			
		case webcamxtra_globPixels:
			ThrowErr(XScrp_webcamxtra_globPixels(callPtr));
			break;
			
		case webcamxtra_globEdgePoints:
			ThrowErr(XScrp_webcamxtra_globEdgePoints(callPtr));
			break;
			
		case webcamxtra_globQuads:
			ThrowErr(XScrp_webcamxtra_globQuads(callPtr));
			break;
			
		case webcamxtra_trackColor:
			ThrowErr(XScrp_webcamxtra_trackColor(callPtr));
			break;
		
		case webcamxtra_trackNotColor:
			ThrowErr(XScrp_webcamxtra_trackNotColor(callPtr));
			break;
		
		case webcamxtra_average:
			ThrowErr(XScrp_webcamxtra_average(callPtr));
			break;
		
		case webcamxtra_averageFloat:
			ThrowErr(XScrp_webcamxtra_averageFloat(callPtr));
			break;
		
		case webcamxtra_retinaImage:
			ThrowErr(XScrp_webcamxtra_retinaImage(callPtr));
			break;
		
		case webcamxtra_adaptivity:
			ThrowErr(XScrp_webcamxtra_adaptivity(callPtr));
			break;
			
		case webcamxtra_adapt:
			ThrowErr(XScrp_webcamxtra_adapt(callPtr));
			break;
		
		case webcamxtra_differenceImage:
  			ThrowErr(XScrp_webcamxtra_differenceImage(callPtr));
			break;

		case webcamxtra_hitcheck:
			ThrowErr(XScrp_webcamxtra_hitCheck(callPtr));
			break;

		case webcamxtra_hijack:
  			ThrowErr(XScrp_webcamxtra_hijack(callPtr));
			break;


		case webcamxtra_width:
  			ThrowErr(XScrp_webcamxtra_width(callPtr));
			break;


		case webcamxtra_height:
  			ThrowErr(XScrp_webcamxtra_height(callPtr));
			break;



		case webcamxtra_getForcedWidth:
  			ThrowErr(XScrp_webcamxtra_getForcedWidth(callPtr));
			break;


		case webcamxtra_getForcedHeight:
  			ThrowErr(XScrp_webcamxtra_getForcedHeight(callPtr));
			break;

		case webcamxtra_setDifferenceMaskThreshold:
  			ThrowErr(XScrp_webcamxtra_setDifferenceMaskThreshold(callPtr));
			break;


		
		case webcamxtra_setDifferenceMaskMatteColor:
  			ThrowErr(XScrp_webcamxtra_setDifferenceMaskMatteColor(callPtr));
			break;


		case webcamxtra_setDifferenceMaskReduceNoise:
  			ThrowErr(XScrp_webcamxtra_setDifferenceMaskReduceNoise(callPtr));
			break;

		case webcamxtra_setAnalysisDownSampleSteps:
  			ThrowErr(XScrp_webcamxtra_setAnalysisDownSampleSteps(callPtr));
			break;

		case webcamxtra_setDifferenceMaskHoleFillMaxSize:
  			ThrowErr(XScrp_webcamxtra_setDifferenceMaskHoleFillMaxSize(callPtr));
			break;

		case webcamxtra_setDifferenceMaskEdgeContract:
  			ThrowErr(XScrp_webcamxtra_setDifferenceMaskEdgeContract(callPtr));
			break;

		case webcamxtra_updateCameraInSeperateThread:
  			ThrowErr(XScrp_webcamxtra_updateCameraInSeperateThread(callPtr));
			break;
		
		case webcamxtra_hijackFromFileRaw:
  			ThrowErr(XScrp_webcamxtra_hijackFromFileRaw(callPtr));
			break;
		
		/*
		 * --> insert additional methodSelector cases -->
		 */

	}
moa_catch
moa_catch_end
moa_try_end
}


/*****************************************************************************
 *  Private Methods
 *  -------------------
 *  Implementation of Private Class Methods
 /*
 *  This is the actual code for the defined methods. They are defined as 
 *  functions, and called from the switch statement in Call().
 *
 ****************************************************************************/

MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_start(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaMmValue argValue3;
	MoaLong w;
	MoaLong h;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	pciGetArgByIndex( pCall, 3, &argValue3 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &w));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue3, &h));

	myron->start(w,h);

moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_stop(PMoaDrCallInfo pCall)
{
	//MoaMmValue argValue;
	//MoaLong num;
	
moa_try

	/* This shows how to access an argument
	/  the first argument in the list is the "me" value, so the user arguments
	/  start at the second position in the list */
	//pciGetArgByIndex( pCall, 2, &argValue );
	
	//ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue, &num));
	//ThrowErr (pObj->pMoaUtils->PrintMessage1("ChildHandler called with (%d)\n", num));

	/*
	 *  --> insert additional code -->
	 */
	myron->stop();
	delete myron;
	
moa_catch
moa_catch_end	
moa_try_end	
}





MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_update(PMoaDrCallInfo pCall)
{
moa_try
	myron->update();
moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_settings(PMoaDrCallInfo pCall)
{
moa_try
	myron->settings();
moa_catch
moa_catch_end	
moa_try_end	
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_version(PMoaDrCallInfo pCall) {	
	char p[256];
	sprintf(p,"%s",myron->version());
moa_try
	ThrowErr (pObj->pValueInterface->StringToValue( p, &(pCall->resultValue) ));
moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_findGlobs(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaLong val2;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &val2));
	myron->findGlobs(val2);
	
moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_globsImage(PMoaDrCallInfo pCall)
{
	
	unsigned char *globPixels = myron->globsImage();
	
moa_try
    unsigned char *pPixels;
    //generate an image object using videoBaseAddress for the pixels.
   	pObj->pMmImage->NewImage(myron->width(),myron->height(),24,1,0, &(pCall->resultValue));
   	
    pObj->pMmImage->LockPixels(&(pCall->resultValue),(void**)&pPixels);
    
	int hmax = myron->height()-1;
	int w4 = 4*myron->width();
	int w3 = 3*myron->width();

    for(int y=0;y<myron->height();y++)for(int x=0;x<myron->width();x++){
	
#if defined(_MACINTOSH)
		pPixels[y*w4+x*4+0] = 255;
	 	pPixels[y*w4+x*4+1] = globPixels[y*myron->width()+x];
	 	pPixels[y*w4+x*4+2] = globPixels[y*myron->width()+x];
	 	pPixels[y*w4+x*4+3] = globPixels[y*myron->width()+x];
#else
		pPixels[((hmax-y)*w4+x*4+3)] = 255;
	 	pPixels[((hmax-y)*w4+x*4+2)] = globPixels[y*myron->width()+x];
	 	pPixels[((hmax-y)*w4+x*4+1)] = globPixels[y*myron->width()+x];
	 	pPixels[((hmax-y)*w4+x*4+0)] = globPixels[y*myron->width()+x];
#endif
	}

	pObj->pMmImage->UnlockPixels(&(pCall->resultValue));	
	
	//ThrowErr(pObj->pValueInterface->IntegerToValue(  69   , &pCall->resultValue));

moa_catch
moa_catch_end	
moa_try_end	
}




MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_sensitivity(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	double val2;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	
	ThrowErr (pObj->pValueInterface->ValueToFloat( &argValue2, &val2));

	myron->sensitivity((float)val2);
	
moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_minDensity(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaLong val2;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &val2));

	myron->minDensity(val2);
	
moa_catch
moa_catch_end	
moa_try_end	
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_maxDensity(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaLong val2;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &val2));

	myron->maxDensity(val2);
	
moa_catch
moa_catch_end	
moa_try_end	
}

MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_cameraImage(PMoaDrCallInfo pCall)
{
	unsigned char *cameraPixels = myron->image();
moa_try
    unsigned char *pPixels;
    //generate an image object using videoBaseAddress for the pixels.
   	pObj->pMmImage->NewImage(myron->width(),myron->height(),24,0,0, &(pCall->resultValue));
   	
    pObj->pMmImage->LockPixels(&(pCall->resultValue),(void**)&pPixels);
	int hmax = myron->height()-1;
	int w4 = 4*myron->width();
	int w3 = 3*myron->width();

	//memcpy(pPixels,cameraPixels,myron->width()*myron->height()*3);


    for(int y=0;y<myron->height();y++)for(int x=0;x<myron->width();x++){

#if defined(_MACINTOSH)

		pPixels[y*w4+x*4+0] = 255;
	 	pPixels[y*w4+x*4+1] = cameraPixels[y*w3+x*3+0];
	 	pPixels[y*w4+x*4+2] = cameraPixels[y*w3+x*3+1];
	 	pPixels[y*w4+x*4+3] = cameraPixels[y*w3+x*3+2];

#else
		pPixels[((hmax-y)*w4+x*4+3)] = 255;
	 	pPixels[((hmax-y)*w4+x*4+2)] = cameraPixels[(y*w3)+x*3+0];
	 	pPixels[((hmax-y)*w4+x*4+1)] = cameraPixels[(y*w3)+x*3+1];
	 	pPixels[((hmax-y)*w4+x*4+0)] = cameraPixels[(y*w3)+x*3+2];
#endif

	}
	
	pObj->pMmImage->UnlockPixels(&(pCall->resultValue));	
	
moa_catch
moa_catch_end	
moa_try_end	
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_globBoxes(PMoaDrCallInfo pCall){

	int *boxes = myron->globBoxes();
	int count = myron->globCount();

moa_try

	pObj->pMmList->NewListValue(&pCall->resultValue);
	
	for(int i=0;i<count;i++){
		MoaMmValue newval;
		MoaRect r;
		r.left = boxes[i*4+0];
		r.top = boxes[i*4+1];
		r.right = boxes[i*4+2];
		r.bottom = boxes[i*4+3];
		pObj->pValueInterface->RectToValue(&r,&newval);
		pObj->pMmList->AppendValueToList(&pCall->resultValue,&newval);
		pObj->pValueInterface->ValueRelease(&newval);
	}
	
moa_catch
moa_catch_end	
moa_try_end	
}

MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_globCenters(PMoaDrCallInfo pCall){


	int *pts = myron->globCenters();
	int count = myron->globCount();

moa_try
	
	pObj->pMmList->NewListValue(&pCall->resultValue);
	
	for(int i=0;i<count;i++){
		MoaMmValue newval;
		MoaPoint r;
		r.x = pts[i*2  ];
		r.y = pts[i*2+1];
		pObj->pValueInterface->PointToValue(&r,&newval);
		pObj->pMmList->AppendValueToList(&pCall->resultValue,&newval);
		pObj->pValueInterface->ValueRelease(&newval);
	}	
	
	
moa_catch
moa_catch_end	
moa_try_end	
}




MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_globPixels(PMoaDrCallInfo pCall){

	int *pxls = myron->globPixels();
	int count = myron->globPixelsCount();


moa_try
	
	pObj->pMmList->NewListValue(&pCall->resultValue);
	
	MoaMmValue thisList;

	MoaPoint p;
	int tag;	
	for(int i=0;i<count;i++){
		MoaMmValue newval;
		tag = pxls[i*3+2];
		p.x = pxls[i*3+0];
		p.y = pxls[i*3+1];
		pObj->pValueInterface->PointToValue(&p,&newval);
		
		if(tag==1){//beginning a glob
			pObj->pMmList->NewListValue(&thisList);
		}
		pObj->pMmList->AppendValueToList(&thisList,&newval);
		pObj->pValueInterface->ValueRelease(&newval);
		if(tag==2){//ending a glob
			pObj->pMmList->AppendValueToList(&pCall->resultValue,&thisList);
			pObj->pValueInterface->ValueRelease(&thisList);
		}
	}
moa_catch
moa_catch_end	
moa_try_end	
}

MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_globEdgePoints(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaLong val2;
	
	int count;
	int *pxls;
	int i;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &val2));

	count = myron->globEdgePoints(val2);//must be called before result
	pxls = myron->globEdgePointsResult();
	
	pObj->pMmList->NewListValue(&pCall->resultValue);
	
	MoaMmValue thisList;

	MoaPoint p;
	int tag;	
	for(i=0;i<count;i++){
		MoaMmValue newval;
		tag = pxls[i*3+0];
		p.x = pxls[i*3+1];
		p.y = pxls[i*3+2];
		pObj->pValueInterface->PointToValue(&p,&newval);
		
		if(tag==1){//beginning a glob
			pObj->pMmList->NewListValue(&thisList);
		}
		pObj->pMmList->AppendValueToList(&thisList,&newval);
		pObj->pValueInterface->ValueRelease(&newval);
		if(tag==2){//ending a glob
			pObj->pMmList->AppendValueToList(&pCall->resultValue,&thisList);
			pObj->pValueInterface->ValueRelease(&thisList);
		}
	}

moa_catch
moa_catch_end	
moa_try_end	
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_globQuads(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaMmValue argValue3;
	double minSideLength;
	double maxSideLength;
	int *quads;
	int count;
	int i;
moa_try

	pciGetArgByIndex( pCall, 2, &argValue2 );
	pciGetArgByIndex( pCall, 3, &argValue3 );
	 
	ThrowErr (pObj->pValueInterface->ValueToFloat( &argValue2, &minSideLength));
	ThrowErr (pObj->pValueInterface->ValueToFloat( &argValue3, &maxSideLength));

	quads = myron->globQuads((float)minSideLength,(float)maxSideLength);
	count = myron->globCount();

	pObj->pMmList->NewListValue(&pCall->resultValue);
	
	MoaMmValue thisList;

	MoaPoint p;
	for(i=0;i<count;i++){
		MoaMmValue newval;
		pObj->pMmList->NewListValue(&thisList);
		
		p.x = quads[i*8+0];
		p.y = quads[i*8+1];
		pObj->pValueInterface->PointToValue(&p,&newval);		
		pObj->pMmList->AppendValueToList(&thisList,&newval);
		
		p.x = quads[i*8+2];
		p.y = quads[i*8+3];
		pObj->pValueInterface->PointToValue(&p,&newval);		
		pObj->pMmList->AppendValueToList(&thisList,&newval);
		
		
		p.x = quads[i*8+4];
		p.y = quads[i*8+5];
		pObj->pValueInterface->PointToValue(&p,&newval);		
		pObj->pMmList->AppendValueToList(&thisList,&newval);
		
		p.x = quads[i*8+6];
		p.y = quads[i*8+7];
		pObj->pValueInterface->PointToValue(&p,&newval);		
		pObj->pMmList->AppendValueToList(&thisList,&newval);
		
		pObj->pValueInterface->ValueRelease(&newval);

		pObj->pMmList->AppendValueToList(&pCall->resultValue,&thisList);
		pObj->pValueInterface->ValueRelease(&thisList);
	}

moa_catch
moa_catch_end	
moa_try_end	
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_trackColor(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaMmValue argValue3;
	MoaMmValue argValue4;
	MoaMmValue argValue5;
	MoaLong red;
	MoaLong green;
	MoaLong blue;
	MoaLong tolerance;

moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	pciGetArgByIndex( pCall, 3, &argValue3 );
	pciGetArgByIndex( pCall, 4, &argValue4 );
	pciGetArgByIndex( pCall, 5, &argValue5 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &red));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue3, &green));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue4, &blue));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue5, &tolerance));
	
	myron->trackColor(red,green,blue,tolerance);
moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_trackNotColor(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaMmValue argValue3;
	MoaMmValue argValue4;
	MoaMmValue argValue5;
	MoaLong red;
	MoaLong green;
	MoaLong blue;
	MoaLong tolerance;

moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	pciGetArgByIndex( pCall, 3, &argValue3 );
	pciGetArgByIndex( pCall, 4, &argValue4 );
	pciGetArgByIndex( pCall, 5, &argValue5 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &red));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue3, &green));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue4, &blue));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue5, &tolerance));
	
	myron->trackNotColor(red,green,blue,tolerance);
moa_catch
moa_catch_end	
moa_try_end	
}




MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_average(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaMmValue argValue3;
	MoaMmValue argValue4;
	MoaMmValue argValue5;
	MoaMmValue argValue6;
	MoaLong region_top;
	MoaLong region_left;
	MoaLong region_right;
	MoaLong region_bottom;
	MoaLong skip;
	unsigned char retval[3];
	//int r;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	pciGetArgByIndex( pCall, 3, &argValue3 );
	pciGetArgByIndex( pCall, 4, &argValue4 );
	pciGetArgByIndex( pCall, 5, &argValue5 );
	pciGetArgByIndex( pCall, 6, &argValue6 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &region_left));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue3, &region_top));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue4, &region_right));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue5, &region_bottom));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue6, &skip));
	
	MoaMmColorSpec c;
	c.type = kMoaMmColorSpec_RGB;
	
	myron->average(region_left,region_top,region_right,region_bottom,retval,skip);

	c.color.rgb.red = retval[0];
	c.color.rgb.green = retval[1];
	c.color.rgb.blue = retval[2];
	

	pObj->pMmColor->ColorToValue(&c,&pCall->resultValue);

moa_catch
moa_catch_end	
moa_try_end	
}




MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_averageFloat(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaMmValue argValue3;
	MoaMmValue argValue4;
	MoaMmValue argValue5;
	MoaMmValue argValue6;
	MoaLong region_top;
	MoaLong region_left;
	MoaLong region_right;
	MoaLong region_bottom;
	MoaLong skip;
	float retval[3];
	//int r;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	pciGetArgByIndex( pCall, 3, &argValue3 );
	pciGetArgByIndex( pCall, 4, &argValue4 );
	pciGetArgByIndex( pCall, 5, &argValue5 );
	pciGetArgByIndex( pCall, 6, &argValue6 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &region_left));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue3, &region_top));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue4, &region_right));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue5, &region_bottom));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue6, &skip));
	
	pObj->pMmList->NewListValue(&pCall->resultValue);
	
	myron->averageFloat(region_left,region_top,region_right,region_bottom,retval,skip);

	MoaMmValue rval;
	MoaMmValue gval;
	MoaMmValue bval;
/*
	c.color.rgb.red = (int)retval[0];
	c.color.rgb.green = (int)retval[1];
	c.color.rgb.blue = (int)retval[2];
*/
	ThrowErr(pObj->pValueInterface->FloatToValue(retval[0], &rval));
	ThrowErr(pObj->pValueInterface->FloatToValue(retval[1], &gval));
	ThrowErr(pObj->pValueInterface->FloatToValue(retval[2], &bval));


	pObj->pMmList->AppendValueToList(&pCall->resultValue,&rval);
	pObj->pMmList->AppendValueToList(&pCall->resultValue,&gval);
	pObj->pMmList->AppendValueToList(&pCall->resultValue,&bval);

	pObj->pValueInterface->ValueRelease(&rval);
	pObj->pValueInterface->ValueRelease(&gval);
	pObj->pValueInterface->ValueRelease(&bval);

moa_catch
moa_catch_end	
moa_try_end	
}






MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_retinaImage(PMoaDrCallInfo pCall)
{
	unsigned char *retinaPixels = myron->retinaImage();	
moa_try
    unsigned char *pPixels;
    //generate an image object using videoBaseAddress for the pixels.
   	pObj->pMmImage->NewImage(myron->width(),myron->height(),24,1,0, &(pCall->resultValue));
   	
    pObj->pMmImage->LockPixels(&(pCall->resultValue),(void**)&pPixels);
	
	
	int hmax = myron->height()-1;
	int w4 = 4*myron->width();
	int w3 = 3*myron->width();

    for(int y=0;y<myron->height();y++)for(int x=0;x<myron->width();x++){
	
#if defined(_MACINTOSH)
		pPixels[y*w4+x*4+0] = 255;
	 	pPixels[y*w4+x*4+1] = retinaPixels[y*w3+x*3+0];
	 	pPixels[y*w4+x*4+2] = retinaPixels[y*w3+x*3+1];
	 	pPixels[y*w4+x*4+3] = retinaPixels[y*w3+x*3+2];
#else
		pPixels[((hmax-y)*w4+x*4+3)] = 255;
	 	pPixels[((hmax-y)*w4+x*4+2)] = retinaPixels[y*w3+x*3+0];
	 	pPixels[((hmax-y)*w4+x*4+1)] = retinaPixels[y*w3+x*3+1];
	 	pPixels[((hmax-y)*w4+x*4+0)] = retinaPixels[y*w3+x*3+2];
#endif

	}
	
	
	
	
	pObj->pMmImage->UnlockPixels(&(pCall->resultValue));	
	
moa_catch
moa_catch_end	
moa_try_end	
}





MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_adaptivity(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	double ad;
moa_try

	pciGetArgByIndex( pCall, 2, &argValue2 );
	 
	ThrowErr (pObj->pValueInterface->ValueToFloat( &argValue2, &ad));
	myron->adaptivity((float)ad);
	
moa_catch
moa_catch_end	
moa_try_end	
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_adapt(PMoaDrCallInfo pCall)
{	
moa_try

	myron->adapt();
moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_differenceImage(PMoaDrCallInfo pCall)
{
	unsigned char *differencePixels = myron->differenceImage();
moa_try
    unsigned char *pPixels;
    //generate an image object using videoBaseAddress for the pixels.
   	pObj->pMmImage->NewImage(myron->width(),myron->height(),24,1,0, &(pCall->resultValue));
   	
    pObj->pMmImage->LockPixels(&(pCall->resultValue),(void**)&pPixels);
    

	int hmax = myron->height()-1;
	int w4 = 4*myron->width();
	int w3 = 3*myron->width();

    for(int y=0;y<myron->height();y++)for(int x=0;x<myron->width();x++){
	
#if defined(_MACINTOSH)
		pPixels[y*w4+x*4+0] = 255;
	 	pPixels[y*w4+x*4+1] = differencePixels[y*w3+x*3+0];
	 	pPixels[y*w4+x*4+2] = differencePixels[y*w3+x*3+1];
	 	pPixels[y*w4+x*4+3] = differencePixels[y*w3+x*3+2];
#else
		pPixels[((hmax-y)*w4+x*4+3)] = 255;
	 	pPixels[((hmax-y)*w4+x*4+2)] = differencePixels[y*w3+x*3+0];
	 	pPixels[((hmax-y)*w4+x*4+1)] = differencePixels[y*w3+x*3+1];
	 	pPixels[((hmax-y)*w4+x*4+0)] = differencePixels[y*w3+x*3+2];
#endif

	}
		
	pObj->pMmImage->UnlockPixels(&(pCall->resultValue));	
	
	//ThrowErr(pObj->pValueInterface->IntegerToValue(  69   , &pCall->resultValue));

moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_hitCheck(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;	

	unsigned char *globPixels = myron->globsImage();
	int i;

moa_try

	int hmax = myron->height()-1;

	pciGetArgByIndex( pCall, 2, &argValue2 );	

	ThrowErr (pObj->pMmList->NewListValue(&pCall->resultValue));
		
	for (i = 0; i < pObj->pMmList->CountElements(&argValue2); i++) {
		MoaMmValue componentValue;
		MoaMmValue newVal;
		MoaPoint tPoint;

		ThrowErr (pObj->pMmList->GetValueByIndex(&argValue2, i+1, &componentValue));

		// the componentValue is a point. Let's check what is inside the point.
		ThrowErr (pObj->pValueInterface->ValueToPoint(&componentValue, &tPoint));
		ThrowErr (pObj->pValueInterface->ValueRelease(&componentValue));
		if (tPoint.x < myron->width() && tPoint.y < myron->height()) {
			pObj->pMoaUtils->PrintMessage3("-- [WebCamXtra] x:%ld y:%ld pixel:%ld\n", tPoint.x, tPoint.y,  globPixels[tPoint.y*myron->width()+tPoint.x]);
	 		ThrowErr (pObj->pValueInterface->IntegerToValue((globPixels[tPoint.y*myron->width()+tPoint.x] == 0), &newVal));
		} else
			ThrowErr (pObj->pValueInterface->IntegerToValue(0, &newVal));
			
		ThrowErr (pObj->pMmList->AppendValueToList(&pCall->resultValue,&newVal));
		ThrowErr (pObj->pValueInterface->ValueRelease(&newVal));
	}

	
moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_hijack(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	
	MoaMmImageInfo info;
	pObj->pMmImage->GetImageInfo(&argValue2,&info);
	
	unsigned char *pPixels;
    pObj->pMmImage->LockPixels(&argValue2,(void**)&pPixels);
#if defined(_MACINTOSH)
    myron->hijackARGB(info.iWidth,info.iHeight,pPixels);    
#else
    myron->hijackARGBInvert(info.iWidth,info.iHeight,pPixels);    
#endif
	pObj->pMmImage->UnlockPixels(&argValue2);
	
moa_catch
moa_catch_end	
moa_try_end	
}





MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_width(PMoaDrCallInfo pCall){
moa_try
	ThrowErr(pObj->pValueInterface->IntegerToValue(myron->width(), &pCall->resultValue));
moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_height(PMoaDrCallInfo pCall){
moa_try
	ThrowErr(pObj->pValueInterface->IntegerToValue(myron->height(), &pCall->resultValue));
moa_catch
moa_catch_end	
moa_try_end	
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_getForcedWidth(PMoaDrCallInfo pCall){
moa_try
	ThrowErr(pObj->pValueInterface->IntegerToValue(myron->getForcedWidth(), &pCall->resultValue));
moa_catch
moa_catch_end	
moa_try_end	
}


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_getForcedHeight(PMoaDrCallInfo pCall){
moa_try
	ThrowErr(pObj->pValueInterface->IntegerToValue(myron->getForcedHeight(), &pCall->resultValue));
moa_catch
moa_catch_end	
moa_try_end	
}





int recurseFill(unsigned char *pix,
			int mw,
			int mh,
			int rowbytes,
			int x,
			int y			
			,unsigned char red,unsigned char green,unsigned char blue
			
){

	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = pix[(rowbytes*y+x*4)+1];
	g = pix[(rowbytes*y+x*4)+2];
	b = pix[(rowbytes*y+x*4)+3];

	if(r==0 && g==255 && b==0){//is it green?
		
		pix[(rowbytes*y+x*4)+1] = red;
		pix[(rowbytes*y+x*4)+2] = green;
		pix[(rowbytes*y+x*4)+3] = blue;
		
		return true;
	}else return false;
}


/*
	shrinks a white-on-red glob image by 1 pixel. only knows 32-bit image depth.
*/
void contract(unsigned char *pix,int mw,int mh,int rowbytes,int smallestWidth, int smallestHeight){
	int y_dwP;
	int xP;

	//mask pixels now	    
	//eliminate black globs that are completely surrounded by white
	for(int y=0;y<smallestHeight;y++){
		#if defined (WIN32)
				 y_dwP=((smallestHeight-1)-y)*rowbytes;
		#else
		    	y_dwP=y*rowbytes;
		#endif
		    	int y_mw3=y*mw*3;
	

		for(int x=0;x<smallestWidth;x++){
	    	xP = x*4;
			
			//if the pixel is matted out...			
			if(pix[y_dwP+xP+3]==255){

				//test for edge-ness
				int foundEdge = false;
				
				// S				
				if(y<mh-1){
					if(pix[(y+1)*rowbytes+xP+3] == 0){
						foundEdge=true;
					}
				}
				
				// N
				if(y>0){
					if(pix[(y-1)*rowbytes+xP+3] == 0){
						foundEdge=true;
					}
				}
				
				// E
				if(x<mw-1){
					if(pix[y_dwP+(x+1)*4+3] == 0){
						foundEdge=true;
					}
				}
				
				// W
				if(x>0){
					if(pix[y_dwP+(x-1)*4+3] == 0){
						foundEdge=true;
					}
				}
				
				
				//added in the corners to make it square.
				
				// NE
				if(y>0 && x<mw-1){
					if(pix[(y-1)*rowbytes+(x+1)*4+3] == 0){
						foundEdge=true;
					}
				}
				
				
				// NW
				if(y>0 && x>0){
					if(pix[(y-1)*rowbytes+(x-1)*4+3] == 0){
						foundEdge=true;
					}
				}
				
				
				// SE
				if(y<mh-1 && x<mw-1){
					if(pix[(y+1)*rowbytes+(x+1)*4+3] == 0){
						foundEdge=true;
					}
				}
				
				
				// SW
				if(y<mh-1 && x>0){
					if(pix[(y+1)*rowbytes+(x-1)*4+3] == 0){
						foundEdge=true;
					}
				}
				
				
				
				if(foundEdge){
			 		pix[y_dwP+xP+2] = 0;
			 	}



			}

		}
	}


	//then convert all magenta to red.
	for(int y=0;y<smallestHeight;y++){
			#if defined (WIN32)
					 y_dwP=((smallestHeight-1)-y)*rowbytes;
			#else
			    	y_dwP=y*rowbytes;
			#endif
			    	int y_mw3=y*mw*3;
		
			for(int x=0;x<smallestWidth;x++){
		    	xP = x*4;
				
				
				// if the pixel is magenta			
				if(
					pix[y_dwP+xP+1]==255 &&
					pix[y_dwP+xP+2]==0   &&
					pix[y_dwP+xP+3]==255
				
				){
					// then make it red.
					pix[y_dwP+xP+1]=255;
					pix[y_dwP+xP+2]=0;
					pix[y_dwP+xP+3]=0;

				
				}
			}
		}


}


/*
	kills the donut holes in the matted content
*/

void eliminateHoles(unsigned char *pix,int mw,int mh,int rowbytes,int holefillmaxsize){

	int rx;
	int ry;
	
	int ret;
	int regionCount = 0;
	unsigned char curRed;
	unsigned char curGreen;
	unsigned char curBlue;



	int *lifo = new int[mw*mh*6];//queue for the recursive XY recording.
	int *cach = new int[mw*mh*6];//queue for the XY list caching.
	
	int lifo_count = 0;
	int cach_count = 0;
	int foundOne = false;
	
	curRed = 255;//colours[regionCount*3+0];
	curGreen = 0;//colours[regionCount*3+1];
	curBlue = 0;//colours[regionCount*3+2];

	for(int y=0;y<mh;y++){
		for(int x=0;x<mw;x++){

			
			//pop THIS one on for analysis.
			lifo[lifo_count*2  ] = x;
			lifo[lifo_count*2+1] = y;
			lifo_count++;
			
			foundOne = false;
			cach_count = 0;
			while(lifo_count>0){//loop forever until we don't find any more
				
				//pop a job off the stack.
				rx = lifo[(lifo_count-1)*2  ];
				ry = lifo[(lifo_count-1)*2+1];
				lifo_count--;
				
				ret = recurseFill(pix,mw,mh,rowbytes,rx,ry,curRed,curGreen,curBlue);
				if(ret){
				
					//record it.
					cach[cach_count*2  ] = rx;
					cach[cach_count*2+1] = ry;
					cach_count++;

					//queue up the neighbours for analysis.
						
					if(rx<mw-1){
						lifo[lifo_count*2  ] = rx+1;
						lifo[lifo_count*2+1] = ry;
						lifo_count++;
					}

					if(rx>0){											
						lifo[lifo_count*2  ] = rx-1;
						lifo[lifo_count*2+1] = ry;
						lifo_count++;
					}
					
					if(ry<mh-1){
						lifo[lifo_count*2  ] = rx;
						lifo[lifo_count*2+1] = ry+1;
						lifo_count++;
					}
					
					if(ry>0){
						lifo[lifo_count*2  ] = rx;
						lifo[lifo_count*2+1] = ry-1;
						lifo_count++;
					}
					
					foundOne = true;
				}
			}
			
			if(foundOne){
				
				if(cach_count<  holefillmaxsize  ){//are we within donut hole limit?
					//loop through them all and fill them with some colour.
					//attempt to re-fill it with black
					while(cach_count>0){
						//pop a job off the stack.
						rx = cach[(cach_count-1)*2  ];
						ry = cach[(cach_count-1)*2+1];
						cach_count--;	
						
						pix[(rowbytes*ry+rx*4)+1] = 255;
						pix[(rowbytes*ry+rx*4)+2] = 255;
						pix[(rowbytes*ry+rx*4)+3] = 255;
							
					}
				}	
				cach_count--;	
		
					
			}
			
			
		}	
	}
	
	
	delete lifo;
	delete cach;	
}



/*
	NNAPick
	Nearest Neighbor Average by a radius - simlar to ::average(), but written for use with points - CENTER-oriented.
	effectively omits neighbor pixels that are off the map.
	
	[  ][N ][  ]
	[W ]    [E ]
	[  ][S ][  ]


	
*/


int averageByCenter(int x,int y,unsigned char *pix, int w,int h, int rad){

	int accum = 0;
	int pixelcount = 0;
	int xx;
	int yy;
	
	//for each X movement
	for(int i=0;i<rad*2+1;i++){
		
		//for each Y movement
		for(int ii=0;ii<rad*2+1;ii++){
			xx=x+(i-rad);
			yy=y+(ii-rad);
			
			//filter out the pixels that are off the edge
			if(yy>=0 && yy < h && xx>=0 && xx < w){
				pixelcount++;                       
				accum += pix[(yy*w+xx)*3  ];          
				accum += pix[(yy*w+xx)*3+1];          
				accum += pix[(yy*w+xx)*3+2];         
			}

		}
	}
	
	return accum / pixelcount;	
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_cameraImageCopy(PMoaDrCallInfo pCall){
	MoaMmImageInfo imgInfo;
	unsigned char *srcpix = myron->image();
	unsigned char *diffpix = myron->differenceImage();
	MoaMmValue argValue1;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue1 );
    unsigned char *dstpix;


    pObj->pMmImage->GetImageInfo(&argValue1,&imgInfo);
    pObj->pMmImage->LockPixels(&argValue1,(void**)&dstpix);

	int smallestWidth = myron->width();
	if(smallestWidth>imgInfo.iWidth)smallestWidth = imgInfo.iWidth;
	
	int smallestHeight = myron->height();
	if(smallestHeight>imgInfo.iHeight)smallestHeight = imgInfo.iHeight;

	int mw = myron->width();
	int mh = myron->height();
	
	int mw3 = myron->width()*3;
	int dwP = imgInfo.iRowBytes;
	int y_dwP;
	int y_mw3;
	int x3;
	int xP; 
		
	
	int averageByCenter_mod;
		
	if(imgInfo.iTotalDepth==32){
			
		for(int y=0;y<smallestHeight;y++){
					
				#if defined (WIN32)
						 y_dwP=((smallestHeight-1)-y)*dwP;
				#else
				    	y_dwP=y*dwP;
				#endif
				    	y_mw3=y*mw3;
				    	
				    	 
				for(int x=0;x<smallestWidth;x++){
				
					if( x%(pObj->analysisDownSampleSteps)==0){
						averageByCenter_mod = averageByCenter(x,y,diffpix,mw,mh, pObj->diffmasknoiseradius);
					}
					
			    	x3 = (x<<1)+x;
			    	xP = x*(imgInfo.iTotalDepth/8);

					#if defined (WIN32)
					/**
						note: win32 version is falling behind because of speed development time in simon biggs proj. consider porting up
						to the myron core before coming back and doing the per-wrapper tweaks.
					**/
						dstpix[y_dwP+xP+3] = 255;
					 	dstpix[y_dwP+xP+2] = srcpix[y_mw3+x3  ];
					 	dstpix[y_dwP+xP+1] = srcpix[y_mw3+x3+1];
					 	dstpix[y_dwP+xP  ] = srcpix[y_mw3+x3+2];
					#else
					
						if( averageByCenter_mod > pObj->diffmaskthresh ){

							//copy the pixel from srcpix to dstpix
							dstpix[y_dwP+xP  ] = 255;
						 	dstpix[y_dwP+xP+1] = srcpix[y_mw3+x3  ];
						 	dstpix[y_dwP+xP+2] = srcpix[y_mw3+x3+1];
						 	dstpix[y_dwP+xP+3] = srcpix[y_mw3+x3+2];
						}else{
						
							//render the matte
							dstpix[y_dwP+xP  ] = 255;
						 	dstpix[y_dwP+xP+1] = pObj->diffmaskMatteR;
						 	dstpix[y_dwP+xP+2] = pObj->diffmaskMatteG;
						 	dstpix[y_dwP+xP+3] = pObj->diffmaskMatteB;
						}
					#endif
							
				}				
				
		}
		    
		//eliminate black globs that are completely surrounded by white
		for(int y=0;y<smallestHeight;y++){
				#if defined (WIN32)
						 y_dwP=((smallestHeight-1)-y)*dwP;
				#else
				    	y_dwP=y*dwP;
				#endif
				    	y_mw3=y*mw3;
			

				for(int x=0;x<smallestWidth;x++){
			    	x3 = (x<<1)+x;
			    	xP = x*(imgInfo.iTotalDepth/8);
						

					//if the pixel is matted out...			
					if(
						dstpix[y_dwP+xP+1] == pObj->diffmaskMatteR &&
						dstpix[y_dwP+xP+2] == pObj->diffmaskMatteG &&
						dstpix[y_dwP+xP+3] == pObj->diffmaskMatteB
					){
						//copy the pixel from srcpix to dstpix
						dstpix[y_dwP+xP  ] = 255;
					 	dstpix[y_dwP+xP+1] = 0;
					 	dstpix[y_dwP+xP+2] = 255;
					 	dstpix[y_dwP+xP+3] = 0;
					}else{
						//copy the pixel from srcpix to dstpix
						dstpix[y_dwP+xP  ] = 255;
					 	dstpix[y_dwP+xP+1] = 255;
					 	dstpix[y_dwP+xP+2] = 255;
					 	dstpix[y_dwP+xP+3] = 255;

					}

				}

		}

		eliminateHoles(dstpix,mw,mh,dwP,pObj->diffmaskHoleFillMaxSize);

		if(pObj->diffmaskEdgeContract>0)for(int i=0;i<pObj->diffmaskEdgeContract;i++)contract(dstpix,mw,mh,dwP,smallestWidth, smallestHeight);		


		//mask pixels now	    
		for(int y=0;y<smallestHeight;y++){
				#if defined (WIN32)
						 y_dwP=((smallestHeight-1)-y)*dwP;
				#else
				    	y_dwP=y*dwP;
				#endif
				    	y_mw3=y*mw3;
			
				for(int x=0;x<smallestWidth;x++){
			    	xP = x*(imgInfo.iTotalDepth/8);
					x3 = x*3;
					
					//if the pixel is matted out...			
					if(
						dstpix[y_dwP+xP+1] == 255 &&
						dstpix[y_dwP+xP+2] == 0 &&
						dstpix[y_dwP+xP+3] == 0
					){
						//copy the pixel from srcpix to dstpix
						
						#if(__LITTLE_ENDIAN__)
						dstpix[y_dwP+xP+3] = 255;
					 	dstpix[y_dwP+xP+2] = pObj->diffmaskMatteR;
					 	dstpix[y_dwP+xP+1] = pObj->diffmaskMatteG;
					 	dstpix[y_dwP+xP+0] = pObj->diffmaskMatteB;
						#else
						dstpix[y_dwP+xP+0] = 255;
					 	dstpix[y_dwP+xP+1] = pObj->diffmaskMatteR;
					 	dstpix[y_dwP+xP+2] = pObj->diffmaskMatteG;
					 	dstpix[y_dwP+xP+3] = pObj->diffmaskMatteB;
						#endif
				}else{
					
					
						//copy the pixel from srcpix to dstpix
						
						#if(__LITTLE_ENDIAN__)
						dstpix[y_dwP+xP+3] = 255;
					 	dstpix[y_dwP+xP+2] = srcpix[y_mw3+x3+0];
					 	dstpix[y_dwP+xP+1] = srcpix[y_mw3+x3+1];
					 	dstpix[y_dwP+xP+0] = srcpix[y_mw3+x3+2];
						#else
						dstpix[y_dwP+xP+0] = 255;
					 	dstpix[y_dwP+xP+1] = srcpix[y_mw3+x3+0];
					 	dstpix[y_dwP+xP+2] = srcpix[y_mw3+x3+1];
					 	dstpix[y_dwP+xP+3] = srcpix[y_mw3+x3+2];
						#endif
					}

				}
		}


		
	}else if(imgInfo.iTotalDepth==16){
			unsigned char r,g_hi,g_lo,b;
	
			for(int y=0;y<smallestHeight;y++){
				#if defined (WIN32)
						 y_dwP=((smallestHeight-1)-y)*dwP;
				#else
				    	y_dwP=y*dwP;
				#endif

		    	y_mw3=y*mw3;
			    for(int x=0;x<smallestWidth;x++){
			    		x3 = (x<<1)+x;
				    	xP = x*(imgInfo.iTotalDepth/8);

						/*
						arrrrrgg gggbbbbb
						*/
	

					#if defined(__LITTLE_ENDIAN__)

						b    = (srcpix[y_mw3+x3  ] & 0xF8) >> 1;
						g_lo = (srcpix[y_mw3+x3+1] & 0xC0) >> 6;
						g_hi = (srcpix[y_mw3+x3+1] & 0x38) << 2;
						r    = (srcpix[y_mw3+x3+2] & 0xF8) >> 3;
					#else
						r    = (srcpix[y_mw3+x3  ] & 0xF8) >> 1;
						g_hi = (srcpix[y_mw3+x3+1] & 0xC0) >> 6;
						g_lo = (srcpix[y_mw3+x3+1] & 0x38) << 2;
						b    = (srcpix[y_mw3+x3+2] & 0xF8) >> 3;
					#endif
						
						dstpix[y_dwP+xP  ] = 0x80 | r | g_hi;
						dstpix[y_dwP+xP+1] = g_lo | b;
					

				}//end for x
			}//end for y

	}else{ //8 bit is as far down as I will go for now.
	
			MoaMmRGBTriple rgbTriple;
			MoaMmColorIndex returnIndex;
			for(int y=0;y<smallestHeight;y++){
				#if defined (WIN32)
						 y_dwP=((smallestHeight-1)-y)*dwP;
				#else
				    	y_dwP=y*dwP;
				#endif
				
		    	y_mw3=y*mw3;
			    for(int x=0;x<smallestWidth;x++){
			    	x3 = (x<<1)+x;
			    	//xP = x*(imgInfo.iTotalDepth/8);	
			    	
					
					#if defined(__LITTLE_ENDIAN__)
					rgbTriple.blue   = srcpix[y_mw3+x3  ];
					rgbTriple.green = srcpix[y_mw3+x3+1];
					rgbTriple.red  = srcpix[y_mw3+x3+2];
					#else
					rgbTriple.red   = srcpix[y_mw3+x3  ];
					rgbTriple.green = srcpix[y_mw3+x3+1];
					rgbTriple.blue  = srcpix[y_mw3+x3+2];
					#endif
					
					ThrowErr(pObj->pMoaUtils->RGBToIndex(&rgbTriple,&returnIndex));
					dstpix[y_dwP+x] = returnIndex;
						
				}//end for x
			}//end for y
	}

	
	ThrowErr(pObj->pMmImage->UnlockPixels( &argValue1 ));
	
	
	// flag the image dirty by getting and setting pixel 0,0.
	// is there a better way to do this?

	MoaLong buf;
	pObj->pMmImage->GetPixelInteger(&argValue1,0,0,&buf);
	pObj->pMmImage->SetPixelInteger(&argValue1,0,0,buf);
	

	
	
moa_catch
moa_catch_end	
moa_try_end	
}




MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_setDifferenceMaskThreshold(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaLong val2;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &val2));

	pObj->diffmaskthresh = val2;
	
moa_catch
moa_catch_end
moa_try_end
}





MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_setDifferenceMaskMatteColor(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaMmValue argValue3;
	MoaMmValue argValue4;
	MoaLong val2;
	MoaLong val3;
	MoaLong val4;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	pciGetArgByIndex( pCall, 3, &argValue3 );
	pciGetArgByIndex( pCall, 4, &argValue4 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &val2));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue3, &val3));
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue4, &val4));

	pObj->diffmaskMatteR = val2;
	pObj->diffmaskMatteG = val3;
	pObj->diffmaskMatteB = val4;
	
moa_catch
moa_catch_end	
moa_try_end	
}





MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_setDifferenceMaskReduceNoise(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaDouble val2;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	
	ThrowErr (pObj->pValueInterface->ValueToFloat( &argValue2, &val2));

	pObj->diffmasknoiseradius = val2;
	
moa_catch
moa_catch_end
moa_try_end
}





MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_setAnalysisDownSampleSteps(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaLong val2;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &val2));

	pObj->analysisDownSampleSteps = val2;
	
moa_catch
moa_catch_end
moa_try_end
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_setDifferenceMaskHoleFillMaxSize(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaLong val2;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &val2));

	pObj->diffmaskHoleFillMaxSize = val2;
	
moa_catch
moa_catch_end
moa_try_end
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_setDifferenceMaskEdgeContract(PMoaDrCallInfo pCall){
	MoaMmValue argValue2;
	MoaLong val2;
moa_try
	pciGetArgByIndex( pCall, 2, &argValue2 );
	
	ThrowErr (pObj->pValueInterface->ValueToInteger( &argValue2, &val2));

	pObj->diffmaskEdgeContract = val2;
	
moa_catch
moa_catch_end
moa_try_end
}



MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_updateCameraInSeperateThread(PMoaDrCallInfo pCall){
moa_try
	myron->updateCameraInSeperateThread();
moa_catch
moa_catch_end
moa_try_end
}


static unsigned char pPixels[921600];


MoaError TStdXtra_IMoaMmXScript::XScrp_webcamxtra_hijackFromFileRaw(PMoaDrCallInfo pCall){
moa_try
    myron->hijackRGBMemCopy(myron->width()*myron->height()*3,pPixels);
moa_catch
moa_catch_end
moa_try_end
}















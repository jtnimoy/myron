#ifndef _H_Script
#define _H_Script

#include <string.h>
#include <stdlib.h>
#include "xclassver.h" 
#include "moatry.h"
#include "driservc.h" 
#include "drivalue.h"
#include "mmivalue.h" 
#include "mmiplist.h"
#include "mmidate.h"
#include "math.h"
#include "moastdif.h"
#include "xmmvalue.h"
#include "mmiutil.h"
#include "mmiimage.h" 
#include "xmmlist.h" 
#include "mmiClr.h"


//THE ONE AND ONLY MYRON
#include "myron.h"




//#error PLEASE DEFINE A NEW CLSID
//DEFINE_GUID(CLSID_TStdXtra );
DEFINE_GUID(CLSID_TStdXtra, 0x4833DFACL, 0x4C4A, 0x11D8, 0xBC, 0x21,
0x00, 0x0A, 0x95, 0x7B, 0x2D, 0xC6);


EXTERN_BEGIN_DEFINE_CLASS_INSTANCE_VARS(TStdXtra)
	//interfaces that provide macromedia functions.
	PIMoaMmUtils2 	pMoaUtils;
	PIMoaMmValue	pValueInterface;
	PIMoaMmImage	pMmImage;
	PIMoaMmList	pMmList;
	PIMoaMmColor	pMmColor;
	Myron *myron;
	int diffmaskthresh;
	int diffmaskMatteR;
	int diffmaskMatteG;
	int diffmaskMatteB;
	int diffmasknoiseradius;
	int analysisDownSampleSteps;
	int diffmaskHoleFillMaxSize;
	int diffmaskEdgeContract;
EXTERN_END_DEFINE_CLASS_INSTANCE_VARS
	
/*****************************************************************************
 * Xtra Moa Registration Interface - Class definition
 ****************************************************************************/

EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(TStdXtra, IMoaRegister)

	EXTERN_DEFINE_METHOD(MoaError, Register, (PIMoaCache, PIMoaXtraEntryDict))

EXTERN_END_DEFINE_CLASS_INTERFACE


/*****************************************************************************
 * Xtra Moa Scripting Interface - Class definition
 ****************************************************************************/

EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(TStdXtra, IMoaMmXScript)

	EXTERN_DEFINE_METHOD(MoaError, Call, (PMoaDrCallInfo))
private:
	// Methods that implement the Lingo commands.
	// These are dispatched from "Call"

	//these are the methods that are linked to the API
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_start, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_stop, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_update, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_settings, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_version, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_findGlobs, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_globsImage, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_sensitivity, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_minDensity, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_maxDensity, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_cameraImage, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_cameraImageCopy, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_globBoxes, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_globCenters, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_globPixels, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_globEdgePoints, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_globQuads, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_trackColor, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_trackNotColor, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_average, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_averageFloat, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_retinaImage, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_adaptivity, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_adapt, (PMoaDrCallInfo))
    EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_differenceImage, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_hitCheck, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_hijack, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_width, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_height, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_getForcedWidth, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_getForcedHeight, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_setDifferenceMaskThreshold, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_setDifferenceMaskMatteColor, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_setDifferenceMaskReduceNoise, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_setAnalysisDownSampleSteps, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_setDifferenceMaskHoleFillMaxSize, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_setDifferenceMaskEdgeContract, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_updateCameraInSeperateThread, (PMoaDrCallInfo))
	EXTERN_DEFINE_METHOD(MoaError, XScrp_webcamxtra_hijackFromFileRaw, (PMoaDrCallInfo))
	
	//these are the internally used functions.
	
	/*
	 * ---> insert additional method(s) -->
	 */ 
	 
EXTERN_END_DEFINE_CLASS_INTERFACE

#endif /* _H_Script */

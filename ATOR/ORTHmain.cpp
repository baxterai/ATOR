/*******************************************************************************
 * 
 * This file is part of BAIPROJECT.
 * 
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
 * 
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 * 
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 * 
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: ORTHmain.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: ATOR (Axis Transformation Object Recognition) Functions
 * Project Version: 3a11b 09-July-2012
 * NB pointmap is a new addition for test streamlining; NB in test scenarios 2 and 3, there will be no pointmap available; the pointmap will have to be generated after depth map is obtained by using calculatePointUsingTInWorld()
 *******************************************************************************/

#include "ORTHmain.h"
#include "ORmethod.h"
#include "ORglobalDefs.h"
#include "XMLrulesClass.h"
#include "ORrules.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

//#define TEMPTESTEDGEFIT

/*
#ifdef TEMPTESTEDGEFIT
#include "ORfeature.h"
#include "RTppm.h"
#include "RTviewinfo.h"
#include "RTpixelMaps.h"
int main
{


	int imageWidth = 768;
	int imageHeight = 576;
	unsigned char * rgbMap = new unsigned char[imageWidth*imageHeight*RGB_NUM];
	bool * edgeBoolMap = new bool[imageWidth*imageHeight];
	char * rgbMapFileName = "testedge.ppm";
	pixmap * rgbPixMap;
	cout << "rgbPixMap = load_ppm(" << rgbMapFileName << ");" << endl;
	rgbPixMap = load_ppm(rgbMapFileName);
	cout << "imageWidth = " << imageWidth << endl;
	cout << "imageHeight = " << imageHeight << endl;
	cout << "createRGBMapFromPixmapImage(rgbPixMap, rgbMap);" << endl;
	createRGBMapFromPixmapImage(rgbPixMap, rgbMap);
	free_pixmap(rgbPixMap);
	double * nullpointer = NULL;
	view_info * vi = NULL;

	generateEdgeListFromRGBMapWithQuadraticFit(rgbMap, edgeBoolMap, imageWidth, imageHeight, 1.0, false, nullpointer, nullpointer, 1, vi);

}

int mainTemp
#else
*/
int main()
{
	if(!parseORRulesXMLFile())
	{
		cout << "error: no rules file detected" << endl;
		exit(0);
	}
	fillInORRulesExternVariables();


	#ifdef COMPILE_TH_OR_METHOD_2DOD

		int imageWidthFacingPoly = TH_OR_METHOD2DOD_FACING_POLY_DEFAULT_IMAGE_WIDTH;
		int imageHeightFacingPoly = TH_OR_METHOD2DOD_FACING_POLY_DEFAULT_IMAGE_HEIGHT;

		int maxNumberOfPolygonsTrain = OR_METHOD2DOD_MAX_NUMBER_OF_POLYGONS_TRAIN;
		int numberOfTrainViewIndiciesPerObject = OR_METHOD2DOD_NUMBER_OF_VIEWINDICIES_TRAIN;

		view_info viTrain;

		viTrain.imgwidth = TH_OR_METHOD2DOD_DEFAULT_IMAGE_WIDTH;
		viTrain.imgheight = TH_OR_METHOD2DOD_DEFAULT_IMAGE_HEIGHT;
		viTrain.viewwidth = TH_OR_METHOD2DOD_DEFAULT_VIEWSIZE_WIDTH;
		viTrain.viewheight = TH_OR_METHOD2DOD_DEFAULT_VIEWSIZE_HEIGHT;
		viTrain.focal_length = TH_OR_METHOD2DOD_DEFAULT_FOCAL;

		viTrain.eye.x = TH_OR_METHOD2DOD_DEFAULT_EYE_X;		//CHECK THIS; preferably the eye moves around the object
		viTrain.eye.y = TH_OR_METHOD2DOD_DEFAULT_EYE_Y;
		viTrain.eye.z = TH_OR_METHOD2DOD_DEFAULT_EYE_Z;
		viTrain.viewat.x = TH_OR_METHOD2DOD_DEFAULT_VIEWAT_X;
		viTrain.viewat.y = TH_OR_METHOD2DOD_DEFAULT_VIEWAT_Y;
		viTrain.viewat.z = TH_OR_METHOD2DOD_DEFAULT_VIEWAT_Z;
		viTrain.viewup.x = TH_OR_METHOD2DOD_DEFAULT_VIEWUP_X;
		viTrain.viewup.y = TH_OR_METHOD2DOD_DEFAULT_VIEWUP_Y;
		viTrain.viewup.z = TH_OR_METHOD2DOD_DEFAULT_VIEWUP_Z;

		int maxNumberOfPolygonsTest = OR_METHOD2DOD_MAX_NUMBER_OF_POLYGONS_TEST;
		int numberOfTestViewIndiciesPerObject = OR_METHOD2DOD_NUMBER_OF_VIEWINDICIES_TEST;

		view_info viTest;

		viTest.imgwidth = TH_OR_METHOD2DOD_DEFAULT2_IMAGE_WIDTH;
		viTest.imgheight = TH_OR_METHOD2DOD_DEFAULT2_IMAGE_HEIGHT;
		viTest.viewwidth = TH_OR_METHOD2DOD_DEFAULT2_VIEWSIZE_WIDTH;
		viTest.viewheight = TH_OR_METHOD2DOD_DEFAULT2_VIEWSIZE_HEIGHT;
		viTest.focal_length = TH_OR_METHOD2DOD_DEFAULT2_FOCAL;

		viTest.eye.x = TH_OR_METHOD2DOD_DEFAULT2_EYE_X;		//CHECK THIS; preferably the eye moves around the object, however not to the same locations as used during training
		viTest.eye.y = TH_OR_METHOD2DOD_DEFAULT2_EYE_Y;
		viTest.eye.z = TH_OR_METHOD2DOD_DEFAULT2_EYE_Z;
		viTest.viewat.x = TH_OR_METHOD2DOD_DEFAULT2_VIEWAT_X;
		viTest.viewat.y = TH_OR_METHOD2DOD_DEFAULT2_VIEWAT_Y;
		viTest.viewat.z = TH_OR_METHOD2DOD_DEFAULT2_VIEWAT_Z;
		viTest.viewup.x = TH_OR_METHOD2DOD_DEFAULT2_VIEWUP_X;
		viTest.viewup.y = TH_OR_METHOD2DOD_DEFAULT2_VIEWUP_Y;
		viTest.viewup.z = TH_OR_METHOD2DOD_DEFAULT2_VIEWUP_Z;

		string trainObjectNameArray[10];
		trainObjectNameArray[0] = OR_METHOD2DOD_OBJECT_0_NAME;
		trainObjectNameArray[1] = OR_METHOD2DOD_OBJECT_1_NAME;
		trainObjectNameArray[2] = OR_METHOD2DOD_OBJECT_2_NAME;
		trainObjectNameArray[3] = OR_METHOD2DOD_OBJECT_3_NAME;
		trainObjectNameArray[4] = OR_METHOD2DOD_OBJECT_4_NAME;
		trainObjectNameArray[5] = OR_METHOD2DOD_OBJECT_5_NAME;
		trainObjectNameArray[6] = OR_METHOD2DOD_OBJECT_6_NAME;
		trainObjectNameArray[7] = OR_METHOD2DOD_OBJECT_7_NAME;
		trainObjectNameArray[8] = OR_METHOD2DOD_OBJECT_8_NAME;
		trainObjectNameArray[9] = OR_METHOD2DOD_OBJECT_9_NAME;

		string testObjectNameArray[10];
		testObjectNameArray[0] = OR_METHOD2DOD_OBJECT_0_NAME;

	#ifdef OR_METHOD2DOD_USE_PREEXISTING_IMAGE_DATA
		int objectDataSource = OR_OBJECT_DATA_SOURCE_PREEXISTING_DATA;
	#elif defined OR_METHOD2DOD_GENERATE_IMAGE_DATA
		int objectDataSource = OR_OBJECT_DATA_SOURCE_GENERATE_DATA;
	#endif
		int dimension = OR_METHOD2DOD_DIMENSIONS;
		int numberOfTrainObjects = OR_METHOD2DOD_NUM_OF_OBJECTS;
		int numberOfTestObjects = 1;

		int numberOfTrainZoomIndicies = OR_METHOD2DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS;
		int numberOfTestZoomIndicies = OR_METHOD2DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS;

		int numberOfTrainViewIndiciesPerObjectWithUniquePolygons;
		int numberOfTestViewIndiciesPerObjectWithUniquePolygons;
		if(dimension == OR_METHOD3DOD_DIMENSIONS)
		{
			numberOfTrainViewIndiciesPerObjectWithUniquePolygons = 1;
			numberOfTestViewIndiciesPerObjectWithUniquePolygons = 1;
		}
		else if(dimension == OR_METHOD2DOD_DIMENSIONS)
		{
			numberOfTrainViewIndiciesPerObjectWithUniquePolygons = numberOfTrainViewIndiciesPerObject;
			numberOfTestViewIndiciesPerObjectWithUniquePolygons = numberOfTestViewIndiciesPerObject;
		}

		int * numberOfTrainPolys = new int[numberOfTrainObjects*numberOfTrainViewIndiciesPerObjectWithUniquePolygons*numberOfTrainZoomIndicies];
		int * numberOfTestPolys = new int[numberOfTestObjects*numberOfTestViewIndiciesPerObjectWithUniquePolygons*numberOfTestZoomIndicies];

		//cout << "OR_METHOD2DOD_DIMENSIONS = " << OR_METHOD2DOD_DIMENSIONS << endl;
		ORTHMethod(dimension, numberOfTrainObjects, trainObjectNameArray, numberOfTestObjects, testObjectNameArray, numberOfTrainPolys, numberOfTestPolys, objectDataSource, &viTrain, &viTest, imageWidthFacingPoly, imageHeightFacingPoly, maxNumberOfPolygonsTrain, maxNumberOfPolygonsTest, numberOfTrainViewIndiciesPerObject, numberOfTestViewIndiciesPerObject, numberOfTrainViewIndiciesPerObjectWithUniquePolygons, numberOfTestViewIndiciesPerObjectWithUniquePolygons, numberOfTrainZoomIndicies, numberOfTestZoomIndicies);

	#elif defined COMPILE_TH_OR_METHOD_3DOD

		int imageWidthFacingPoly = TH_OR_METHOD3DOD_FACING_POLY_DEFAULT_IMAGE_WIDTH;
		int imageHeightFacingPoly = TH_OR_METHOD3DOD_FACING_POLY_DEFAULT_IMAGE_HEIGHT;

		int maxNumberOfPolygonsTrain = OR_METHOD3DOD_MAX_NUMBER_OF_POLYGONS_TRAIN;
		int numberOfTrainViewIndiciesPerObject = OR_METHOD3DOD_NUMBER_OF_VIEWINDICIES_TRAIN;

		view_info viTrain;

		viTrain.imgwidth = TH_OR_METHOD3DOD_DEFAULT_IMAGE_WIDTH;
		viTrain.imgheight = TH_OR_METHOD3DOD_DEFAULT_IMAGE_HEIGHT;
		viTrain.viewwidth = TH_OR_METHOD3DOD_DEFAULT_VIEWSIZE_WIDTH;
		viTrain.viewheight = TH_OR_METHOD3DOD_DEFAULT_VIEWSIZE_HEIGHT;
		viTrain.focal_length = TH_OR_METHOD3DOD_DEFAULT_FOCAL;

		viTrain.eye.x = TH_OR_METHOD3DOD_DEFAULT_EYE_X;		//CHECK THIS; preferably the eye moves around the object
		viTrain.eye.y = TH_OR_METHOD3DOD_DEFAULT_EYE_Y;
		viTrain.eye.z = TH_OR_METHOD3DOD_DEFAULT_EYE_Z;
		viTrain.viewat.x = TH_OR_METHOD3DOD_DEFAULT_VIEWAT_X;
		viTrain.viewat.y = TH_OR_METHOD3DOD_DEFAULT_VIEWAT_Y;
		viTrain.viewat.z = TH_OR_METHOD3DOD_DEFAULT_VIEWAT_Z;
		viTrain.viewup.x = TH_OR_METHOD3DOD_DEFAULT_VIEWUP_X;
		viTrain.viewup.y = TH_OR_METHOD3DOD_DEFAULT_VIEWUP_Y;	//[house3DOD1: 0 / 50 (view1) / 100 (view2)] / [house3DOD2: 0 / 50 (view1) / 100 (view2)]
		viTrain.viewup.z = TH_OR_METHOD3DOD_DEFAULT_VIEWUP_Z;	//[house3DOD1: 100] / [house3DOD2: -100]

		int maxNumberOfPolygonsTest = OR_METHOD3DOD_MAX_NUMBER_OF_POLYGONS_TEST;
		int numberOfTestViewIndiciesPerObject = OR_METHOD3DOD_NUMBER_OF_VIEWINDICIES_TEST;

		view_info viTest;

		viTest.imgwidth = TH_OR_METHOD3DOD_DEFAULT2_IMAGE_WIDTH;
		viTest.imgheight = TH_OR_METHOD3DOD_DEFAULT2_IMAGE_HEIGHT;
		viTest.viewwidth = TH_OR_METHOD3DOD_DEFAULT2_VIEWSIZE_WIDTH;
		viTest.viewheight = TH_OR_METHOD3DOD_DEFAULT2_VIEWSIZE_HEIGHT;
		viTest.focal_length = TH_OR_METHOD3DOD_DEFAULT2_FOCAL;

		viTest.eye.x = TH_OR_METHOD3DOD_DEFAULT2_EYE_X;		//CHECK THIS; preferably the eye moves around the object, however not to the same locations as used during training
		viTest.eye.y = TH_OR_METHOD3DOD_DEFAULT2_EYE_Y;
		viTest.eye.z = TH_OR_METHOD3DOD_DEFAULT2_EYE_Z;
		viTest.viewat.x = TH_OR_METHOD3DOD_DEFAULT2_VIEWAT_X;
		viTest.viewat.y = TH_OR_METHOD3DOD_DEFAULT2_VIEWAT_Y;
		viTest.viewat.z = TH_OR_METHOD3DOD_DEFAULT2_VIEWAT_Z;
		viTest.viewup.x = TH_OR_METHOD3DOD_DEFAULT2_VIEWUP_X;
		viTest.viewup.y = TH_OR_METHOD3DOD_DEFAULT2_VIEWUP_Y;
		viTest.viewup.z = TH_OR_METHOD3DOD_DEFAULT2_VIEWUP_Z;

		string trainObjectNameArray[10];
		trainObjectNameArray[0] = OR_METHOD3DOD_OBJECT_0_NAME;
		trainObjectNameArray[1] = OR_METHOD3DOD_OBJECT_1_NAME;
		trainObjectNameArray[2] = OR_METHOD3DOD_OBJECT_2_NAME;
		trainObjectNameArray[3] = OR_METHOD3DOD_OBJECT_3_NAME;
		trainObjectNameArray[4] = OR_METHOD3DOD_OBJECT_4_NAME;
		trainObjectNameArray[5] = OR_METHOD3DOD_OBJECT_5_NAME;
		trainObjectNameArray[6] = OR_METHOD3DOD_OBJECT_6_NAME;
		trainObjectNameArray[7] = OR_METHOD3DOD_OBJECT_7_NAME;
		trainObjectNameArray[8] = OR_METHOD3DOD_OBJECT_8_NAME;
		trainObjectNameArray[9] = OR_METHOD3DOD_OBJECT_9_NAME;

		string testObjectNameArray[10];
		testObjectNameArray[0] = OR_METHOD3DOD_OBJECT_0_NAME;

	#ifdef OR_METHOD3DOD_USE_PREEXISTING_IMAGE_DATA
		int objectDataSource = OR_OBJECT_DATA_SOURCE_PREEXISTING_DATA;
	#elif defined OR_METHOD3DOD_GENERATE_IMAGE_DATA
		int objectDataSource = OR_OBJECT_DATA_SOURCE_GENERATE_DATA;
	#endif

		int dimension = OR_METHOD3DOD_DIMENSIONS;
		int numberOfTrainObjects = OR_METHOD3DOD_NUM_OF_OBJECTS;
		int numberOfTestObjects = 1;

		int numberOfTrainZoomIndicies = OR_METHOD3DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS;
		int numberOfTestZoomIndicies = OR_METHOD3DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS;

		int numberOfTrainViewIndiciesPerObjectWithUniquePolygons;
		int numberOfTestViewIndiciesPerObjectWithUniquePolygons;
		if(dimension == OR_METHOD3DOD_DIMENSIONS)
		{
			numberOfTrainViewIndiciesPerObjectWithUniquePolygons = 1;
			numberOfTestViewIndiciesPerObjectWithUniquePolygons = 1;
		}
		else if(dimension == OR_METHOD2DOD_DIMENSIONS)
		{
			numberOfTrainViewIndiciesPerObjectWithUniquePolygons = numberOfTrainViewIndiciesPerObject;
			numberOfTestViewIndiciesPerObjectWithUniquePolygons = numberOfTestViewIndiciesPerObject;
		}

		int * numberOfTrainPolys = new int[numberOfTrainObjects*numberOfTrainViewIndiciesPerObjectWithUniquePolygons*numberOfTrainZoomIndicies];
		int * numberOfTestPolys = new int[numberOfTestObjects*numberOfTestViewIndiciesPerObjectWithUniquePolygons*numberOfTestZoomIndicies];

		ORTHMethod(dimension, numberOfTrainObjects, trainObjectNameArray, numberOfTestObjects, testObjectNameArray, numberOfTrainPolys, numberOfTestPolys, objectDataSource, &viTrain, &viTest, imageWidthFacingPoly, imageHeightFacingPoly, maxNumberOfPolygonsTrain, maxNumberOfPolygonsTest, numberOfTrainViewIndiciesPerObject, numberOfTestViewIndiciesPerObject, numberOfTrainViewIndiciesPerObjectWithUniquePolygons, numberOfTestViewIndiciesPerObjectWithUniquePolygons, numberOfTrainZoomIndicies, numberOfTestZoomIndicies);
	#else
		cout << "error: COMPILE_TH_OR_METHOD_3DOD or COMPILE_TH_OR_METHOD_2DOD must be defined for TH OR" << endl;
		exit(0);
	#endif

}





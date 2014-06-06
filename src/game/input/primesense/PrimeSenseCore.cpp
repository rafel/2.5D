#include "PrimeSenseCore.h"
#include <glm/glm.hpp>

#include <stdio.h>
#include <iostream>


using namespace openni;

// Const.
PrimeSenseCore::PrimeSenseCore()
{

}

// Deconst. 
PrimeSenseCore::~PrimeSenseCore()
{
	
	depth.stop();
	depth.destroy();
	device.close();
	OpenNI::shutdown();
}

// Initialize PrimeSense
int PrimeSenseCore::initialize()
{

	rc = OpenNI::initialize();
	if (rc != STATUS_OK)
	{
		printf("Initialize failed\n%s\n", OpenNI::getExtendedError());
		return 1;
	}

	
	rc = device.open(ANY_DEVICE);
	if (rc != STATUS_OK)
	{
		printf("Couldn't open device\n%s\n", OpenNI::getExtendedError());
		return 2;
	}

	

	if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
	{
		rc = depth.create(device, SENSOR_DEPTH);
		if (rc != STATUS_OK)
		{
			printf("Couldn't create depth stream\n%s\n", OpenNI::getExtendedError());
			return 3;
		}
	}

	rc = depth.start();
	if (rc != STATUS_OK)
	{
		printf("Couldn't start the depth stream\n%s\n", OpenNI::getExtendedError());
		return 4;
	}
	return 0;
}

// Gets the cloest point from depthbuffer
glm::vec3 PrimeSenseCore::getClosestPoint()
{

	int changedStreamDummy;
	VideoStream* pStream = &depth;
	rc = OpenNI::waitForAnyStream(&pStream, 1, &changedStreamDummy, SAMPLE_READ_WAIT_TIMEOUT);
	if (rc != STATUS_OK)
	{
		printf("Wait failed! (timeout is %d ms)\n%s\n", SAMPLE_READ_WAIT_TIMEOUT, OpenNI::getExtendedError());
	}

	rc = depth.readFrame(&frame);
	if (rc != STATUS_OK)
	{
		printf("Read failed!\n%s\n", OpenNI::getExtendedError());
	}

	if (frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_1_MM && frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_100_UM)
	{
		printf("Unexpected frame format\n");
	}

	DepthPixel* pDepth = (DepthPixel*)frame.getData();
	//int row = 0;
	//int col = 0;
	//float middleIndex = (frame.getHeight()+1)*frame.getWidth()/2;
	float row = 0;
	float col = 0;
	float tempValue = 10000;
	for(int i = 10; i < frame.getHeight() - 10; i++) //row
	{
		for(int j = 10; j < frame.getWidth()-10; j++) // col
		{

			float depthValue = pDepth[i*frame.getWidth()+j];
			if(depthValue < tempValue && depthValue < 3000){
				
				bool isHead = true; 
				for(int down = 0; down < 8; down++)
				{
					if(!(abs(pDepth[(down+i)*frame.getWidth()+j] - depthValue) < 100)){
						isHead = false;
						break;
							
					}
				}
				if(isHead == true)
				{
					tempValue = depthValue;
					col = j/(float(frame.getWidth()-10.0f));
					row = i/(float(frame.getHeight()-10.0f));
				}
				
			}
		}
	}

	return glm::vec3((col*2)-1,(row*2)-1,tempValue);
	
	
	//std::cout<<"x: "<<col<<" y: "<<row<<"\n";
	//printf("[%08llu] %8d\n", (long long)frame.getTimestamp(), pDepth[middleIndex]);
	//return glm::vec3(0,0,0);
}

#ifndef PRIMESENSECORE_H
#define PRIMESENSECORE_H
#include <glm\glm.hpp>
#include <OpenNI.h>


//#include "OniSampleUtilities.h"

#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms
using namespace openni;
class PrimeSenseCore
{
public:
	int initialize();
	//glm::vec3 getClosestPoint();
	glm::vec3 getClosestPoint();
	PrimeSenseCore();
	~PrimeSenseCore();

private:
	VideoStream depth;
	VideoFrameRef frame;
	Device device;
	Status rc;
};


#endif
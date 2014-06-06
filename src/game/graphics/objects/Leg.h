#ifndef LEG_H
#define LEG_H
#include <glm/glm.hpp>
#include "Image.h"
#include "Gear.h"
#define LEG_RIGHT_DIR true
#define LEG_LEFT_DIR false
#define LEG_GOTO_NOTHING -1
#define LEG_GOTO_WAY_CIRCULAR 0
#define LEG_GOTO_WAY_LINEAR 1
#define LEG_SEARCH_WAY_CIRCULAR 2


class Leg
{
public:
	Leg();
	~Leg();
	void draw(glm::mat4 projMatrix, glm::vec3 cameraPosition, float delta);

	glm::vec3 rotationCenterPoint;
	
	float rotationAngle;
	float radius;
	bool legDirection;
	bool goTo(glm::vec3 desiredFootPosition, int way);
	bool isStanding;
	float getLength();
	glm::vec3 getRealPosition();
	Gear* getGearStandingOn();
	bool  checkCollisionWithGear(Gear* gearToTest);
	float getExpansionPercent();
private:

	float delta;
	Image* legPartFirst;
	Image* legPartSecond;
	Image* debugPic;
	void reorganizeLegParts();
	glm::vec3 getRealFootPosition();
	void moveTowardsDesiredPosition();
	void checkCollisionWithDesiredPosition();
	glm::vec3 footPosition;
	glm::vec3 desiredPosition;
	glm::vec3 realPosition;
	int desiredPositionWay;
	int currentGearHillIndex;
	Gear* currentGear;
	
	
};


	
#endif
#ifndef Gear_H
#define Gear_H

#include <glm\glm.hpp>
#include "Image.h"
#include "../graphicssettings.h"
#include <vector>

#define PROPERTY_RANDOM_BOTTOM 0
#define PROPERTY_RANDOM_MIDDLE 1
#define PROPERTY_RANDOM_NOFOCUS 2
class Gear
{
public:
	Gear();
	Gear(glm::mat4 projMatrix);
	Gear(int imageID,glm::mat4 projMatrix);

	void setProjMatrix(glm::mat4 projMatrix);
	~Gear();
	void reset();

	void buildBody();
	void setRandomProperty(int propertysetting);
	void spinGear(float delta);
	void draw(glm::vec3 cameraPosition, float delta);
	bool inScreen();
	void moveGearX(float direction);
	void moveGearY(float direction);
	void moveGearZ(float direction);
	void setPosition(glm::vec3 position);
	void setSize(float size);
	float getSize();
	void setDirection(float direction);
	glm::vec3 getHillPositionFromIndex(int index);

	glm::vec3 getPosition();
	bool checkCollision(glm::vec3 position, float checkRadius);
	void setNrOfHills(int nrOfHills);
	int getNrOfHills();
	float getCurrentAngle();
	int getClosestHillIndex(glm::vec3 position);
	Image* gearImage;
	float direction;
	
private:
	float hillIndex;
	glm::mat4 projMatrix;
	std::string gearImages[3];
	int nrOfHills;
	float angleStep;
};

#endif


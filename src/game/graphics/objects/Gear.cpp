#include "Gear.h"
#include <iostream>

// Const. new gear image and build gear body
Gear::Gear(glm::mat4 projMatrix)
{
	// We can have diffrent images for gear
	this->gearImages[0] = "gameGear.png";
	this->gearImages[1] = "gameGear.png";
	this->gearImages[2] = "gameGear.png";

	this->projMatrix = projMatrix;

	// Random image
	this->gearImage = new Image(this->gearImages[rand() % 3]);

	// Reset
	this->gearImage->position = glm::vec3(100.0f,100.0f,400.0f);
	nrOfHills=0;
	angleStep=0;
	hillIndex=0;
}

// New gear with random image
Gear::Gear()
{
	this->gearImages[0] = "gameGear.png";
	this->gearImages[1] = "gameGear2.png";
	this->gearImages[2] = "gameGear3.png";
	this->gearImage = new Image(this->gearImages[rand() % 3]);
	nrOfHills=0;
	angleStep=0;
}

// Set projection matrix
void Gear::setProjMatrix(glm::mat4 projMatrix){
	this->projMatrix = projMatrix;

}

// Set gear direction
void Gear::setDirection(float direction){
	this->direction = direction;
}

// Set random property for gear (randomSetting defined in gear.h)
void Gear::setRandomProperty(int propertysetting){

	// If random gears in button of screen , random properties 
	if(propertysetting == PROPERTY_RANDOM_BOTTOM){
		double direction = ((float(rand()) / float(RAND_MAX)) * (2 - -2)) + -2;
		if(direction < 0.2 && direction > -0.2){
			direction * -2;
		}
		this->direction = direction;
		int size = (512 - 400) * ( (double)rand() / (double)RAND_MAX ) + 400;
		int x = (WINDOW_WIDTH - 100) * ( (double)rand() / (double)RAND_MAX ) + 100;
		int y = WINDOW_HEIGHT - (size/2);
		int z = (150 - 50) * ( (double)rand() / (double)RAND_MAX ) + 50;
		this->gearImage->height = size;
		this->gearImage->width = size;
		this->gearImage->position.x = x;
		this->gearImage->position.y = y;
		this->gearImage->position.z = z;
	}
	// Random properties for gears in middle of screen
	else if(propertysetting == PROPERTY_RANDOM_MIDDLE){
		double direction = ((float(rand()) / float(RAND_MAX)) * (1 - -1)) + -1;
		if(direction < 0.2 && direction > -0.2){
			direction * -2;
		}
		this->direction = direction;
		int size = 800.0f;
		this->gearImage->height = size;
		this->gearImage->width = size;
		glm::vec3 startPosition ;
		startPosition = this->gearImage->convertPixelPosToInGameCoord(glm::vec2(0-(WINDOW_WIDTH/2),0));
		startPosition.x = startPosition.x - (size*2) +  rand() % 50;
		startPosition.y = startPosition.y  + ((float(rand()) / float(RAND_MAX)) * (500 - 500)) + 500;
		startPosition.z = 400.0f;
		this->gearImage->position = startPosition;
		
	}
}

// If gear in screen
bool Gear::inScreen(){
	glm::vec3 screensides = this->gearImage->convertPixelPosToInGameCoord(glm::vec2((WINDOW_WIDTH/2),0));
	if(this->getPosition().x < screensides.x + (this->gearImage->width)){
		return true;
	}
	return false;
}

// Remove gear image
Gear::~Gear()
{
	delete this->gearImage;
}

// Draw
void Gear::draw(glm::vec3 cameraPosition, float delta){
	this->gearImage->draw(this->projMatrix,cameraPosition);
	this->spinGear(delta);
}

// Spin gear
void Gear::spinGear(float delta){
	if(this->gearImage->rotationAngle >= (M_PI * 2) ||this->gearImage->rotationAngle <= (M_PI * -2)){
		this->gearImage->rotationAngle = 0;
	}
		this->gearImage->rotationAngle =+ this->gearImage->rotationAngle + (this->direction/100) * delta; 
}

// Move gear X direction
void Gear::moveGearX(float direction){
	this->gearImage->position.x =+ this->gearImage->position.x + direction;
}

// Move gear Y direction
void Gear::moveGearY(float direction){
	this->gearImage->position.y =+ this->gearImage->position.y + direction;
}

// Move gear Z direction
void Gear::moveGearZ(float direction){
	this->gearImage->position.z =+ this->gearImage->position.z + direction;
}

// Set gear position
void Gear::setPosition(glm::vec3 position){
	 this->gearImage->position = position;
}

// Get gear position
glm::vec3 Gear::getPosition(){
	return this->gearImage->position;
}

// Sets number of hills on the gear
void Gear::setNrOfHills(int nrOfHills)
{
	angleStep = float(M_2PI/nrOfHills);
	this->nrOfHills= nrOfHills;
}

// Return hill position from index
glm::vec3 Gear::getHillPositionFromIndex(int index)
{
	float angle = index*angleStep-M_PI_2+gearImage->getRealRotationAngle();
	float x = gearImage->height*cos(angle) + gearImage->getRealPosition().x;
	float y = gearImage->height*sin(angle) + gearImage->getRealPosition().y;
	float z = gearImage->getRealPosition().z;
	
	return glm::vec3(x,y,z);
}

// Checks collision with position for radius
bool Gear::checkCollision(glm::vec3 position, float checkRadius)
{
	if(glm::distance(position, gearImage->getRealPosition())<(this->gearImage->height+checkRadius))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Get nr of hills on gear
int Gear::getNrOfHills()
{
	return nrOfHills;
}

// Gets cloest hill index
int Gear::getClosestHillIndex(glm::vec3 position)
{
	float angle = atan2(position.y-gearImage->getRealPosition().y,position.x-gearImage->getRealPosition().x);
	angle = angle +M_PI_2-gearImage->getRealRotationAngle();


	int index = int(float (angle/(angleStep))); 
	
	return index;
}

// Set gear size
void Gear::setSize(float size)
{
	gearImage->width=size;
	gearImage->height=size;
}

// Get gear size
float Gear::getSize()
{
	return gearImage->height;
}

// Get current gear angle
float Gear::getCurrentAngle()
{
	return gearImage->getRealRotationAngle();
}

// Reset to middle
void Gear::reset(){
	this->setRandomProperty(PROPERTY_RANDOM_MIDDLE);
}

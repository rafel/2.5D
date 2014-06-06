#include "StateLayer.h"


StateLayer::StateLayer(glm::mat4 projMatrix)
{
	this->projMatrix = projMatrix;

	// Screen images
	this->startScreen = new Image("startScreen.png");
	this->endScreen = new Image("endScreen.png");
	this->pausScreen = new Image("pausScreen.png");

	// No lighting
	this->startScreen->enableLight(false);
	this->endScreen->enableLight(false);
	this->pausScreen->enableLight(false);

	// Rotation
	this->startScreen->rotationAngle = 0;
	this->endScreen->rotationAngle = 0;
	this->pausScreen->rotationAngle = 0;

	// Position
	this->startScreen->position = glm::vec3(0,0,300);
	this->endScreen->position = glm::vec3(0,0,300);
	this->pausScreen->position = glm::vec3(0,0,300);

	// Size
	float zRatio = 100.0f/startScreen->position.z;
	this->startScreen->height = (WINDOW_HEIGHT/2)/(WCY*zRatio);
	this->startScreen->width = (WINDOW_WIDTH/2)/(WCX*zRatio);

	this->endScreen->height = this->startScreen->height;
	this->endScreen->width = this->startScreen->width;

	this->pausScreen->height = this->startScreen->height;
	this->pausScreen->width = this->startScreen->width;
}

// Delete all images
StateLayer::~StateLayer()
{
	delete startScreen;
	delete pausScreen;
	delete endScreen;
}

// Draw startscreen
void StateLayer::drawStart(glm::vec3 cameraPosition, float delta){
	 this->startScreen->draw(projMatrix, cameraPosition);
}

// Draw endScreen
void StateLayer::drawEnd(glm::vec3 cameraPosition, float delta){
	 this->endScreen->draw(projMatrix, cameraPosition);
}

// Draw PausScreen
void StateLayer::drawPaus(glm::vec3 cameraPosition, float delta){
	 this->pausScreen->draw(projMatrix, cameraPosition);
}
#include "BackgroundLayer.h"

// Const. new background , full screen
BackgroundLayer::BackgroundLayer(glm::mat4 projMatrix)
{
	this->projMatrix = projMatrix;
	this->bg = new Image("background4.png");

	this->bg->rotationAngle = 0;
	this->bg->position = glm::vec3(0,0,500);
	float zRatio = 100.0f/bg->position.z;
	this->bg->height = WINDOW_HEIGHT*1.5/(WCY*zRatio);
	this->bg->width = WINDOW_WIDTH*1.5/(WCX*zRatio);
}

// Delete bg
BackgroundLayer::~BackgroundLayer()
{
	delete bg;
}

// Draw Bg
void BackgroundLayer::draw(glm::vec3 cameraPosition, float delta){
	 bg->draw(projMatrix, cameraPosition);
}
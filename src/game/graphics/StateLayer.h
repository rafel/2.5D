#ifndef STATELAYER_H
#define STATELAYER_H

#include "graphicssettings.h"
#include "objects\Image.h"

class StateLayer
{
public:
	StateLayer(glm::mat4 projMatrix);
	~StateLayer();
	void drawStart(glm::vec3 cameraPosition, float delta);
	void drawEnd(glm::vec3 cameraPosition, float delta);
	void drawPaus(glm::vec3 cameraPosition, float delta);
	
private:
	Image* startScreen;
	Image* endScreen;
	Image* pausScreen;
	glm::mat4 projMatrix;
	glm::vec3 cameraPosition;
};
#endif
#ifndef BACKGROUNDLAYER_H
#define BACKGROUNDLAYER_H

#include "graphicssettings.h"
#include "objects\Image.h"

class BackgroundLayer
{
public:
	BackgroundLayer(glm::mat4 projMatrix);
	~BackgroundLayer();
	void draw(glm::vec3 cameraPosition, float delta);
	
private:
	Image* bg;
	glm::mat4 projMatrix;
	glm::vec3 cameraPosition;
};
#endif
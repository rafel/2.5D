#ifndef ForegroundLayer_H
#define ForegroundLayer_H
#include <glm/glm.hpp>
#include "graphicssettings.h"
#include "../gamesettings.h"
#include "objects\Gear.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <list>

#ifndef PrintGear_H
#define PrintGear_H
class PrintGear
{
    public:
        PrintGear(glm::vec3 cameraPosition,float delta): cameraPosition(cameraPosition), delta(delta) {}
		
        void operator()(Gear& x) const
        {  x.draw(this->cameraPosition,this->delta);}
    private:
        glm::vec3 cameraPosition;
		float delta;
};
#endif

class ForegroundLayer
{
public:
	ForegroundLayer(glm::mat4 projMatrix);
	~ForegroundLayer();
	void draw(glm::vec3 cameraPosition, float delta);
private:
	std::list<Gear> gears;
	glm::mat4 projMatrix;
	glm::vec3 cameraPosition;
	float delta;
};

#endif
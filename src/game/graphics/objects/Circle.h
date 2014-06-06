#ifndef CIRCLE_H
#define CIRCLE_H

#include <glm/glm.hpp>
#include "../graphicssettings.h"

class Circle
{
public:
	Circle(glm::vec2,GLfloat);
	~Circle();
	void draw();
	void setColor(glm::vec3);
	void setRadius(GLfloat);
	void setPosition(glm::vec2);
	void moveCircle(glm::vec2);
private:
    float   radius;
    float   x,y;
	float	r,g,b;
};


#endif
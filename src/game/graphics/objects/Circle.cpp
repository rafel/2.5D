#include "Circle.h"

Circle::Circle(glm::vec2 position,GLfloat radius)
{
	this->x = position.x;
	this->y = position.y;
	this->radius = radius;
}

Circle::~Circle()
{
}

void Circle::setColor(glm::vec3 color){
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
}

void Circle::setRadius(GLfloat radius){
	this->radius = radius;
}

void Circle::setPosition(glm::vec2 position){
	this->x = position.x;
	this->y = position.y;
}

void Circle::moveCircle(glm::vec2 direction){
	this->x += direction.x;
	this->y += direction.y;
}

void Circle::draw(){
        int i;
		int triangleAmount = 40; //# of triangles used to draw circle
	
		//GLfloat radius = 0.8f; //radius
		GLfloat twicePi = 2.0f * M_PI;

		glBegin(GL_TRIANGLE_FAN);
			glColor3f(r,g,b); //a orange triangle
			glVertex2f(this->x, this->y); // center of circle
			for(i = 0; i <= triangleAmount;i++) { 
				glVertex2f(
						x + (radius * cos(i *  twicePi / triangleAmount)), 
					y + (radius * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
}
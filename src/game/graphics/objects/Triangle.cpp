#include "Triangle.h"
#include "../graphicssettings.h"

Triangle::Triangle(float triangle_width , float   triangle_height)
{
	this->triangle_width = triangle_width;
	this->triangle_height = triangle_height;
}
Triangle::Triangle()
{
	this->triangle_width = 200.0f;
	this->triangle_height = 200.0f;
}

Triangle::~Triangle()
{
}

void Triangle::setColor(float red,float green,float blue){
	this->r = red;
	this->g = green;
	this->b = blue;
}

void Triangle::draw(){
        //here will go the drawing
        //glBegin will start the drawing of a primitive and glEnd will end it.
        //using the GL_TRIANGLES as the primitive type, the glBegin() -> glEnd() block will draw a
        //triangle for each 3 points we add.
        glBegin(GL_TRIANGLES);
            //set the color of the triangle, using float RGB format
            glColor3f(r,g,b); //a orange triangle
            //Top point
            glVertex2f(WINDOW_WIDTH/2,WINDOW_HEIGHT/2-triangle_height/2);
            //Bottom left point
            glVertex2f(WINDOW_WIDTH/2-triangle_width/2,WINDOW_HEIGHT/2+triangle_height/2);
            //Bottom right point
            glVertex2f(WINDOW_WIDTH/2+triangle_width/2,WINDOW_HEIGHT/2+triangle_height/2);
        glEnd();
}
#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
public:
	Triangle(float,float);
	Triangle();
	~Triangle();
	void draw();
	void setColor(float,float,float);
private:
    float   triangle_height; // distance between the top point and the base
    float   triangle_width; // length of the base
	float	r,g,b;
};


#endif
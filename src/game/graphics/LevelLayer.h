#ifndef LevelLayer_H
#define LevelLayer_H
#include <glm/glm.hpp>
#include "graphicssettings.h"
#include "../gamesettings.h"
#include "objects\Gear.h"
#include "objects\Player.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <list>

#define GEAR_BUFFER_SIZE 10
#define MAX_GEARS	5

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

class LevelLayer
{
public:
	LevelLayer(glm::mat4 projMatrix);
	~LevelLayer();
	void draw(glm::vec3 cameraPosition, float delta);
	void reset();
	void movePlayer(glm::vec3 directions);
	void movePlayerZ(float directions);
	void movePlayerAngle(float angle);
	void movePlayerJump();
	void rotatePlayer(float directions);
	void turnOffPlayerLight();
	bool playerAlive;
	void setPlayerBlur(bool value);
private:
	bool holdPlayer;
	glm::vec3 playerStartPosition;
	std::list<Gear> gears;
	std::vector<Gear> gearsOnScreen;
	Gear* gearsBuffert[GEAR_BUFFER_SIZE];
	glm::mat4 projMatrix;
	glm::vec3 cameraPosition;
	float delta;
	int onScreen;
	int currentGears[MAX_GEARS];
	int startGear;
	Player* player;
	//Gear* debugGear;
};


#endif
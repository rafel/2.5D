#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <glm/glm.hpp>
#include "graphicssettings.h"
#include "../gamesettings.h"
#include "StateLayer.h"
#include "BackgroundLayer.h"
#include "ForegroundLayer.h"
#include "LevelLayer.h"
#include "objects\Player.h"
#include <iostream>



class Environment
{
public:
	Environment(glm::mat4 projMatrix);
	~Environment();
	void draw(glm::vec3 cameraPosition, float delta);
	void setProjMatrix(glm::mat4);
	void reset();
	void show();
	void changeColors();
	void moveCircle(float,float);
	void setGameState(int);
	int getGameState();
	void movePlayerX(float direction);
	void movePlayerY(float direction);
	void movePlayerZ(float direction);
	void movePlayer(glm::vec3 directions);
	void movePlayerAngle(float angle);
	void rotatePlayer(float angleDirection);
	void movePlayerJump();
	void setPlayerBlur(bool value);
private:
	void drawStartScreen();
	void drawGameScreen();
	void drawPausScreen();
	void drawEndScreen();
	StateLayer* stateLayer;
	BackgroundLayer* background;
	ForegroundLayer* foreground;
	LevelLayer* levelLayer;

	glm::mat4 projMatrix;
	int gameState;
	glm::vec3 cameraPosition;
	float delta;
};


#endif
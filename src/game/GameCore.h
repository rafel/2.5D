#ifndef GAMECORE
#define GAMECORE

#include "input/InputCore.h"
#include "graphics/window.h"
#include "graphics/Environment.h"
#include "gamesettings.h"
#include "sound/AudioPlayer.h"
#include <glm/glm.hpp>
extern bool lightOnGame;

class GameCore
{
public:
	GameCore();
	~GameCore();
	void start();
	
private:
	/* these two are used to generate a delata value that is used overall in the game */
	void calculateDelta();
	float lastFrameTime;
	float delta;
	/*************************/

	void startGameLoop();
	void startScreen();
	void gameScreen();
	void pausScreen();
	void endScreen();
	int gameState;
	bool running;
	InputCore* input;
	Window* windowOpengl;
	Environment*environment;
	AudioPlayer* audioPlayer;
	glm::vec3 cameraPosition;
};

#endif
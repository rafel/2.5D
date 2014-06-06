#include "GameCore.h"
#include "input/InputCore.h"
#include "graphics/window.h"
#include <iostream>
#include "graphics\graphicssettings.h"

// Lights on
bool lightOnGame = true;

// Const. new Window, reset camera position
GameCore::GameCore()
{
	this->windowOpengl = new Window();
	windowOpengl->show();
	this->cameraPosition=glm::vec3(0,0,400);
}

// Deconst. remove all created objects
GameCore::~GameCore()
{
	delete input;
	delete windowOpengl;
	delete environment;
	delete audioPlayer;
}

// Calculated delta time
void GameCore::calculateDelta()
{
	float time = glfwGetTime();
	float delta = time - lastFrameTime;
	lastFrameTime = time;
	this->delta = (delta)*1000/16.67f;
}

// Starts the game
void GameCore::start()
{
	try
	{
		// New inputcore, audioplayer, game enviroment
		this->input= new InputCore();
		this->audioPlayer = new AudioPlayer();
		this->gameState = GAME_STATE_START;
		this->running = true;
		this->environment = new Environment(windowOpengl->getProjecionMatrix());
		this->environment->setGameState(gameState);
		environment->show();
		
		// Starts gameloop
		startGameLoop();
	}
	catch(const char* s)
	{
		throw s;
	}	
}

// GameLoop
void GameCore::startGameLoop()
{
	try
	{
		while(running)
		{
			calculateDelta();

			/* Head tracking to camera position  */
			if(this->input->buttonL2())
				cameraPosition.x=int(input->getDirectionHeadRX_Clean().x*100)*10;
			else
				cameraPosition.x=0;


			
			
			/* Calls functions according to game states */
			if(gameState == GAME_STATE_RUN){
				this->gameScreen();
			}
			else if(gameState == GAME_STATE_PAUS){
				this->pausScreen();
			}
			else if(gameState == GAME_STATE_START){
				this->startScreen();
			}
			else if(gameState == GAME_STATE_END){
				this->endScreen();
			}
			environment->draw(cameraPosition,delta);
			windowOpengl->update();
		}
	}
	catch(const char* s)
	{
		throw s;
	}
}

// Game screen (playing screen)
void GameCore::gameScreen(){

	/* Light on/off */
	if(this->input->buttonR2())
		lightOnGame=false;
	if(this->input->buttonR1())
		lightOnGame=true;

	// Enable blur on the gear the player stands on
	environment->setPlayerBlur(this->input->buttonL1());
	if(!windowOpengl->windowVisible()){
		this->running = false;
	}

	// Paus
	if(input->onReleaseStartButton()){
		gameState = GAME_STATE_PAUS;
		this->environment->setGameState(gameState);
	}

	// Jump
	if(input->onReleaseButtonThree()){
		environment->movePlayerJump();
	}
	
	// Move direction X
	if(input->directionMovmentX() !=0){
		this->environment->movePlayerAngle(input->directionMovmentX()/10);
	}

	environment->draw(cameraPosition,delta);
	this->gameState = this->environment->getGameState();
}

// Paus screen
void GameCore::pausScreen(){
	lightOnGame=false;

		// Back to game
		if(input->onReleaseStartButton()){
			gameState = GAME_STATE_RUN;
			this->environment->setGameState(gameState);
		}
		// Exit
		if(input->onReleaseSelectButton()){
			gameState = GAME_STATE_END;
			this->environment->setGameState(gameState);
		}
		environment->draw(cameraPosition,delta);
		this->gameState = this->environment->getGameState();
}

// Start screen
void GameCore::startScreen(){
	lightOnGame=false;

	// Starts the game
	if(input->onReleaseStartButton()){
		gameState = GAME_STATE_RUN;
		this->environment->setGameState(gameState);
	}
	environment->draw(cameraPosition,delta);
}

// End screen
void GameCore::endScreen(){
	lightOnGame=false;
	// reset the game
	if(input->onReleaseStartButton()){
		this->environment->reset();
		gameState = GAME_STATE_RUN;
		this->environment->setGameState(gameState);
	}
	// Exit
	if(input->onReleaseSelectButton()){
		this->running = false;
	}
	environment->draw(cameraPosition,delta);
	this->gameState = this->environment->getGameState();
}

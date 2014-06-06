#include "LevelLayer.h"
#include <time.h>

clock_t timeStamp;	// timeStamp for last time new gear shown
float padding = 200 + ((float(rand()) / float(RAND_MAX)) * (100 - -50)) + -50;	// Random padding between gears

// Const. New gears, new player
LevelLayer::LevelLayer(glm::mat4 projMatrix)
{
	this->projMatrix = projMatrix;

	// reset
	onScreen = 0;
	startGear = 0;
	timeStamp = clock();
	holdPlayer =true;
	playerStartPosition= glm::vec3(-600.0f,-1000.0f,400.0f);

	// New player
	player = new Player(this->projMatrix);
	playerAlive = true;

	/* NEW GEARS */
	for (int i=0; i<GEAR_BUFFER_SIZE; i++){
		gearsBuffert[i] = new Gear(this->projMatrix);
	//	gearsBuffert[i]->setRandomProperty(PROPERTY_RANDOM_MIDDLE);
		gearsBuffert[i]->setNrOfHills(18);
	}
}

// Deconst. remove gears & player
LevelLayer::~LevelLayer()
{
	for (int i=0; i<GEAR_BUFFER_SIZE; i++){
		delete gearsBuffert[i];
	}
	delete player;
	//delete debugGear;
}

// Move player
void LevelLayer::movePlayer(glm::vec3 directions){
	player->movePlayer(directions);
}

// Move player in Z
void LevelLayer::movePlayerZ(float direction){
	player->movePlayerZ(direction);
}

// Rotate player
void LevelLayer::rotatePlayer(float direction){
	player->rotatePlayer(direction);
}

// Turn playerLight Off
void LevelLayer::turnOffPlayerLight(){
	player->turnOffLight();
}

// Move player in angle
void LevelLayer::movePlayerAngle(float angle)
{
	player->movePlayerAngle(angle);
}

// Player jump
void LevelLayer::movePlayerJump()
{
	player->movePlayerJump();
}

// Reset level
void LevelLayer::reset(){
	player->reset();
	for(int i = 0; i < GEAR_BUFFER_SIZE; i++){
		if(gearsBuffert[i]->inScreen()){
			gearsBuffert[i]->reset();
		}
	}
	this->playerAlive = true;
	onScreen = 0;
	startGear = 0;
	timeStamp = clock();
	holdPlayer =true;
}

// Draw
void LevelLayer::draw(glm::vec3 cameraPosition, float delta){
	if(holdPlayer)player->setPosition(playerStartPosition);
	player->draw(cameraPosition,delta);
	// If player out of screen == dead

	if(player->inScreen()==false&&holdPlayer==false){
		player->explode();
		playerAlive = false;
	}
	

	// For eacg gear in buffer size
	for(int i = 0; i < GEAR_BUFFER_SIZE; i++){
		
		// If slot in screen available && current gear not in screen && last shown gear was over 8 sec ago, show new gear
		if(onScreen<MAX_GEARS){
			if(!gearsBuffert[i]->inScreen() && (float( clock () - timeStamp ) /  CLOCKS_PER_SEC) > 8.00){
				gearsBuffert[i]->setRandomProperty(PROPERTY_RANDOM_MIDDLE);
				onScreen++;
				timeStamp = clock();
			}
		}
		// If gear inscreen move
		if(gearsBuffert[i]->inScreen()){
			gearsBuffert[i]->setPosition(glm::vec3(gearsBuffert[i]->getPosition().x + 2.5f * delta ,gearsBuffert[i]->getPosition().y,gearsBuffert[i]->getPosition().z));
			// if gear out of screen, new slot available for new random gear
			if(!gearsBuffert[i]->inScreen()){
				onScreen--;
			}
			else {
				// Put player on first gear
				if(holdPlayer)
				{
					if(gearsBuffert[i]->getPosition().x>player->getPlayerPosition().x-50.0f&&gearsBuffert[i]->getPosition().x<player->getPlayerPosition().x+50.0f)
					{
						holdPlayer=false;
					}
				}
				// Draw gear
				gearsBuffert[i]->draw(cameraPosition,delta);

				// If player not standing on gear, check new collision
				if(!player->getIsStanding())
				{
					player->checkCollision(gearsBuffert[i]);
				}

			}
		}
	}
}

// Player blur true/false
void LevelLayer::setPlayerBlur(bool value)
{
	player->setPlayerBlur(value);
}
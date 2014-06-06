#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_STATE_MID_AIR 0
#define PLAYER_STATE_WALKING 1
#define PLAYER_STATE_JUMPING 2

#include "../graphicssettings.h" 
    
extern glm::vec3 playerPosition;
extern glm::vec2 playerLightSize;


#include <glm\glm.hpp>
#include "Image.h"
#include "Gear.h"
#include "Leg.h"
//#include "../../GameCore.h"

class Player
{
public:
	Player(glm::mat4 projMatrix);
	~Player();
	void draw(glm::vec3 cameraPosition, float delta);
	void movePlayerX(float direction);
	void movePlayerY(float direction);
	void movePlayerZ(float direction);
	void movePlayerAngle(float angle);
	void movePlayerJump();
	void rotatePlayer(float angleDirection);

	bool getIsStanding();
	bool checkCollision(Gear* gearToCheckCollisionWith);


	void reset();
	
	void movePlayer(glm::vec3 directions);
	void turnOffLight();
	void explode();
	bool inScreen();
	glm::vec3 getPlayerPosition();

	void setPosition(glm::vec3 position);
	void setPlayerBlur(bool value);
private:


		struct PlayerLight{
		glm::vec3 lightPosition;
		glm::vec2 lightAngle;
		glm::vec2 lightSize;
	};
    
    
    float lightWorkingMaring;
        
    PlayerLight playerLight;
    
    	void spinGear(float direction);

	struct PlayerBody{
		Image* body;
		Image* smallGear;
		Image* gear;
		Image* pipe;
		Image* chassis;
		Leg*   rightLeg;
		Leg*   leftLeg;
	};
	bool isStanding;
	Gear* gearStandingOn;
	float delta;
	PlayerBody playerBody;
	float playerSize;
	glm::mat4 projMatrix;
	void drawBody();
	void loadBody();
	glm::vec3 cameraPosition;
	void spinSmallGear();
	//void spinGear(int direction);
	float distanceOverGear;
	int playerState;
	glm::vec3 midAirDirection;
	float desiredJumpAngle;
	float currentMoovementAngle;
};

#endif
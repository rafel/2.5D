#include "Player.h"

glm::vec3 playerPosition = glm::vec3(0,0,0);
glm::vec2 playerLightSize = glm::vec2(2000,50);

// Const Player 
Player::Player(glm::mat4 projMatrix)
{
	gearStandingOn=NULL;
	isStanding=false;
	this->projMatrix = projMatrix;

	this->loadBody();
	this->drawBody();
	
	playerState=PLAYER_STATE_MID_AIR;
	midAirDirection = glm::vec3(0,0,0);
	desiredJumpAngle=0;
	currentMoovementAngle=0;

}

// Set player position
void Player::setPosition(glm::vec3 position)
{
	playerBody.body->position=position;
	playerBody.body->secondRotationRadius=0;
	playerBody.body->secondRotationAngle=0;
	gearStandingOn=NULL;
	isStanding=false;	
}

// Remove player images
Player::~Player()
{
	delete this->playerBody.body;
	delete this->playerBody.smallGear;
	delete this->playerBody.chassis;
	delete this->playerBody.gear;
	delete this->playerBody.pipe;
	delete this->playerBody.rightLeg;
}

// Load player body
void Player::loadBody(){

	// Load body parts
	this->playerBody.body = new Image("playerbody.png");
	this->playerBody.smallGear = new Image("smallGear.png");
	this->playerBody.chassis = new Image("chassis.png");
	this->playerBody.gear = new Image("gear.png");
	this->playerBody.pipe = new Image("playerpipe.png");
	this->playerBody.rightLeg= new Leg();
	this->playerBody.rightLeg->legDirection=LEG_RIGHT_DIR;
	this->playerBody.leftLeg= new Leg();
	this->playerBody.leftLeg->legDirection=LEG_LEFT_DIR;

	// Position
	this->playerBody.body->position.x =100.0f;
	this->playerBody.body->position.y =100.0f;
	this->playerBody.body->position.z = 410.0f;

	// Size
	this->playerBody.body->width = 400.0f;
	this->playerBody.body->height = 320.0f;
	this->playerBody.smallGear->width = 103.0f;
	this->playerBody.smallGear->height = 104.0f;
	this->playerBody.chassis->width = 105.0f;
	this->playerBody.chassis->height = 131.0f;
	this->playerBody.gear->width = 152.0f;
	this->playerBody.gear->height = 154.0f;
	this->playerBody.pipe->width = 132.0f;
	this->playerBody.pipe->height = 210.0f;
	this->playerSize = 1.0f;
	distanceOverGear=this->playerBody.body->height;

	// Light
	this->playerLight.lightPosition = glm::vec3(0,0,0);
	this->playerLight.lightAngle = glm::vec2(-357.0f,0.65f);
	this->playerLight.lightSize = glm::vec2(2000,50);
	this->lightWorkingMaring = 0;
}

// Draw body
void Player::drawBody(){
	
	if(gearStandingOn!=NULL)
	{
		isStanding=true;
		playerBody.body->position = gearStandingOn->getPosition();
		if(playerState==PLAYER_STATE_JUMPING)
		{
			playerBody.body->secondRotationRadius+=70.0f*delta;
		}


		//we have been or standing right now on a gear
		bool rightlegIsStanding = playerBody.rightLeg->isStanding;
		bool leftlegIsStanding = playerBody.leftLeg->isStanding;


		if(rightlegIsStanding==true&&leftlegIsStanding==true)
		{
			//Rotate right here also...

			//playerBody.body->secondRotationAngle=gearStandingOn->getCurrentAngle()+currentMoovementAngle;

			if(playerState!=PLAYER_STATE_JUMPING)
			{

				
				if(playerBody.body->rotationAngle<1.3)
				{
					playerBody.body->rotationAngle+=2.0f*delta;
				}
				else if(playerBody.body->rotationAngle>1.5)
				{
					playerBody.body->rotationAngle-=2.0f*delta;
				}

			}
			


			isStanding=true;
		}
		if(rightlegIsStanding==true||leftlegIsStanding==true)
		{

			//playerBody.body->secondRotationAngle=gearStandingOn->getCurrentAngle()+currentMoovementAngle;

			if(playerState!=PLAYER_STATE_JUMPING)
			{
				playerBody.body->rotationAngle=1.4;
				
				if(playerBody.body->secondRotationRadius>(gearStandingOn->getSize()+distanceOverGear+10.0f))
				{
					playerBody.body->secondRotationRadius-=60.0f*delta;

				}else if(playerBody.body->secondRotationRadius<(gearStandingOn->getSize()+distanceOverGear-10.0f))
				{
					playerBody.body->secondRotationRadius+=60.0f*delta;
				}
			}
				
			//one is standing
			//rotate player towards
			
		}

		if(rightlegIsStanding==false&&leftlegIsStanding==false)
		{
			//none is standig, why? we should check if they have a gear on target
			bool rightHaveTarget = (playerBody.rightLeg->getGearStandingOn()!=NULL);
			bool leftHaveTarget = (playerBody.leftLeg->getGearStandingOn()!=NULL);
			
			
			
			if(rightHaveTarget==true&&leftHaveTarget==true)
			{
				//they both have targets, lets wait.
				//or maybe check so that we all have the same taget???
				



			}
			else if(rightHaveTarget==true&&leftHaveTarget==false)
			{
				//right leg has a target, give it to left leg
				playerBody.leftLeg->checkCollisionWithGear(playerBody.rightLeg->getGearStandingOn());
			}
			else if(rightHaveTarget==false&&leftHaveTarget==true)
			{
				//left leg has a target, give it to right leg
				playerBody.rightLeg->checkCollisionWithGear(playerBody.leftLeg->getGearStandingOn());
			}
			else if(rightHaveTarget==false&&leftHaveTarget==false)
			{
				//this is bad, we are in mid-air. Lets remove the gravity point and change the positioning system
				if(glm::distance(gearStandingOn->getPosition(),playerBody.body->getRealPosition())>((playerBody.body->width*2)+gearStandingOn->getSize()))
				{
					isStanding=false;
					playerState=PLAYER_STATE_MID_AIR;
					//currentMoovementAngle=0;
					//std::cout<<"no point\n";

					playerBody.body->position= playerBody.body->getRealPosition();
					playerBody.body->rotationAngle+=playerBody.body->secondRotationRadius;
					playerBody.body->secondRotationRadius=0;
					playerBody.body->secondRotationAngle=0;
					gearStandingOn=NULL;
				}

			}
		}


	}
	else
	{
		//Mid-air, lets see if one of the legs has a gear on target
		isStanding=false;
		playerState=PLAYER_STATE_MID_AIR;
		//currentMoovementAngle=0;
		bool rightHaveTarget = (playerBody.rightLeg->getGearStandingOn()!=NULL);
		bool leftHaveTarget = (playerBody.leftLeg->getGearStandingOn()!=NULL);

		if(rightHaveTarget==true||leftHaveTarget==true)
		{
			//here we have to take the z-position of the FOOT that has a target
			//if(rightHaveTarget)playerBody.body->position.z = playerBody.rightLeg->

			if(playerBody.rightLeg->isStanding)
			{
				gearStandingOn=playerBody.rightLeg->getGearStandingOn();
				playerBody.leftLeg->checkCollisionWithGear(gearStandingOn);
			}
			else if(playerBody.leftLeg->isStanding)
			{
				gearStandingOn=playerBody.leftLeg->getGearStandingOn();
				playerBody.rightLeg->checkCollisionWithGear(gearStandingOn);
			}

			if(gearStandingOn!=NULL)
			{

				//just found something to stand on, lets change the positioning system
				float radius= glm::distance(playerBody.body->position,gearStandingOn->getPosition());
				float angle = atan2(playerBody.body->getRealPosition().y-gearStandingOn->getPosition().y,playerBody.body->getRealPosition().x-gearStandingOn->getPosition().x);
			
				playerBody.body->position = gearStandingOn->getPosition();
				playerBody.body->rotationAngle-=angle;
				playerBody.body->secondRotationAngle=angle;
			
				playerBody.body->secondRotationRadius=radius;
			}

		}
		else
		{
			//this is bad, we are in mid-air

			
			//fall
			midAirDirection.y+=0.005*delta;
			if(midAirDirection.x>0)midAirDirection.x-=0.003*delta;
			if(midAirDirection.x<0)midAirDirection.x+=0.003*delta;
			
			//std::cout<<"falling\n";
			
			playerBody.body->position= playerBody.body->getRealPosition();
			playerBody.body->rotationAngle-=playerBody.body->secondRotationAngle;
			playerBody.body->secondRotationRadius=0;
			playerBody.body->secondRotationAngle=0;
			gearStandingOn=NULL;
			//playerBody.body->position+=midAirDirection*40.0f*delta;
			
			playerBody.body->position.x+=midAirDirection.x*40.0f*delta;
			playerBody.body->position.y+=midAirDirection.y*40.0f*delta;
			playerBody.body->position.z+=midAirDirection.z*40.0f*delta;
			
		}

	}


	this->playerBody.rightLeg->rotationCenterPoint = this->playerBody.body->getRealPosition();
	this->playerBody.rightLeg->radius= 260.0f;
	this->playerBody.rightLeg->rotationAngle=this->playerBody.body->getRealRotationAngle()+1.22173048f;


	this->playerBody.leftLeg->rotationCenterPoint = this->playerBody.body->getRealPosition();
	this->playerBody.leftLeg->radius= 213.66;
	this->playerBody.leftLeg->rotationAngle=this->playerBody.body->getRealRotationAngle()+2.09378f;

	this->playerBody.gear->position = this->playerBody.body->getRealPosition();
	//this->playerBody.gear->secondRotationRadius = 140.0f;
	
	//this->playerBody.gear->secondRotationAngle = this->playerBody.body->getRealRotationAngle()+0.628318531f;
	//this->playerBody.gear->secondRotationAngle =this->playerBody.body->getRealRotationAngle()+variableToAdd;
	this->playerBody.gear->secondRotationAngle =this->playerBody.body->getRealRotationAngle()+0.8068;
	this->playerBody.gear->secondRotationRadius = 191.072f;
	
	
	this->playerBody.pipe->position = this->playerBody.body->getRealPosition();
	this->playerBody.pipe->secondRotationAngle =this->playerBody.body->getRealRotationAngle()+0.0868633;
	this->playerBody.pipe->secondRotationRadius = 184.476;
	
	this->playerBody.chassis->position = this->playerBody.body->getRealPosition();
	this->playerBody.chassis->secondRotationAngle =this->playerBody.body->getRealRotationAngle()+1.58436f;
	this->playerBody.chassis->secondRotationRadius = 125.731;
	this->playerBody.chassis->rotationAngle= -1.15999;
		
	this->playerBody.smallGear->position = this->playerBody.body->getRealPosition();
	this->playerBody.smallGear->secondRotationAngle =this->playerBody.body->getRealRotationAngle()+2.00811;
	this->playerBody.smallGear->secondRotationRadius = 96.2629;


	
	/* LIGHTING */
	// Position
	this->playerLight.lightPosition = this->playerBody.body->getRealPosition();
	this->playerLight.lightPosition.x += this->playerLight.lightAngle.x * cos(this->playerLight.lightAngle.y+this->playerBody.body->rotationAngle+this->playerBody.body->secondRotationAngle);
	this->playerLight.lightPosition.y += this->playerLight.lightAngle.x * sin(this->playerLight.lightAngle.y+this->playerBody.body->rotationAngle+this->playerBody.body->secondRotationAngle);

	float zRatio = (100.0f/(this->playerBody.body->position.z));
	this->playerLight.lightPosition = glm::vec3((this->playerLight.lightPosition.x-cameraPosition.x)*WCX*zRatio,(this->playerLight.lightPosition.y-cameraPosition.y)*WCY*zRatio,this->playerBody.body->position.z);

	playerPosition = this->playerLight.lightPosition;
	playerPosition.x += (WINDOW_WIDTH/2);
	playerPosition.y = WINDOW_HEIGHT - (playerPosition.y + WINDOW_HEIGHT/2);

	// Light size
	this->playerLight.lightSize = glm::vec2(2000+this->lightWorkingMaring,50);
	playerLightSize = this->playerLight.lightSize;

	// Gear
	this->spinSmallGear();
}

// Move player in angle
void Player::movePlayerAngle(float angle)
{
	
	if(this->playerBody.body->secondRotationAngle >M_2PI) this->playerBody.body->secondRotationAngle -=M_2PI;
	if(this->playerBody.body->secondRotationAngle < 0) this->playerBody.body->secondRotationAngle +=M_2PI;
	this->playerBody.body->secondRotationAngle += angle*delta;

	if(angle > 0){
		this->lightWorkingMaring = 50;
		this->spinGear(10);
	}
	else {
		this->lightWorkingMaring = 50;
		this->spinGear(-10);
	}
}

// Move player X
void Player::movePlayerX(float direction){
	this->playerBody.body->position.x += direction*delta;
	this->spinGear(direction);
}

// Move player Y
void Player::movePlayerY(float direction){
	this->playerBody.body->position.y += direction*delta;
	this->spinGear(direction);
	this->drawBody();
}

// Draw 
void Player::draw(glm::vec3 cameraPosition, float delta){

	this->delta=delta;
	this->cameraPosition = cameraPosition;

	// Draw all parts
	this->playerBody.pipe->draw(projMatrix,cameraPosition);
	this->playerBody.gear->draw(projMatrix,cameraPosition);
	this->playerBody.rightLeg->draw(projMatrix,cameraPosition,delta);
	this->playerBody.leftLeg->draw(projMatrix,cameraPosition,delta);
	this->playerBody.body->draw(projMatrix,cameraPosition);
	this->playerBody.smallGear->draw(projMatrix,cameraPosition);
	this->playerBody.chassis->draw(projMatrix,cameraPosition);
	
	// Spin small gear
	this->spinSmallGear();
	
	// Draws the body
	this->drawBody();


}

// Spin smallgear
void Player::spinSmallGear(){
	if(this->playerBody.smallGear->rotationAngle >M_2PI){
		this->playerBody.smallGear->rotationAngle = 0;
	}
	this->playerBody.smallGear->rotationAngle += 0.02f*delta;
}


// Spin gear
void Player::spinGear(float direction){
	this->playerBody.gear->rotationAngle += (direction/100) * delta; 
}

// Move player Z
void Player::movePlayerZ(float direction){
	this->playerBody.body->position.z += (direction*delta);
}


// Rotate player
void Player::rotatePlayer(float angleDirection)
{
	if(this->playerBody.body->rotationAngle >M_2PI||this->playerBody.body->rotationAngle <-M_2PI)
		this->playerBody.body->rotationAngle =0;
	this->playerBody.body->rotationAngle +=angleDirection*delta;

}

// If standing
bool Player::getIsStanding()
{
	return isStanding;
}

// Check collition with gear
bool Player::checkCollision(Gear* gearToCheckCollisionWith)
{
	if(gearToCheckCollisionWith->checkCollision(this->playerBody.rightLeg->rotationCenterPoint,this->playerBody.rightLeg->getLength()))
	{
		if(this->playerBody.rightLeg->checkCollisionWithGear(gearToCheckCollisionWith))
		{
			return true;
		}
	}
	if(gearToCheckCollisionWith->checkCollision(this->playerBody.leftLeg->rotationCenterPoint,this->playerBody.leftLeg->getLength()))
	{
		if(this->playerBody.leftLeg->checkCollisionWithGear(gearToCheckCollisionWith))
		{
			return true;
		}
	}
	return false;
}

// Jump
void Player::movePlayerJump()
{
	if(playerState!=PLAYER_STATE_JUMPING&&gearStandingOn!=NULL)
	{
		playerState=PLAYER_STATE_JUMPING;
		desiredJumpAngle= M_PI+playerBody.body->rotationAngle;

		playerBody.body->rotationAngle = desiredJumpAngle;
		midAirDirection=playerBody.body->getRealPosition()-gearStandingOn->getPosition();
		midAirDirection/=glm::distance(playerBody.body->getRealPosition(),gearStandingOn->getPosition());
	}
}


// Move player in direction
void Player::movePlayer(glm::vec3 direction){
	if(direction.x != 0){
		this->playerBody.body->position.x += direction.x*delta;
		if(direction.x > 0){
			this->lightWorkingMaring = 5*direction.x*-1;
		}else {
			this->lightWorkingMaring = 5*direction.x;
		}
		this->spinGear(direction.x);
	}
	if(direction.y != 0){
		this->playerBody.body->position.y += direction.y*delta;
		if(direction.y > 0){
			this->lightWorkingMaring = 5*direction.y*-1;
		}else {
			this->lightWorkingMaring = 5*direction.y;
		}
		this->spinGear(direction.y);
	}
	if(direction.x == 0 && direction.y == 0){
		this->lightWorkingMaring =0;
	}
	if(direction.x != 0 && direction.y != 0){
		this->spinGear(direction.x);
	}
	this->drawBody();
}


// Get player position
glm::vec3 Player::getPlayerPosition(){
	return this->playerBody.body->position;
}

// Explore (runs when player die)
void Player::explode(){
	playerPosition = glm::vec3(0,0,0);
}

// Turn off lights
void Player::turnOffLight(){
	playerPosition = glm::vec3(0,0,0);
	std::cout << playerPosition.x << " : " << playerPosition.y << "\n";
}

// If player in screen
bool Player::inScreen(){
	return this->playerBody.body->inScreen();
}


// Reset positions
void Player::reset(){
	this->playerBody.body->position.x =100.0f;
	this->playerBody.body->position.y =100.0f;
	this->playerBody.body->position.z = 400;
	this->playerBody.body->width = 400.0f;
	this->playerBody.body->height = 320.0f;
	this->playerBody.smallGear->width = 103.0f;
	this->playerBody.smallGear->height = 104.0f;
	this->playerBody.chassis->width = 105.0f;
	this->playerBody.chassis->height = 131.0f;
	this->playerBody.gear->width = 152.0f;
	this->playerBody.gear->height = 154.0f;
	this->playerBody.pipe->width = 132.0f;
	this->playerBody.pipe->height = 210.0f;
	this->playerSize = 1.0f;
	this->playerLight.lightPosition = glm::vec3(0,0,0);
	this->playerLight.lightAngle = glm::vec2(-357.0f,0.65f);
	this->playerLight.lightSize = glm::vec2(2000,50);
	this->lightWorkingMaring = 0;
	this->draw(cameraPosition,delta);
}

// Set blur on standing on gear 
void Player::setPlayerBlur(bool value)
{

	if(gearStandingOn!=NULL)
	{
		if(value)
			gearStandingOn->gearImage->blur(glm::vec2(1,1));
		else
			gearStandingOn->gearImage->blur(glm::vec2(0,0));

	}
}
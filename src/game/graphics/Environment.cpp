#include "Environment.h"

// Const
Environment::Environment(glm::mat4 projMatrix)
{
	this->projMatrix = projMatrix;
}

// Removes all new objects
Environment::~Environment()
{
	delete background;
	delete foreground;
	delete levelLayer;
}

// Draw 
void Environment::draw(glm::vec3 cameraPosition, float delta){
	this->delta = delta;
	this->cameraPosition = cameraPosition;

	/* Draw screen for current gamestate */
	if(gameState == GAME_STATE_RUN){
		this->drawGameScreen();
	}
	else if(gameState == GAME_STATE_PAUS){
		this->drawPausScreen();
	}
	else if(gameState == GAME_STATE_START){
		this->drawStartScreen();
	}
	else if(gameState == GAME_STATE_END){
		this->drawEndScreen();
	}
}

// Game screen
void Environment::drawGameScreen(){

	// Enablue alpha to be able to blend pixels
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT );

	// Draw objects
	background->draw(cameraPosition,delta);
	levelLayer->draw(cameraPosition,delta);
	foreground->draw(cameraPosition,delta);

	// If player not alive, change state
	if(!levelLayer->playerAlive){
		levelLayer->turnOffPlayerLight();
		setGameState(GAME_STATE_END);
	}

	// Disable blend
	glDisable(GL_BLEND);
}

// Returns gamestate
int Environment::getGameState(){
	return this->gameState;
}

// Draws PausScreen
void Environment::drawPausScreen(){
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
    glClear( GL_COLOR_BUFFER_BIT );
	stateLayer->drawPaus(cameraPosition,delta);
	glDisable(GL_BLEND);
}

// Draws start screen
void Environment::drawStartScreen(){
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
    glClear( GL_COLOR_BUFFER_BIT );
	stateLayer->drawStart(cameraPosition,delta);
	glDisable(GL_BLEND);
}

// Draws end screen
void Environment::drawEndScreen(){
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
    glClear( GL_COLOR_BUFFER_BIT );
	stateLayer->drawEnd(cameraPosition,delta);
	glDisable(GL_BLEND);
}

// Sets gameState
void Environment::setGameState(int state){
	this->gameState = state;
}

// Reset game
void Environment::reset(){
	this->levelLayer->reset();
	this->setGameState(GAME_STATE_RUN);
}

// Sets projection matrix
void Environment::setProjMatrix(glm::mat4 projMatrix)
{
	this->projMatrix= projMatrix;
}

// Show game enviroment
void Environment::show(){
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //we tell opengl that we are using the entire window to draw.
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glOrtho(0,WINDOW_WIDTH,WINDOW_HEIGHT,0,0,1);
    glDisable(GL_DEPTH_TEST);

    //get back to drawing
    glMatrixMode( GL_MODELVIEW );

    //set the background color
    glClearColor( 0.58f, 0.58f, 0.47f, 0.0f );
	
	// new game layers
	stateLayer = new StateLayer(this->projMatrix);
	background = new BackgroundLayer(this->projMatrix);
	foreground = new ForegroundLayer(this->projMatrix);
	levelLayer = new LevelLayer(this->projMatrix);
}

// Move player
void Environment::movePlayer(glm::vec3 directions){
	levelLayer->movePlayer(directions);
}

// Move player Z player
void Environment::movePlayerZ(float direction){
	levelLayer->movePlayerZ(direction);
}

// Rotate player in direction
void Environment::rotatePlayer(float direction){
	levelLayer->rotatePlayer(direction);
}

// Move player in angles
void Environment::movePlayerAngle(float angle)
{
	levelLayer->movePlayerAngle(angle);
}

// Player jump
void Environment::movePlayerJump()
{
	levelLayer->movePlayerJump();
}

// Enable/disable blur
void Environment::setPlayerBlur(bool value)
{
	levelLayer->setPlayerBlur(value);
}
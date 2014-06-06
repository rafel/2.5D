/*********************************

2.5D , Rafel, Sam , Atie

**********************************/


#include "game/GameCore.h"


int main(int argc, const char* argv[])
{
	// Runs the game
	GameCore* theGame = new GameCore();
	theGame->start();
	delete theGame;
	return 0; 
}
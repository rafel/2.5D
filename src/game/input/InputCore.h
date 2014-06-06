#ifndef INPUTCORE
#define INPUTCORE


#include "joystick\JoystickHandler.h"
#include "primesense\PrimeSenseCore.h"
#include <glm\glm.hpp>


#define PRIMESENSE_BUFFER_SIZE 20



class InputCore

{
public:
	InputCore();
	~InputCore();
	bool fireAction();
	bool jumpAction();
	glm::vec3 getDirectionHeadRX();
	glm::vec3 getDirectionHeadRX_Clean();
	float directionMovmentX();
	float directionMovmentY();
	float directionMovmentZ();
	float directionRotation();
	bool quitKeyPressed();
	bool startButton();
	bool selectButton();
	
	bool lastButtonThreeValue;
	bool onReleaseButtonThree();

	bool lastButtonStartValue;
	bool onReleaseStartButton();

	bool lastButtonSelectValue;
	
	bool onReleaseSelectButton();

		bool buttonL1();
	bool buttonL2();
	bool buttonR1();
	bool buttonR2();
private:
	bool JOYSTICK_FOUND;
bool PRIMESENSE_FOUND;
	float primeSenseBuffer[PRIMESENSE_BUFFER_SIZE];
	int primeSenseBufferPointer;
	JoystickHandler* joystick;
	PrimeSenseCore* primeSense;
};

#endif
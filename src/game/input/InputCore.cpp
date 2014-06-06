#include "InputCore.h"
#include <GL/glfw.h>
#include <iostream>

// Constructor, here we initialize joystick & primesense
InputCore::InputCore()
{
	PRIMESENSE_FOUND=false;
	JOYSTICK_FOUND=false;
	primeSense = new PrimeSenseCore();
	joystick = new JoystickHandler();
	primeSenseBufferPointer=0;
	if(joystick->initialize()){
		JOYSTICK_FOUND =true;
	}
	if(primeSense->initialize()==0){
		PRIMESENSE_FOUND = true;

		for (int i = 0; i < PRIMESENSE_BUFFER_SIZE; i++)
		{
			primeSenseBuffer[i]=0.0f;
		}

	}
}

//Deconst.
InputCore::~InputCore()
{
	joystick->~JoystickHandler();
	delete primeSense;
}

// If nothing pressed , return direction X 0. If joystick analog or keyarrows pressed returns direction X value between [-1,1]
float InputCore::directionMovmentX(){
	if(JOYSTICK_FOUND){
		if(this->joystick->getAnalogValue(JOYSTICK_ANALOG_LEFTX) != 0){
			return this->joystick->getAnalogValue(JOYSTICK_ANALOG_LEFTX);
		}
		if(joystick->dPADPressed(JOYSTICK_DPAD_LEFT)){
			return -1;
		}
		if(joystick->dPADPressed(JOYSTICK_DPAD_RIGHT)){
			return 1;
		}
		if(joystick->dPADPressed(JOYSTICK_DPAD_LEFTUP) || joystick->dPADPressed(JOYSTICK_DPAD_DOWNLEFT)){
			return -1;
		}
		if(joystick->dPADPressed(JOYSTICK_DPAD_UPRIGHT) || joystick->dPADPressed(JOYSTICK_DPAD_RIGHTDOWN)){
			return 1;
		}
	}
	if((glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) ){
		return 1;
	}
	if((glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) ){
		return -1;
	}
	return 0;
}

// If nothing pressed , return direction Y 0. If joystick analog or keyarrows pressed returns direction Y value between [-1,1]
float InputCore::directionMovmentY(){
	if(JOYSTICK_FOUND){
		if(this->joystick->getAnalogValue(JOYSTICK_ANALOG_LEFTY) != 0){
			return this->joystick->getAnalogValue(JOYSTICK_ANALOG_LEFTY);
		}
		if(joystick->dPADPressed(JOYSTICK_DPAD_UP)){
			return -1;
		}
		if(joystick->dPADPressed(JOYSTICK_DPAD_DOWN)){
			return 1;
		}
		if(joystick->dPADPressed(JOYSTICK_DPAD_LEFTUP) || joystick->dPADPressed(JOYSTICK_DPAD_UPRIGHT)){
			return -1;
		}
		if(joystick->dPADPressed(JOYSTICK_DPAD_DOWNLEFT) || joystick->dPADPressed(JOYSTICK_DPAD_RIGHTDOWN)){
			return 1;
		}
	}
	if((glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) ){
		return -1;
	}
	if((glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS)){
		return 1;
	}
	return 0;
}

glm::vec3 InputCore::getDirectionHeadRX(){
	if(JOYSTICK_FOUND){
		if(this->joystick->buttonPressed(JOYSTICK_BUTTON_R2)){
			return glm::vec3(this->joystick->getAnalogValue(JOYSTICK_ANALOG_LEFTX),this->joystick->getAnalogValue(JOYSTICK_ANALOG_LEFTY),this->joystick->getAnalogValue(JOYSTICK_ANALOG_LEFTZ));
		}
	}
	if(PRIMESENSE_FOUND){
		return this->primeSense->getClosestPoint();
	}
	return glm::vec3(0,0,0);
}

glm::vec3 InputCore::getDirectionHeadRX_Clean(){
	if(JOYSTICK_FOUND){
		if(this->joystick->buttonPressed(JOYSTICK_BUTTON_R2)){
			return glm::vec3(this->joystick->getAnalogValue(JOYSTICK_ANALOG_LEFTX),this->joystick->getAnalogValue(JOYSTICK_ANALOG_LEFTY),this->joystick->getAnalogValue(JOYSTICK_ANALOG_LEFTZ));
		}
	}
	if(PRIMESENSE_FOUND){
		glm::vec3 closestRightNow = this->primeSense->getClosestPoint();

		if(primeSenseBufferPointer>=PRIMESENSE_BUFFER_SIZE) primeSenseBufferPointer=0;
		if(primeSenseBufferPointer<0) primeSenseBufferPointer=0;
		primeSenseBufferPointer++;
		primeSenseBuffer[primeSenseBufferPointer]=closestRightNow.x;
		float cleanX =0;
		for (int i = 0; i < PRIMESENSE_BUFFER_SIZE; i++)
		{
			cleanX+=primeSenseBuffer[i];
		}
		cleanX/=PRIMESENSE_BUFFER_SIZE;
		closestRightNow.x=cleanX;
		return closestRightNow;
	}
	return glm::vec3(0,0,0);
}


// Return true if button three or space is released
bool InputCore::onReleaseButtonThree()
{
	if(joystick->buttonPressed(JOYSTICK_BUTTON_THREE) || (glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS)){
		this->lastButtonThreeValue = true;
		return false;
	}
	else {
		if(lastButtonThreeValue == true){
			lastButtonThreeValue = false;
			return true;
		}
	}
	return false;
}

// Return true if start button or enter is released
bool InputCore::onReleaseStartButton()
{
	if(joystick->buttonPressed(JOYSTICK_BUTTON_START) || (glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS)){
		this->lastButtonStartValue = true;
		return false;
	}
	else {
		if(lastButtonStartValue == true){
			lastButtonStartValue = false;
			return true;
		}
	}
	return false;
}

// Return true if select button or esc is released
bool InputCore::onReleaseSelectButton()
{
	if(joystick->buttonPressed(JOYSTICK_BUTTON_SELECT) || (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)){
		this->lastButtonSelectValue = true;
		return false;
	}
	else {
		if(lastButtonSelectValue == true){
			lastButtonSelectValue = false;
			return true;
		}
	}
	return false;
}


// If L2 or 2 is pressed
bool InputCore::buttonL2()
{
	return (this->joystick->buttonPressed(JOYSTICK_BUTTON_L2) || (glfwGetKey('2') == GLFW_PRESS) );
}

// If L1 or 1 is pressed
bool InputCore::buttonL1()
{
	return (this->joystick->buttonPressed(JOYSTICK_BUTTON_L1) || (glfwGetKey('1') == GLFW_PRESS) );
}

// If R1 or 3 is pressed
bool InputCore::buttonR1()
{
	return (this->joystick->buttonPressed(JOYSTICK_BUTTON_R1) || (glfwGetKey('3') == GLFW_PRESS) );
}

// If R2 or 4 is pressed
bool InputCore::buttonR2()
{
	return (this->joystick->buttonPressed(JOYSTICK_BUTTON_R2) || (glfwGetKey('4') == GLFW_PRESS) );
}
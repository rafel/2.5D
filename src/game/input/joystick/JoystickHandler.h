#pragma once
#include <windows.h>
#include <stdio.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class JoystickHandler
{
public:
	JoystickHandler(void);
	~JoystickHandler(void);
	bool initialize();
	bool dPADPressed(int);
	float getAnalogValue(int);
	bool buttonPressed(int);
	bool comboButtonsPressed(int[]);
protected:
	struct Entry {
        DIDEVICEINSTANCE        diDeviceInstance;
        DIDEVCAPS               diDevCaps;
        LPDIRECTINPUTDEVICE8    diDevice;
        DIJOYSTATE2             joystate;
    };

	Entry*          entry;
    int             maxEntry;
    int             nEntry;
    LPDIRECTINPUT   di;
    LPCDIDATAFORMAT lpdf;
	const DIJOYSTATE2* js;
	static BOOL CALLBACK DIEnumDevicesCallback_static(LPCDIDEVICEINSTANCE,LPVOID);
	BOOL DIEnumDevicesCallback(LPCDIDEVICEINSTANCE , LPVOID );
	void clear();
	void enumerate(LPDIRECTINPUT, DWORD, LPCDIDATAFORMAT, DWORD, int);
	int getEntryCount() const;
	const Entry* getEntry(int) const;
	bool update();
};


// Buttons , Analog, Pads
#define JOYSTICK_DPAD_NOTHING					-1
#define JOYSTICK_DPAD_UP						0
#define JOYSTICK_DPAD_UPRIGHT					45
#define JOYSTICK_DPAD_RIGHT						90
#define JOYSTICK_DPAD_RIGHTDOWN					135
#define JOYSTICK_DPAD_DOWN						180
#define JOYSTICK_DPAD_DOWNLEFT					225
#define JOYSTICK_DPAD_LEFT						270
#define JOYSTICK_DPAD_LEFTUP					315

#define JOYSTICK_ANALOG_LEFTX					0
#define JOYSTICK_ANALOG_LEFTY					1
#define JOYSTICK_ANALOG_LEFTZ					2
#define JOYSTICK_ANALOG_RIGHTX					3
#define JOYSTICK_ANALOG_RIGHTY					4
#define JOYSTICK_ANALOG_RIGHTZ					5

#define JOYSTICK_BUTTON_ONE						1
#define JOYSTICK_BUTTON_TWO						2
#define JOYSTICK_BUTTON_THREE					4
#define JOYSTICK_BUTTON_FOUR					8
#define JOYSTICK_BUTTON_L1						16
#define JOYSTICK_BUTTON_R1						32
#define JOYSTICK_BUTTON_L2						64
#define JOYSTICK_BUTTON_R2						128
#define JOYSTICK_BUTTON_SELECT					256
#define JOYSTICK_BUTTON_START					512
#define JOYSTICK_BUTTON_L3						1024
#define JOYSTICK_BUTTON_R3						2048
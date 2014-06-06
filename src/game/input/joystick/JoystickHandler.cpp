#include "JoystickHandler.h"

// Const. reset values
JoystickHandler::JoystickHandler()
{
	this->entry = 0;
	this->maxEntry = 0;
	this->nEntry = 0;
	this->di = 0;
}

// Deconst.
JoystickHandler::~JoystickHandler()
{
	this->clear();
}

// If values, clean
void JoystickHandler::clear(){
	if(entry) {
		delete [] entry;
		entry = 0;
	}
	maxEntry    = 0;
	nEntry      = 0;
	di          = 0;
}	

// Hook on joystick
void JoystickHandler::enumerate(LPDIRECTINPUT di, DWORD dwDevType = DI8DEVTYPE_JOYSTICK, LPCDIDATAFORMAT lpdf = &c_dfDIJoystick2, DWORD dwFlags = DIEDFL_ATTACHEDONLY, int maxEntry = 16) {
        clear();
 
        entry           = new Entry [maxEntry];
        this->di        = di;
        this->maxEntry  = maxEntry;
        nEntry          = 0;
        this->lpdf      = lpdf;
	
		// Callbacks to DIEnumDevicesCallback_static
        di->EnumDevices(dwDevType, DIEnumDevicesCallback_static, this, dwFlags);
 
        this->di        = 0;
}
 
// Returns nEntry
int JoystickHandler::getEntryCount() const {
    return nEntry;
}
 
// Returns entry by index
const JoystickHandler::Entry* JoystickHandler::getEntry(int index) const {
    const Entry* e = 0;
    if(index >= 0 && index < nEntry) {
        e = &entry[index];
    }
    return e;
}
 
// Update, polls values from Joystick
bool JoystickHandler::update() {
    for(int iEntry = 0; iEntry < nEntry; ++iEntry) {
        Entry& e = entry[iEntry];
        LPDIRECTINPUTDEVICE8 d = e.diDevice;
 
        if(FAILED(d->Poll())) {
            HRESULT hr = d->Acquire();
            while(hr == DIERR_INPUTLOST) {
                hr = d->Acquire();
            }
        } else {
            d->GetDeviceState(sizeof(DIJOYSTATE2), &e.joystate);
        }
    }

	const JoystickHandler::Entry* e = this->getEntry(0);
    if(e) {
		this->js = &e->joystate;
		return true;
	}
	return false;

}

// On callback , call DIEnumDevicesCallback
BOOL CALLBACK JoystickHandler::DIEnumDevicesCallback_static(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef) {
    return reinterpret_cast<JoystickHandler*>(pvRef)->DIEnumDevicesCallback(lpddi, pvRef);
}

// Callbacks from hooking on device
BOOL JoystickHandler::DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef) {
    if(nEntry < maxEntry) {
        Entry e = { 0 };
 
        memcpy(&e.diDeviceInstance, lpddi, sizeof(e.diDeviceInstance));
        e.diDevCaps.dwSize = sizeof(e.diDevCaps);
 
        LPDIRECTINPUTDEVICE8    did = 0;
 
        if(SUCCEEDED(di->CreateDevice(lpddi->guidInstance, (LPDIRECTINPUTDEVICE*) &did, 0))) {
            if(SUCCEEDED(did->SetDataFormat(lpdf))) {
                if(SUCCEEDED(did->GetCapabilities(&e.diDevCaps))) {
                    e.diDevice = did;
                    entry[nEntry++] = e;
                }
            }
        }
    }
    return DIENUM_CONTINUE;
}

// If dPADPressed for button(dPads defined in .h file)
bool JoystickHandler::dPADPressed(int dPADValue){
	if(!this->update()){
		return false;
	}
	int pov = this->js->rgdwPOV[0];

    if(pov < 0) {
        pov = -1;
    } else {
        pov /= 100;
    }
    int btn = 0;
    for(int i = 0; i < 32; ++i) {
        if(this->js->rgbButtons[i]) {
            btn |= 1 << i;
        }
    }
				
	if(pov == dPADValue){
		return true;
	}
	else {
		return false;
	}
}

// Get analog value for joysticks between [-1,1] (analog defined in .h file)
float JoystickHandler::getAnalogValue(int JoyValue){
	if(!this->update()){
		return false;
	}
	float currentValue = 0;
	switch(JoyValue){
	case 0:
		currentValue = float(this->js->lX);
		break;
	case 1:
		currentValue = float(this->js->lY);
		break;
	case 2:
		currentValue = float(this->js->lZ);
		break;
	case 3:
		currentValue = float(this->js->lRz);
		break;
	}

	currentValue = currentValue - (65534 - 32767);
	currentValue = currentValue / 32767;
	if(currentValue > 1){
		currentValue = 1;
	}
	if(currentValue < -1){
		currentValue = -1;
	}
	return currentValue;
}

// If button pressed (buttons defined in .h file)
bool JoystickHandler::buttonPressed(int buttonValue){
	if(!this->update()){
		return false;
	}
	int btn = 0;
	for(int i = 0; i < 32; ++i) {
		if(this->js->rgbButtons[i]) {
			btn |= 1 << i;
		}
	}
	if(buttonValue == btn){
		return true;
	}
	else {
		return false;
	}
}

// If all buttons in array pressed at the same time
bool JoystickHandler::comboButtonsPressed(int comboArray[]){
	if(!this->update()){
		return false;
	}
	int buttonsValue = 0;
	for(int i = 0, length = sizeof(comboArray) - 1; i < length; ++i)
	{
		buttonsValue +=  comboArray[i];
	}
	int btn = 0;
	for(int i = 0; i < 32; ++i) {
		if(this->js->rgbButtons[i]) {
			btn |= 1 << i;
		}
	}
	if(buttonsValue == btn){
		return true;
	}
	else {
		return false;
	}
}

// Initialize joystick
bool JoystickHandler::initialize(){
	LPDIRECTINPUT lpDi = 0;
	if(SUCCEEDED(DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**) &lpDi, 0))) {
		this->enumerate(lpDi);
		return true;
	}
	return false;
}

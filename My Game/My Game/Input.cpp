#include "Input.h"

//=============================================================================
// default constructor
//=============================================================================
Input::Input()
{
	// clear key down array
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysDown[i] = false;
	// clear key pressed array
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysPressed[i] = false;
	newLine = true;                     // start new line
	textIn = "";                        // clear textIn
	charIn = 0;                         // clear charIn

	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		controllers[i].vibrateTimeLeft = 0;
		controllers[i].vibrateTimeRight = 0;
	}
}

//=============================================================================
// destructor
//=============================================================================
Input::~Input() {}

//=============================================================================
// initialize input
//=============================================================================
void Input::initialize(HWND hwnd)
{
	// Clear controllers state
	ZeroMemory(controllers, sizeof(ControllerState) * MAX_CONTROLLERS);

	checkControllers();             // check for connected controllers
}

//=============================================================================
// Set true in the keysDown and keysPessed array for this key
// Pre: wParam contains the virtual key code (0--255)
//=============================================================================
void Input::keyDown(WPARAM wParam)
{
	// make sure key code is within buffer range
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		keysDown[wParam] = true;    // update keysDown array
		// key has been "pressed", erased by clear()
		keysPressed[wParam] = true; // update keysPressed array
		DebugOut("[INFO] KeyDown: %d", wParam);
	}
}

//=============================================================================
// Set false in the keysDown array for this key
// Pre: wParam contains the virtual key code (0--255)
//=============================================================================
void Input::keyUp(WPARAM wParam)
{
	// make sure key code is within buffer range
	if (wParam < inputNS::KEYS_ARRAY_LEN)
		// update state table
		keysDown[wParam] = false;
	DebugOut("[INFO] KeyUp: %d", wParam);
}

//=============================================================================
// Save the char just entered in textIn string
// Pre: wParam contains the char
//=============================================================================
void Input::keyIn(WPARAM wParam)
{
	if (newLine)                            // if start of new line
	{
		textIn.clear();
		newLine = false;
	}

	if (wParam == '\b')                     // if backspace
	{
		if (textIn.length() > 0)             // if characters exist
			textIn.erase(textIn.size() - 1);  // erase last character entered
	}
	else
	{
		textIn += wParam;                   // add character to textIn
		charIn = wParam;                    // save last char entered
	}

	if ((char)wParam == '\r')               // if return    
		newLine = true;                     // start new line
}

//=============================================================================
// Returns true if the specified VIRTUAL KEY is down, otherwise false.
//=============================================================================
bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysDown[vkey];
	else
		return false;
}

//=============================================================================
// Return true if the specified VIRTUAL KEY has been pressed in the most recent
// frame. Key presses are erased at the end of each frame.
//=============================================================================
bool Input::wasKeyPressed(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysPressed[vkey];
	else
		return false;
}

//=============================================================================
// Return true if any key was pressed in the most recent frame.
// Key presses are erased at the end of each frame.
//=============================================================================
bool Input::anyKeyPressed() const
{
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		if (keysPressed[i] == true)
			return true;
	return false;
}

//=============================================================================
// Clear the specified key press
//=============================================================================
void Input::clearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		keysPressed[vkey] = false;
}

//=============================================================================
// Clear specified input buffers
// See input.h for what values
//=============================================================================
void Input::clear(UCHAR what)
{
	if (what & inputNS::KEYS_DOWN)       // if clear keys down
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysDown[i] = false;
	}
	if (what & inputNS::KEYS_PRESSED)    // if clear keys pressed
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysPressed[i] = false;
	}
	if (what & inputNS::TEXT_IN)
		clearTextIn();
}

//=============================================================================
// Check for connected controllers
//=============================================================================
void Input::checkControllers()
{
	DWORD result;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		result = XInputGetState(i, &controllers[i].state);
		if (result == ERROR_SUCCESS)
			controllers[i].connected = true;
		else
			controllers[i].connected = false;
	}
}

//=============================================================================
// Read state of connected controllers
//=============================================================================
void Input::readControllers()
{
	DWORD result;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			result = XInputGetState(i, &controllers[i].state);
			if (result == ERROR_DEVICE_NOT_CONNECTED)    // if controller disconnected
				controllers[i].connected = false;
		}
	}
}

//=============================================================================
// Vibrate connected controllers
//=============================================================================
void Input::vibrateControllers(float frameTime)
{
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			controllers[i].vibrateTimeLeft -= frameTime;
			if (controllers[i].vibrateTimeLeft < 0)
			{
				controllers[i].vibrateTimeLeft = 0;
				controllers[i].vibration.wLeftMotorSpeed = 0;
			}
			controllers[i].vibrateTimeRight -= frameTime;
			if (controllers[i].vibrateTimeRight < 0)
			{
				controllers[i].vibrateTimeRight = 0;
				controllers[i].vibration.wRightMotorSpeed = 0;
			}
			XInputSetState(i, &controllers[i].vibration);
		}
	}
}
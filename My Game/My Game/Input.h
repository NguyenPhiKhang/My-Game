#ifndef _INPUT_H	// Prevent multiple definitions if this
#define _INPUT_H	// file is included in more than one place

class Input;

#include <Windows.h>
#include <string>
#include <XInput.h>
#include "constants.h"
#include "debug.h"

namespace inputNS
{
	const int KEYS_ARRAY_LEN = 256;	// size of key arrays

	// what values for clear(), bit flag
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_TEXT = KEYS_DOWN + KEYS_PRESSED + TEXT_IN;
}
	
const DWORD MAX_CONTROLLERS = 4; // Maximum number of controllers supported by XInput

struct ControllerState
{
	XINPUT_STATE		state;
	XINPUT_VIBRATION	vibration;
	float				vibrateTimeLeft;    // mSec
	float				vibrateTimeRight;   // mSec
	bool				connected;
};

class Input
{
private:
	bool keysDown[inputNS::KEYS_ARRAY_LEN];			// true if specified key is down
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];		// true if specified key was pressed
	std::string textIn;								// user entered text
	char charIn;									// last character entered
	bool newLine;									// true on start of new line
	ControllerState controllers[MAX_CONTROLLERS];	// state of controllers
	
public:
	// Constructor
	Input();

	// Destructor
	virtual ~Input();

	// initialize input
	void initialize(HWND);

	// Save key down state
	void keyDown(WPARAM);

	// Save key up state
	void keyUp(WPARAM);

	// Save the char just entered in textIn string
	void keyIn(WPARAM);

	// Returns true if the specified VIRTUAL KEY is down, otherwise false.
	bool isKeyDown(UCHAR vkey) const;

	// Return true if the specified VIRTUAL KEY has been pressed in the most recent frame.
	// Key presses are erased at the end of each frame.
	bool wasKeyPressed(UCHAR vkey) const;

	// Return true if any key was pressed in the most recent frame.
	// Key presses are erased at the end of each frame.
	bool anyKeyPressed() const;

	// Clear the specified key press
	void clearKeyPress(UCHAR vkey);

	// Clear specified input buffers where what is any combination of
	// KEYS_DOWN, KEYS_PRESSED, MOUSE, TEXT_IN or KEYS_MOUSE_TEXT.
	// Use OR '|' operator to combine parmeters.
	void clear(UCHAR what);

	// Clears key, mouse and text input data
	void clearAll() { clear(inputNS::KEYS_TEXT); }

	// Clear text input buffer
	void clearTextIn() { textIn.clear(); }

	// Return text input as a string
	std::string getTextIn() { return textIn; }

	// Return last character entered
	char getCharIn() { return charIn; }

	// Update connection status of game controllers.
	void checkControllers();

	// Save input from connected game controllers.
	void readControllers();

	// Return state of specified game controller.
	const ControllerState* getControllerState(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return &controllers[n];
	}

	// Vibrates the connected controllers for the desired time.
	void vibrateControllers(float frameTime);
};

#endif
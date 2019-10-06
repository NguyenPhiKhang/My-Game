#ifndef _INPUT_H	// Prevent multiple definitions if this
#define _INPUT_H	// file is included in more than one place

class Input;

#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <XInput.h>
#include "constants.h"
#include "debug.h"

// for high-definition mouse
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif
//--------------------------

namespace inputNS
{
	const int KEYS_ARRAY_LEN = 256;	// size of key arrays

	// what values for clear(), bit flag
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
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
	int  mouseX, mouseY;                        // mouse screen coordinates
	int  mouseRawX, mouseRawY;                  // high-definition mouse data
	RAWINPUTDEVICE Rid[1];                      // for high-definition mouse
	bool mouseCaptured;                         // true if mouse captured
	bool mouseLButton;                          // true if left mouse button down
	bool mouseMButton;                          // true if middle mouse button down
	bool mouseRButton;                          // true if right mouse button down
	bool mouseX1Button;                         // true if X1 mouse button down
	bool mouseX2Button;                         // true if X2 mouse button down
	ControllerState controllers[MAX_CONTROLLERS];	// state of controllers
	
public:
	// Constructor
	Input();

	// Destructor
	virtual ~Input();

	// initialize input
	void initialize(HWND, bool);

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

	// Reads mouse screen position into mouseX, mouseY
	void mouseIn(LPARAM);

	// Reads raw mouse data into mouseRawX, mouseRawY
	// This routine is compatible with a high-definition mouse
	void mouseRawIn(LPARAM);

	// Save state of mouse button
	void setMouseLButton(bool b) { mouseLButton = b; }

	// Save state of mouse button
	void setMouseMButton(bool b) { mouseMButton = b; }

	// Save state of mouse button
	void setMouseRButton(bool b) { mouseRButton = b; }

	// Save state of mouse button
	void setMouseXButton(WPARAM wParam) {
		mouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
		mouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
	}
	// Return mouse X position
	int  getMouseX()        const { return mouseX; }

	// Return mouse Y position
	int  getMouseY()        const { return mouseY; }

	// Return raw mouse X movement. Left is <0, Right is >0
	// Compatible with high-definition mouse.
	int  getMouseRawX()     const { return mouseRawX; }

	// Return raw mouse Y movement. Up is <0, Down is >0
	// Compatible with high-definition mouse.
	int  getMouseRawY()     const { return mouseRawY; }

	// Return state of left mouse button.
	bool getMouseLButton()  const { return mouseLButton; }

	// Return state of middle mouse button.
	bool getMouseMButton()  const { return mouseMButton; }

	// Return state of right mouse button.
	bool getMouseRButton()  const { return mouseRButton; }

	// Return state of X1 mouse button.
	bool getMouseX1Button() const { return mouseX1Button; }

	// Return state of X2 mouse button.
	bool getMouseX2Button() const { return mouseX2Button; }

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
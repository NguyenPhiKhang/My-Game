#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <d3dx9.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
//// Safely delete pointer referenced item
//#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
//// Safely release pointer referenced item
//#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
//// Safely delete pointer referenced array
//#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
//// Safely call onLostDevice
//#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
//// Safely call onResetDevice
//#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
//#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// graphic images
const char NEBULA_IMAGE[] = "Resources\\orion.jpg";  // photo source NASA/courtesy of nasaimages.org 
const char PLANET_IMAGE[] = "Resources\\planet.png"; // picture of planet
const char SHIP_IMAGE[] = "Resources\\ship.png"; //picture of spaceship
const char TEXTURE_IMAGE[] = "Resources\\textures1.png";	// game texture
const char BACKDROP_IMAGE[] = "Resources\\backdrop.png";
const char PADDLE_IMAGE[] = "Resources\\paddle.png";
const char FONT_IMAGE[] = "Resources\\CKfont.png";
const char SPACE_IMAGE[] = "Resources\\space.jpg";	// photo source NASA/courtesy of nasaimages.org
const char MENU_IMAGE[] = "Resources\\menu.png";
const char SQUARE_IMAGE[] = "Resources\\square.png";	//dealine
const char STARS_IMAGE[] = "Resources\\stars.png";
const char BALL_IMAGE[] = "Resources\\balls_color.png";
const char FRAME_GAME[] = "Resources\\frameGame.png";




// window
const char CLASS_NAME[] = "My Game";
const char GAME_TITLE[] = "My Game";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 640;				// width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
const D3DXVECTOR2 POS_WINDOW = D3DXVECTOR2(100, 100);		// x, y of game
const float TEXT_FRAME_HEIGHT = 40.0f;
const float TEXT_FRAME_WIDTH = 16.0f;

// game
const double PI = 3.14159265;
const float FRAME_RATE = 60.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE; // maximum time used in calculations
//const float GRAVITY = 6.67428e-11f;             // gravitational constant
const float MASS_PLANET = 1.0e14f;
const float MASS_SHIP = 5.0f;
const bool VSYNC = true;                    // true locks display to vertical sync rate
const float GRAVITY = 500.0f;				// acceleration of gravity pixels/ sec

//Direction
const int D_LEFT = 1;
const int D_RIGHT = 2;
const int D_UP = 3;
const int D_DOWN = 4;

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[] = "audio\\Win\\WavesExample1.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\SoundsExample1.xsb";

// audio cues
const char BEEP1[] = "./Audio/beep1.wave";
const char BEEP2[] = "beep2";
const char BEEP3[] = "beep3";
const char BEEP4[] = "beep4";
const char HIT[] = "hit";


// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY = VK_MENU;     // Alt key
const UCHAR ENTER_KEY = VK_RETURN;   // Enter key
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT; // Right arrow
const UCHAR SHIP_LEFT_KEY = VK_LEFT; // Left arrow
const UCHAR SHIP_UP_KEY = VK_UP; // Up arrow
const UCHAR SHIP_DOWN_KEY = VK_DOWN; // Down arrow
const UCHAR A_KEY = 0x41;
const UCHAR S_KEY = 0x53;
const UCHAR D_KEY = 0x44;
const UCHAR W_KEY = 0x57;

// weapon types
enum WEAPON{TORPEDO, SHIP, PLANET};

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = NULL;
	}
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
	if (ptr)
		ptr->onLostDevice();
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
	if (ptr)
		ptr->onResetDevice();
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

#endif


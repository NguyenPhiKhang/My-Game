#ifndef _GRAPHICS_H             // Prevent multiple definitions if this 
#define _GRAPHICS_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "debug.h"


// Color defines
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

namespace graphicsNS
{
	// Some common colors
	// ARGB numbers range from 0 through 255
	// A = Alpha channel (transparency where 255 is opaque)
	// R = Red, G = Green, B = Blue
	const COLOR_ARGB ORANGE = D3DCOLOR_ARGB(255, 255, 165, 0);
	const COLOR_ARGB BROWN = D3DCOLOR_ARGB(255, 139, 69, 19);
	const COLOR_ARGB LTGRAY = D3DCOLOR_ARGB(255, 192, 192, 192);
	const COLOR_ARGB GRAY = D3DCOLOR_ARGB(255, 128, 128, 128);
	const COLOR_ARGB OLIVE = D3DCOLOR_ARGB(255, 128, 128, 0);
	const COLOR_ARGB PURPLE = D3DCOLOR_ARGB(255, 128, 0, 128);
	const COLOR_ARGB MAROON = D3DCOLOR_ARGB(255, 128, 0, 0);
	const COLOR_ARGB TEAL = D3DCOLOR_ARGB(255, 0, 128, 128);
	const COLOR_ARGB GREEN = D3DCOLOR_ARGB(255, 0, 128, 0);
	const COLOR_ARGB NAVY = D3DCOLOR_ARGB(255, 0, 0, 128);
	const COLOR_ARGB WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
	const COLOR_ARGB YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0);
	const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255, 255, 0, 255);
	const COLOR_ARGB RED = D3DCOLOR_ARGB(255, 255, 0, 0);
	const COLOR_ARGB CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const COLOR_ARGB LIME = D3DCOLOR_ARGB(255, 0, 255, 0);
	const COLOR_ARGB BLUE = D3DCOLOR_ARGB(255, 0, 0, 255);
	const COLOR_ARGB BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);
	const COLOR_ARGB FILTER = D3DCOLOR_ARGB(0, 0, 0, 0);  // use to specify drawing with colorFilter
	const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255);  // AND with color to get 25% alpha
	const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128, 255, 255, 255);  // AND with color to get 50% alpha
	const COLOR_ARGB BACK_COLOR = NAVY;                         // background color of game

	enum DISPLAY_MODE { TOGGLE, FULLSCREEN, WINDOW };
}

// SpriteData: The properties required by Graphics::drawSprite to draw a sprite
struct SpriteData
{
	int         width;      // width of sprite in pixels
	int         height;     // height of sprite in pixels
	float       x;          // screen location (top left corner of sprite)
	float       y;
	float       scale;      // <1 smaller, >1 bigger
	float       angle;      // rotation angle in radians
	RECT        rect;       // used to select an image from a larger texture
	LPDIRECT3DTEXTURE9  texture;    // pointer to texture
	bool        flipHorizontal; // true to flip sprite horizontally (mirror)
	bool        flipVertical;   // true to flip sprite vertically
	int			direction;		
};

class Graphics
{
private:
	// DirectX pointers and stuff
	LPDIRECT3D9       d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	
	LPD3DXSPRITE   spriteHandler;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

	// other variables
	HRESULT     result;         // standard Windows return codes
	HWND        hwnd;
	bool        fullscreen;
	int         width;
	int         height;
	COLOR_ARGB  backColor;      // background color

	// (For internal engine use only. No user serviceable parts inside.)
	// Initialize D3D presentation parameters
	void    initD3Dpp();

public:
	// Constructor
	Graphics();

	// Destructor
	virtual ~Graphics();

	// Releases direct3d and device3d.
	void    releaseAll();

	// Initialize DirectX graphics
	// Throws GameError on error
	// Pre: hw = handle to window
	//      width = width in pixels
	//      height = height in pixels
	//      fullscreen = true for full screen, false for window
	void    initialize(HWND hw, int width, int height, bool fullscreen);

	// Load the texture into default D3D memory (normal texture use)
	// For internal engine use only. Use the TextureManager class to load game textures.
	// Pre: filename = name of texture file.
	//      transcolor = transparent color
	// Post: width and height = size of texture
	//       texture points to texture
	HRESULT loadTexture(const char* filename, COLOR_ARGB transcolor, UINT& width, UINT& height, LPDIRECT3DTEXTURE9& texture);

	// Display the offscreen backbuffer to the screen.
	HRESULT showBackbuffer();

	// Checks the adapter to see if it is compatible with the BackBuffer height,
	// width and refresh rate specified in d3dpp. Fills in the pMode structure with
	// the format of the compatible mode, if found.
	// Pre: d3dpp is initialized.
	// Post: Returns true if compatible mode found and pMode structure is filled.
	//       Returns false if no compatible mode found.
	bool    isAdapterCompatible();

	// Draw the sprite described in SpriteData structure.
	// color is optional, it is applied as a filter, WHITE is default (no change).
	// Creates a sprite Begin/End pair.
	// Pre: spriteData.rect defines the portion of spriteData.texture to draw
	//      spriteData.rect.right must be right edge + 1
	//      spriteData.rect.bottom must be bottom edge + 1
	void    drawSprite(const SpriteData& spriteData,           // sprite to draw
		COLOR_ARGB color = graphicsNS::WHITE);      // default to white color filter (no change)

// Reset the graphics device.
	HRESULT reset();

	// Toggle, fullscreen or window display mode
	// Pre: All user created D3DPOOL_DEFAULT surfaces are freed.
	// Post: All user surfaces are recreated.
	void    changeDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

	// Return lenght of vector v.
	static float  Vector2Lenght(const D3DXVECTOR2* v) { return D3DXVec2Length(v); }

	// Return Dot product of vectors v1 and v2.
	static float  Vector2Dot(const D3DXVECTOR2* v1, const D3DXVECTOR2* v2) { return D3DXVec2Dot(v1, v2); }

	// Normalize vector v.
	static void   Vector2Normallize(D3DXVECTOR2* v) { D3DXVec2Normalize(v, v); }

	// Transform vector v with matrix m.
	static D3DXVECTOR2* Vector2Transform(D3DXVECTOR2* v, D3DXMATRIX* m) { return D3DXVec2TransformCoord(v, v, m); }

	// get functions
	// Return direct3d.
	LPDIRECT3D9   getD3D() { return d3d; }

	// Return device3d.
	LPDIRECT3DDEVICE9 get3Ddevice() { return d3ddev; }

	// Return sprite
	LPD3DXSPRITE  getSpriteHandler() { return spriteHandler; }

	// Return handle to device context (window).
	HDC     getDC() { return GetDC(hwnd); }

	// Test for lost device
	HRESULT getDeviceState();

	// Return fullscreen
	bool    getFullscreen() { return fullscreen; }

	// Set color used to clear screen
	void setBackColor(COLOR_ARGB c) { backColor = c; }

	//=============================================================================
	// Clear backbuffer and BeginScene()
	//=============================================================================
	HRESULT beginScene()
	{
		result = E_FAIL;
		if (d3d == NULL)
			return result;
		// clear backbuffer to backColor
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
		result = d3ddev->BeginScene();          // begin scene for drawing
		return result;
	}

	//=============================================================================
	// EndScene()
	//=============================================================================
	HRESULT endScene()
	{
		result = E_FAIL;
		if (d3ddev)
			result = d3ddev->EndScene();
		return result;
	}

	//=============================================================================
	// Sprite Begin
	//=============================================================================
	void spriteBegin()
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	}

	//=============================================================================
	// Sprite End
	//=============================================================================
	void spriteEnd()
	{
		spriteHandler->End();
	}
};

#endif



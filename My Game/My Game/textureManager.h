#ifndef _TEXTUREMANAGER_H       // Prevent multiple definitions if this 
#define _TEXTUREMANAGER_H       // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <string>
#include <fstream>
#include "graphics.h"
#include "constants.h"

class TextureManager
{
	// TextureManager properties
private:
	std::vector<UINT>       width;       // width of texture in pixels
	std::vector<UINT>       height;      // height of texture in pixels
	std::vector<LPDIRECT3DTEXTURE9> texture;     // pointer to texture
	std::vector<std::string> fileNames;			 // name of file
	Graphics* graphics;     // save pointer to graphics
	bool    initialized;    // true when successfully initialized
	HRESULT hr;             // standard return type

public:
	// Constructor
	TextureManager();

	// Destructor
	virtual ~TextureManager();

	// Returns a pointer to the texture n
	LPDIRECT3DTEXTURE9 getTexture(UINT n = 0) const { return (n >= texture.size()) ? NULL : texture[n]; }

	// Returns the texture width n
	UINT getWidth(UINT n = 0) const { return (n >= texture.size()) ? 0 : width[0]; }

	// Return the texture height
	UINT getHeight(UINT n = 0) const { return (n >= texture.size()) ? 0 : height[0]; }

	// Initialize the textureManager
	// Pre: *g points to Graphics object
	//      file is name of texture file to load.
	//      If file extension is .txt it is assumed to
	//      contain a list of texture file names, one name
	//      per row.
	// Post: The texture file(s) are loaded
	virtual bool initialize(Graphics* g, std::string file);

	// Release resources
	virtual void onLostDevice();

	// Restore resourses
	virtual void onResetDevice();	

	// safely release texture
	void safeReleaseTexture(LPDIRECT3DTEXTURE9& ptr)
	{
		if (ptr)
		{
			ptr->Release();
			ptr = NULL;
		}
	}
};

#endif

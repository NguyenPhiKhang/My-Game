#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
	// game items
	TextureManager nebulaTexture;   // nebula texture
	TextureManager planetTexture;   // planet texture
	TextureManager shipTexture;		// ship texture
	Image   planet;                 // planet image
	Image   nebula;                 // nebula image
	Image ship;

public:
	// Constructor
	Spacewar();

	// Destructor
	virtual ~Spacewar();

	// Initialize the game
	void initialize(HWND hwnd);
	void update(float frametime);      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

#endif

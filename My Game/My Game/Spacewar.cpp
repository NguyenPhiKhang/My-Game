#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	// nebula texture
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		DebugOut("Error initializing nebula texture");

	// planet texture
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		DebugOut("Error initializing planet texture");

	// ship texture
	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		DebugOut("Error initializing ship texture");

	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		DebugOut("Error initializing nebula");

	// planet
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		DebugOut("Error initializing planet");
	// place planet in center of screen
	planet.setX(GAME_WIDTH * 0.5f - planet.getWidth() * 0.5f);
	planet.setY(GAME_HEIGHT * 0.5f - planet.getHeight() * 0.5f);

	// ship
	if (!ship.initialize(graphics, SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &shipTexture))
		DebugOut("Error initializing ship");
	//ship.setX(GAME_WIDTH / 4);
	ship.setY(GAME_HEIGHT / 4);
	ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	ship.setCurrentFrame(SHIP_START_FRAME);
	ship.setDegrees(45.0f);
	ship.setScale(SHIP_SCALE);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update(float frametime)
{
	ship.update(frametime);
	ship.setDegrees(ship.getDegrees() + frameTime * ROTATION_RATE);
	ship.setScale(ship.getScale() - frameTime * SCALE_RATE);
	ship.setX(ship.getX() + frameTime * SHIP_SPEED);
	if (ship.getX() > GAME_WIDTH)
	{
		ship.setX(ship.getX() - GAME_WIDTH);
		ship.setScale(SHIP_SCALE);
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	nebula.draw();                          // add the orion nebula to the scene
	planet.draw();                          // add the planet to the scene
	ship.draw();							// add the ship to thte scene

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();

	Game::resetAll();
	return;
}

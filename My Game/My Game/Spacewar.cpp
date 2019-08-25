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
	ship.setDegrees(0.0f);
	ship.setScale(SHIP_SCALE);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update(float frametime)
{
	if (input->isKeyDown(SHIP_RIGHT_KEY))            // if move right
	{
		if (ship.getDirection() != D_RIGHT) {
			ship.flipHorizontal(false);
			//ship.setDegrees(360.0f);
			ship.setDirection(D_RIGHT);
		}
		ship.setX(ship.getX() + frameTime * SHIP_SPEED);
		if (ship.getX() > GAME_WIDTH)               // if off screen right
			ship.setX((float)-ship.getWidth());     // position off screen left
		DebugOut("[GET X] = %.2f\n", ship.getX());
	}
	if (input->isKeyDown(SHIP_LEFT_KEY))             // if move left
	{
		if (ship.getDirection() != D_LEFT)
		{
			ship.flipHorizontal(true);
			//ship.setDegrees(180.0f);
			ship.setDirection(D_LEFT);
		}
		ship.setX(ship.getX() - frameTime * SHIP_SPEED);
		if (ship.getX() < -ship.getWidth())         // if off screen left
			ship.setX((float)GAME_WIDTH);           // position off screen right
		DebugOut("[GET X] = %.2f\n", ship.getX());
	}
	if (input->isKeyDown(SHIP_UP_KEY))               // if move up
	{
		ship.setY(ship.getY() - frameTime * SHIP_SPEED);
		if (ship.getY() < -ship.getHeight())        // if off screen top
			ship.setY((float)GAME_HEIGHT);          // position off screen bottom
	}
	if (input->isKeyDown(SHIP_DOWN_KEY))             // if move down
	{
		ship.setY(ship.getY() + frameTime * SHIP_SPEED);
		if (ship.getY() > GAME_HEIGHT)              // if off screen bottom
			ship.setY((float)-ship.getHeight());    // position off screen top
	}

	ship.update(frameTime);
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
	shipTexture.onLostDevice();

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
	shipTexture.onResetDevice();

	Game::resetAll();
	return;
}

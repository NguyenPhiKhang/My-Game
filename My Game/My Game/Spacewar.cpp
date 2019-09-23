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

	//// planet texture
	//if (!planetTexture.initialize(graphics, PLANET_IMAGE))
	//	DebugOut("Error initializing planet texture");

	//// ship texture
	//if (!shipTexture.initialize(graphics, SHIP_IMAGE))
	//	DebugOut("Error initializing ship texture");

	// game texture
	if (!gameTexture.initialize(graphics, TEXTURE_IMAGE))
		DebugOut("Error initializing game texture");

	if(!squareTexture.initialize(graphics, SQUARE_IMAGE))
		DebugOut("Error initializing square texture");

	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		DebugOut("Error initializing nebula");

	// planet
	if (!planet.initialize(this, planetNS::WIDTH, planetNS::HEIGHT, planetNS::TEXTURE_COLS, &gameTexture))
		DebugOut("Error initializing planet");
	// place planet in center of screen
	/*planet.setX(GAME_WIDTH * 0.5f - planet.getWidth() * 0.5f);
	planet.setY(GAME_HEIGHT * 0.5f - planet.getHeight() * 0.5f);*/

	if(!square1.initialize(this, squareNS::WIDTH, squareNS::HEIGHT, squareNS::TEXTURE_COLS, &squareTexture))
		DebugOut("Error initializing square");
	square1.setFrames(squareNS::SQUARE_START_FRAME, squareNS::SQUARE_END_FRAME);
	square1.setCurrentFrame(squareNS::SQUARE_START_FRAME);
	square1.setVelocity(D3DXVECTOR2(squareNS::SPEED, 0.0f));
	//square1.setScale(2);
	//square1.setDegrees(30);

	if (!square2.initialize(this, squareNS::WIDTH, squareNS::HEIGHT, squareNS::TEXTURE_COLS, &squareTexture))
		DebugOut("Error initializing square");
	square2.setFrames(squareNS::SQUARE_START_FRAME, squareNS::SQUARE_END_FRAME);
	square2.setCurrentFrame(squareNS::SQUARE_START_FRAME);
	square2.setVelocity(D3DXVECTOR2(squareNS::SPEED, squareNS::SPEED));
	square2.setY(GAME_HEIGHT / 2);
	square2.setMoveType(squareNS::SIN_SHAPE);
	square2.setVelocity(D3DXVECTOR2(squareNS::SPEED / 4, squareNS::SPEED));
	square2.setScale(2.0f);

	// ship
	if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTexture))
		DebugOut("Error initializing ship");
	ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
	ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
	ship1.setX(GAME_WIDTH / 4);
	ship1.setY(GAME_HEIGHT / 4);
	ship1.setVelocity(D3DXVECTOR2(shipNS::SPEED, -shipNS::SPEED));

	// ship2
	if (!ship2.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTexture))
		DebugOut("Error initializing ship2");
	ship2.setFrames(shipNS::SHIP2_START_FRAME, shipNS::SHIP2_END_FRAME);
	ship2.setCurrentFrame(shipNS::SHIP2_START_FRAME);
	ship2.setX(GAME_WIDTH - GAME_WIDTH/4);
	ship2.setY(GAME_HEIGHT / 4);
	ship2.setVelocity(D3DXVECTOR2(-shipNS::SPEED, -shipNS::SPEED));

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update(float frametime)
{
	//// input keyboard
	//if (input->isKeyDown(SHIP_RIGHT_KEY))            // if move right
	//{
	//	if (ship.getDirection() != D_RIGHT) {
	//		ship.flipHorizontal(false);
	//		//ship.setDegrees(360.0f);
	//		ship.setDirection(D_RIGHT);
	//	}
	//	ship.setX(ship.getX() + frameTime * SHIP_SPEED);
	//	if (ship.getX() > GAME_WIDTH)               // if off screen right
	//		ship.setX((float)-ship.getWidth());     // position off screen left
	//	DebugOut("[GET X] = %.2f\n", ship.getX());
	//}
	//if (input->isKeyDown(SHIP_LEFT_KEY))             // if move left
	//{
	//	if (ship.getDirection() != D_LEFT)
	//	{
	//		ship.flipHorizontal(true);
	//		//ship.setDegrees(180.0f);
	//		ship.setDirection(D_LEFT);
	//	}
	//	ship.setX(ship.getX() - frameTime * SHIP_SPEED);
	//	if (ship.getX() < -ship.getWidth())         // if off screen left
	//		ship.setX((float)GAME_WIDTH);           // position off screen right
	//	DebugOut("[GET X] = %.2f\n", ship.getX());
	//}
	//if (input->isKeyDown(SHIP_UP_KEY))               // if move up
	//{
	//	ship.setY(ship.getY() - frameTime * SHIP_SPEED);
	//	if (ship.getY() < -ship.getHeight())        // if off screen top
	//		ship.setY((float)GAME_HEIGHT);          // position off screen bottom
	//}
	//if (input->isKeyDown(SHIP_DOWN_KEY))             // if move down
	//{
	//	ship.setY(ship.getY() + frameTime * SHIP_SPEED);
	//	if (ship.getY() > GAME_HEIGHT)              // if off screen bottom
	//		ship.setY((float)-ship.getHeight());    // position off screen top
	//}

	planet.update(frameTime);
	ship1.update(frameTime);
	ship2.update(frameTime);
	square1.update(frameTime);
	square2.update(frameTime);
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
{
	D3DXVECTOR2 collisionVector;
	// if collision between ship and planet
	if (ship1.collidesWith(planet, collisionVector))
	{
		// bounce off planet
		ship1.bounce(collisionVector, planet);
		ship1.damage(PLANET);
	}
	if (ship2.collidesWith(planet, collisionVector))
	{
		// bounce off planet
		ship2.bounce(collisionVector, planet);
		ship2.damage(PLANET);
	}
	// if collision between ships
	if (ship1.collidesWith(ship2, collisionVector))
	{
		// bounce off ship
		ship1.bounce(collisionVector, ship2);
		ship1.damage(SHIP);
		// change the direction of the collisionVector for ship2
		ship2.bounce(collisionVector * -1, ship1);
		ship2.damage(SHIP);
	}
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	//nebula.draw();                          // add the orion nebula to the scene
	//planet.draw();                          // add the planet to the scene
	//ship1.draw();							// add the ship to the scene
	//ship2.draw();
	square1.draw();
	square2.draw();

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	//planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();
	//shipTexture.onLostDevice();
	gameTexture.onLostDevice();
	squareTexture.onLostDevice();

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
	/*planetTexture.onResetDevice();
	shipTexture.onResetDevice();*/
	gameTexture.onResetDevice();
	squareTexture.onResetDevice();

	Game::resetAll();
	return;
}

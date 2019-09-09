#include "Ship.h"


//=============================================================================
// default constructor
//=============================================================================
Ship::Ship() : Entity()
{
	spriteData.width = shipNS::WIDTH;           // size of Ship1
	spriteData.height = shipNS::HEIGHT;
	spriteData.x = shipNS::X;                   // location on screen
	spriteData.y = shipNS::Y;
	spriteData.rect.bottom = shipNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = shipNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = shipNS::SHIP_ANIMATION_DELAY;
	//startFrame = shipNS::SHIP_START_FRAME;      // first frame of ship animation
	//endFrame = shipNS::SHIP_END_FRAME;      // last frame of ship animation
	//currentFrame = startFrame;
	radius = shipNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	shieldOn = false;
	mass = shipNS::MASS;
}

//=============================================================================
// draw the ship
//=============================================================================
void Ship::draw()
{
	Image::draw();	// drawship
	if (shieldOn)
		// draw shield using colorFilter 50% alpha
		shield.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Ship::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM)
{
	shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	shield.setFrames(shipNS::SHIELD_START_FRAME, shipNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(shipNS::SHIELD_START_FRAME);
	shield.setFrameDelay(shipNS::SHIELD_ANIMATION_DELAY);
	shield.setLoop(false);		// do not loop animation
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Ship::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.angle += frameTime * shipNS::ROTATION_RATE;	// rotated the ship
	spriteData.x += frameTime * velocity.x;	// move ship along X
	spriteData.y += frameTime * velocity.y;	// move ship along Y

	// Bounce off walls
	// If hit right screen edge
	if (spriteData.x > GAME_WIDTH - shipNS::WIDTH * getScale())
	{
		// position at right screen edge
		spriteData.x = GAME_WIDTH - shipNS::WIDTH * getScale();
		velocity.x = -velocity.x;								// reverse X direction
	}
	else if (spriteData.x < 0)                  // else if hit left screen edge
	{
		spriteData.x = 0;                       // position at left screen edge
		velocity.x = -velocity.x;               // reverse X direction
	}
	// if hit bottom screen edge
	if (spriteData.y > GAME_HEIGHT - shipNS::HEIGHT * getScale())
	{
		// position at bottom screen edge
		spriteData.y = GAME_HEIGHT - shipNS::HEIGHT * getScale();
		velocity.y = -velocity.y;               // reverse Y direction
	}
	else if (spriteData.y < 0)                  // else if hit top screen edge
	{
		spriteData.y = 0;                       // position at top screen edge
		velocity.y = -velocity.y;               // reverse Y direction
	}
	if (shieldOn)
	{
		shield.update(frameTime);
		if (shield.getAnimationComplete())
		{
			shieldOn = false;
			shield.setAnimationComplete(false);
		}
	}
}

//=============================================================================
// damage
//=============================================================================
void Ship::damage(WEAPON)
{
	shieldOn = true;
}

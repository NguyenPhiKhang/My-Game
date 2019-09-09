#include "Planet.h"

//=============================================================================
// default constructor
//=============================================================================
Planet::Planet() : Entity()
{
	spriteData.x = planetNS::X;			// location on screen
	spriteData.y = planetNS::Y;
	radius = planetNS::COLLISION_RADIUS;
	mass = planetNS::MASS;
	startFrame = planetNS::START_FRAME;	// first frame of ship animation
	endFrame = planetNS::END_FRAME;		// end frame of ship animation
	setCurrentFrame(startFrame);
}

void Planet::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.angle += frameTime * planetNS::ROTATION_RATE;
}

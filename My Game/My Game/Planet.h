#ifndef _PLANET_H               // Prevent multiple definitions if this 
#define _PLANET_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace planetNS
{
	const int	WIDTH  = 128;					// image width
	const int	HEIGHT = 128;					// image height
	const int	COLLISION_RADIUS = 120 / 2;		// for circular collision
	const int	X = GAME_WIDTH / 2 - WIDTH / 2;	// location on screen
	const int	Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float MASS = 1.0e14f;					// mass
	const int TEXTURE_COLS = 2;					// Texture has 1 column
	const int START_FRAME = 1;					// starts at frame 0
	const int END_FRAME = 1;					// no animation
	const float ROTATION_RATE = (float)PI / 12;
}

class Planet : public Entity // inherits from entity class
{
public :
	// constructor
	Planet();

	// rotated planet
	void update(float frameTime);
};

#endif
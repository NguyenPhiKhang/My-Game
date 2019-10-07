#ifndef _BALL_H
#define _BALL_H

#include <time.h>
#include "constants.h"
#include "Entity.h"

namespace ballNS {
	const int WIDTH = 16;
	const int HEIGHT = 16;
	const float SPEED = 180.0f;
	const int BALL_START_FRAME = 0;
	const int BALL_END_FRAME = 4;
	const float X = GAME_WIDTH / 2 - WIDTH / 2;
	const float Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float BALL_ANIMATION_DELAY = 0.5f;
	const int TEXTURE_COLS = 5;
}

class Ball: public Entity
{
private:
	bool outsideScopeLeft;
	bool outsideScopeRight;
public:
	Ball();
	void update(float frameTime, bool checkPos= false);
	bool getOutsideScopeLeft() { return outsideScopeLeft; }
	bool getOutsideScopeRight() { return outsideScopeRight; }
};

#endif
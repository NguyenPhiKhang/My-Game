#ifndef _PADDLE_H
#define _PADDLE_H

#include "constants.h"
#include "Entity.h"

constexpr auto PADDLE_STATE_IDLE = 0;
constexpr auto PADDLE_STATE_MOVE_UP = 100;
constexpr auto PADDLE_STATE_MOVE_DOWN = 200;


namespace paddleNS {
	const int WIDTH = 16;
	const int HEIGHT = 64;
	const float X = GAME_WIDTH / 2 - WIDTH / 2;	// location on screen
	const float Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int PADDLE_START_FRAME = 1;
	const int PADDLE_END_FRAME = 1;
	const float SPEED = 200.0f;
}


class Paddle: public Entity
{
public:
	Paddle();
	void update(float frameTime, bool checkPos = false);
	void setState(int state);
};

#endif
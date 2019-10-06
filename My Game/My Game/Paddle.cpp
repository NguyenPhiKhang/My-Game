#include "Paddle.h"

Paddle::Paddle()
{
	spriteData.width = paddleNS::WIDTH;
	spriteData.height = paddleNS::HEIGHT;
	edge = {-paddleNS::WIDTH/2,-paddleNS::HEIGHT / 2,paddleNS::WIDTH / 2, paddleNS::HEIGHT / 2 };
}

void Paddle::update(float frameTime, bool checkPos)
{
	Entity::update(frameTime, checkPos);
	if (spriteData.y < 0)
		spriteData.y = 0;
	if (spriteData.y > GAME_HEIGHT - paddleNS::HEIGHT)
		spriteData.y = GAME_HEIGHT - paddleNS::HEIGHT;
}

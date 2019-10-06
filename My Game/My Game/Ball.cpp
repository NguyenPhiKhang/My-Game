#include "Ball.h"

Ball::Ball()
{
	spriteData.width = ballNS::WIDTH;
	spriteData.height = ballNS::HEIGHT;
	edge = { -ballNS::WIDTH / 2,-ballNS::HEIGHT / 2,ballNS::WIDTH / 2, ballNS::HEIGHT / 2 };
}

void Ball::update(float frameTime, bool checkPos)
{
	Entity::update(frameTime, checkPos);
	spriteData.x += velocity.x * frameTime;
	spriteData.y += velocity.y * frameTime;
	if (spriteData.x > GAME_WIDTH - ballNS::WIDTH||spriteData.x <0)
	{
		Sleep(500);
		spriteData.x = GAME_WIDTH/2 - ballNS::WIDTH/2;
		spriteData.y = GAME_HEIGHT / 2 - ballNS::HEIGHT / 2;
		//velocity.x *= -1;
		int rd = -5 + rand() % 9;
		if (rd >= 0)
			velocity.x *= -1;
		else velocity.y *= -1;
	}
	/*if (spriteData.x < 0)
	{
		spriteData.x = 0;
		velocity.x *= -1;
	}*/
	if (spriteData.y > GAME_HEIGHT - ballNS::HEIGHT)
	{
		spriteData.y = GAME_HEIGHT - ballNS::HEIGHT;
		velocity.y *= -1;
	}
	if (spriteData.y < 0)
	{
		spriteData.y = 0;
		velocity.y *= -1;
	}
}

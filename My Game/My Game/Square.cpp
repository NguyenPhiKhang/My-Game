#include "Square.h"

Square::Square():Entity()
{
	spriteData.x = squareNS::X;
	spriteData.y = squareNS::Y;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	moveType = squareNS::AROUND;
	totalTime = 0.0f;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Square::update(float frameTime)
{
	Entity::update(frameTime);

	if (moveType == squareNS::AROUND)
	{
		spriteData.x += velocity.x * frameTime;
		spriteData.y += velocity.y * frameTime;

		if (spriteData.x > GAME_WIDTH - squareNS::WIDTH*getScale())
		{
			spriteData.x = GAME_WIDTH - squareNS::WIDTH*getScale();
			setVelocity(D3DXVECTOR2(0.0f, squareNS::SPEED));
		}
		if (spriteData.y > GAME_HEIGHT - squareNS::HEIGHT*getScale())
		{
			spriteData.y = GAME_HEIGHT - squareNS::HEIGHT*getScale();
			setVelocity(D3DXVECTOR2(-squareNS::SPEED, 0.0f));
		}
		if (spriteData.x < 0)
		{
			spriteData.x = 0;
			setVelocity(D3DXVECTOR2(0.0f, -squareNS::SPEED));
		}
		if (spriteData.y < 0)
		{
			spriteData.y = 0;
			setVelocity(D3DXVECTOR2(squareNS::SPEED, 0.0f));
		}
	}
	else
	{
		totalTime += frameTime;
		spriteData.x += velocity.x * frameTime;
		spriteData.y = velocity.y * cos(((float)PI / 2) * totalTime + (float)PI / 2) + GAME_HEIGHT / 2;
		spriteData.angle += frameTime * squareNS::ROTATION_RATE;

		if (spriteData.x > GAME_WIDTH - squareNS::WIDTH*getScale() || spriteData.x < 0)
			spriteData.x = 0.0f;
	}
}

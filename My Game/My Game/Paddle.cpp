#include "Paddle.h"

Paddle::Paddle()
{
	spriteData.width = paddleNS::WIDTH;
	spriteData.height = paddleNS::HEIGHT;
	edge = {-paddleNS::WIDTH/2,-paddleNS::HEIGHT / 2,paddleNS::WIDTH / 2, paddleNS::HEIGHT / 2 };
	velocity = D3DXVECTOR2(0.0f, 0.0f);
}

void Paddle::update(float frameTime, bool checkPos)
{
	Entity::update(frameTime, checkPos);
	if (spriteData.y < TEXT_FRAME_HEIGHT)
		spriteData.y = TEXT_FRAME_HEIGHT;
	if (spriteData.y > GAME_HEIGHT - paddleNS::HEIGHT)
		spriteData.y = GAME_HEIGHT - paddleNS::HEIGHT;
}

void Paddle::setState(int state)
{
	Image::setState(state);
	switch (state)
	{
	case PADDLE_STATE_MOVE_DOWN:
		velocity.y = paddleNS::SPEED;
		break;
	case PADDLE_STATE_MOVE_UP:
		velocity.y = -paddleNS::SPEED;
		break;
	case PADDLE_STATE_IDLE:
		velocity.y = 0;
		break;
	}
}

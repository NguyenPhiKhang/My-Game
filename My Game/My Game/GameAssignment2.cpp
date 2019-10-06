#include "GameAssignment2.h"

void GameAssignment2::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	if (!spaceTexture.initialize(graphics, STARS_IMAGE))
		DebugOut("Error initializing space texture");

	if(!paddleTexture.initialize(graphics, PADDLE_IMAGE))
		DebugOut("Error initializing paddle texture");

	if(!ballTexture.initialize(graphics, BALL_IMAGE))
		DebugOut("Error initializing ball texture");

	if(!space.initialize(graphics, 0,0,0,&spaceTexture))
		DebugOut("Error initializing space");
	
	if (!paddle1.initialize(this, paddleNS::WIDTH, paddleNS::HEIGHT,0, &paddleTexture))
		DebugOut("Error initalizing paddle 1");
	paddle1.addAnim(RECT{92,51,92+paddleNS::WIDTH,51+paddleNS::HEIGHT});
	paddle1.setFrames(paddleNS::PADDLE_START_FRAME, paddleNS::PADDLE_END_FRAME);
	paddle1.setCurrentFrame(paddleNS::PADDLE_START_FRAME, paddle1.getAnim());
	paddle1.setX(0.0f);
	paddle1.setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT/2);
	//paddle1.setDegrees(90);
	paddle1.setCollisionType(entityNS::BOX);

	if (!paddle2.initialize(this, paddleNS::WIDTH, paddleNS::HEIGHT, 0, &paddleTexture))
		DebugOut("Error initalizing paddle 2");
	paddle2.addAnim(RECT{ 112, 51, 112 + paddleNS::WIDTH-1, 51 + paddleNS::HEIGHT-1 });
	paddle2.setFrames(paddleNS::PADDLE_START_FRAME, paddleNS::PADDLE_END_FRAME);
	paddle2.setCurrentFrame(paddleNS::PADDLE_START_FRAME, paddle2.getAnim());
	paddle2.setX(GAME_WIDTH - paddleNS::WIDTH);
	paddle2.setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT/2);
	paddle2.flipHorizontal(true);
	paddle2.setCollisionType(entityNS::BOX);

	if (!ball.initialize(this, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &ballTexture))
		DebugOut("Error initializing ball");
	ball.setFrames(ballNS::BALL_START_FRAME, ballNS::BALL_END_FRAME);
	ball.setCurrentFrame(ballNS::BALL_START_FRAME);
	ball.setFrameDelay(ballNS::BALL_ANIMATION_DELAY);
	ball.setX(ballNS::X);
	ball.setY(ballNS::Y);
	ball.setVelocity(D3DXVECTOR2(ballNS::SPEED*1.5, ballNS::SPEED));
	ball.setCollisionType(entityNS::BOX);

	return;
}

void GameAssignment2::update(float frameTime)
{
	if (input->isKeyDown(W_KEY))
		paddle1.setY(paddle1.getY() - frameTime * paddleNS::SPEED);
	if (input->isKeyDown(S_KEY))
		paddle1.setY(paddle1.getY() + frameTime * paddleNS::SPEED);
	paddle2.setY((float)input->getMouseY());
	paddle1.update(frameTime, true);
	paddle2.update(frameTime, true);
	ball.update(frameTime);
}

void GameAssignment2::ai()
{
}

void GameAssignment2::collisions()
{
	D3DXVECTOR2 collisionVector;
	if (ball.collidesWith(paddle1, collisionVector)|| ball.collidesWith(paddle2, collisionVector))
	{
		ball.setVelocityX(-ball.getVelocity().x);
	}
}

void GameAssignment2::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	//paddle1.setSpriteDataRect(paddle1.getAnim());
	space.draw();
	paddle1.draw();
	DebugOut("x : %.2f\n", paddle1.getX());
	paddle2.draw();
	ball.draw();

	graphics->spriteEnd();                  // end drawing sprites
}

void GameAssignment2::releaseAll()
{
	ballTexture.onLostDevice();
	spaceTexture.onLostDevice();
	paddleTexture.onLostDevice();
	Game::releaseAll();
	return;
}

void GameAssignment2::resetAll()
{
	ballTexture.onResetDevice();
	spaceTexture.onResetDevice();
	paddleTexture.onResetDevice();
	Game::resetAll();
	return;
}


#include "GameAssignment2.h"

GameAssignment2::GameAssignment2()
{
	spaceTexture = new TextureManager();
	ballTexture = new TextureManager();
	paddleTexture = new TextureManager();
	ball = new Ball();
	paddle1 = new Paddle();
	paddle2 = new Paddle();
	space = new Image();
	fontCK = new Text();

	scorePaddle1 = 0;
	scorePaddle2 = 0;
}

GameAssignment2::~GameAssignment2()
{
	releaseAll();
	safeDelete(fontCK);
}

void GameAssignment2::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	if (!spaceTexture->initialize(graphics, FRAME_GAME))
		DebugOut("Error initializing space texture");

	if (!paddleTexture->initialize(graphics, PADDLE_IMAGE))
		DebugOut("Error initializing paddle texture");

	if (!ballTexture->initialize(graphics, BALL_IMAGE))
		DebugOut("Error initializing ball texture");

	if (!space->initialize(graphics, GAME_WIDTH - (int)TEXT_FRAME_WIDTH * 2, GAME_HEIGHT - (int)TEXT_FRAME_HEIGHT, 0, spaceTexture))
		DebugOut("Error initializing space");
	space->setY(TEXT_FRAME_HEIGHT);
	space->setX(TEXT_FRAME_WIDTH);

	if (!paddle1->initialize(this, paddleNS::WIDTH, paddleNS::HEIGHT, 0, paddleTexture))
		DebugOut("Error initalizing paddle 1");
	paddle1->addAnim(RECT{ 92,51,92 + paddleNS::WIDTH,51 + paddleNS::HEIGHT });
	paddle1->setFrames(paddleNS::PADDLE_START_FRAME, paddleNS::PADDLE_END_FRAME);
	paddle1->setCurrentFrame(paddleNS::PADDLE_START_FRAME, paddle1->getAnim());
	paddle1->setX(0.0f);
	paddle1->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);
	//paddle1->setDegrees(90);
	paddle1->setCollisionType(entityNS::BOX);

	if (!paddle2->initialize(this, paddleNS::WIDTH, paddleNS::HEIGHT, 0, paddleTexture))
		DebugOut("Error initalizing paddle 2");
	paddle2->addAnim(RECT{ 112, 51, 112 + paddleNS::WIDTH - 1, 51 + paddleNS::HEIGHT - 1 });
	paddle2->setFrames(paddleNS::PADDLE_START_FRAME, paddleNS::PADDLE_END_FRAME);
	paddle2->setCurrentFrame(paddleNS::PADDLE_START_FRAME, paddle2->getAnim());
	paddle2->setX(GAME_WIDTH - paddleNS::WIDTH);
	paddle2->setY(GAME_HEIGHT / 2 - paddleNS::HEIGHT / 2);
	paddle2->flipHorizontal(true);
	paddle2->setCollisionType(entityNS::BOX);

	if (!ball->initialize(this, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, ballTexture))
		DebugOut("Error initializing ball");
	ball->setFrames(ballNS::BALL_START_FRAME, ballNS::BALL_END_FRAME);
	ball->setCurrentFrame(ballNS::BALL_START_FRAME);
	ball->setFrameDelay(ballNS::BALL_ANIMATION_DELAY);
	ball->setX(ballNS::X);
	ball->setY(ballNS::Y);
	ball->setVelocity(D3DXVECTOR2(ballNS::SPEED, ballNS::SPEED));
	ball->setCollisionType(entityNS::BOX);

	//init TEXT
	if (!fontCK->initialize(graphics, FONT_IMAGE))
		DebugOut("Error initializing font");
	fpsOn = true;

	return;
}

void GameAssignment2::update(float frameTime)
{
	if (input->isKeyDown(W_KEY))
		paddle1->setY(paddle1->getY() - frameTime * paddleNS::SPEED);
	if (input->isKeyDown(S_KEY))
		paddle1->setY(paddle1->getY() + frameTime * paddleNS::SPEED);
	paddle2->setY((float)input->getMouseY());
	paddle1->update(frameTime, true);
	paddle2->update(frameTime, true);
	ball->update(frameTime);
	if (ball->getOutsideScopeLeft())
		scorePaddle2++;
	if (ball->getOutsideScopeRight())
		scorePaddle1++;
}

void GameAssignment2::ai()
{
}

void GameAssignment2::collisions()
{
	D3DXVECTOR2 collisionVector;
	if (ball->collidesWith(*paddle1, collisionVector) || ball->collidesWith(*paddle2, collisionVector))
	{
		ball->setVelocityX(-ball->getVelocity().x);
	}
}

void GameAssignment2::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	paddle1->draw();
	DebugOut("x : %.2f\n", paddle1->getX());
	paddle2->draw();

	// display Text
	fontCK->setProportional(false);
	fontCK->setFontColor(graphicsNS::RED);
	fontCK->setBackColor(graphicsNS::TRANSCOLOR);
	fontCK->setFontHeight(textNS::FONT_HEIGHT / 2);
	fontCK->print("PONG GAME", GAME_WIDTH / 2 - (textNS::FONT_WIDTH * 9) / 4, TEXT_FRAME_HEIGHT / 2 - textNS::FONT_HEIGHT / 4);

	// display fps
	if (fpsOn)
	{
		fontCK->setFontColor(graphicsNS::BLUE);
		fontCK->setBackColor(graphicsNS::TRANSCOLOR);
		fontCK->setFontHeight(textNS::FONT_HEIGHT / 4);
		sprintf_s(textFPS, "FPS: %.0f", fps);
		fontCK->print(textFPS, GAME_WIDTH - (textNS::FONT_WIDTH * 7) / 4, 5);
	}

	// display scores
	fontCK->setFontColor(graphicsNS::PURPLE);
	fontCK->setBackColor(graphicsNS::TRANSCOLOR);
	fontCK->setFontHeight(textNS::FONT_HEIGHT / 2);
	sprintf_s(textScorePaddle1, "%d", scorePaddle1);
	sprintf_s(textScorePaddle2, "%d", scorePaddle2);
	fontCK->print(textScorePaddle1, GAME_WIDTH / 2 - (textNS::FONT_WIDTH * 3) / ((scorePaddle1 > 9) ? 2 : 3), 50);
	fontCK->print(textScorePaddle2, GAME_WIDTH / 2 + (textNS::FONT_WIDTH * 3) / 6, 50);

	space->draw();
	ball->draw();

	graphics->spriteEnd();                  // end drawing sprites
}

void GameAssignment2::releaseAll()
{
	ballTexture->onLostDevice();
	spaceTexture->onLostDevice();
	paddleTexture->onLostDevice();
	fontCK->onLostDevice();
	Game::releaseAll();
	return;
}

void GameAssignment2::resetAll()
{
	ballTexture->onResetDevice();
	spaceTexture->onResetDevice();
	paddleTexture->onResetDevice();
	fontCK->onResetDevice();
	Game::resetAll();
	return;
}


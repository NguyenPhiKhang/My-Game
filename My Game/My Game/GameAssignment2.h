#ifndef _GAME_ASSIGNMENT2_H
#define _GAME_ASSIGNMENT2_H

#include "Game.h"
#include "textureManager.h"
#include "Ball.h"
#include "Paddle.h"
#include "image.h"

class GameAssignment2: public Game
{
private: 
	TextureManager spaceTexture;
	TextureManager ballTexture;
	TextureManager paddleTexture;

	Ball ball;
	Paddle paddle1;
	Paddle paddle2;
	Image space;
public:
	GameAssignment2() {};
	~GameAssignment2() {};

	// Initialize the game
	void initialize(HWND hwnd);
	void update(float frameTime);      // must override pure virtual from Game
	void ai();         // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

#endif
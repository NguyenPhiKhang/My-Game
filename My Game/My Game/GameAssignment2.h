#ifndef _GAME_ASSIGNMENT2_H
#define _GAME_ASSIGNMENT2_H

#include "Game.h"
#include "textureManager.h"
#include "Ball.h"
#include "Paddle.h"
#include "image.h"
#include "Text.h"
#include <string>


class GameAssignment2: public Game
{
private: 
	TextureManager* spaceTexture;
	TextureManager* ballTexture;
	TextureManager* paddleTexture;
	TextureManager* testTexture;

	Image* test;

	Ball* ball;
	Paddle* paddle1;
	Paddle* paddle2;
	Image* space;

	Text* fontCK;

	//scores
	UINT scorePaddle1;
	UINT scorePaddle2;

	// text fps, score
	char textFPS[20];
	char textScorePaddle1[10];
	char textScorePaddle2[10];
	
public:
	GameAssignment2();
	~GameAssignment2();

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
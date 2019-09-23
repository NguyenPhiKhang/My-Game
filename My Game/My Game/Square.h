#ifndef _SQUARE_H
#define _SQUARE_H

#include "constants.h"
#include "Entity.h"


namespace squareNS
{
	const int WIDTH = 16;						// image width
	const int HEIGHT = 16;						// image height
	const int X = 0;	// location on screen
	const int Y = 0;
	const float ROTATION_RATE = (float)PI/2;
	const float SPEED = 100.0f;					// 100 pixels per second
	const int TEXTURE_COLS = 1;					// texture has 1 columns
	const int SQUARE_START_FRAME = 0;			
	const int SQUARE_END_FRAME = 0;
	enum MOVE_TYPE{AROUND, SIN_SHAPE};
}

class Square : public Entity
{
private:
	squareNS::MOVE_TYPE moveType;
	float totalTime;
public:
	Square();
	void update(float frameTime);
	void setMoveType(squareNS::MOVE_TYPE movetype) { moveType = movetype; };
};

#endif
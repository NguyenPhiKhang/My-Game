#ifndef _MAP_GAME_H
#define _MAP_GAME_H

#include <JsonCpp/json/json.h>
#include "constants.h"
#include "image.h"
#include <fstream>
#include "textureManager.h"
#include "Camera.h"
#include "Graphics.h"

// for convenience

namespace MapNS {
	const int TEXTURE_SIZE = 8;
	const int TEXTURE_COLS = 100;
	const int MAP_HEIGHT_1 = 1134;
	const int MAP_WIDTH_1 = 2270;
	const int MAX_SPEED_KEYB = 500;
	const float POSX_KEYB = 160.0f;
	const float POSY_KEYB = 120.0f;

	//const int __ = -1;                  // empty tile
	//const int tileMap[MAP_HEIGHT][MAP_WIDTH] = {
	//	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	//	 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	//	 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	//	 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
	//	 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	//	 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
	//	 96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,
	//	112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
	//};

}


class MapGame
{
private:
	Image* map;

	int ColumnsMap, RowsMap;
	int tileWidth, tileHeight;
	int bankMapWidth, bankMapHeight;

	int tileMap[142][284];

public:
	MapGame();
	~MapGame();
	bool initialize(Graphics* graphics, TextureManager* texture);
	void ReadMapJSON(std::string filename);
	void Render(Camera* camera);
};

#endif // !1


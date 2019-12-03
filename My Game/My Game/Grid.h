#ifndef _GRID_H
#define _GRID_H

#include "Entity.h"
#include "Camera.h"
#include "constants.h"
#include <fstream>
#include <JsonCpp/json/json.h>
#include <unordered_map>

#include "AppleItem.h"

namespace gridNS {
	const int GRID_CELL_WIDTH = GAME_WIDTH / 4;
	const int GRID_CELL_HEIGHT = GAME_HEIGHT / 4;

	const int GRID_CELL_MAX_ROW = 20;
	const int GRID_CELL_MAX_COLUMN = 30;
}

using namespace gridNS;

class Grid
{
private:
	std::vector<Entity*> cells[GRID_CELL_MAX_ROW][GRID_CELL_MAX_COLUMN];
	std::string filepath;

public:
	Grid();
	~Grid();

	void SetFile(std::string str); // Đọc các object từ file
	void ReloadGrid(TextureManager* texture, Game* game);


	Entity* GetNewEntity(int type, float x, float y, int w, int h, TextureManager* texture, Game* game);
	void Insert(int id, int type, float x, float y, int w, int h, TextureManager* texture, Game* game); //Thêm object vào grid
	void GetListObject(std::vector<Entity*>& ListObj, Camera* camera);

};

#endif // !_GRID_H
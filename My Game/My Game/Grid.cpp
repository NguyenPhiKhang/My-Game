#include "Grid.h"

Grid::Grid()
{
}

Grid::~Grid()
{
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++)
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++)
		{
			cells[i][j].clear();
		}
}

void Grid::SetFile(std::string str)
{
	filepath = str;
}

void Grid::ReloadGrid(TextureManager* texture, Game* game)
{
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++)
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++)
		{
			cells[i][j].clear();
		}


	int id, type, w, h, n;
	float x, y;

	std::ifstream ifs(filepath);
	Json::Reader reader;
	Json::Value root;
	reader.parse(ifs, root);

	Json::Value mapItem = root["mapItem"];
	n = mapItem["n"].asInt();

	for (int i = 0; i < n; i++)
	{
		id = mapItem["imagelayer"][i]["_id"].asInt();
		type = mapItem["imagelayer"][i]["_type"].asInt();
		x = mapItem["imagelayer"][i]["_offsetx"].asFloat();
		y = mapItem["imagelayer"][i]["_offsety"].asFloat();
		w = mapItem["_width"].asInt();
		h = mapItem["_height"].asInt();
		Insert(id, type, x, y, w, h, texture, game);
	}
	ifs.close();
}

Entity* Grid::GetNewEntity(int type, float x, float y, int w, int h, TextureManager* texture, Game* game)
{
	AppleItem* apple = new AppleItem(x, y);
	apple->initialize(game, w, h, 1, texture);
	return apple;
}

void Grid::GetListObject(std::vector<Entity*>& ListObj, Camera* camera)
{
	ListObj.clear();

	std::unordered_map<int, Entity*> mapObject;

	int bottom = (int)((camera->getYCamera() + GAME_HEIGHT - 1) / GRID_CELL_HEIGHT);
	int top = (int)((camera->getYCamera() + 1) / GRID_CELL_HEIGHT);

	int left = (int)((camera->getXCamera() + 1) / GRID_CELL_WIDTH);
	int right = (int)((camera->getXCamera() + GAME_WIDTH - 1) / GRID_CELL_WIDTH);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				if (mapObject.find(cells[i][j].at(k)->getID()) == mapObject.end())
					mapObject[cells[i][j].at(k)->getID()] = cells[i][j].at(k);
			}
	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}
}

void Grid::Insert(int id, int type, float x, float y, int w, int h, TextureManager* texture, Game* game)
{
	int top = (int)(y / GRID_CELL_HEIGHT);
	int bottom = (int)((y + h) / GRID_CELL_HEIGHT);
	int left = (int)(x / GRID_CELL_WIDTH);
	int right = (int)((x + w) / GRID_CELL_WIDTH);

	Entity* ent = GetNewEntity(type, x, y, w, h, texture, game);
	if (ent == NULL)
		return;
	ent->setID(id);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(ent);
}
#include "MapGame.h"

MapGame::MapGame()
{
	map = new Image();

	ColumnsMap = RowsMap = 0;
	tileWidth = tileHeight = 0;
}

MapGame::~MapGame()
{
	safeDelete(map);
}

bool MapGame::initialize(Graphics* graphics, TextureManager* texture)
{
	ReadMapJSON(SULTAN_TILE_FILE);
	return map->initialize(graphics, tileWidth, tileHeight, MapNS::TEXTURE_COLS, texture);
}

void MapGame::ReadMapJSON(std::string filename)
{
	std::ifstream ifs(filename);
	Json::Reader reader;
	Json::Value root;
	reader.parse(ifs, root);

	const Json::Value& infoMap = root["map"];
	ColumnsMap = infoMap["_cols"].asInt();
	RowsMap = infoMap["_rows"].asInt();
	tileWidth = infoMap["_tilewidth"].asInt();
	tileHeight = infoMap["_tileheight"].asInt();
	bankMapWidth = infoMap["_width"].asInt();
	bankMapHeight = infoMap["_height"].asInt();
	const Json::Value& dataMap = infoMap["data"];

	for (int i=0;i<RowsMap;i++){
		for (int j = 0; j < ColumnsMap; j++) {
			tileMap[i][j] = dataMap[i * ColumnsMap + j].asInt();
		}
	}
	DebugOut("done");
	ifs.close();
}

void MapGame::Render(Camera* camera)
{
	int col = camera->getXCamera() / tileWidth;
	int row = camera->getYCamera() / tileHeight;

	float xViewPort = -((int)camera->getXCamera() % tileWidth/* + (camera->getXCamera()-(int)camera->getXCamera())*/);
	float YViewPort = -((int)camera->getYCamera() % tileHeight/* + (camera->getYCamera() - (int)camera->getYCamera())*/);

	for (int i = 0; i <= GAME_HEIGHT / tileWidth; i++) {
		for (int j = 0; j <= GAME_WIDTH / tileHeight; j++) {
			if (!(row + i < 0 || row + i >= RowsMap || j + col < 0 || j + col > ColumnsMap))
			{
				map->setCurrentFrame(tileMap[row + i][col + j]-1);
				map->setViewportX(j * tileWidth + xViewPort);
				map->setViewportY(i * tileHeight + YViewPort);
				map->draw();
			}
		}
	}
}

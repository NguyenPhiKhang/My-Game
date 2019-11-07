#include "SultansDungeonScene.h"

SultansDungeonScene::SultansDungeonScene()
{
	sultansDungeonTexture = new TextureManager();
	appleItemTexture = new TextureManager();
	testTexture = new TextureManager();

	test = new Image();
	tileMap = new MapGame();
	camera = new Camera();
	grid = new Grid();

	posX = 0;
	posY = 1134;
	camera->setPositionCam(0, 894);
	verticalX = MapNS::MAX_SPEED_KEYB;
	verticalY = MapNS::MAX_SPEED_KEYB;
}

SultansDungeonScene::~SultansDungeonScene()
{
	releaseAll();
}

void SultansDungeonScene::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	if (!sultansDungeonTexture->initialize(graphics, SULTAN_IMAGE))
		DebugOut("Error initializing sultan texture");
	if (!appleItemTexture->initialize(graphics, APPLE_ITEM_IMAGE))
		DebugOut("Error initializing apple Item texture");

	grid->SetFile(SULTAN_ITEM);
	grid->ReloadGrid(appleItemTexture, this);
	
	if (!tileMap->initialize(graphics, sultansDungeonTexture))
		DebugOut("Error initializing sultanScene");

	testTexture->initialize(graphics, "Resources\\test.png");
	test->initialize(graphics, 62, 79, 39, testTexture);
	test->setFrames(0, 38);
	test->setCurrentFrame(0);
	test->setFrameDelay(0.12f);
	test->setX(82.0f);
	test->setY(1018.0f);
	//test->flipHorizontal(true);

}

void SultansDungeonScene::update(float frameTime)
{
	grid->GetListObject(listEntity, camera);

	if(input->isKeyDown(SHIP_UP_KEY))
	{ 
		verticalY = - MapNS::MAX_SPEED_KEYB;
		posY += verticalY*frameTime;
		if (posY > MapNS::POSY_KEYB&&posY<MapNS::MAP_HEIGHT_1-MapNS::POSY_KEYB)
		{
			camera->setPositionCam(camera->getXCamera(), posY-MapNS::POSY_KEYB);
		}
		if (posY < MapNS::POSY_KEYB) { camera->setPositionCam(camera->getXCamera(), 0); }
		if (posY < 0)
			posY = 0;
	}
	if(input->isKeyDown(SHIP_DOWN_KEY))
	{ 
		verticalY = MapNS::MAX_SPEED_KEYB;
		posY += verticalY * frameTime;
		if (posY > MapNS::POSY_KEYB&& posY < MapNS::MAP_HEIGHT_1 - MapNS::POSY_KEYB)
		{
			camera->setPositionCam(camera->getXCamera(), camera->getYCamera() + verticalY * frameTime);
		}
		if (posY > MapNS::MAP_HEIGHT_1 - MapNS::POSY_KEYB) { camera->setPositionCam(camera->getXCamera(), MapNS::MAP_HEIGHT_1-2*MapNS::POSY_KEYB); }
		if (posY > MapNS::MAP_HEIGHT_1)
			posY = MapNS::MAP_HEIGHT_1;
	}
	if(input->isKeyDown(SHIP_LEFT_KEY))
	{
		verticalX = -MapNS::MAX_SPEED_KEYB;
		posX += verticalX * frameTime;
		if (posX > MapNS::POSX_KEYB&&posX<MapNS::MAP_WIDTH_1-MapNS::POSX_KEYB)
		{
			camera->setPositionCam(posX-MapNS::POSX_KEYB, camera->getYCamera());
		}
		if(posX < MapNS::POSX_KEYB) { camera->setPositionCam(0, camera->getYCamera()); }
		if (posX < 0)
			posX = 0;
	}
	if(input->isKeyDown(SHIP_RIGHT_KEY))
	{
		verticalX = MapNS::MAX_SPEED_KEYB;
		posX += verticalX * frameTime;
		if (posX > MapNS::POSX_KEYB&& posX < MapNS::MAP_WIDTH_1 - MapNS::POSX_KEYB)
		{
			camera->setPositionCam(posX-MapNS::POSX_KEYB, camera->getYCamera());
		}
		if(posX> MapNS::MAP_WIDTH_1 - MapNS::POSX_KEYB) { camera->setPositionCam(MapNS::MAP_WIDTH_1-2*MapNS::POSX_KEYB, camera->getYCamera()); }
		if (posX > MapNS::MAP_WIDTH_1)
			posX = MapNS::MAP_WIDTH_1;
	}

	if (test->getCurrentFrame() == 3 || test->getCurrentFrame() == 6 || test->getCurrentFrame() == 21 || test->getCurrentFrame() == 38)
		test->setFrameDelay(0.6f);
	else if (test->getCurrentFrame() == 0)
		test->setFrameDelay(1.0f);
	else test->setFrameDelay(0.12f);
	test->update(frameTime);
}

void SultansDungeonScene::ai()
{
}

void SultansDungeonScene::collisions()
{
}

void SultansDungeonScene::render()
{
	graphics->spriteBegin();

	tileMap->Render(camera);
	for (auto& ent : listEntity)
	{
		D3DXVECTOR2 pos = camera->CameraTransform(ent->getX(), ent->getY());
		ent->setViewportX(pos.x);
		ent->setViewportY(pos.y);
		ent->draw();
	}

	D3DXVECTOR2 pos1 = camera->CameraTransform(test->getX(), test->getY());
	test->setViewportX(pos1.x);
	test->setViewportY(pos1.y);
	test->draw();

	graphics->spriteEnd();
}

void SultansDungeonScene::releaseAll()
{
	sultansDungeonTexture->onLostDevice();
	appleItemTexture->onLostDevice();
	testTexture->onLostDevice();
	Game::releaseAll();
	return;
}

void SultansDungeonScene::resetAll()
{
	sultansDungeonTexture->onResetDevice();
	appleItemTexture->onResetDevice();
	testTexture->onResetDevice();
	Game::resetAll();
	return;
}

#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene()
{
}
GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
	SCENEMANAGER->addScene("Title", new Title);
	SCENEMANAGER->addScene("IntroStage", new IntroStage);
	SCENEMANAGER->addScene("Stage", new Stage);
	SCENEMANAGER->addScene("Ending", new Ending);
	SCENEMANAGER->changeScene("Title");
	return S_OK;
}

void GameScene::release()
{
	SCENEMANAGER->release();
}

void GameScene::update()
{
	SCENEMANAGER->update();
}

void GameScene::render()
{
	SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());
}

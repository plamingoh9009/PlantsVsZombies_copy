#pragma once
#include "gameNode.h"
#include "Title.h"
#include "IntroStage.h"
#include "Stage.h"
#include "Ending.h"
class GameScene: public gameNode
{
public:
	GameScene();
	~GameScene();
	HRESULT init();
	void release();
	void update();
	void render();
};


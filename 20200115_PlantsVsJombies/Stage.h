#pragma once
#include "gameNode.h"
#include "UI.h"
#include "ObjectControl.h"
class Stage: public gameNode
{
private:
	UI * _ui;
	ObjectControl * _objControl;
	image * _gameOverImg;
	RECT _gameOverRect;
	// ���������� �ѱ�� �� ���� ��ٸ���
	int _sceneChangeCount;
	int _sceneChangeDelay;
protected:
	void change_sceneEnding();
	void init_gameOver();
	void delete_gameOverImg();
	void init_uiToObjControl();
public:
	void update_clickedUi();
	void update_uiToObjControl();
	void update_objControlToUi();
public:
	Stage();
	~Stage();
	HRESULT init();
	void release();
	void update();
	void render();
};


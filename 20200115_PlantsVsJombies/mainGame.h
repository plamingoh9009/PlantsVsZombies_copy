#pragma once
#include"gameNode.h"
#include "GameScene.h"
class mainGame :  public gameNode
{
private:
	GameScene * _gameScene;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

	
};


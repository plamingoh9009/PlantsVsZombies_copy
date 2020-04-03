#pragma once
#include "gameNode.h"
class Ending: public gameNode
{
private:
	image * _img;
	RECT _rect;
public:
	Ending();
	~Ending();
	HRESULT init();
	void release();
	void update();
	void render();
};


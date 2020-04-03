#pragma once
#include "gameNode.h"
class Object: public gameNode
{
public:
	Object();
	~Object();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};


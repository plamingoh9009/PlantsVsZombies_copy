#include "stdafx.h"
#include "Ending.h"


Ending::Ending()
{
}
Ending::~Ending()
{
}
HRESULT Ending::init()
{
	_img = IMAGEMANAGER->addImage("GameWin",
		"images/GameWin.bmp", 1000, 851, false, COLOR_MAGENTA);
	_rect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 1000, 851);
	return S_OK;
}
void Ending::release()
{
	_img = nullptr;
	IMAGEMANAGER->deleteImage("GameWin");
}
void Ending::update()
{
}
void Ending::render()
{
	_img->render(getMemDC(), _rect.left, _rect.top);
}

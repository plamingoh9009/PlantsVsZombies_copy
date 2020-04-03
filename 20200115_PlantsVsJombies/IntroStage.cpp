#include "stdafx.h"
#include "IntroStage.h"

// ================================================
// **			레디셋플랜트 초기화					 **
// ================================================
void IntroStage::init_imgWord()
{
	_width = 300;
	_height = 133;
	_imgWord = IMAGEMANAGER->addImage("Word_Ready",
		"images/ui/Word_Ready.bmp", _width, _height, true, COLOR_MAGENTA);
	IMAGEMANAGER->addImage("Word_Set",
		"images/ui/Word_Set.bmp", _width, _height, true, COLOR_MAGENTA);
	IMAGEMANAGER->addImage("Word_Plant",
		"images/ui/Word_Plant.bmp", _width, _height, true, COLOR_MAGENTA);
	_wordCount = 0;
	_wordDelay = 60;
	_imgWordRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
		_width, _height);
	_fReady = true;
	_fSet = false;
	_fPlant = false;
}
void IntroStage::delete_imgWord()
{
	IMAGEMANAGER->deleteImage("Word_Ready");
	IMAGEMANAGER->deleteImage("Word_Set");
	IMAGEMANAGER->deleteImage("Word_Plant");
	_imgWord = nullptr;
}
void IntroStage::change_imgWord()
{
	_wordCount++;
	if (_wordCount >= _wordDelay)
	{
		if (_fReady == true)
		{
			_imgWord = IMAGEMANAGER->findImage("Word_Set");
			_fReady = false;
			_fSet = true;
		}
		else if (_fSet == true)
		{
			_imgWord = IMAGEMANAGER->findImage("Word_Plant");
			_fSet = false;
			_fPlant = true;
		}
		else if (_fPlant == true)
		{
			SCENEMANAGER->changeScene("Stage");
		}
		_wordCount = 0;
	}
}
void IntroStage::show_imgWordRect()
{
	FrameRect(getMemDC(), &_imgWordRect,
		CreateSolidBrush(RGB(255, 255, 255)));
}

IntroStage::IntroStage()
{
}
IntroStage::~IntroStage()
{
}
HRESULT IntroStage::init()
{
	_map = new Map;
	_map->init();
	_map->init_forIntro();
	init_imgWord();
	return S_OK;
}
void IntroStage::release()
{
	_map = nullptr;
	delete_imgWord();
}
void IntroStage::update()
{
	_map->update();
	if (_map->is_ReadySetPlantOK() == true)
	{
		_map->set_isShowMapAll(false);
		change_imgWord();
	}
}
void IntroStage::render()
{
	_map->render();
	if (_map->is_ReadySetPlantOK() == true)
	{
		_imgWord->render(getMemDC(), _imgWordRect.left, _imgWordRect.top);
	}
}

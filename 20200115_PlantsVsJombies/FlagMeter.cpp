#include "stdafx.h"
#include "FlagMeter.h"
// ================================================
// **			플래그미터 컨트롤					 **
// ================================================
void FlagMeter::run_flagmeter()
{
	if (0 < _currentGauge)
	{
		_flagmeterCount++;
		if (_flagmeterCount >= _flagmeterDelay)
		{
			// 플래그미터를 움직인다.
			_currentGauge--;
			move_flagmeter();
			_flagmeterCount = 0;
		}
	}//if: 게이지가 존재하는 동안
	else
	{
		_fGameWin = true;
	}//else: 게이지가 없다면
}
void FlagMeter::move_flagmeter()
{
	float percent = _currentGauge / _maxGauge;
	_currentWidth = _width * percent;
	_headRect.left = (LONG)(_rect.left + _currentWidth - (_headWidth / 2));
	_headRect.right = _headRect.left + _headWidth;
}
void FlagMeter::move_flagmeter(float percent)
{
	percent = _currentGauge / _maxGauge;
	_currentWidth = _width * percent;
	_headRect.left = (LONG)(_rect.left + _currentWidth - (_headWidth / 2));
	_headRect.right = _headRect.left + _headWidth;
}
void FlagMeter::init_flagmeter()
{
	_flagmeterCount = 0;
	_flagmeterDelay = 8;
	_maxGauge = 60 * 20;
	//_maxGauge = 10;
	_currentGauge = _maxGauge;
	_currentWidth = (float)(_width);
	_headWidth = 25;
	// 좀비 헤드 초기화
	_headRect.left = (LONG)(_rect.left + _currentWidth - (_headWidth / 2));
	_headRect.top = _rect.top;
	_headRect.right = _headRect.left + _headWidth;
	_headRect.bottom = _headRect.right + 25;
	_fGameWin = false;
}
void FlagMeter::show_rect()
{
	FrameRect(getMemDC(), &_rect,
		CreateSolidBrush(RGB(0, 0, 0)));
}

FlagMeter::FlagMeter()
{
}
FlagMeter::~FlagMeter()
{
}
HRESULT FlagMeter::init()
{
	// 초기위치
	int initX = 694;
	int initY = 568;
	_width = 158;
	_height = 24;
	_rect = RectMake(initX, initY, _width, _height);
	_imgEmpty = IMAGEMANAGER->addImage("Flagmeter_Empty",
		"images/ui/Flagmeter_Back.bmp", _width, _height, true, COLOR_MAGENTA);
	_imgFull = IMAGEMANAGER->addImage("Flagmeter_Full",
		"images/ui/Flagmeter_Front.bmp", _width, _height, true, COLOR_MAGENTA);
	_imgFlag = IMAGEMANAGER->addImage("Flag",
		"images/ui/Flag.bmp", 24, 26, true, COLOR_MAGENTA);
	_imgHead = IMAGEMANAGER->addImage("Flag_Head",
		"images/ui/Flag_Head.bmp", 25, 25, true, COLOR_MAGENTA);
	// 플래그미터를 초기화한다.
	init_flagmeter();
	return S_OK;
}
void FlagMeter::release()
{
	IMAGEMANAGER->deleteImage("Flagmeter_Back");
	IMAGEMANAGER->deleteImage("Flagmeter_Front");
	IMAGEMANAGER->deleteImage("Flag");
	IMAGEMANAGER->deleteImage("Flag_Head");
	_imgEmpty = nullptr;
	_imgFull = nullptr;
	_imgFlag = nullptr;
	_imgHead = nullptr;
}
void FlagMeter::update()
{
	run_flagmeter();
}
void FlagMeter::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) {}
	else
	{
		_imgFull->render(getMemDC(), _rect.left, _rect.top);
		_imgEmpty->render(getMemDC(), _rect.left, _rect.top,
			0, 0, (int)(_currentWidth), _height);
		_imgFlag->render(getMemDC(), _rect.left, _rect.top);
		_imgHead->render(getMemDC(), _headRect.left, _headRect.top);
	}//else: 탭키를 안눌렀을때 보여준다.
}

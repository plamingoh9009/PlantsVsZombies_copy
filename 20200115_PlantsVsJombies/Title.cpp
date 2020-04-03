#include "stdafx.h"
#include "Title.h"


bool Title::is_mouseInStart()
{
	if (IntersectRect(&RECT(), &_mouse, &_gameStart))
	{
		return true;
	}
	return false;
}
bool Title::is_mouseInQuit()
{
	if (IntersectRect(&RECT(), &_mouse, &_gameQuit))
	{
		return true;
	}
	return false;
}
// ================================================
// **				디버그를 위한 부분				 **
// ================================================
void Title::make_mouseRect()
{
	_mouse = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, 5, 5);
}
void Title::show_mouseRect()
{
	FrameRect(getMemDC(), &_mouse,
		CreateSolidBrush(RGB(255, 255, 255)));
}
void Title::init_buttonRect()
{
	int initX, initY;
	int startWidth = 330;
	int startHeight = 100;
	initX = 405 + _blank;
	initY = 78;
	_gameStart = RectMake(initX, initY, startWidth, startHeight);
	int exitWidth = 70;
	int exitHeight = 40;
	initX = 710 + _blank;
	initY = 506;
	_gameQuit = RectMake(initX, initY, exitWidth, exitHeight);
}
void Title::show_buttonRect()
{
	FrameRect(getMemDC(), &_gameStart,
		CreateSolidBrush(RGB(255, 255, 255)));
	FrameRect(getMemDC(), &_gameQuit,
		CreateSolidBrush(RGB(255, 255, 255)));
}

Title::Title()
{
}
Title::~Title()
{
}
HRESULT Title::init()
{
	_img = IMAGEMANAGER->addImage("Title",
		"images/ui/Title.bmp", 800, 600, false, COLOR_MAGENTA);
	IMAGEMANAGER->addImage("Title_Start",
		"images/ui/Title_Start.bmp", 800, 600, false, COLOR_MAGENTA);
	IMAGEMANAGER->addImage("Title_Quit",
		"images/ui/Title_Quit.bmp", 800, 600, false, COLOR_MAGENTA);
	_type = "Title";
	_blank = (1024 - 800) / 2;
	_initX = _blank;
	init_buttonRect();
	return S_OK;
}
void Title::release()
{
	IMAGEMANAGER->deleteImage("Title");
	IMAGEMANAGER->deleteImage("Title_Start");
	IMAGEMANAGER->deleteImage("Title_Quit");
	_img = nullptr;
}
void Title::update()
{
	if (is_mouseInStart() == true)
	{
		_img = IMAGEMANAGER->findImage("Title_Start");
		_type = "Title_Start";
	}
	else if (is_mouseInQuit() == true)
	{
		_img = IMAGEMANAGER->findImage("Title_Quit");
		_type = "Title_Quit";
	}
	else
	{
		if(_type.compare("Title") != 0)
		{
			_img = IMAGEMANAGER->findImage("Title");
			_type = "Title";
		}
		else {}
	}

// ================================================
// **				클릭했을 때					 **
// ================================================
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (is_mouseInStart() == true)
		{
			SCENEMANAGER->changeScene("IntroStage");
		}
		else if (is_mouseInQuit() == true)
		{
			keybd_event(VK_ESCAPE, 0, 0, 0);
		}
	}
	make_mouseRect();
}
void Title::render()
{
	_img->render(getMemDC(), _initX, 0);
}

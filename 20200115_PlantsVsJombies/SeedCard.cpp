#include "stdafx.h"
#include "SeedCard.h"

// ================================================
// **				����׿� �Լ� 					 **
// ================================================
void SeedCard::show_costRect()
{
	FrameRect(getMemDC(), &_costRect,
		CreateSolidBrush(RGB(0, 0, 0)));
}
void SeedCard::show_rect()
{
	FrameRect(getMemDC(), &_rect,
		CreateSolidBrush(RGB(255, 255, 255)));
}

RECT SeedCard::get_oneFrameRect()
{
	return _oneFrameRect;
}
RECT SeedCard::make_oneFrameRect()
{
	int x = _rect.left;
	int y = _rect.top;
	int width = _img->getFrameWidth();
	int height = _img->getFrameHeight();
	RECT oneFrameRect = RectMake(x, y, width, height);
	return oneFrameRect;
}
void SeedCard::show_oneFrameRect()
{
	FrameRect(getMemDC(), &_oneFrameRect, 
		CreateSolidBrush(RGB(255, 255, 255)));
}

void SeedCard::init_plantImage()
{
	//SunFlower
	IMAGEMANAGER->addImage("SunFlower_Disable",
		"images/ui/SunFlower_Disable.bmp", 27, 27, false, COLOR_MAGENTA);
	IMAGEMANAGER->addImage("SunFlower_Enable",
		"images/ui/SunFlower_Enable.bmp", 35, 35, true, COLOR_MAGENTA);
	//Wallnut
	IMAGEMANAGER->addImage("Wallnut_Disable",
		"images/ui/Wallnut_Disable.bmp", 26, 25, false, COLOR_MAGENTA);
	IMAGEMANAGER->addImage("Wallnut_Enable",
		"images/ui/Wallnut_Enable.bmp", 36, 35, true, COLOR_MAGENTA);
	//PeaShooter
	IMAGEMANAGER->addImage("PeaShooter_Disable",
		"images/ui/PeaShooter_Disable.bmp", 26, 27, false, COLOR_MAGENTA);
	IMAGEMANAGER->addImage("PeaShooter_Enable",
		"images/ui/PeaShooter_Enable.bmp", 34, 35, true, COLOR_MAGENTA);
}
void SeedCard::set_seedCard(string strKey, int x, int y)
{
	// ī�� 1���� �����Ѵ�.
	_type = strKey;
	_rect = RectMake(x, y, _width, _height);
	int initPlantImgX, initPlantImgY;
	// ī�� �̹��� ����
	if (strKey.compare("SunFlower") == 0)
	{
		_cost = 50;
		_kindOfPlant = strKey.append("_Enable");
		initPlantImgX = 8;
		initPlantImgY = 12;
		_kindOfCardBack = "Rare";
		_plantImage = IMAGEMANAGER->findImage(_kindOfPlant);
	}
	else if (strKey.compare("Wallnut") == 0)
	{
		_cost = 50;
		_kindOfPlant = strKey.append("_Enable");
		initPlantImgX = 8;
		initPlantImgY = 12;
		_kindOfCardBack = "Normal";
		_plantImage = IMAGEMANAGER->findImage(_kindOfPlant);
	}
	else if (strKey.compare("PeaShooter") == 0)
	{
		_cost = 100;
		_kindOfPlant = strKey.append("_Enable");
		initPlantImgX = 8;
		initPlantImgY = 12;
		_kindOfCardBack = "Normal";
		_plantImage = IMAGEMANAGER->findImage(_kindOfPlant);
	}
	// ī�� �̹��� ��ġ ����
	_plantImage->setX((float)(_rect.left + initPlantImgX));
	_plantImage->setY((float)(_rect.top + initPlantImgY));

	// ī�� ��� �̹��� ����
	if (_kindOfCardBack.compare("Rare") == 0)
	{
		_currentFrameX = 1;
		_currentFrameY = 0;
	}
	//if: ����ī��� 2��° �̹���
	else if (_kindOfCardBack.compare("Normal") == 0)
	{
		_currentFrameX = 2;
		_currentFrameY = 0;
	}
	//if: �븻ī��� 3��° �̹���

	// ī�� �� ���� �簢���� �ʱ�ȭ
	_oneFrameRect = make_oneFrameRect();
}
void SeedCard::set_plantImage(bool isEnable)
{
	string result;
	if (isEnable = true)
	{
		result = _type.append("_Enable");
	}
	else
	{
		result = _type.append("_Disable");
	}
	_plantImage = IMAGEMANAGER->findImage(result);
}
// ================================================
// **			ī�� ������ ����					 **
// ================================================
void SeedCard::set_costRect()
{
	int initX = 5;
	int initY = 53;
	int width = 25;
	int height = 10;
	_costRect.left = _oneFrameRect.left + initX;
	_costRect.top = _oneFrameRect.top + initY;
	_costRect.right = _costRect.left + width;
	_costRect.bottom = _costRect.top + height;
	wsprintf(_strCost, "%d", _cost);
}

SeedCard::SeedCard()
{
}
SeedCard::~SeedCard()
{
}
HRESULT SeedCard::init()
{
	_width = 450;
	_height = 70;
	_maxFrameX = 9;
	_maxFrameY = 1;
	_img = IMAGEMANAGER->addFrameImage("SeedCard", "images/SeedCard.bmp",
		_width, _height, _maxFrameX, _maxFrameY, false, COLOR_MAGENTA);
	// ī����� �Ĺ� �̹����� �ε��Ѵ�.
	init_plantImage();
	// ī�� on, off �ϴ� ����
	_fCardEnable = true;
	// ī���� ������ �ʱ�ȭ
	_cost = 0;
	return S_OK;
}
void SeedCard::release()
{
	//delete_plantImage�� SeedBank Ŭ������ �ϰ� �ִ�.
	_img = nullptr;
	_plantImage = nullptr;
}
void SeedCard::update()
{
}
void SeedCard::render()
{
	// ī���� ����� ����
	IMAGEMANAGER->frameRender("SeedCard", getMemDC(),
		_rect.left, _rect.top, _currentFrameX, _currentFrameY);
	// ī���� �Ĺ��׸��� ����
	_plantImage->render(getMemDC(),
		(int)(_plantImage->getX()), (int)(_plantImage->getY()));
	// ī���� �ڽ�Ʈ�� ����
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOut(getMemDC(), _costRect.left, _costRect.top, 
		_strCost, strlen(_strCost));
}

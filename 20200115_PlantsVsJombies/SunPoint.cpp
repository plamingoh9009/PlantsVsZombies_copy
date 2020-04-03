#include "stdafx.h"
#include "SunPoint.h"

void SunPoint::delete_default()
{
	_deleteCount++;
	if (_deleteCount >= _deleteDelay)
	{
		_fDelete = true;
		_deleteCount = 0;
	}
}
void SunPoint::move_defaultMove()
{
	_fallCount++;
	if (_fallCount >= _fallDelay)
	{
		if (_distance > 0)
		{
			_rect.top += _fallSpeed;
			_rect.bottom += _fallSpeed;
			_hitPoint.top += _fallSpeed;
			_hitPoint.bottom += _fallSpeed;
			_distance--;
		}
		_fallCount = 0;
	}
}
void SunPoint::init_hitPoint()
{
	int width = (int)(_width * 0.3);
	int height = (int)(_height * 0.3);
	_hitPoint.left = _rect.left + width;
	_hitPoint.top = _rect.top + height;
	_hitPoint.right = _rect.right - width;
	_hitPoint.bottom = _rect.bottom - height;
}
void SunPoint::show_hitPoint()
{
	FrameRect(getMemDC(), &_hitPoint,
		CreateSolidBrush(RGB(255, 255, 255)));
}
void SunPoint::init_rect()
{
	// x, y ������ ���� 4������ ���� 700, 380 ����
	// �ʱ� ��ġ�� 138, 94
	int x = RND->getFromIntTo(138 - (_width/2), 138 + 700 - (_width/2));
	int y = RND->getFromIntTo(94 - (_height/2), 94 + 380 - (_height/2));
	_rect = RectMake(x, y, _width, _height);
	init_hitPoint();
}

SunPoint::SunPoint()
{
}
SunPoint::~SunPoint()
{
}
HRESULT SunPoint::init()
{
	_width = 50;
	_height = 50;
	_img = IMAGEMANAGER->addImage("SunPoint",
		"images/SunPoint.bmp", _width, _height, true, COLOR_MAGENTA);
	// �޺��� ������ �� ���� ����
	_distance = 20;
	_fallCount = 0;
	_fallDelay = 8;
	_fallSpeed = 3;
	// �޺��� �Ա� ���� ����
	_fUseSunPoint = false;
	// ������ ������� ���� ����
	_fDelete = false;
	_deleteCount = 0;
	_deleteDelay = 60 * 7;
	return S_OK;
}
void SunPoint::release()
{
	_img = nullptr;
}
void SunPoint::update()
{
	move_defaultMove();
	// ���� �ð��� ���� �޺��� �������.
	delete_default();
}
void SunPoint::render()
{
	IMAGEMANAGER->render("SunPoint", getMemDC(), _rect.left, _rect.top);
}

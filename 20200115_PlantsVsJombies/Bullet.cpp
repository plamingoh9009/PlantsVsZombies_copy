#include "stdafx.h"
#include "Bullet.h"


void Bullet::init_hitPoint()
{
	_hitPoint = RectMake(_rect.left, _rect.top, 15, 15);
}
void Bullet::check_deleteBullet()
{
	if (_rect.left >= WINSIZEX)
	{
		_fDeleteBullet = true;
	}
}
void Bullet::move_toRight()
{
	_rect.left += _speed;
	_rect.right += _speed;
	// 총알의 실제 타격점이다.
	_hitPoint.left += _speed;
	_hitPoint.right += _speed;
}

void Bullet::draw_hitPoint()
{
	FrameRect(getMemDC(), &_hitPoint, 
		CreateSolidBrush(RGB(0, 0, 255)));
}
void Bullet::init_bullet(LONG x, LONG y)
{
	_rect = RectMake(x, y + _height, _width, _height);
	init_hitPoint();
}

Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}

HRESULT Bullet::init()
{
	_width = 24;
	_height = 24;
	_img = IMAGEMANAGER->addImage("PeaBullet",
		"images/plants/Pea_Bullet.bmp", _width, _height, 
		true, COLOR_MAGENTA);
	_speed = 2;
	_damage = 1;
	_fDeleteBullet = false;
	return S_OK;
}
void Bullet::release()
{
}
void Bullet::update()
{
	move_toRight();
	check_deleteBullet();
}
void Bullet::render()
{
	IMAGEMANAGER->render("PeaBullet", getMemDC(), _rect.left, _rect.top);
}

#include "stdafx.h"
#include "Plant.h"

void Plant::show_plantRect()
{
	// 설치된 공간을 출력
	FrameRect(getMemDC(), &_plantPoint, RGB(0, 0, 0));
	// 객체의 한 프레임을 출력
	FrameRect(getMemDC(), &_rect, CreateSolidBrush(RGB(0, 0, 255)));
}
void Plant::show_bulletHitPoints()
{
	_itBullets = _bullets.begin();
	for (;_itBullets != _bullets.end();_itBullets++)
	{
		(*_itBullets)->draw_hitPoint();
	}
}
void Plant::hit_plant(int lostHp)
{
	if (lostHp > 0)
	{
		_hp -= lostHp;
	}
}
// ================================================
// **	식물이 공격할 때 이미지 바꾸는 함수			 **
// ================================================
void Plant::change_plantImgForAttack()
{
	_img = IMAGEMANAGER->findImage("PeaShooter_Attack");
	// 프레임을 돌리기 위한 변수
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameCount = 0;
	_frameDelay = 12;
	// _rect를 만들기 위한 변수
	_maxFrameX = 5;
	_maxFrameY = 1;
	_width = 375;
	_height = 75;
	_rect = RectMake(_rect.left, _rect.top,
		_width / _maxFrameX, _height / _maxFrameY);
}
void Plant::change_plantImgForIdle()
{
	_img = IMAGEMANAGER->findImage("PeaShooter");
	// 프레임을 돌리기 위한 변수
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameCount = 0;
	// _rect를 만들기 위한 변수
	_frameDelay = 8;
	_maxFrameX = 7;
	_maxFrameY = 1;
	_width = 525;
	_height = 75;
	_rect = RectMake(_rect.left, _rect.top,
		_width / _maxFrameX, _height / _maxFrameY);
}
void Plant::init_lostZombieHp()
{
	_lostZombieHp = 0;
	_fHitZombie = false;
}
bool Plant::is_hitZombie()
{
	return _fHitZombie;
}
void Plant::move_plant(LONG x, LONG y)
{
	_rect.left = x;
	_rect.top = y;
	_rect.right = x + _img->getFrameWidth();
	_rect.bottom = y + _img->getFrameHeight();
}
void Plant::follow_mouseMove()
{
	_rect.left = m_ptMouse.x - (_img->getFrameWidth() / 2);
	_rect.top = m_ptMouse.y - (_img->getFrameHeight() / 2);
}
void Plant::run_frameImg()
{
	// 여기서 프레임을 돌린다.
	_frameCount++;
	if (_frameCount >= _frameDelay)
	{
		_currentFrameX++;
		if (_currentFrameX >= _maxFrameX) { _currentFrameX = 0; }
		_frameCount = 0;
	}
}
void Plant::check_deadPlant()
{
	if (_hp < 1)
	{
		_fDeadPlant = true;
	}
}
// ================================================
// **			좀비 때릴때 쓰는 함수				 **
// ================================================
bool Plant::is_bulletHitZombies(RECT bullet)
{
	if (bullet.right >= _zombieDamagePoint.left)
	{
		return true;
	}//if: 총알의 오른쪽이 좀비의 왼쪽 포인트에 맞았을 경우
	return false;
}
bool Plant::is_plantInRect(RECT rect)
{
	RECT temp;
	if (IntersectRect(&temp, &rect, &_plantPoint))
	{
		return true;
	}
	return false;
}
// ================================================
// **				총알 컨트롤					 **
// ================================================
void Plant::shot_bullet()
{
	Bullet * bullet = new Bullet;
	_shotCount++;
	if (_shotCount >= _shotDelay)
	{
		bullet->init();
		bullet->init_bullet(_rect.right, _rect.top);
		_bullets.push_back(bullet);
		bullet = nullptr;
		// 총알을 쏘고 난 다음 콩슈터 이미지 변경
		_fPlantAttacking = false;
		change_plantImgForIdle();
		// 총알을 쏘고 난 다음 총알 카운트 초기화
		_shotCount = 0;
	}
}
void Plant::delete_bullets()
{
	_itBullets = _bullets.begin();
	for (;_itBullets != _bullets.end();)
	{
		if ((*_itBullets)->get_fDeleteBullet() == true)
		{
			(*_itBullets)->release();
			_itBullets = _bullets.erase(_itBullets);
		}
		else { _itBullets++; }
	}
}
void Plant::move_bullets()
{
	_itBullets = _bullets.begin();
	for (;_itBullets != _bullets.end(); _itBullets++)
	{
		(*_itBullets)->init_bullet(_rect.left, _rect.right);
	}
}
void Plant::update_bullets()
{
	bool fBulletHitZombie = false;
	if (_bullets.empty() == true) {}
	else
	{
		_itBullets = _bullets.begin();
		for (;_itBullets != _bullets.end();_itBullets++)
		{
			(*_itBullets)->update();
			// ================================================
			// **		총알과 좀비 충돌여부 검사				 **
			// ================================================
			if (_fZombieAtSameLine == true)
			{
				fBulletHitZombie = is_bulletHitZombies(
					(*_itBullets)->get_hitPoint());
			}
			if (fBulletHitZombie == true)
			{
				// 좀비를 때린 처리를 한다.
				_fHitZombie = true;
				_lostZombieHp += (*_itBullets)->get_damege();
				// 총알을 지운다.
				(*_itBullets)->set_fDeleteBullet(true);
			}//if: 좀비가 총알을 맞았다면
		}
	}
}
void Plant::delete_bulletsAll()
{
	_itBullets = _bullets.begin();
	for (;_itBullets != _bullets.end();)
	{
		(*_itBullets)->release();
		_itBullets = _bullets.erase(_itBullets);
	}
	_bullets.clear();
}
void Plant::draw_bullets()
{
	if (_bullets.empty() == true) {}
	else
	{
		_itBullets = _bullets.begin();
		for (;_itBullets != _bullets.end();_itBullets++)
		{
			(*_itBullets)->render();
		}
	}
}

void Plant::set_plantPoint(RECT plantPoint)
{
	_plantPoint = plantPoint;
}


Plant::Plant()
{
}
Plant::~Plant()
{
}
// ================================================
// **				식물 초기화					 **
// ================================================
void Plant::init_plant(string strKey, int x, int y)
{
	_img = IMAGEMANAGER->findImage(strKey);
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameCount = 0;
	_type = strKey;
	if (_type.compare("SunFlower") == 0)
	{
		_frameDelay = 8;
		_maxFrameX = 8;
		_maxFrameY = 1;
		_width = 600;
		_height = 75;
		_rect = RectMake(x, y, _width / _maxFrameX, _height / _maxFrameY);
	}//if: SunFlower는 width 29, height 32
	else if (_type.compare("Wallnut") == 0)
	{
		_hp = _hp * 3;
		_frameDelay = 8;
		_maxFrameX = 6;
		_maxFrameY = 1;
		_width = 450;
		_height = 75;
		_rect = RectMake(x, y, _width / _maxFrameX, _height / _maxFrameY);
	}//if: Wallnut은 width 27, height 32
	else if (_type.compare("PeaShooter") == 0)
	{
		_frameDelay = 8;
		_maxFrameX = 7;
		_maxFrameY = 1;
		_width = 525;
		_height = 75;
		_rect = RectMake(x, y, _width / _maxFrameX, _height / _maxFrameY);
	}//if: PeaShooter는 width 54, height 36
}
HRESULT Plant::init()
{
	IMAGEMANAGER->addFrameImage("SunFlower",
		"images/plants/Sunflower_Idle.bmp",
		600, 75, 8, 1, true, COLOR_MAGENTA);
	IMAGEMANAGER->addFrameImage("Wallnut",
		"images/plants/Wallnut_Idle.bmp",
		450, 75, 6, 1, true, COLOR_MAGENTA);
	IMAGEMANAGER->addFrameImage("PeaShooter",
		"images/plants/PeaShooter_Idle.bmp",
		525, 75, 7, 1, true, COLOR_MAGENTA);
	IMAGEMANAGER->addFrameImage("PeaShooter_Attack",
		"images/plants/PeaShooter_Attack.bmp",
		375, 75, 5, 1, true, COLOR_MAGENTA);
	// 마우스를 따라갈지 정하는 변수
	_fMouseFollow = false;
	// 총알 컨트롤 변수
	_shotDelay = 100 * 2;
	_shotCount = 0;
	_fZombieAtSameLine = false;
	// 좀비 때릴때 쓰는 정보
	_fHitZombie = false;
	_lostZombieHp = 0;
	// 식물 죽었는지 확인하는 변수
	_fDeadPlant = false;
	// 식물이 공격할 때 쓰는 변수
	_fPlantAttacking = false;
	return S_OK;
}
void Plant::release()
{
	_img = nullptr;
	delete_bulletsAll();
}
void Plant::update()
{
	if (_fMouseFollow == true)
	{
		follow_mouseMove();
	}//if: 마우스를 따라간다.
	else
	{
		// ================================================
		// **				총알 쏘는 부분					 **
		// ================================================
		if (_type.compare("PeaShooter") == 0 && _fZombieAtSameLine == true)
		{
			// 총알을 쏘기 전에 이미지를 바꾼다.
			// 이미지를 바꾸는 시점은 _shotCount가 
			// _shotDelay - (_frameDelay * _maxFrameX) 되는 시점
			// 그래야 총 쏘는 타이밍이 딱 맞게 된다.
			if (_fPlantAttacking == false && 
				_shotCount >= _shotDelay - (_frameDelay * _maxFrameX))
			{
				_fPlantAttacking = true;
				change_plantImgForAttack();
			}
			else
			{
				// 총알을 쏘고 난 후에 이미지를 shot_bullet에서 바꾼다.
				shot_bullet();
			}
		}
		run_frameImg();
	}
	// 식물이 죽었는지 확인
	check_deadPlant();
	// 총알 업데이트
	update_bullets();
	// 쓰지 않는 총알을 지운다.
	delete_bullets();
}
void Plant::render()
{
	_img->frameRender(getMemDC(), _rect.left, _rect.top,
		_currentFrameX, _currentFrameY);
	draw_bullets();
}

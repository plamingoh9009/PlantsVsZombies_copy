#include "stdafx.h"
#include "Plant.h"

void Plant::show_plantRect()
{
	// ��ġ�� ������ ���
	FrameRect(getMemDC(), &_plantPoint, RGB(0, 0, 0));
	// ��ü�� �� �������� ���
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
// **	�Ĺ��� ������ �� �̹��� �ٲٴ� �Լ�			 **
// ================================================
void Plant::change_plantImgForAttack()
{
	_img = IMAGEMANAGER->findImage("PeaShooter_Attack");
	// �������� ������ ���� ����
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameCount = 0;
	_frameDelay = 12;
	// _rect�� ����� ���� ����
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
	// �������� ������ ���� ����
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameCount = 0;
	// _rect�� ����� ���� ����
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
	// ���⼭ �������� ������.
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
// **			���� ������ ���� �Լ�				 **
// ================================================
bool Plant::is_bulletHitZombies(RECT bullet)
{
	if (bullet.right >= _zombieDamagePoint.left)
	{
		return true;
	}//if: �Ѿ��� �������� ������ ���� ����Ʈ�� �¾��� ���
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
// **				�Ѿ� ��Ʈ��					 **
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
		// �Ѿ��� ��� �� ���� �ὴ�� �̹��� ����
		_fPlantAttacking = false;
		change_plantImgForIdle();
		// �Ѿ��� ��� �� ���� �Ѿ� ī��Ʈ �ʱ�ȭ
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
			// **		�Ѿ˰� ���� �浹���� �˻�				 **
			// ================================================
			if (_fZombieAtSameLine == true)
			{
				fBulletHitZombie = is_bulletHitZombies(
					(*_itBullets)->get_hitPoint());
			}
			if (fBulletHitZombie == true)
			{
				// ���� ���� ó���� �Ѵ�.
				_fHitZombie = true;
				_lostZombieHp += (*_itBullets)->get_damege();
				// �Ѿ��� �����.
				(*_itBullets)->set_fDeleteBullet(true);
			}//if: ���� �Ѿ��� �¾Ҵٸ�
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
// **				�Ĺ� �ʱ�ȭ					 **
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
	}//if: SunFlower�� width 29, height 32
	else if (_type.compare("Wallnut") == 0)
	{
		_hp = _hp * 3;
		_frameDelay = 8;
		_maxFrameX = 6;
		_maxFrameY = 1;
		_width = 450;
		_height = 75;
		_rect = RectMake(x, y, _width / _maxFrameX, _height / _maxFrameY);
	}//if: Wallnut�� width 27, height 32
	else if (_type.compare("PeaShooter") == 0)
	{
		_frameDelay = 8;
		_maxFrameX = 7;
		_maxFrameY = 1;
		_width = 525;
		_height = 75;
		_rect = RectMake(x, y, _width / _maxFrameX, _height / _maxFrameY);
	}//if: PeaShooter�� width 54, height 36
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
	// ���콺�� ������ ���ϴ� ����
	_fMouseFollow = false;
	// �Ѿ� ��Ʈ�� ����
	_shotDelay = 100 * 2;
	_shotCount = 0;
	_fZombieAtSameLine = false;
	// ���� ������ ���� ����
	_fHitZombie = false;
	_lostZombieHp = 0;
	// �Ĺ� �׾����� Ȯ���ϴ� ����
	_fDeadPlant = false;
	// �Ĺ��� ������ �� ���� ����
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
	}//if: ���콺�� ���󰣴�.
	else
	{
		// ================================================
		// **				�Ѿ� ��� �κ�					 **
		// ================================================
		if (_type.compare("PeaShooter") == 0 && _fZombieAtSameLine == true)
		{
			// �Ѿ��� ��� ���� �̹����� �ٲ۴�.
			// �̹����� �ٲٴ� ������ _shotCount�� 
			// _shotDelay - (_frameDelay * _maxFrameX) �Ǵ� ����
			// �׷��� �� ��� Ÿ�̹��� �� �°� �ȴ�.
			if (_fPlantAttacking == false && 
				_shotCount >= _shotDelay - (_frameDelay * _maxFrameX))
			{
				_fPlantAttacking = true;
				change_plantImgForAttack();
			}
			else
			{
				// �Ѿ��� ��� �� �Ŀ� �̹����� shot_bullet���� �ٲ۴�.
				shot_bullet();
			}
		}
		run_frameImg();
	}
	// �Ĺ��� �׾����� Ȯ��
	check_deadPlant();
	// �Ѿ� ������Ʈ
	update_bullets();
	// ���� �ʴ� �Ѿ��� �����.
	delete_bullets();
}
void Plant::render()
{
	_img->frameRender(getMemDC(), _rect.left, _rect.top,
		_currentFrameX, _currentFrameY);
	draw_bullets();
}

#include "stdafx.h"
#include "Zombie.h"
// ================================================
// **			������ ������ ���� �Լ�				 **
// ================================================
bool Zombie::is_zombiePassByLine()
{
	if (IsRectEmpty(&_stageRect) == false)
	{
		if (_zombieHitPoint.right < _stageRect.left)
		{
			return true;
		}//if: ���� ������ �Ѿ�� ����
	}//if: �������� ��Ʈ�� �����Ѵٸ�
	return false;
}

void Zombie::init_zombieAttackRange(RECT hitPoint)
{
	int width = 10;
	_zombieAttackRange.left = hitPoint.left - width;
	_zombieAttackRange.right = hitPoint.left;
	_zombieAttackRange.top = hitPoint.top;
	_zombieAttackRange.bottom = hitPoint.bottom;
}
void Zombie::check_deadZombie()
{
	if (_hp < 1)
	{
		_fDeadZombie = true;
	}
}
// ================================================
// **				���� �Ĺ� ������				 **
// ================================================
void Zombie::attack_plant()
{
	_attackCount++;
	if (_attackCount >= _attackDelay)
	{
		_fZombieAttack = true;
		_lostPlantHp += _damage;
		_attackCount = 0;
		// ���� �Ŀ��� ���� �̹����� ������.
		change_zombieImgForWalk();
	}
}
void Zombie::change_zombieImgForAttack()
{
	_img = IMAGEMANAGER->findImage("Zombie_Attack");
	// �������� ������ ���� ����
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameDelay = 8;
	_frameCount = 0;
	// _rect�� ����� ���� ����
	_maxFrameX = 7;
	_maxFrameY = 1;
	_width = 630;
	_height = 130;
	_rect = RectMake(_rect.left, _rect.top,
		_width / _maxFrameX, _height / _maxFrameY);
}
void Zombie::change_zombieImgForWalk()
{
	_img = IMAGEMANAGER->findImage("Zombie");
	// �������� ������ ���� ����
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameDelay = 8;
	_frameCount = 0;
	// _rect�� ����� ���� ����
	_maxFrameX = 10;
	_maxFrameY = 1;
	_width = 990;
	_height = 130;
	_rect = RectMake(_rect.left, _rect.top,
		_width / _maxFrameX, _height / _maxFrameY);
}

void Zombie::init_lostPlantHp()
{
	_fZombieAttack = false;
	_lostPlantHp = 0;
}
bool Zombie::is_zombieAttack()
{
	return _fZombieAttack;
}

// ================================================
// **			���� �ڵ����� �� ��				 **
// ================================================
void Zombie::walk_toLeft()
{
	_walkCount++;
	if (_walkCount >= _walkDelay)
	{
		// ���� ������ �� ���� ���� ������Ʈ
		_rect.left -= _walkSpeed;
		_rect.right -= _walkSpeed;
		// ���� Ÿ���� ���� ������Ʈ
		_zombieHitPoint.left -= _walkSpeed;
		_zombieHitPoint.right -= _walkSpeed;
		// ���� �����Ÿ� ���� ������Ʈ
		_zombieAttackRange.left -= _walkSpeed;
		_zombieAttackRange.right -= _walkSpeed;
		_walkCount = 0;
	}
}
void Zombie::run_frame()
{
	_frameCount++;
	if (_frameCount >= _frameDelay)
	{
		_currentFrameX++;
		if (_currentFrameX >= _maxFrameX)
		{
			_currentFrameX = 0;
		}
		_frameCount = 0;
	}
}

void Zombie::show_zombieRect()
{
	FrameRect(getMemDC(), &_rect,
		CreateSolidBrush(RGB(255, 0, 0)));
}
void Zombie::show_zombieHitPoint()
{
	FrameRect(getMemDC(), &_zombieHitPoint,
		CreateSolidBrush(RGB(255, 0, 0)));
}
void Zombie::show_zombieAttackRange()
{
	FrameRect(getMemDC(), &_zombieAttackRange,
		CreateSolidBrush(RGB(255, 0, 0)));
}
// ================================================
// **		���� ��ġ �ʱ�ȭ�� ���⼭				 **
// ================================================
void Zombie::init_zombiePosition(vector<RECT> lines)
{
	// ������ ������ ���� -> �� ������ ������ �� �߿� �ϳ����� �Ѵ�.
	int range = (int)(lines.size());
	int idx = RND->getInt(range);
	int blank = WINSIZEX - lines[idx].right;
	// ��Ʈ ����
	_rect.right = lines[idx].right + (blank*2);
	_rect.bottom = lines[idx].bottom;
	_rect.left = _rect.right - _img->getFrameWidth();
	_rect.top = _rect.bottom - _img->getFrameHeight();
	// ���� �ǰ����� ����
	_zombieHitPoint = lines[idx];
	_zombieHitPoint.left += (blank * 2);
	_zombieHitPoint.right += (blank * 2);
	// ���� Ÿ������ ����
	init_zombieAttackRange(_zombieHitPoint);
}

void Zombie::hit_zombie(int lostHp)
{
	_hp -= lostHp;
}

Zombie::Zombie()
{
}
Zombie::~Zombie()
{
}
HRESULT Zombie::init()
{
	_width = 990;
	_height = 130;
	_img = IMAGEMANAGER->addFrameImage("Zombie",
		"images/zombies/Zombie_Walk.bmp", _width, _height,
		10, 1, true, COLOR_MAGENTA);
	IMAGEMANAGER->addFrameImage("Zombie_Attack",
		"images/zombies/Zombie_Attack.bmp", 630, 130,
		7, 1, true, COLOR_MAGENTA);
	_maxFrameX = 10;
	_maxFrameY = 1;
	// ������ ���� ����
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameDelay = 8;
	_frameCount = 0;
	// ���� �ȱ����� ����
	_walkDelay = 5;
	_walkCount = 0;
	_walkSpeed = 1;
	// ���� �ο�� ���� ����
	_fPlantInRange = false;
	_fDeadZombie = false;
	_fZombieAttack = false;
	_hp = 10;
	_damage = 1;
	_lostPlantHp = 0;
	_attackCount = 0;
	_attackDelay = 100;
	return S_OK;
}
void Zombie::release()
{
	_img = nullptr;
}
void Zombie::update()
{
	if (_fPlantInRange == true)
	{
		// ������ ���� �̹����� �ٲ۴�.
		if (_attackCount >= _attackDelay - (_frameDelay * (_maxFrameX)))
		{
			change_zombieImgForAttack();
		}
		attack_plant();
	}//if: �Ĺ��� ��ó�� �ִٸ�
	else
	{
		walk_toLeft();
	}//else: �Ĺ��� ��ó�� ���ٸ� ���� �ȴ´�.
	check_deadZombie();
	run_frame();
}
void Zombie::render()
{
	_img->frameRender(getMemDC(),
		_rect.left, _rect.top, _currentFrameX, _currentFrameY);
}

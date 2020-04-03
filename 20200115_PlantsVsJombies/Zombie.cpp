#include "stdafx.h"
#include "Zombie.h"
// ================================================
// **			게임을 끝내기 위한 함수				 **
// ================================================
bool Zombie::is_zombiePassByLine()
{
	if (IsRectEmpty(&_stageRect) == false)
	{
		if (_zombieHitPoint.right < _stageRect.left)
		{
			return true;
		}//if: 좀비가 라인을 넘어가는 순간
	}//if: 스테이지 렉트가 존재한다면
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
// **				좀비가 식물 때릴때				 **
// ================================================
void Zombie::attack_plant()
{
	_attackCount++;
	if (_attackCount >= _attackDelay)
	{
		_fZombieAttack = true;
		_lostPlantHp += _damage;
		_attackCount = 0;
		// 때린 후에는 원래 이미지로 돌린다.
		change_zombieImgForWalk();
	}
}
void Zombie::change_zombieImgForAttack()
{
	_img = IMAGEMANAGER->findImage("Zombie_Attack");
	// 프레임을 돌리기 위한 변수
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameDelay = 8;
	_frameCount = 0;
	// _rect를 만들기 위한 변수
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
	// 프레임을 돌리기 위한 변수
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameDelay = 8;
	_frameCount = 0;
	// _rect를 만들기 위한 변수
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
// **			좀비가 자동으로 할 일				 **
// ================================================
void Zombie::walk_toLeft()
{
	_walkCount++;
	if (_walkCount >= _walkDelay)
	{
		// 좀비를 렌더할 때 쓰는 정보 업데이트
		_rect.left -= _walkSpeed;
		_rect.right -= _walkSpeed;
		// 좀비 타격점 정보 업데이트
		_zombieHitPoint.left -= _walkSpeed;
		_zombieHitPoint.right -= _walkSpeed;
		// 좀비 사정거리 정보 업데이트
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
// **		좀비 위치 초기화는 여기서				 **
// ================================================
void Zombie::init_zombiePosition(vector<RECT> lines)
{
	// 좀비의 오른쪽 끝이 -> 각 라인의 오른쪽 끝 중에 하나여야 한다.
	int range = (int)(lines.size());
	int idx = RND->getInt(range);
	int blank = WINSIZEX - lines[idx].right;
	// 렉트 셋팅
	_rect.right = lines[idx].right + (blank*2);
	_rect.bottom = lines[idx].bottom;
	_rect.left = _rect.right - _img->getFrameWidth();
	_rect.top = _rect.bottom - _img->getFrameHeight();
	// 좀비 피격지점 셋팅
	_zombieHitPoint = lines[idx];
	_zombieHitPoint.left += (blank * 2);
	_zombieHitPoint.right += (blank * 2);
	// 좀비 타격지점 셋팅
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
	// 프레임 돌릴 정보
	_currentFrameX = 0;
	_currentFrameY = 0;
	_frameDelay = 8;
	_frameCount = 0;
	// 좀비가 걷기위한 정보
	_walkDelay = 5;
	_walkCount = 0;
	_walkSpeed = 1;
	// 좀비가 싸우기 위한 정보
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
		// 때리기 전에 이미지를 바꾼다.
		if (_attackCount >= _attackDelay - (_frameDelay * (_maxFrameX)))
		{
			change_zombieImgForAttack();
		}
		attack_plant();
	}//if: 식물이 근처에 있다면
	else
	{
		walk_toLeft();
	}//else: 식물이 근처에 없다면 그저 걷는다.
	check_deadZombie();
	run_frame();
}
void Zombie::render()
{
	_img->frameRender(getMemDC(),
		_rect.left, _rect.top, _currentFrameX, _currentFrameY);
}

#include "stdafx.h"
#include "SunPointControl.h"

// ================================================
// **			해바라기로 햇빛 만들기				 **
// ================================================
void SunPointControl::init_forSunflower()
{
	_newSunflowerAmount = 0;
	_sunflowerCount = 0;
	_useSunflowerCount = 0;
	_useSunflowerDelay = 60 * 24;
	_newSunflowerDelay = 60 * 7;
}
void SunPointControl::make_sunPointsUseSunflower()
{
	int loop = 0;
	_useSunflowerCount++;
	if (0 < _newSunflowerAmount)
	{
		if (_useSunflowerCount >= _newSunflowerDelay)
		{
			// 총 해바라기 중에서 새로 심은 해바라기만 7초
			loop = _newSunflowerAmount;
			for (int i = 0; i < loop; i++)
			{
				make_sunPoint();
			}
			_newSunflowerAmount -= loop;
			_sunflowerCount -= loop;
		}//if: 7초마다 1개씩 생성한다.
	}//if: 새로 심은 해바라기가 존재한다면
	if (0 < _sunflowerCount)
	{
		if (_useSunflowerCount >= _newSunflowerDelay)
		{
			loop = _sunflowerCount;
			for (int i = 0; i < loop; i++)
			{
				make_sunPoint();
			}
			// 해바라기 생성 카운트를 초기화한다.
			_useSunflowerCount = 0;
		}//if: 24초마다 1개씩 생성한다.
	}//if: 새로심은 해바라기 외에 다른 해바라기가 존재한다면
	else
	{
		// 해바라기 생성 카운트를 초기화한다.
		_useSunflowerCount = 0;
	}
}
// ================================================
// **				햇빛 컨트롤					 **
// ================================================
void SunPointControl::init_forMakeSunPoints()
{
	_makeSunCount = 0;
	_makeSunDelay = 60 * 5;
}
void SunPointControl::make_sunPointsDefault()
{
	_makeSunCount++;
	if (_makeSunCount >= _makeSunDelay)
	{
		make_sunPoint();
		_makeSunCount = 0;
	}
}
void SunPointControl::make_sunPoint()
{
	SunPoint * sunPoint = new SunPoint;
	sunPoint->init();
	sunPoint->init_rect();
	_sunPoints.push_back(sunPoint);
	sunPoint = nullptr;
	// 햇빛은 5~6초 사이에 랜덤하게 나온다.
	_makeSunDelay = RND->getFromIntTo(60*5, 60*6);
}
void SunPointControl::delete_sunPointsAll()
{
	_itSunPoints = _sunPoints.begin();
	for (;_itSunPoints != _sunPoints.end();)
	{
		_itSunPoints = _sunPoints.erase(_itSunPoints);
	}
	swap(_sunPoints, vSunPoints_t());
}
void SunPointControl::delete_sunPoints()
{
	_itSunPoints = _sunPoints.begin();
	for (;_itSunPoints != _sunPoints.end();)
	{
		if ((*_itSunPoints)->is_useSunPoint() == true ||
			(*_itSunPoints)->is_deleteSunPoint() == true)
		{
			_itSunPoints = _sunPoints.erase(_itSunPoints);
		}
		else
		{
			_itSunPoints++;
		}
	}
}
void SunPointControl::update_sunPoints()
{
	_itSunPoints = _sunPoints.begin();
	for (;_itSunPoints != _sunPoints.end();_itSunPoints++)
	{
		(*_itSunPoints)->update();
	}
}
void SunPointControl::draw_sunPoints()
{
	_itSunPoints = _sunPoints.begin();
	for (;_itSunPoints != _sunPoints.end();_itSunPoints++)
	{
		(*_itSunPoints)->render();
	}
}
void SunPointControl::update_sunflowerInfo(int count, int newCount)
{
	_sunflowerCount = count;
	_newSunflowerAmount += newCount;
}
// ================================================
// **				햇빛 먹을때 쓰는 함수					 **
// ================================================
bool SunPointControl::mine_sunPoints(RECT mouse)
{
	_itSunPoints = _sunPoints.begin();
	for (;_itSunPoints != _sunPoints.end(); _itSunPoints++)
	{
		if (IntersectRect(&RECT(),
			&(*_itSunPoints)->get_hitPoint(), &mouse))
		{
			(*_itSunPoints)->set_fUseSunPoint(true);
			_amount += 25;
			return true;
		}
	}
	return false;
}
void SunPointControl::init_amount()
{
	_amount = 0;
}
// ================================================
// **				디버그용 함수					 **
// ================================================
void SunPointControl::show_sunPointRects()
{
	_itSunPoints = _sunPoints.begin();
	for (;_itSunPoints != _sunPoints.end();_itSunPoints++)
	{
		(*_itSunPoints)->show_hitPoint();
	}
}

SunPointControl::SunPointControl()
{
}
SunPointControl::~SunPointControl()
{
}
HRESULT SunPointControl::init()
{
	_amount = 0;
	init_forMakeSunPoints();
	init_forSunflower();
	return S_OK;
}
void SunPointControl::release()
{
	delete_sunPointsAll();
}
void SunPointControl::update()
{
	update_sunPoints();

	if (KEYMANAGER->isOnceKeyDown(0x30))
	{
		make_sunPoint();
	}
	// 해바라기로 햇빛을 생성한다.
	make_sunPointsUseSunflower();
	// 햇빛이 자동으로 생성된다.
	make_sunPointsDefault();
	// 먹은 햇빛은 사라진다.
	delete_sunPoints();
}
void SunPointControl::render()
{
	draw_sunPoints();
}

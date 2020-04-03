#include "stdafx.h"
#include "SunPointControl.h"

// ================================================
// **			�عٶ��� �޺� �����				 **
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
			// �� �عٶ�� �߿��� ���� ���� �عٶ�⸸ 7��
			loop = _newSunflowerAmount;
			for (int i = 0; i < loop; i++)
			{
				make_sunPoint();
			}
			_newSunflowerAmount -= loop;
			_sunflowerCount -= loop;
		}//if: 7�ʸ��� 1���� �����Ѵ�.
	}//if: ���� ���� �عٶ�Ⱑ �����Ѵٸ�
	if (0 < _sunflowerCount)
	{
		if (_useSunflowerCount >= _newSunflowerDelay)
		{
			loop = _sunflowerCount;
			for (int i = 0; i < loop; i++)
			{
				make_sunPoint();
			}
			// �عٶ�� ���� ī��Ʈ�� �ʱ�ȭ�Ѵ�.
			_useSunflowerCount = 0;
		}//if: 24�ʸ��� 1���� �����Ѵ�.
	}//if: ���ν��� �عٶ�� �ܿ� �ٸ� �عٶ�Ⱑ �����Ѵٸ�
	else
	{
		// �عٶ�� ���� ī��Ʈ�� �ʱ�ȭ�Ѵ�.
		_useSunflowerCount = 0;
	}
}
// ================================================
// **				�޺� ��Ʈ��					 **
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
	// �޺��� 5~6�� ���̿� �����ϰ� ���´�.
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
// **				�޺� ������ ���� �Լ�					 **
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
// **				����׿� �Լ�					 **
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
	// �عٶ��� �޺��� �����Ѵ�.
	make_sunPointsUseSunflower();
	// �޺��� �ڵ����� �����ȴ�.
	make_sunPointsDefault();
	// ���� �޺��� �������.
	delete_sunPoints();
}
void SunPointControl::render()
{
	draw_sunPoints();
}

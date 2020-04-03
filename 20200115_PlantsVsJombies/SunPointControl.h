#pragma once
#include "gameNode.h"
#include "SunPoint.h"
class SunPointControl: public gameNode
{
private:
	// SunPoint ����
	typedef vector<SunPoint *> vSunPoints_t;
private:
	vSunPoints_t _sunPoints;
	vSunPoints_t::iterator _itSunPoints;
	// �޺� ���� ���� ����
	int _amount;
	// �޺��� �ڵ����� ���� �� ���� ����
	int _makeSunCount;
	int _makeSunDelay;
	// �޺��� ���� �� ���� �عٶ�� ����
	int _newSunflowerAmount;
	int _sunflowerCount;
	int _useSunflowerCount;
	int _useSunflowerDelay;
	int _newSunflowerDelay;
protected:
	// �عٶ��� �޺� �����
	void init_forSunflower();
	void make_sunPointsUseSunflower();
	// �޺��� �ڵ����� ����� �Լ�
	void init_forMakeSunPoints();
	void make_sunPointsDefault();
	void make_sunPoint();
	void delete_sunPointsAll();
	void delete_sunPoints();
	void update_sunPoints();
	void draw_sunPoints();
public:
	// �عٶ�� ���� �޴� �Լ�
	void update_sunflowerInfo(int count, int newCount);
	// �޺� ������ ���� �Լ�
	bool mine_sunPoints(RECT mouse);
	void init_amount();
	int get_amount() { return _amount; }
	// ����׿� �Լ�
	void show_sunPointRects();
public:
	SunPointControl();
	~SunPointControl();
	HRESULT init();
	void release();
	void update();
	void render();
};


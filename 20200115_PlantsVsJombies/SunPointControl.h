#pragma once
#include "gameNode.h"
#include "SunPoint.h"
class SunPointControl: public gameNode
{
private:
	// SunPoint 벡터
	typedef vector<SunPoint *> vSunPoints_t;
private:
	vSunPoints_t _sunPoints;
	vSunPoints_t::iterator _itSunPoints;
	// 햇빛 점수 누적 변수
	int _amount;
	// 햇빛을 자동으로 만들 때 쓰는 변수
	int _makeSunCount;
	int _makeSunDelay;
	// 햇빛을 만들 때 쓰는 해바라기 변수
	int _newSunflowerAmount;
	int _sunflowerCount;
	int _useSunflowerCount;
	int _useSunflowerDelay;
	int _newSunflowerDelay;
protected:
	// 해바라기로 햇빛 만들기
	void init_forSunflower();
	void make_sunPointsUseSunflower();
	// 햇빛을 자동으로 만드는 함수
	void init_forMakeSunPoints();
	void make_sunPointsDefault();
	void make_sunPoint();
	void delete_sunPointsAll();
	void delete_sunPoints();
	void update_sunPoints();
	void draw_sunPoints();
public:
	// 해바라기 정보 받는 함수
	void update_sunflowerInfo(int count, int newCount);
	// 햇빛 먹을때 쓰는 함수
	bool mine_sunPoints(RECT mouse);
	void init_amount();
	int get_amount() { return _amount; }
	// 디버그용 함수
	void show_sunPointRects();
public:
	SunPointControl();
	~SunPointControl();
	HRESULT init();
	void release();
	void update();
	void render();
};


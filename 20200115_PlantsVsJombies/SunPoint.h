#pragma once
#include "gameNode.h"
class SunPoint: public gameNode
{
private:
	image * _img;
	RECT _rect;
	int _width, _height;
	// 햇빛이 아래로 떨어지기 위한 변수
	int _distance;
	int _fallCount, _fallDelay, _fallSpeed;
	// 햇빛을 먹기 위한 변수
	bool _fUseSunPoint;
	RECT _hitPoint;
	// 스스로 사라지기 위한 변수
	bool _fDelete;
	int _deleteCount;
	int _deleteDelay;
protected:
	// 스스로 사라지기 위한 함수
	void delete_default();
	void move_defaultMove();
	void init_hitPoint();
public:
	void show_hitPoint();
	void init_rect();
	// 스스로 사라지기 위한 함수
	bool is_deleteSunPoint() { return _fDelete; }
	// 햇빛을 먹기 위한 함수
	bool is_useSunPoint() { return _fUseSunPoint; }
	void set_fUseSunPoint(bool fResult) { _fUseSunPoint = fResult; }
	RECT get_hitPoint() { return _hitPoint; }
public:
	SunPoint();
	~SunPoint();
	HRESULT init();
	void release();
	void update();
	void render();
};


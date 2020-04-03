#pragma once
#include "gameNode.h"
class SunPoint: public gameNode
{
private:
	image * _img;
	RECT _rect;
	int _width, _height;
	// �޺��� �Ʒ��� �������� ���� ����
	int _distance;
	int _fallCount, _fallDelay, _fallSpeed;
	// �޺��� �Ա� ���� ����
	bool _fUseSunPoint;
	RECT _hitPoint;
	// ������ ������� ���� ����
	bool _fDelete;
	int _deleteCount;
	int _deleteDelay;
protected:
	// ������ ������� ���� �Լ�
	void delete_default();
	void move_defaultMove();
	void init_hitPoint();
public:
	void show_hitPoint();
	void init_rect();
	// ������ ������� ���� �Լ�
	bool is_deleteSunPoint() { return _fDelete; }
	// �޺��� �Ա� ���� �Լ�
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


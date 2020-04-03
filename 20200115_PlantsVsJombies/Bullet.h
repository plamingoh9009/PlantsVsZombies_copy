#pragma once
#include "gameNode.h"
class Bullet: public gameNode
{
private:
	image * _img;
	RECT _rect;
	int _width;
	int _height;
	int _speed;
	int _damage;
	// 총알의 유효 영역
	RECT _hitPoint;
	// 총알 없앨때 쓰는 정보
	bool _fDeleteBullet;
protected:
	void init_hitPoint();
	void check_deleteBullet();
	void move_toRight();
public:
	// 총알 타격점 보여주는 함수
	void draw_hitPoint();
	void init_bullet(LONG x, LONG y);
	void set_fDeleteBullet(bool fResult) { _fDeleteBullet = fResult; }
	bool get_fDeleteBullet() { return _fDeleteBullet; }
	int get_damege() { return _damage; }
	RECT get_rect() { return _rect; }
	RECT get_hitPoint() { return _hitPoint; }
public:
	Bullet();
	~Bullet();
	HRESULT init();
	void release();
	void update();
	void render();
};


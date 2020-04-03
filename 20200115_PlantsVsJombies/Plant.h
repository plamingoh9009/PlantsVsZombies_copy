#pragma once
#include "gameNode.h"
#include "Bullet.h"
class Plant : public gameNode
{
private:
	typedef vector<Bullet *> vBullets_t;
private:
	// 식물 객체를 나타내는 정보
	image * _img;
	RECT _rect;
	int _width;
	int _height;
	int _maxFrameX;
	int _maxFrameY;
	string _type;
	int _currentFrameX;
	int _currentFrameY;
	int _frameDelay;
	int _frameCount;
	int _hp=3;
	// 마우스를 따라가는지 정하는 변수
	bool _fMouseFollow;
	// 식물을 심을 때 쓰는 정보
	RECT _plantPoint;
	// 총알컨트롤에 쓰는 정보
	vBullets_t _bullets;
	vBullets_t::iterator _itBullets;
	int _shotDelay;
	int _shotCount;
	bool _fZombieAtSameLine;
	RECT _zombieDamagePoint;
	// 식물 이미지를 공격용으로 바꿀때 쓰는 변수
	bool _fPlantAttacking;
	// 좀비 때릴때 쓰는 변수
	bool _fHitZombie;
	int _lostZombieHp;
	// 식물이 죽었는지 확인하는 변수
	bool _fDeadPlant;
protected:
	void follow_mouseMove();
	void run_frameImg();
	// 식물이 죽었는지 확인하는 함수
	void check_deadPlant();
	// 좀비 때릴때 쓰는 함수
	bool is_bulletHitZombies(RECT bullet);
	// 총알 컨트롤
	void shot_bullet();
	void delete_bullets();
	void move_bullets();
	void update_bullets();
	void delete_bulletsAll();
	void draw_bullets();
public:
	// 식물 초기화
	void init_plant(string strKey, int x, int y);
	void move_plant(LONG, LONG);
	// 좀비 때릴 때 쓰는 함수
	bool is_plantInRect(RECT);
	void show_plantRect();
	// 디버그 모드용 함수
	void show_bulletHitPoints();
	// 식물이 맞을 때 쓰는 함수
	void hit_plant(int lostHp);
	bool is_deadPlant() { return _fDeadPlant; }
	// 식물이 공격할 때 이미지 바꾸는 함수
	void change_plantImgForAttack();
	void change_plantImgForIdle();
	void init_lostZombieHp();
	bool is_hitZombie();
	// setter
	void set_fZombieAtSameLine(bool fResult)
	{
		_fZombieAtSameLine = fResult;
	}
	void set_zombieDamagePoint(RECT rect)
	{
		_zombieDamagePoint = rect;
	}
	void set_plantPoint(RECT);
	void set_fMouseFollow(bool flag) { _fMouseFollow = flag; }
	// getter
	string get_type() { return _type; }
	RECT get_rect() { return _rect; }
	RECT get_plantPoint() { return _plantPoint; }
	int get_lostZombieHp() { return _lostZombieHp; }
	bool get_fMouseFollow() { return _fMouseFollow; }
	bool get_fZombieAtSameLine() { return _fZombieAtSameLine; }
public:
	Plant();
	~Plant();
	HRESULT init();
	void release();
	void update();
	void render();
};


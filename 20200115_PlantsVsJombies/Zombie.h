#pragma once
#include "gameNode.h"
class Zombie: public gameNode
{
private:
	// 이미지 정보
	image * _img;
	RECT _rect;
	int _width;
	int _height;
	int _maxFrameX;
	int _maxFrameY;
	// 프레임을 재생할 정보
	int _currentFrameX;
	int _currentFrameY;
	int _frameDelay;
	int _frameCount;
	// 게임이 끝나기 위한 정보
	RECT _stageRect;
	// 좀비가 걷기 위한 정보
	int _walkDelay;
	int _walkCount;
	int _walkSpeed;
	// 좀비가 맞기 위한 정보
	bool _fDeadZombie;
	RECT _zombieHitPoint;
	int _hp;
	// 좀비가 때리기 위한 정보
	bool _fPlantInRange;
	bool _fZombieAttack;
	RECT _zombieAttackRange;
	int _damage;
	int _lostPlantHp;
	int _attackCount;
	int _attackDelay;
protected:
	void init_zombieAttackRange(RECT hitPoint);
	void check_deadZombie();
	// 좀비가 때릴 때 쓰는 함수
	void attack_plant();
	void change_zombieImgForAttack();
	void change_zombieImgForWalk();
	// 좀비가 평소에 쓰는 함수
	void walk_toLeft();
	void run_frame();
public:
	// 게임을 끝내기 위한 함수
	bool is_zombiePassByLine();
	void set_stageRect(RECT stage) { _stageRect = stage; }

	RECT get_rect() { return _rect; }
	RECT get_zombieDamagePoint() { return _zombieHitPoint; }
	RECT get_zombieAttackRange() { return _zombieAttackRange; }
	// 식물 때릴 때 쓰는 함수
	int get_lostPlantHp() { return _lostPlantHp; }
	void set_fPlantInRange(bool fResult) { _fPlantInRange = fResult; }
	void show_zombieRect();
	void show_zombieHitPoint();
	void show_zombieAttackRange();
	void init_zombiePosition(vector<RECT>);
	// 좀비가 맞을 때 쓰는 함수
	void hit_zombie(int lostHp);
	bool is_deadZombie() { return _fDeadZombie; }
	// 좀비가 때릴 때 쓰는 함수
	void init_lostPlantHp();
	bool is_zombieAttack();
public:
	Zombie();
	~Zombie();
	HRESULT init();
	void release();
	void update();
	void render();
};


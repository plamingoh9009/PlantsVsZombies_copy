#pragma once
#include "gameNode.h"
class Zombie: public gameNode
{
private:
	// �̹��� ����
	image * _img;
	RECT _rect;
	int _width;
	int _height;
	int _maxFrameX;
	int _maxFrameY;
	// �������� ����� ����
	int _currentFrameX;
	int _currentFrameY;
	int _frameDelay;
	int _frameCount;
	// ������ ������ ���� ����
	RECT _stageRect;
	// ���� �ȱ� ���� ����
	int _walkDelay;
	int _walkCount;
	int _walkSpeed;
	// ���� �±� ���� ����
	bool _fDeadZombie;
	RECT _zombieHitPoint;
	int _hp;
	// ���� ������ ���� ����
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
	// ���� ���� �� ���� �Լ�
	void attack_plant();
	void change_zombieImgForAttack();
	void change_zombieImgForWalk();
	// ���� ��ҿ� ���� �Լ�
	void walk_toLeft();
	void run_frame();
public:
	// ������ ������ ���� �Լ�
	bool is_zombiePassByLine();
	void set_stageRect(RECT stage) { _stageRect = stage; }

	RECT get_rect() { return _rect; }
	RECT get_zombieDamagePoint() { return _zombieHitPoint; }
	RECT get_zombieAttackRange() { return _zombieAttackRange; }
	// �Ĺ� ���� �� ���� �Լ�
	int get_lostPlantHp() { return _lostPlantHp; }
	void set_fPlantInRange(bool fResult) { _fPlantInRange = fResult; }
	void show_zombieRect();
	void show_zombieHitPoint();
	void show_zombieAttackRange();
	void init_zombiePosition(vector<RECT>);
	// ���� ���� �� ���� �Լ�
	void hit_zombie(int lostHp);
	bool is_deadZombie() { return _fDeadZombie; }
	// ���� ���� �� ���� �Լ�
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


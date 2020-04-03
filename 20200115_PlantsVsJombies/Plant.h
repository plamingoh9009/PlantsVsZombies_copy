#pragma once
#include "gameNode.h"
#include "Bullet.h"
class Plant : public gameNode
{
private:
	typedef vector<Bullet *> vBullets_t;
private:
	// �Ĺ� ��ü�� ��Ÿ���� ����
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
	// ���콺�� ���󰡴��� ���ϴ� ����
	bool _fMouseFollow;
	// �Ĺ��� ���� �� ���� ����
	RECT _plantPoint;
	// �Ѿ���Ʈ�ѿ� ���� ����
	vBullets_t _bullets;
	vBullets_t::iterator _itBullets;
	int _shotDelay;
	int _shotCount;
	bool _fZombieAtSameLine;
	RECT _zombieDamagePoint;
	// �Ĺ� �̹����� ���ݿ����� �ٲܶ� ���� ����
	bool _fPlantAttacking;
	// ���� ������ ���� ����
	bool _fHitZombie;
	int _lostZombieHp;
	// �Ĺ��� �׾����� Ȯ���ϴ� ����
	bool _fDeadPlant;
protected:
	void follow_mouseMove();
	void run_frameImg();
	// �Ĺ��� �׾����� Ȯ���ϴ� �Լ�
	void check_deadPlant();
	// ���� ������ ���� �Լ�
	bool is_bulletHitZombies(RECT bullet);
	// �Ѿ� ��Ʈ��
	void shot_bullet();
	void delete_bullets();
	void move_bullets();
	void update_bullets();
	void delete_bulletsAll();
	void draw_bullets();
public:
	// �Ĺ� �ʱ�ȭ
	void init_plant(string strKey, int x, int y);
	void move_plant(LONG, LONG);
	// ���� ���� �� ���� �Լ�
	bool is_plantInRect(RECT);
	void show_plantRect();
	// ����� ���� �Լ�
	void show_bulletHitPoints();
	// �Ĺ��� ���� �� ���� �Լ�
	void hit_plant(int lostHp);
	bool is_deadPlant() { return _fDeadPlant; }
	// �Ĺ��� ������ �� �̹��� �ٲٴ� �Լ�
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


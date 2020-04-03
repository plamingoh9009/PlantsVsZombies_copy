#pragma once
#include "gameNode.h"
class SeedCard: public gameNode
{
private:
	image * _img;
	RECT _rect;
	image * _plantImage;
	int _maxFrameX;
	int _maxFrameY;
	int _width;
	int _height;
	string _type;
	string _kindOfPlant;
	string _kindOfCardBack;
	// ī�� ������ Rect ��
	RECT _oneFrameRect;
	int _currentFrameX;
	int _currentFrameY;
	// ī�带 on, off �� �� ���� ����
	bool _fCardEnable;
	// ī���� ����
	int _cost;
	RECT _costRect;
	char _strCost[30];
protected:
	void delete_seedCardImg();
public:
	// ����׿� �Լ�
	void show_costRect();
	void show_rect();
	RECT get_oneFrameRect();
	RECT make_oneFrameRect();
	void show_oneFrameRect();
	void init_plantImage();
	void set_seedCard(string strKey, int x, int y);
	void set_plantImage(bool isEnable);
	// �ڽ�Ʈ ����
	int get_cost() { return _cost; }
	void set_costRect();
public:
	SeedCard();
	~SeedCard();
	HRESULT init();
	void release();
	void update();
	void render();
};


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
	// 카드 한장의 Rect 값
	RECT _oneFrameRect;
	int _currentFrameX;
	int _currentFrameY;
	// 카드를 on, off 할 때 쓰는 정보
	bool _fCardEnable;
	// 카드의 가격
	int _cost;
	RECT _costRect;
	char _strCost[30];
protected:
	void delete_seedCardImg();
public:
	// 디버그용 함수
	void show_costRect();
	void show_rect();
	RECT get_oneFrameRect();
	RECT make_oneFrameRect();
	void show_oneFrameRect();
	void init_plantImage();
	void set_seedCard(string strKey, int x, int y);
	void set_plantImage(bool isEnable);
	// 코스트 셋팅
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


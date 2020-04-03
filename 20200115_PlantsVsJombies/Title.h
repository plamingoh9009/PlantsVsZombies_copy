#pragma once
#include "gameNode.h"
class Title: public gameNode
{
private:
	image * _img;
	// 초기 위치를 잡기 위한 변수
	int _blank;
	int _initX;
	// 이미지 전환을 위한 변수
	string _type;
	RECT _mouse;
	RECT _gameStart;
	RECT _gameQuit;
protected:
	// 이미지 전환을 위한 함수
	bool is_mouseInStart();
	bool is_mouseInQuit();
	// 디버그용 함수
	void make_mouseRect();
	void show_mouseRect();
	void init_buttonRect();
	void show_buttonRect();
public:
	Title();
	~Title();
	HRESULT init();
	void release();
	void update();
	void render();
};


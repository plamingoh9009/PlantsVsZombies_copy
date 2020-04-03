#pragma once
#include "gameNode.h"
class Title: public gameNode
{
private:
	image * _img;
	// �ʱ� ��ġ�� ��� ���� ����
	int _blank;
	int _initX;
	// �̹��� ��ȯ�� ���� ����
	string _type;
	RECT _mouse;
	RECT _gameStart;
	RECT _gameQuit;
protected:
	// �̹��� ��ȯ�� ���� �Լ�
	bool is_mouseInStart();
	bool is_mouseInQuit();
	// ����׿� �Լ�
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


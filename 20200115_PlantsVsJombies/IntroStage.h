#pragma once
#include "gameNode.h"
#include "Map.h"
class IntroStage: public gameNode
{
private:
	Map * _map;
	// ������÷�Ʈ�� ���� ����
	RECT _imgWordRect;
	image * _imgWord;
	int _wordCount, _wordDelay;
	int _width, _height;
	bool _fReady, _fSet, _fPlant;
protected:
	void init_imgWord();
	void delete_imgWord();
	void change_imgWord();
	void show_imgWordRect();
public:
	IntroStage();
	~IntroStage();
	HRESULT init();
	void release();
	void update();
	void render();
};


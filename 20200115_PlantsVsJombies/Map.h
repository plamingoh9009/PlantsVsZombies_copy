#pragma once
#include "gameNode.h"
class Map: public gameNode
{
private:
	typedef vector<RECT> vLines_t;
	typedef vector<RECT> vSpaces_t;
private:
	// 가져올 이미지 변수
	image * _img;
	RECT _rect;
	string _type;
	// 맵을 쭉 보여줄 때 쓰는 변수
	bool _isShowMapAll;
	int _distance;
	const int _SPEED = 3;
	// 맵의 5개 라인 정보를 담는 벡터
	vLines_t _lines;
	vLines_t::iterator _itLines;
	// 맵에 식물을 설치할 수 있는 사각형 9x5개 벡터
	vSpaces_t _spaces;
	vSpaces_t::iterator _itSpaces;
	// 초반에 딜레이를 주기 위한 변수
	int _delay;
	// 스테이지 범위를 담는 변수
	RECT _stage;
	// 인트로를 위한 변수
	bool _fReadySetPlant;
protected:
	void init_stage();
	void change_mapImg();
	void show_mapAll();
public:
	// 인트로를 위한 함수
	void init_forIntro();
	bool is_ReadySetPlantOK() { return _fReadySetPlant; }
	void set_isShowMapAll(bool fResult) { _isShowMapAll = fResult; }

	RECT get_stage() { return _stage; }
	vector<RECT> get_spaces();
	vector<RECT>::iterator get_itSpaces();
	vector<RECT> get_lines();
	vector<RECT>::iterator get_itLines();
	// 디버그용 함수
	void show_stage();
	void show_lines();
	void delete_lines();
	void show_spaces();
	void init_spaces();
	void delete_spaces();
public:
	Map();
	~Map();
	HRESULT init();
	void release();
	void update();
	void render();
};
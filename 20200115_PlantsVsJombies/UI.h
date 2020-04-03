#pragma once
#include "gameNode.h"
#include "Map.h"
#include "SeedBank.h"
#include "FlagMeter.h"
#include "SunPointControl.h"
class UI: public gameNode
{
private:
	typedef map<string, RECT> mCardRects_t;
	typedef vector<RECT> vMapSpaces_t;
	typedef vector<RECT> vMapLines_t;
private:
	Map * _map;
	SeedBank * _bank;
	// 햇빛 컨트롤
	SunPointControl * _sunControl;
	// 시드뱅크가 가지고 있는 시드카드의 렉트맵
	mCardRects_t _cardRects;
	mCardRects_t::iterator _itCardRects;
	// 맵이 가지고 있는 공간정보 렉트벡터
	vMapSpaces_t _mapSpaces;
	vMapSpaces_t::iterator _itMapSpaces;
	// 맵이 가지고 있는 라인 렉트벡터
	vMapLines_t _mapLines;
	vMapLines_t::iterator _itMapLines;
	// 햇빛을 만들 때 쓰는 해바라기 정보
	int _newSunflowerCount;
	int _sunflowerCount;
	// 햇빛을 클릭했는지 정보
	bool _fClickSunPoint;
	// 클릭했을 때 쓰는 정보
	string _cardType;
	bool _fClickCard;
	bool _fClickStage;
	bool _fBuyCard;
	// 플래그미터 정보
	FlagMeter * _flagmeter;
	bool _fPassOverGauge;
	float _currentGauge;
	int _flagmeterCount;
	int _flagmeterDelay;
protected:
	// 카드를 살 수 있는지 없는지 정한다.
	void check_buyCard();
	// 플래그 미터를 넘길지말지 정한다.
	void check_currentGauge();
	void init_currentGauge();
	// 햇빛을 업데이트한다.
	void init_forSunflower();
	void check_clickSunPoint();
	// 클릭했는지 체크
	void check_clickCard();
	void check_clickStage();
public:
	bool is_gameWin() { return (_flagmeter->is_gameWin()); }
	// 해바라기 정보를 받는다.
	void update_sunflowerInfo(int count, int newCount);
	// 변하는 플래그 미터 정보를 처리한다.
	void change_flagmeterUseDeadZombies(float percent);
	// 플래그 미터의 정보를 넘긴다.
	bool is_passOverGauge() { return _fPassOverGauge; }
	void set_fPassOverGauge(bool fResult) { _fPassOverGauge = fResult; }
	float get_currentGauge() { return _currentGauge; }
	// 시드뱅크에 클릭여부, 카드 타입을 넘긴다.
	void set_fClickCardToBank(bool fResult);
	void set_cardTypeToBank(string cardType);
	// 클릭했을 때 정보를 주고받는다.
	void set_fBuyCard(bool fResult) { _fBuyCard = fResult; }
	bool get_fBuyCard() { return _fBuyCard; }
	void set_fClickCard(bool fResult) { _fClickCard = fResult; }
	bool get_fClickCard() { return _fClickCard; }
	void set_fClickStage(bool fResult) { _fClickStage = fResult; }
	bool get_fClickStage() { return _fClickStage; }
	string get_cardType() { return _cardType; }
	// 맵의 스테이지 렉트를 넘긴다.
	RECT get_mapStage();
	// 맵의 공간정보 렉트벡터를 넘긴다.
	vector<RECT> get_mapSpaces();
	vector<RECT>::iterator get_itMapSpaces();
	// 맵의 라인 렉트벡터를 넘긴다.
	vector<RECT> get_mapLines();
	vector<RECT>::iterator get_itMapLines();
	// 시드카드의 렉트 맵을 넘긴다.
	map<string, RECT> get_cardRects();
	map<string, RECT>::iterator get_itCardRects();

	RECT make_mouseRect();
	// 맵의 공간 벡터를 처리한다.
	void show_mapSpaces();
	void init_mapSpaces();
	void delete_mapSpaces();
	// 맵의 라인 벡터를 처리한다.
	void show_mapLines();
	void init_mapLines();
	void delete_mapLines();
	// 시드카드의 렉트 맵을 처리한다.
	void show_cardRects();
	void init_cardRects();
	void delete_cardRects();
public:
	UI();
	~UI();
	HRESULT init();
	void release();
	void update();
	void render();
};


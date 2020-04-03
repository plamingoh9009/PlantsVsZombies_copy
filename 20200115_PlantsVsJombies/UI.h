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
	// �޺� ��Ʈ��
	SunPointControl * _sunControl;
	// �õ��ũ�� ������ �ִ� �õ�ī���� ��Ʈ��
	mCardRects_t _cardRects;
	mCardRects_t::iterator _itCardRects;
	// ���� ������ �ִ� �������� ��Ʈ����
	vMapSpaces_t _mapSpaces;
	vMapSpaces_t::iterator _itMapSpaces;
	// ���� ������ �ִ� ���� ��Ʈ����
	vMapLines_t _mapLines;
	vMapLines_t::iterator _itMapLines;
	// �޺��� ���� �� ���� �عٶ�� ����
	int _newSunflowerCount;
	int _sunflowerCount;
	// �޺��� Ŭ���ߴ��� ����
	bool _fClickSunPoint;
	// Ŭ������ �� ���� ����
	string _cardType;
	bool _fClickCard;
	bool _fClickStage;
	bool _fBuyCard;
	// �÷��׹��� ����
	FlagMeter * _flagmeter;
	bool _fPassOverGauge;
	float _currentGauge;
	int _flagmeterCount;
	int _flagmeterDelay;
protected:
	// ī�带 �� �� �ִ��� ������ ���Ѵ�.
	void check_buyCard();
	// �÷��� ���͸� �ѱ������� ���Ѵ�.
	void check_currentGauge();
	void init_currentGauge();
	// �޺��� ������Ʈ�Ѵ�.
	void init_forSunflower();
	void check_clickSunPoint();
	// Ŭ���ߴ��� üũ
	void check_clickCard();
	void check_clickStage();
public:
	bool is_gameWin() { return (_flagmeter->is_gameWin()); }
	// �عٶ�� ������ �޴´�.
	void update_sunflowerInfo(int count, int newCount);
	// ���ϴ� �÷��� ���� ������ ó���Ѵ�.
	void change_flagmeterUseDeadZombies(float percent);
	// �÷��� ������ ������ �ѱ��.
	bool is_passOverGauge() { return _fPassOverGauge; }
	void set_fPassOverGauge(bool fResult) { _fPassOverGauge = fResult; }
	float get_currentGauge() { return _currentGauge; }
	// �õ��ũ�� Ŭ������, ī�� Ÿ���� �ѱ��.
	void set_fClickCardToBank(bool fResult);
	void set_cardTypeToBank(string cardType);
	// Ŭ������ �� ������ �ְ�޴´�.
	void set_fBuyCard(bool fResult) { _fBuyCard = fResult; }
	bool get_fBuyCard() { return _fBuyCard; }
	void set_fClickCard(bool fResult) { _fClickCard = fResult; }
	bool get_fClickCard() { return _fClickCard; }
	void set_fClickStage(bool fResult) { _fClickStage = fResult; }
	bool get_fClickStage() { return _fClickStage; }
	string get_cardType() { return _cardType; }
	// ���� �������� ��Ʈ�� �ѱ��.
	RECT get_mapStage();
	// ���� �������� ��Ʈ���͸� �ѱ��.
	vector<RECT> get_mapSpaces();
	vector<RECT>::iterator get_itMapSpaces();
	// ���� ���� ��Ʈ���͸� �ѱ��.
	vector<RECT> get_mapLines();
	vector<RECT>::iterator get_itMapLines();
	// �õ�ī���� ��Ʈ ���� �ѱ��.
	map<string, RECT> get_cardRects();
	map<string, RECT>::iterator get_itCardRects();

	RECT make_mouseRect();
	// ���� ���� ���͸� ó���Ѵ�.
	void show_mapSpaces();
	void init_mapSpaces();
	void delete_mapSpaces();
	// ���� ���� ���͸� ó���Ѵ�.
	void show_mapLines();
	void init_mapLines();
	void delete_mapLines();
	// �õ�ī���� ��Ʈ ���� ó���Ѵ�.
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


#pragma once
#include "gameNode.h"
#include "SeedCard.h"			
class SeedBank: public gameNode
{
private:
	typedef vector<string> vPlantName_t;
	typedef map<string, SeedCard *> mSeedCards_t;
	typedef map<string, int> mCardCosts_t;
private:
	image * _img;
	RECT _rect;
	// �õ��ũ�� ��ȿ���� ��Ʈ
	RECT _space[6];
	// �Ĺ� �̸� ����
	vPlantName_t _plantName;
	vPlantName_t::iterator _itPlantName;
	// �õ�ī�� ��
	mSeedCards_t _seedCards;
	mSeedCards_t::iterator _itSeedCards;
	// ī�带 on, off �Ҷ� ���� ����
	bool _fClickCard;
	string _cardType;
	// �޺� ����Ʈ�� ����� �� ���� ����
	RECT _sunPointRect;
	char _strSunPoint[128];
	int _sunPoint;
	// ī�带 �� �� ���� ����
	mCardCosts_t _cardCosts;
	mCardCosts_t::iterator _itCardCosts;
	bool _fBuyCard;
	int _buyCost;
protected:
	void delete_plantImage();
	// �Ĺ��̸� ���� �Լ�
	void init_plantName();
	void delete_plantName();
	// �õ�ī�� �� �Լ�
	void draw_seedCards();
	void init_seedCards();
	void delete_seedCards();
	// �õ�ī�� �ڽ�Ʈ �ʱ�ȭ
	void init_cardCosts();
	void delete_cardCosts();
	map<string, int> get_cardCosts() { return _cardCosts; }
	map<string, int>::iterator get_itCardCosts() { return _itCardCosts; }
	// �޺� ����â ��Ʈ��
	void init_sunPoint();
	void draw_sunPoint();
public:
	// ī�带 �� �� �ִ��� �˻�
	bool could_buyCard(string type);
	void set_buyCard(bool fResult) { _fBuyCard = fResult; }
	void buy_seedCard();
	// �õ�ī�� �ѱ��
	map<string, SeedCard *> get_seedCards();
	map<string, SeedCard *>::iterator get_itSeedCards();
	void set_fClickCard(bool fResult) { _fClickCard = fResult; }
	void set_cardType(string cardType) { _cardType = cardType; }
	// �޺� ���� ��Ʈ��
	void add_sunPoint(int amount);
	// ����׸� ���� �Լ�
	void show_costRects();
	void show_sunPointRect();
	void show_seedCardRects();
	void show_space();
	void init_space();
public:
	SeedBank();
	~SeedBank();
	HRESULT init();
	void release();
	void update();
	void render();
};

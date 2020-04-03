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
	// 시드뱅크의 유효공간 렉트
	RECT _space[6];
	// 식물 이름 벡터
	vPlantName_t _plantName;
	vPlantName_t::iterator _itPlantName;
	// 시드카드 맵
	mSeedCards_t _seedCards;
	mSeedCards_t::iterator _itSeedCards;
	// 카드를 on, off 할때 쓰는 정보
	bool _fClickCard;
	string _cardType;
	// 햇빛 포인트를 출력할 때 쓰는 정보
	RECT _sunPointRect;
	char _strSunPoint[128];
	int _sunPoint;
	// 카드를 살 때 쓰는 정보
	mCardCosts_t _cardCosts;
	mCardCosts_t::iterator _itCardCosts;
	bool _fBuyCard;
	int _buyCost;
protected:
	void delete_plantImage();
	// 식물이름 벡터 함수
	void init_plantName();
	void delete_plantName();
	// 시드카드 맵 함수
	void draw_seedCards();
	void init_seedCards();
	void delete_seedCards();
	// 시드카드 코스트 초기화
	void init_cardCosts();
	void delete_cardCosts();
	map<string, int> get_cardCosts() { return _cardCosts; }
	map<string, int>::iterator get_itCardCosts() { return _itCardCosts; }
	// 햇빛 점수창 컨트롤
	void init_sunPoint();
	void draw_sunPoint();
public:
	// 카드를 살 수 있는지 검사
	bool could_buyCard(string type);
	void set_buyCard(bool fResult) { _fBuyCard = fResult; }
	void buy_seedCard();
	// 시드카드 넘기기
	map<string, SeedCard *> get_seedCards();
	map<string, SeedCard *>::iterator get_itSeedCards();
	void set_fClickCard(bool fResult) { _fClickCard = fResult; }
	void set_cardType(string cardType) { _cardType = cardType; }
	// 햇빛 점수 컨트롤
	void add_sunPoint(int amount);
	// 디버그를 위한 함수
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

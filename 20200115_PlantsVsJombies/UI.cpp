#include "stdafx.h"
#include "UI.h"

void UI::check_buyCard()
{
	_fBuyCard = _bank->could_buyCard(_cardType);
	if (_fBuyCard == true)
	{
		_bank->set_buyCard(false);
		_bank->buy_seedCard();
	}
	else
	{
		_fClickCard = false;
	}
}
// ================================================
// **		플래그미터를 넘겨주기 위한 함수			 **
// ================================================
void UI::check_currentGauge()
{
	_flagmeterCount++;
	if (_flagmeterCount >= _flagmeterDelay)
	{
		_fPassOverGauge = true;
		_currentGauge = _flagmeter->get_currentGauge();
		_flagmeterCount = 0;
	}
}
void UI::init_currentGauge()
{
	_fPassOverGauge = false;
	_currentGauge = 0;
	_flagmeterCount = 0;
	_flagmeterDelay = 20;
}
void UI::init_forSunflower()
{
	_newSunflowerCount = 0;
	_sunflowerCount = 0;
}
// ================================================
// **			햇빛을 업데이트					 **
// ================================================
void UI::check_clickSunPoint()
{
	_fClickSunPoint = _sunControl->mine_sunPoints(make_mouseRect());
	if (_fClickSunPoint == true)
	{
		_bank->add_sunPoint(_sunControl->get_amount());
		_sunControl->init_amount();
		_fClickSunPoint = false;
	}
}

void UI::set_fClickCardToBank(bool fResult)
{
	_bank->set_fClickCard(fResult);
}
void UI::set_cardTypeToBank(string cardType)
{
	_bank->set_cardType(cardType);
}
// ================================================
// **		맵의 정보를 넘겨주기 위한 함수			 **
// ================================================
RECT UI::get_mapStage()
{
	return (_map->get_stage());
}
vector<RECT> UI::get_mapSpaces()
{
	return vector<RECT>(_mapSpaces);
}
vector<RECT>::iterator UI::get_itMapSpaces()
{
	return vector<RECT>::iterator(_itMapSpaces);
}
vector<RECT> UI::get_mapLines()
{
	return vector<RECT>(_mapLines);
}
vector<RECT>::iterator UI::get_itMapLines()
{
	return vector<RECT>::iterator(_itMapLines);
}
map<string, RECT> UI::get_cardRects()
{
	return map<string, RECT>(_cardRects);
}
map<string, RECT>::iterator UI::get_itCardRects()
{
	return map<string, RECT>::iterator(_itCardRects);
}

void UI::update_sunflowerInfo(int count, int newCount)
{
	_sunControl->update_sunflowerInfo(count, newCount);
}
// ================================================
// **	좀비 죽으면 플래그미터를 지나게 하는 부분		 **
// ================================================
void UI::change_flagmeterUseDeadZombies(float percent)
{
	_flagmeter->move_flagmeter(percent);
}

RECT UI::make_mouseRect()
{
	return RectMake(m_ptMouse.x, m_ptMouse.y, 5, 5);
}
// ================================================
// **		클릭했을 때 체크하는 함수				 **
// ================================================
void UI::check_clickCard()
{
	// 마우스 위치를 Rect 형태로 가져온다.
	RECT mouseRect = make_mouseRect();
	_itCardRects = _cardRects.begin();
	for (;_itCardRects != _cardRects.end();_itCardRects++)
	{
		if (IntersectRect(&RECT(), &mouseRect, &_itCardRects->second))
		{
			_fClickCard = true;
			_cardType = _itCardRects->first;
		}//if: 내 마우스가 카드를 누르면
	}//for: 식물 맵을 돌린다.
}
void UI::check_clickStage()
{
	RECT mouse = make_mouseRect();
	if (IntersectRect(&RECT(), &mouse, &_map->get_stage()))
	{
		_fClickStage = true;
	}
}
// ================================================
// **			맵의 공간 정보 처리함수				 **
// ================================================
void UI::show_mapSpaces()
{
	_itMapSpaces = _mapSpaces.begin();
	for (;_itMapSpaces != _mapSpaces.end();_itMapSpaces++)
	{
		FrameRect(getMemDC(), &(*_itMapSpaces), RGB(0, 0, 0));
	}
}
void UI::init_mapSpaces()
{
	// 여기서 맵의 공간 벡터를 가져와서 내 Rect vector를 만든다.
	_mapSpaces = _map->get_spaces();
	_itMapSpaces = _map->get_itSpaces();
}
void UI::delete_mapSpaces()
{
	_itMapSpaces = _mapSpaces.begin();
	for (;_itMapSpaces != _mapSpaces.end();)
	{
		_itMapSpaces = _mapSpaces.erase(_itMapSpaces);
	}
	swap(vMapSpaces_t(), _mapSpaces);
}
// ================================================
// **			맵의 라인 정보 처리함수				 **
// ================================================
void UI::show_mapLines()
{
	_itMapLines = _mapLines.begin();
	for (;_itMapLines != _mapLines.end();_itMapLines++)
	{
		FrameRect(getMemDC(), &(*_itMapLines),
			CreateSolidBrush(RGB(64, 0, 64)));
	}
}
void UI::init_mapLines()
{
	// 여기서 맵의 라인 정보를 가져와서 내 RECT vector를 만든다.
	_mapLines = _map->get_lines();
	_itMapLines = _map->get_itLines();
}
void UI::delete_mapLines()
{
	// 렉트는 동적할당 하지 않았기 때문에 erase만 한다.
	_itMapLines = _mapLines.begin();
	for (;_itMapLines != _mapLines.end();)
	{
		_itMapLines = _mapLines.erase(_itMapLines);
	}
	swap(vMapLines_t(), _mapLines);
}
// ================================================
// **			카드 공간 정보 처리함수				 **
// ================================================
void UI::show_cardRects()
{
	_itCardRects = _cardRects.begin();
	for (;_itCardRects != _cardRects.end();_itCardRects++)
	{
		FrameRect(getMemDC(), &_itCardRects->second,
			RGB(0, 0, 0));
	}
}
void UI::init_cardRects()
{
	// 여기서 시드뱅크의 카드벡터를 가져와서 내 Rect map을 만든다.
	map<string, SeedCard*> seedCards = _bank->get_seedCards();
	map<string, SeedCard*>::iterator itSeedCards =
		_bank->get_itSeedCards();
	string strKey;
	RECT rect;
	itSeedCards = seedCards.begin();
	for (;itSeedCards != seedCards.end();itSeedCards++)
	{
		strKey = itSeedCards->first;
		rect = itSeedCards->second->get_oneFrameRect();
		_cardRects.insert(make_pair(strKey, rect));
	}
}
void UI::delete_cardRects()
{
	_itCardRects = _cardRects.begin();
	for (;_itCardRects != _cardRects.end();)
	{
		_cardRects.erase(_itCardRects++);
	}
	_cardRects.clear();
}

UI::UI()
{
}
UI::~UI()
{
}
HRESULT UI::init()
{
	_map = new Map;
	_map->init();
	_bank = new SeedBank;
	_bank->init();
	_flagmeter = new FlagMeter;
	_flagmeter->init();
	// 햇빛을 초기화한다.
	_sunControl = new SunPointControl;
	_sunControl->init();
	// 시드카드 rect 벡터를 초기화한다.
	init_cardRects();
	// 맵의 공간 벡터를 초기화한다.
	init_mapSpaces();
	// 맵의 라인 벡터를 초기화한다.
	init_mapLines();
	// 햇빛을 만드는 정보
	bool _fClickSunPoint = false;
	init_forSunflower();
	// 식물 심을 때 쓰는 정보
	string _cardType = "";
	bool _fClickCard = false;
	bool _fCilckStage = false;
	// 플래그미터 정보
	init_currentGauge();
	_fBuyCard = false;
	return S_OK;
}
void UI::release()
{
	_map->release();
	_map = nullptr;
	_bank->release();
	_bank = nullptr;
	_flagmeter->release();
	_flagmeter = nullptr;
	_sunControl->release();
	_sunControl = nullptr;
	// 카드와 맵 Rect 벡터를 지운다.
	delete_cardRects();
	delete_mapSpaces();
	delete_mapLines();
}
void UI::update()
{
	_map->update();
	_bank->update();
	_flagmeter->update();
	check_currentGauge();
	_sunControl->update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		check_clickSunPoint();
		check_clickCard();
		check_clickStage();
	}
	// 카드를 살지, 말지 정한다.
	if (_fClickCard == true)
	{
		check_buyCard();
	}
}
void UI::render()
{
	_map->render();
	_bank->render();
	_flagmeter->render();
	_sunControl->render();

	if (KEYMANAGER->isToggleKey(0x32))
	{
		_bank->show_seedCardRects();
		_bank->show_sunPointRect();
		_bank->show_costRects();
		_sunControl->show_sunPointRects();
	}
	//if: 2번을 누르면
	if (KEYMANAGER->isToggleKey(0X31))
	{
		_map->show_stage();
		show_mapSpaces();
		show_mapLines();
	}//if: 1번을 누르면
}
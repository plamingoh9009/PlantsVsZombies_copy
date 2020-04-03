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
// **		�÷��׹��͸� �Ѱ��ֱ� ���� �Լ�			 **
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
// **			�޺��� ������Ʈ					 **
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
// **		���� ������ �Ѱ��ֱ� ���� �Լ�			 **
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
// **	���� ������ �÷��׹��͸� ������ �ϴ� �κ�		 **
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
// **		Ŭ������ �� üũ�ϴ� �Լ�				 **
// ================================================
void UI::check_clickCard()
{
	// ���콺 ��ġ�� Rect ���·� �����´�.
	RECT mouseRect = make_mouseRect();
	_itCardRects = _cardRects.begin();
	for (;_itCardRects != _cardRects.end();_itCardRects++)
	{
		if (IntersectRect(&RECT(), &mouseRect, &_itCardRects->second))
		{
			_fClickCard = true;
			_cardType = _itCardRects->first;
		}//if: �� ���콺�� ī�带 ������
	}//for: �Ĺ� ���� ������.
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
// **			���� ���� ���� ó���Լ�				 **
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
	// ���⼭ ���� ���� ���͸� �����ͼ� �� Rect vector�� �����.
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
// **			���� ���� ���� ó���Լ�				 **
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
	// ���⼭ ���� ���� ������ �����ͼ� �� RECT vector�� �����.
	_mapLines = _map->get_lines();
	_itMapLines = _map->get_itLines();
}
void UI::delete_mapLines()
{
	// ��Ʈ�� �����Ҵ� ���� �ʾұ� ������ erase�� �Ѵ�.
	_itMapLines = _mapLines.begin();
	for (;_itMapLines != _mapLines.end();)
	{
		_itMapLines = _mapLines.erase(_itMapLines);
	}
	swap(vMapLines_t(), _mapLines);
}
// ================================================
// **			ī�� ���� ���� ó���Լ�				 **
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
	// ���⼭ �õ��ũ�� ī�庤�͸� �����ͼ� �� Rect map�� �����.
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
	// �޺��� �ʱ�ȭ�Ѵ�.
	_sunControl = new SunPointControl;
	_sunControl->init();
	// �õ�ī�� rect ���͸� �ʱ�ȭ�Ѵ�.
	init_cardRects();
	// ���� ���� ���͸� �ʱ�ȭ�Ѵ�.
	init_mapSpaces();
	// ���� ���� ���͸� �ʱ�ȭ�Ѵ�.
	init_mapLines();
	// �޺��� ����� ����
	bool _fClickSunPoint = false;
	init_forSunflower();
	// �Ĺ� ���� �� ���� ����
	string _cardType = "";
	bool _fClickCard = false;
	bool _fCilckStage = false;
	// �÷��׹��� ����
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
	// ī��� �� Rect ���͸� �����.
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
	// ī�带 ����, ���� ���Ѵ�.
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
	//if: 2���� ������
	if (KEYMANAGER->isToggleKey(0X31))
	{
		_map->show_stage();
		show_mapSpaces();
		show_mapLines();
	}//if: 1���� ������
}
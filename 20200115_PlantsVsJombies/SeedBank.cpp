#include "stdafx.h"
#include "SeedBank.h"
// ================================================
// **		ī�带 �� �� �ִ��� �˻�				 **
// ================================================
bool SeedBank::could_buyCard(string type)
{
	_itCardCosts = _cardCosts.begin();
	for (;_itCardCosts != _cardCosts.end();_itCardCosts++)
	{
		if (_itCardCosts->first.compare(type) == 0)
		{
			if (_itCardCosts->second <= _sunPoint)
			{
				_fBuyCard = true;
				_buyCost = _itCardCosts->second;
				return true;
			}//if: ������ ������ �� �ִٸ�
		}//if: ���� �� ī����
	}
	return false;
}
void SeedBank::buy_seedCard()
{
	_sunPoint -= _buyCost;
	_buyCost = 0;
	wsprintf(_strSunPoint, "%d", _sunPoint);
}
map<string, SeedCard*> SeedBank::get_seedCards()
{
	return map<string, SeedCard*>(_seedCards);
}
map<string, SeedCard*>::iterator SeedBank::get_itSeedCards()
{
	return map<string, SeedCard*>::iterator(_itSeedCards);
}

void SeedBank::delete_plantImage()
{
	IMAGEMANAGER->deleteImage("SunFlower_Disable");
	IMAGEMANAGER->deleteImage("SunFlower_Enable");
	IMAGEMANAGER->deleteImage("Wallnut_Disable");
	IMAGEMANAGER->deleteImage("Wallnut_Enable");
	IMAGEMANAGER->deleteImage("PeaShooter_Disable");
	IMAGEMANAGER->deleteImage("PeaShooter_Enable");
}
void SeedBank::init_plantName()
{
	_plantName.push_back("SunFlower");
	_plantName.push_back("PeaShooter");
	_plantName.push_back("Wallnut");
}
void SeedBank::delete_plantName()
{
	_itPlantName = _plantName.begin();
	for (;_itPlantName != _plantName.end();)
	{
		_itPlantName = _plantName.erase(_itPlantName);
	}
	_plantName.clear();
}

void SeedBank::draw_seedCards()
{
	_itSeedCards = _seedCards.begin();
	for (;_itSeedCards != _seedCards.end(); _itSeedCards++)
	{
		_itSeedCards->second->render();
	}
}
void SeedBank::init_seedCards()
{
	SeedCard * seedCard;
	int size = (int)(_plantName.size());
	for (int i = 0;i < size;i++)
	{
		seedCard = new SeedCard;
		seedCard->init();
		seedCard->set_seedCard(_plantName[i], 
			_space[i].left, _space[i].top);
		seedCard->set_costRect();
		// ���⼭ �õ�ī�� �ʿ� insert
		_seedCards.insert(
			make_pair(_plantName[i], seedCard)
		);
		seedCard = nullptr;
	}
}
void SeedBank::delete_seedCards()
{
	_itSeedCards = _seedCards.begin();
	for (;_itSeedCards != _seedCards.end();)
	{
		_itSeedCards->second->release();
		_seedCards.erase(_itSeedCards++);
	}
	_seedCards.clear();
}
// ================================================
// **			ī�� �ڽ�Ʈ �� �Լ�				 **
// ================================================
void SeedBank::init_cardCosts()
{
	string type;
	int cost;
	_fBuyCard = false;
	_buyCost = 0;
	_itSeedCards = _seedCards.begin();
	for (;_itSeedCards != _seedCards.end();_itSeedCards++)
	{
		type = _itSeedCards->first;
		cost = _itSeedCards->second->get_cost();
		_cardCosts.insert(make_pair(type, cost));
	}
}
void SeedBank::delete_cardCosts()
{
	_itCardCosts = _cardCosts.begin();
	for (;_itCardCosts != _cardCosts.end();)
	{
		_itCardCosts = _cardCosts.erase(_itCardCosts);
	}
	swap(_cardCosts, mCardCosts_t());
}
// ================================================
// **				�޺� ��Ʈ��					 **
// ================================================
void SeedBank::init_sunPoint()
{
	_sunPointRect.left = _rect.left + 14;
	_sunPointRect.top = _rect.top + 64;
	_sunPointRect.right = _sunPointRect.left + 50;
	_sunPointRect.bottom = _sunPointRect.top + 18;
	_sunPoint = 0;
	wsprintf(_strSunPoint, "%d", _sunPoint);
}
void SeedBank::draw_sunPoint()
{
	TextOut(getMemDC(), _sunPointRect.left, _sunPointRect.top,
		_strSunPoint, (int)(strlen(_strSunPoint)));
}
void SeedBank::add_sunPoint(int amount)
{
	_sunPoint += amount;
	wsprintf(_strSunPoint, "%d", _sunPoint);
}
void SeedBank::show_costRects()
{
	_itSeedCards = _seedCards.begin();
	for (;_itSeedCards != _seedCards.end();_itSeedCards++)
	{
		_itSeedCards->second->show_costRect();
	}
}
// ================================================
// **			����׸� ���� �Լ�					 **
// ================================================
void SeedBank::show_sunPointRect()
{
	FrameRect(getMemDC(), &_sunPointRect,
		CreateSolidBrush(RGB(0, 0, 0)));
}
void SeedBank::show_seedCardRects()
{
	_itSeedCards = _seedCards.begin();
	for (;_itSeedCards != _seedCards.end();_itSeedCards++)
	{
		_itSeedCards->second->show_oneFrameRect();
	}
}
void SeedBank::show_space()
{
	for (int i = 0; i < 6; i++)
	{
		Rectangle(getMemDC(), _space[i].left, _space[i].top,
			_space[i].right, _space[i].bottom);
	}
}
void SeedBank::init_space()
{
	int seedCardWidth = 50;
	int seedCardHeight = 70;
	int blankWidth = (int)(seedCardWidth * 0.192);
	int initX = 78 + _rect.left + (int)(blankWidth * 0.5);
	int initY = 8 + _rect.top;
	int currentX, currentY;

	currentY = initY;
	currentX = initX;
	for (int i = 0; i < 6; i++)
	{
		_space[i] = RectMake(currentX, currentY,
			seedCardWidth, seedCardHeight);
		currentX = currentX + seedCardWidth + blankWidth;
	}
}

SeedBank::SeedBank()
{
}
SeedBank::~SeedBank()
{
}
HRESULT SeedBank::init()
{
	// �õ��ũ �̹����� �ʱ�ȭ
	_rect = RectMake(20, 0, 446, 87);
	_img = IMAGEMANAGER->addImage("SeedBank", "images/SeedBank.bmp",
		_rect.right - _rect.left, _rect.bottom - _rect.top,
		false, COLOR_MAGENTA);
	// �õ��ũ ��Ʈ�� �ʱ�ȭ
	init_space();
	// �Ĺ� �̸� ���͸� �ʱ�ȭ
	init_plantName();
	// �õ�ī�� ���͸� �ʱ�ȭ
	init_seedCards();
	// �޺� ����â �ʱ�ȭ
	init_sunPoint();
	// ī�� �ڽ�Ʈ �ʱ�ȭ
	init_cardCosts();
	return S_OK;
}
void SeedBank::release()
{
	IMAGEMANAGER->deleteImage("SeedBank");
	// �Ĺ��̸� ���͸� ����
	delete_plantName();
	delete_plantImage();
	// �õ�ī�� ���͸� ������
	IMAGEMANAGER->deleteImage("SeedCard");
	delete_seedCards();
	// ī�� �ڽ�Ʈ ������
	delete_cardCosts();
}
void SeedBank::update()
{

}
void SeedBank::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) {}
	else
	{
		IMAGEMANAGER->render("SeedBank", getMemDC(), _rect.left, _rect.top);
		draw_sunPoint();
		draw_seedCards();
	}//else: tab Ű�� ������ �ʾ��� ��, �õ��ũ�� ����
}

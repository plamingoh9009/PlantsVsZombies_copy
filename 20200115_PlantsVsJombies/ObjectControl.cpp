#include "stdafx.h"
#include "ObjectControl.h"

// ================================================
// **				���� ��Ʈ��					 **
// ================================================
void ObjectControl::init_forStageLevel()
{
	_stageLevel = 1;
	_maxZombies = 30 * _stageLevel;
	_deadZombieCount = 0;
	_pastGaugePercentAmount = 0;

	_currentGauge = 0;
	_currentZombies = 0;
	_makeZombieCount = 0;
	_makeZombieDelay = 60 * 4;
}
// ================================================
// **			���� ����� �κ�					 **
// ================================================
void ObjectControl::make_zombieAtStage()
{
	_makeZombieCount++;
	if (_makeZombieCount >= _makeZombieDelay)
	{
		if (0 < _currentGauge)
		{
			make_zombie();
			_makeZombieDelay = RND->getFromIntTo(60 * 5, 60 * 10);
		}
		_makeZombieCount = 0;
	}
}
void ObjectControl::make_zombie()
{
	Zombie * zombie = new Zombie;
	zombie->init();
	zombie->init_zombiePosition(_mapLines);
	zombie->set_stageRect(_stageRect);
	_zombies.push_back(zombie);
}
void ObjectControl::delete_zombiesAll()
{
	_itZombies = _zombies.begin();
	for (;_itZombies != _zombies.end();)
	{
		(*_itZombies)->release();
		_itZombies = _zombies.erase(_itZombies);
	}
	swap(vZombies_t(), _zombies);
}
// ================================================
// **				���� �׾��� ��					 **
// ================================================
void ObjectControl::delete_deadZombies()
{
	_itZombies = _zombies.begin();
	for (;_itZombies != _zombies.end();)
	{
		if ((*_itZombies)->is_deadZombie() == true)
		{
			(*_itZombies)->release();
			_itZombies = _zombies.erase(_itZombies);
			_deadZombieCount++;
		}
		else
		{
			_itZombies++;
		}
	}
}
void ObjectControl::update_zombies()
{
	bool fPlantInAttackRange = false;
	_itZombies = _zombies.begin();
	for (;_itZombies != _zombies.end();_itZombies++)
	{
		(*_itZombies)->update();
		// ================================================
		// **				�Ĺ��� �浹üũ				 **
		// ================================================
		fPlantInAttackRange = is_plantInAttackRange(
			(*_itZombies)->get_zombieAttackRange());
		// ================================================
		// **				���� �Ĺ� ����				 **
		// ================================================
		if (fPlantInAttackRange == true)
		{
			(*_itZombies)->set_fPlantInRange(true);
			attack_zombieToPlant(
				(*_itZombies)->get_zombieAttackRange(),
				(*_itZombies)->get_lostPlantHp());
		}//if: �Ĺ��� �����Ÿ� �ȿ� �ִٸ�
		else
		{
			// fPlantInRange�� �ʱ�ȭ�Ѵ�.
			(*_itZombies)->set_fPlantInRange(false);
		}//else: �Ĺ��� �����Ÿ� �ۿ� �ִٸ�
		if ((*_itZombies)->is_zombieAttack() == true)
		{
			// ���� ���� �������� �ʱ�ȭ�Ѵ�.
			(*_itZombies)->init_lostPlantHp();
		}//if: ���� ������ �ߴٸ�

		if ((*_itZombies)->is_zombiePassByLine() == true)
		{
			_fZombiePassByLine = (*_itZombies)->is_zombiePassByLine();
		}
	}//for: ��� ���� ��ġ
}
void ObjectControl::draw_zombies()
{
	_itZombies = _zombies.begin();
	for (;_itZombies != _zombies.end();_itZombies++)
	{
		(*_itZombies)->render();
	}
}
// ================================================
// **			UI ���� Setter �Լ�				 **
// ================================================
void ObjectControl::set_mapSpaces(vector<RECT> mapSpaces)
{
	_mapSpaces = mapSpaces;
}
void ObjectControl::set_itMapSpaces(vector<RECT>::iterator itMapSpaces)
{
	_itMapSpaces = itMapSpaces;
}
void ObjectControl::set_mapLines(vector<RECT> mapLines)
{
	_mapLines = mapLines;
}
void ObjectControl::set_itMapLines(vector<RECT>::iterator itMapLines)
{
	_itMapLines = itMapLines;
}
void ObjectControl::set_cardRects(map<string, RECT> rects)
{
	_cardRects = rects;
}
void ObjectControl::set_itCardRects(map<string, RECT>::iterator itRects)
{
	_itCardRects = itRects;
}
// ================================================
// **			����� ��� �Լ�					 **
// ================================================
void ObjectControl::show_mouseRect()
{
	Rectangle(getMemDC(), _mouseRect.left, _mouseRect.top,
		_mouseRect.right, _mouseRect.bottom);
}
void ObjectControl::make_mouseRect()
{
	_mouseRect = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, 5, 5);
}
void ObjectControl::show_plantRects()
{
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		(*_itPlants)->show_plantRect();
	}
}
void ObjectControl::show_bulletHitPoints()
{
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		(*_itPlants)->show_bulletHitPoints();
	}
}
void ObjectControl::show_zombieRects()
{
	_itZombies = _zombies.begin();
	for (;_itZombies != _zombies.end(); _itZombies++)
	{
		(*_itZombies)->show_zombieRect();
	}
}
void ObjectControl::show_zombieRectsForFight()
{
	_itZombies = _zombies.begin();
	for (;_itZombies != _zombies.end(); _itZombies++)
	{
		(*_itZombies)->show_zombieHitPoint();
		(*_itZombies)->show_zombieAttackRange();
	}
}
// ================================================
// **				�Ĺ� ��Ʈ��					 **
// ================================================
void ObjectControl::update_plants()
{
	bool fResult;
	RECT temp;
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		(*_itPlants)->update();
		// ���ο� ���� �ִ��� Ȯ��.
		if (IsRectEmpty(&_plantPoint) == false)
		{
			fResult = is_zombiesAtSameLine((*_itPlants)->get_plantPoint());
			(*_itPlants)->set_fZombieAtSameLine(fResult);
		}
		// �Ѿ˰� ���� �浹�˻� �ϴ� �κ�
		if ((*_itPlants)->get_fZombieAtSameLine() == true)
		{
			temp = find_zombieDamagePoint(
				(*_itPlants)->get_plantPoint());
			(*_itPlants)->set_zombieDamagePoint(temp);
		}//if: ���ο� ���� �ִٸ�

		// ================================================
		// **		�Ѿ˰� ���� �浹���� ó��				 **
		// ================================================
		if ((*_itPlants)->is_hitZombie() == true)
		{
			attack_plantToZombie((*_itPlants)->get_plantPoint(),
				(*_itPlants)->get_lostZombieHp());
			(*_itPlants)->init_lostZombieHp();
		}//if: �Ĺ��� ���� ���ȴٸ�
	}
}
void ObjectControl::draw_plants()
{
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		(*_itPlants)->render();
	}
}
void ObjectControl::delete_plantsAll()
{
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();)
	{
		(*_itPlants)->release();
		_itPlants = _plants.erase(_itPlants);
	}
	swap(vPlants_t(), _plants);
}
void ObjectControl::delete_deadPlants()
{
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();)
	{
		if ((*_itPlants)->is_deadPlant() == true)
		{
			(*_itPlants)->release();
			_itPlants = _plants.erase(_itPlants);
		}
		else
		{
			_itPlants++;
		}
	}
}
void ObjectControl::make_plant()
{
	// �Ĺ� ��ü�� ����
	Plant * plant = new Plant;
	plant->init();
	plant->init_plant(_cardType, m_ptMouse.x, m_ptMouse.y);
	plant->set_fMouseFollow(true);
	// �Ĺ� ���Ϳ� ����
	_plants.push_back(plant);
	// �Ĺ� �����͸� ����.
	// �̷��� ��ü�� ���� ����.
	plant = nullptr;
}
// ================================================
// **			�÷��׹��� ���ϴ� �κ�				 **
// ================================================
void ObjectControl::change_flagmeterGauge()
{
	float pastGaugePercent;
	if (0 < _deadZombieCount)
	{
		pastGaugePercent =
			(float)(_deadZombieCount) / (float)(_maxZombies);
		_deadZombieCount = 0;
		_pastGaugePercentAmount += pastGaugePercent;
	}//if: ���� ���� �ִٸ�
}
void ObjectControl::init_forSunflower()
{
	_sunflowerCount = 0;
	_newSunflowerCount = 0;
}
// ================================================
// **			�عٶ�� ���� �κ�					 **
// ================================================
void ObjectControl::count_sunflower()
{
	_sunflowerCount = 0;
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		if ((*_itPlants)->get_type().compare("SunFlower") == 0)
		{
			_sunflowerCount++;
		}
	}
}
// ================================================
// **				�Ĺ��� ���� ������				 **
// ================================================
bool ObjectControl::is_zombiesAtSameLine(RECT plantPoint)
{
	_itZombies = _zombies.begin();
	for (;_itZombies != _zombies.end();_itZombies++)
	{
		if (plantPoint.top == (*_itZombies)->get_zombieDamagePoint().top
			&& (*_itZombies)->get_zombieDamagePoint().left < WINSIZEX)
		{
			return true;
		}
	}
	return false;
}
RECT ObjectControl::find_zombieDamagePoint(RECT plantPoint)
{
	_itZombies = _zombies.begin();
	for (;_itZombies != _zombies.end();_itZombies++)
	{
		if (plantPoint.top == (*_itZombies)->get_zombieDamagePoint().top)
		{
			return (*_itZombies)->get_zombieDamagePoint();
		}
	}
	return RECT();
}
void ObjectControl::attack_plantToZombie(RECT plantPoint, int lostHp)
{
	// �Ĺ��� ���� ���ο� �ִ� ���� hp�� ��´�.
	_itZombies = _zombies.begin();
	for (;_itZombies != _zombies.end();_itZombies++)
	{
		if (plantPoint.top == (*_itZombies)->get_zombieDamagePoint().top)
		{
			// ������ ������ Ż���Ѵ�.
			(*_itZombies)->hit_zombie(lostHp);
			break;
		}//if: �Ĺ��� ���� ���ο� �ִ� �����
	}
}
// ================================================
// **				���� �Ĺ� ������				 **
// ================================================
bool ObjectControl::is_plantInAttackRange(RECT zombieRange)
{
	_itPlants = _plants.begin();
	if (_plants.empty() == true) { return false; }
	else
	{
		for (;_itPlants != _plants.end();_itPlants++)
		{
			if (IntersectRect(&RECT(), &zombieRange,
				&(*_itPlants)->get_plantPoint()))
			{
				return true;
			}
		}
	}//else: �Ĺ����Ͱ� ������ ��
	return false;
}
void ObjectControl::attack_zombieToPlant(RECT zombiRange, int lostHp)
{
	RECT plantPoint;
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		plantPoint = (*_itPlants)->get_plantPoint();
		if (IntersectRect(&RECT(), &zombiRange, &plantPoint))
		{
			(*_itPlants)->hit_plant(lostHp);
			break;
		}//if: ���� ���ݰŸ� �ȿ� �ִ� �Ĺ��̶��
	}//for: �Ĺ� ��ġ
}
// ================================================
// **				�Ĺ� ������					 **
// ================================================
void ObjectControl::check_mapSpace()
{
	make_mouseRect();
	RECT temp;
	_itMapSpaces = _mapSpaces.begin();
	for (;_itMapSpaces != _mapSpaces.end();_itMapSpaces++)
	{
		if (IntersectRect(&temp, &_mouseRect, &(*_itMapSpaces)))
		{
			_fMapSpace = true;
			_plantPoint = (*_itMapSpaces);
		}//if: ���� ������ ��ģ�ٸ� ���� ��ġ�� ����ش�.
	}//for: �������͸� ������.
}
void ObjectControl::check_spaceEmpty()
{
	// ������ �ʱ�ȭ�Ѵ�.
	_fPlantInSpace = false;
	// �Ĺ� ���͸� ��ġ�ؼ� _plantPoint�� ���Ѵ�.
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		if ((*_itPlants)->is_plantInRect(_plantPoint) == true)
		{
			_fPlantInSpace = true;
		}//if: ���� �ڸ��� �Ĺ��� �ִٸ�
	}
}
void ObjectControl::plant_plantToMap()
{
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		if ((*_itPlants)->get_fMouseFollow() == true)
		{
			//���� �ɴ´�.
			(*_itPlants)->set_fMouseFollow(false);
			// ��ġ�� ����ش�.
			(*_itPlants)->move_plant(_plantPoint.left, _plantPoint.top);
			(*_itPlants)->set_plantPoint(_plantPoint);
			// ================================================
			// **		���� ���� �عٶ�� ���� �κ�				 **
			// ================================================
			if (_cardType.compare("SunFlower") == 0)
			{
				// ���� �Ĺ��� �عٶ���� newSunflowerCount�� �ø���.
				_newSunflowerCount++;
			}
		}
	}
}

ObjectControl::ObjectControl()
{
}
ObjectControl::~ObjectControl()
{
}
HRESULT ObjectControl::init()
{
	// �Ĺ� ���� �� ���� ����
	_fClickCard = false;
	_fMakingPlant = false;
	_fMapSpace = false;
	_fPlantInSpace = false;
	_cardType = "";
	_fClickStage = false;
	// ������������ ���� �����°� �ʱ�ȭ
	init_forStageLevel();
	// �عٶ�� ���� ���°� �ʱ�ȭ
	init_forSunflower();
	return S_OK;
}
void ObjectControl::release()
{
	// �Ĺ� ����
	delete_plantsAll();
	IMAGEMANAGER->deleteImage("SunFlower");
	IMAGEMANAGER->deleteImage("Wallnut");
	IMAGEMANAGER->deleteImage("PeaShooter");
	IMAGEMANAGER->deleteImage("PeaShooter_Attack");
	// ���� ����
	delete_zombiesAll();
	IMAGEMANAGER->deleteImage("Zombie");
}
void ObjectControl::update()
{
	// �Ĺ� ���͸� ������Ʈ �Ѵ�.
	update_plants();
	// ���� ���͸� ������Ʈ �Ѵ�.
	update_zombies();

	// ================================================
	// **			�Ĺ��� �����ϴ� �κ�				 **
	// ================================================
	if (_fClickCard == true && _fClickStage == false)
	{
		if (_fMakingPlant == false)
		{
			make_plant();
			_fClickCard = false;
			// ��ü�� �����ߴٸ� �ٸ� ��ü�� �� ���������� ���Ѵ�.
			_fMakingPlant = true;
		}//if: �Ĺ��� ����� ���� �ƴ϶�� ��ü�� �����Ѵ�.
	}//if: �������� ���� ī�带 Ŭ������ ��
	else
	{
		_fClickCard = false;
	}

	// ================================================
	// **				�Ĺ��� �ɴ� �κ�				 **
	// ================================================
	if (_fClickStage == true && _fMakingPlant == true)
	{
		check_mapSpace();
		check_spaceEmpty();
	}//if: �Ĺ��� ����� ���̰�, ���� �ڸ��� Ŭ���ߴٸ�

	if (_fMakingPlant == true && _fMapSpace == true &&
		_fClickStage == true)
	{
		if (_fPlantInSpace == false && _fClickStage == true)
		{
			// �Ĺ��� ���� �ɴ´�.
			plant_plantToMap();
			// �ɰ��� �Ĺ��� ����� ���� �ƴϴ�.
			_fClickStage = false;
			_fMakingPlant = false;
			// �ɰ��� �Ĺ��� ������ �����Ѵ�.
			_fPlantInSpace = true;
		}//if: ������ �Ĺ��� ���ٸ�
	}//if: ���� ���� �ְ�, �Ĺ��� �ɴ� ���̶��
	else
	{
		_fClickStage = false;
	}
	// �÷��׹��Ͱ� ���Ѵ�.
	change_flagmeterGauge();
	// �عٶ�⸦ ����.
	count_sunflower();
	// ���� �������� ������ ���� �����.
	make_zombieAtStage();
	// ���� �Ĺ��� �����.
	delete_deadPlants();
	// ���� ���� �����.
	delete_deadZombies();
	// ���콺 ��Ʈ�� �����.
	make_mouseRect();
}
void ObjectControl::render()
{
	draw_plants();
	draw_zombies();
	if (KEYMANAGER->isToggleKey(0x32))
	{
		show_plantRects();
		show_bulletHitPoints();
		show_mouseRect();
	}//if: 2���� ������
	if (KEYMANAGER->isToggleKey(0x33))
	{
		//show_zombieRects();
		show_zombieRectsForFight();
	}
}

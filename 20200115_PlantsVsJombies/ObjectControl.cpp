#include "stdafx.h"
#include "ObjectControl.h"

// ================================================
// **				좀비 컨트롤					 **
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
// **			좀비 만드는 부분					 **
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
// **				좀비 죽었을 때					 **
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
		// **				식물과 충돌체크				 **
		// ================================================
		fPlantInAttackRange = is_plantInAttackRange(
			(*_itZombies)->get_zombieAttackRange());
		// ================================================
		// **				좀비가 식물 공격				 **
		// ================================================
		if (fPlantInAttackRange == true)
		{
			(*_itZombies)->set_fPlantInRange(true);
			attack_zombieToPlant(
				(*_itZombies)->get_zombieAttackRange(),
				(*_itZombies)->get_lostPlantHp());
		}//if: 식물이 사정거리 안에 있다면
		else
		{
			// fPlantInRange를 초기화한다.
			(*_itZombies)->set_fPlantInRange(false);
		}//else: 식물이 사정거리 밖에 있다면
		if ((*_itZombies)->is_zombieAttack() == true)
		{
			// 좀비가 쌓은 데미지를 초기화한다.
			(*_itZombies)->init_lostPlantHp();
		}//if: 좀비가 공격을 했다면

		if ((*_itZombies)->is_zombiePassByLine() == true)
		{
			_fZombiePassByLine = (*_itZombies)->is_zombiePassByLine();
		}
	}//for: 모든 좀비를 서치
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
// **			UI 정보 Setter 함수				 **
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
// **			디버그 모드 함수					 **
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
// **				식물 컨트롤					 **
// ================================================
void ObjectControl::update_plants()
{
	bool fResult;
	RECT temp;
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		(*_itPlants)->update();
		// 라인에 좀비가 있는지 확인.
		if (IsRectEmpty(&_plantPoint) == false)
		{
			fResult = is_zombiesAtSameLine((*_itPlants)->get_plantPoint());
			(*_itPlants)->set_fZombieAtSameLine(fResult);
		}
		// 총알과 좀비 충돌검사 하는 부분
		if ((*_itPlants)->get_fZombieAtSameLine() == true)
		{
			temp = find_zombieDamagePoint(
				(*_itPlants)->get_plantPoint());
			(*_itPlants)->set_zombieDamagePoint(temp);
		}//if: 라인에 좀비가 있다면

		// ================================================
		// **		총알과 좀비 충돌이후 처리				 **
		// ================================================
		if ((*_itPlants)->is_hitZombie() == true)
		{
			attack_plantToZombie((*_itPlants)->get_plantPoint(),
				(*_itPlants)->get_lostZombieHp());
			(*_itPlants)->init_lostZombieHp();
		}//if: 식물이 좀비를 때렸다면
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
	// 식물 객체를 생성
	Plant * plant = new Plant;
	plant->init();
	plant->init_plant(_cardType, m_ptMouse.x, m_ptMouse.y);
	plant->set_fMouseFollow(true);
	// 식물 벡터에 삽입
	_plants.push_back(plant);
	// 식물 포인터를 지움.
	// 이러면 객체는 남아 있음.
	plant = nullptr;
}
// ================================================
// **			플래그미터 변하는 부분				 **
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
	}//if: 죽은 좀비가 있다면
}
void ObjectControl::init_forSunflower()
{
	_sunflowerCount = 0;
	_newSunflowerCount = 0;
}
// ================================================
// **			해바라기 세는 부분					 **
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
// **				식물이 좀비 때릴때				 **
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
	// 식물과 같은 라인에 있던 좀비 hp를 깎는다.
	_itZombies = _zombies.begin();
	for (;_itZombies != _zombies.end();_itZombies++)
	{
		if (plantPoint.top == (*_itZombies)->get_zombieDamagePoint().top)
		{
			// 때리고 루프를 탈출한다.
			(*_itZombies)->hit_zombie(lostHp);
			break;
		}//if: 식물과 같은 라인에 있는 좀비면
	}
}
// ================================================
// **				좀비가 식물 때릴때				 **
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
	}//else: 식물벡터가 존재할 때
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
		}//if: 좀비 공격거리 안에 있는 식물이라면
	}//for: 식물 서치
}
// ================================================
// **				식물 심을때					 **
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
		}//if: 맵의 공간과 겹친다면 심을 위치를 잡아준다.
	}//for: 공간벡터를 돌린다.
}
void ObjectControl::check_spaceEmpty()
{
	// 변수를 초기화한다.
	_fPlantInSpace = false;
	// 식물 벡터를 서치해서 _plantPoint와 비교한다.
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		if ((*_itPlants)->is_plantInRect(_plantPoint) == true)
		{
			_fPlantInSpace = true;
		}//if: 심을 자리에 식물이 있다면
	}
}
void ObjectControl::plant_plantToMap()
{
	_itPlants = _plants.begin();
	for (;_itPlants != _plants.end();_itPlants++)
	{
		if ((*_itPlants)->get_fMouseFollow() == true)
		{
			//땅에 심는다.
			(*_itPlants)->set_fMouseFollow(false);
			// 위치를 잡아준다.
			(*_itPlants)->move_plant(_plantPoint.left, _plantPoint.top);
			(*_itPlants)->set_plantPoint(_plantPoint);
			// ================================================
			// **		새로 만든 해바라기 세는 부분				 **
			// ================================================
			if (_cardType.compare("SunFlower") == 0)
			{
				// 심은 식물이 해바라기라면 newSunflowerCount를 올린다.
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
	// 식물 심을 때 쓰는 변수
	_fClickCard = false;
	_fMakingPlant = false;
	_fMapSpace = false;
	_fPlantInSpace = false;
	_cardType = "";
	_fClickStage = false;
	// 스테이지에서 좀비 나오는거 초기화
	init_forStageLevel();
	// 해바라기 갯수 세는거 초기화
	init_forSunflower();
	return S_OK;
}
void ObjectControl::release()
{
	// 식물 해제
	delete_plantsAll();
	IMAGEMANAGER->deleteImage("SunFlower");
	IMAGEMANAGER->deleteImage("Wallnut");
	IMAGEMANAGER->deleteImage("PeaShooter");
	IMAGEMANAGER->deleteImage("PeaShooter_Attack");
	// 좀비 해제
	delete_zombiesAll();
	IMAGEMANAGER->deleteImage("Zombie");
}
void ObjectControl::update()
{
	// 식물 벡터를 업데이트 한다.
	update_plants();
	// 좀비 벡터를 업데이트 한다.
	update_zombies();

	// ================================================
	// **			식물을 생성하는 부분				 **
	// ================================================
	if (_fClickCard == true && _fClickStage == false)
	{
		if (_fMakingPlant == false)
		{
			make_plant();
			_fClickCard = false;
			// 객체를 생성했다면 다른 객체를 또 생성하지는 못한다.
			_fMakingPlant = true;
		}//if: 식물을 만드는 중이 아니라면 객체를 생성한다.
	}//if: 스테이지 말고 카드를 클릭했을 때
	else
	{
		_fClickCard = false;
	}

	// ================================================
	// **				식물을 심는 부분				 **
	// ================================================
	if (_fClickStage == true && _fMakingPlant == true)
	{
		check_mapSpace();
		check_spaceEmpty();
	}//if: 식물을 만드는 중이고, 심을 자리를 클릭했다면

	if (_fMakingPlant == true && _fMapSpace == true &&
		_fClickStage == true)
	{
		if (_fPlantInSpace == false && _fClickStage == true)
		{
			// 식물을 땅에 심는다.
			plant_plantToMap();
			// 심고나면 식물을 만드는 중이 아니다.
			_fClickStage = false;
			_fMakingPlant = false;
			// 심고나면 식물이 공간에 존재한다.
			_fPlantInSpace = true;
		}//if: 공간에 식물이 없다면
	}//if: 심을 땅이 있고, 식물을 심는 중이라면
	else
	{
		_fClickStage = false;
	}
	// 플래그미터가 변한다.
	change_flagmeterGauge();
	// 해바라기를 센다.
	count_sunflower();
	// 좀비를 스테이지 레벨에 따라서 만든다.
	make_zombieAtStage();
	// 죽은 식물을 지운다.
	delete_deadPlants();
	// 죽은 좀비를 지운다.
	delete_deadZombies();
	// 마우스 렉트를 만든다.
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
	}//if: 2번을 누르면
	if (KEYMANAGER->isToggleKey(0x33))
	{
		//show_zombieRects();
		show_zombieRectsForFight();
	}
}

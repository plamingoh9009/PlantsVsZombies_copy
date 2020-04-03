#include "stdafx.h"
#include "Map.h"

void Map::init_stage()
{
	int size = _spaces.size();
	_stage.left = _spaces[0].left;
	_stage.top = _spaces[0].top;
	_stage.right = _spaces[size - 1].right;
	_stage.bottom = _spaces[size - 1].bottom;
}
void Map::change_mapImg()
{
	if (_type.compare("Background_Yard") == 0)
	{
		_img = IMAGEMANAGER->findImage("Background_Night");
		_type = "Background_Night";
	}
	else if (_type.compare("Background_Night") == 0)
	{
		_img = IMAGEMANAGER->findImage("Background_Snow");
		_type = "Background_Snow";
	}
	else if (_type.compare("Background_Snow") == 0)
	{
		_img = IMAGEMANAGER->findImage("Background_Yard");
		_type = "Background_Yard";
	}
}
// ================================================
// **				인트로 초기화					 **
// ================================================
void Map::init_forIntro()
{
	_isShowMapAll = true;
	_distance = 0;
	_fReadySetPlant = false;
}

vector<RECT> Map::get_spaces()
{
	return vector<RECT>(_spaces);
}
vector<RECT>::iterator Map::get_itSpaces()
{
	return vector<RECT>::iterator(_itSpaces);
}
vector<RECT> Map::get_lines()
{
	return vector<RECT>(_lines);
}
vector<RECT>::iterator Map::get_itLines()
{
	return vector<RECT>::iterator(_itLines);
}

void Map::show_stage()
{
	FrameRect(getMemDC(), &_stage,
		CreateSolidBrush(RGB(0, 0, 0)));
}
void Map::show_lines()
{
	_itLines = _lines.begin();
	for (;_itLines != _lines.end();_itLines++)
	{
		FrameRect(getMemDC(), &(*_itLines),
			CreateSolidBrush(RGB(64, 0, 64)));
	}
}
void Map::delete_lines()
{
	_itLines = _lines.begin();
	for (;_itLines != _lines.end();)
	{
		_lines.erase(_itLines++);
	}
	_lines.clear();
}
void Map::show_spaces()
{
	_itSpaces = _spaces.begin();
	for (;_itSpaces != _spaces.end();_itSpaces++)
	{
		FrameRect(getMemDC(), &(*_itSpaces),
			CreateSolidBrush(RGB(0, 0, 0)));
	}
}
void Map::init_spaces()
{
	int initX = 132;
	int initY = 90;
	int plantWidth = 70;
	int plantHeight = 80;
	int blankWidth = (int)(plantWidth * 0.1429);
	int blankHeight = (int)(plantHeight * 0.2);
	int currentX, currentY;
	RECT rect;
	currentY = initY;
	for (int i = 0; i < 5; i++)
	{
		currentX = initX;
		for (int k = 0; k < 9; k++)
		{
			// 렉트를 만든다.
			rect = RectMake(currentX, currentY,
				plantWidth, plantHeight);
			// 벡터에 넣는다.
			_spaces.push_back(rect);
			currentX = currentX + plantWidth + blankWidth;
		}//for: 좌우 여백은 22픽셀
		currentY = currentY + plantHeight + blankHeight;
		// ================================================
		// **			_lines 벡터를 초기화				 **
		// ================================================
		_lines.push_back(rect);
	}//for: 상하 여백은 38픽셀
}
void Map::delete_spaces()
{
	_itSpaces = _spaces.begin();
	for (;_itSpaces != _spaces.end();)
	{
		_itSpaces = _spaces.erase(_itSpaces);
	}
	swap(vSpaces_t(), _spaces);
}
void Map::show_mapAll()
{
	if (_delay >= (60 * 2))
	{
		// 맵이 어디까지인지 보여주는 함수
		if (_distance + WINSIZEX >= _rect.right - 1)
		{
			_distance = 126;
			_isShowMapAll = false;
			_delay = 0;
			Sleep(2500);
			_fReadySetPlant = true;
		}//if: 윈도우의 끝에 도달하면 멈춘다.
		else
		{
			_distance += _SPEED;
		}//else: 윈도우의 끝이 아니면 움직여서 보여준다.
	}//if: 일정시간이 지난 후
	else { _delay++; }
}

Map::Map()
{
}
Map::~Map()
{
}
HRESULT Map::init()
{
	_rect = RectMake(0, 0, 1400, 600);
	_img = IMAGEMANAGER->addImage("Background_Yard",
		"images/Background_Yard.bmp",
		_rect.right - _rect.left, _rect.bottom - _rect.top,
		false, COLOR_MAGENTA);
	IMAGEMANAGER->addImage("Background_Snow",
		"images/Background_Snow.bmp",
		_rect.right - _rect.left, _rect.bottom - _rect.top,
		false, COLOR_MAGENTA);
	IMAGEMANAGER->addImage("Background_Night",
		"images/Background_Night.bmp",
		_rect.right - _rect.left, _rect.bottom - _rect.top,
		false, COLOR_MAGENTA);
	_type = "Background_Yard";
	// 맵을 전부 보여줄지 말지 정하는 변수
	_isShowMapAll = false;
	_distance = 126;
	// 사각형 타일을 초기화하는 함수
	init_spaces();
	// 초반 딜레이를 위한 변수
	_delay = 0;
	// 스테이지 범위를 갖는 변수
	init_stage();
	return S_OK;
}
void Map::release()
{
	IMAGEMANAGER->deleteImage("Background_Yard");
	IMAGEMANAGER->deleteImage("Background_Snow");
	IMAGEMANAGER->deleteImage("Background_Night");
	_img = nullptr;
	delete_spaces();
}
void Map::update()
{
	if (_isShowMapAll == true)
	{
		show_mapAll();
	}

	if (KEYMANAGER->isOnceKeyDown(0x39))
	{
		change_mapImg();

	}
}
void Map::render()
{
	// 마당을 렌더하는 부분
	_img->loopRender(getMemDC(),
		&RectMake(0, 0, WINSIZEX, WINSIZEY), _distance, 0);
}

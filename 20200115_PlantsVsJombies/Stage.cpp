#include "stdafx.h"
#include "Stage.h"
void Stage::change_sceneEnding()
{
	_sceneChangeCount++;
	if (_sceneChangeCount >= _sceneChangeDelay)
	{
		SCENEMANAGER->changeScene("Ending");
	}
}
void Stage::init_gameOver()
{
	_gameOverImg = IMAGEMANAGER->addImage("GameOver",
		"images/GameOver.bmp", 480, 360, true, COLOR_MAGENTA);
	_gameOverRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 480, 360);
	_sceneChangeCount = 0;
	_sceneChangeDelay = 60 * 3;
}
void Stage::delete_gameOverImg()
{
	_gameOverImg = nullptr;
	IMAGEMANAGER->deleteImage("GameOver");
}
void Stage::init_uiToObjControl()
{
	//�õ�ī���� ��Ʈ ���� �ѱ��.
	_objControl->set_cardRects(_ui->get_cardRects());
	_objControl->set_itCardRects(_ui->get_itCardRects());
	// ���� ���� ��Ʈ ���͸� �ѱ��.
	_objControl->set_mapSpaces(_ui->get_mapSpaces());
	_objControl->set_itMapSpaces(_ui->get_itMapSpaces());
	// ���� ���� ��Ʈ ���͸� �ѱ��.
	_objControl->set_mapLines(_ui->get_mapLines());
	_objControl->set_itMapLines(_ui->get_itMapLines());
	// �������� ��Ʈ�� �ѱ��.
	_objControl->set_stageRect(_ui->get_mapStage());
}
void Stage::update_clickedUi()
{
	if (_ui->get_fClickCard() == true &&
		_ui->get_fBuyCard() == true)
	{
		_objControl->set_fClickCard(true);
		_objControl->set_cardType(_ui->get_cardType());
		_ui->set_fClickCard(false);
		_ui->set_fBuyCard(false);
	}
	else if (_ui->get_fClickStage() == true)
	{
		_objControl->set_fClickStage(true);
		_ui->set_fClickStage(false);
	}
}
void Stage::update_uiToObjControl()
{
	// ���� ������ ������ �ѱ��.
	if (_ui->is_passOverGauge() == true)
	{
		_objControl->set_currentGauge(_ui->get_currentGauge());
		_ui->set_fPassOverGauge(false);
	}
}
void Stage::update_objControlToUi()
{
	// �÷��׹��� ���ϴ� ������ �Ѱ��ش�.
	_ui->change_flagmeterUseDeadZombies(
		_objControl->get_pastGaugePercentAmount()
	);
	_objControl->set_pastGaugePercentAmount(0);
	// �عٶ�� ������ �Ѱ��ش�.
	_ui->update_sunflowerInfo(
		_objControl->get_sunflowerCount(),
		_objControl->get_newSunflowerCount());
	_objControl->set_newSunflowerCount(0);
}
Stage::Stage()
{
}
Stage::~Stage()
{
}
HRESULT Stage::init()
{
	_objControl = new ObjectControl;
	_objControl->init();
	_ui = new UI;
	_ui->init();
	// UI�� ObjControl�� �ʱ�ȭ�� ������ �Ѱ��ش�.
	init_uiToObjControl();
	// ���ӿ��� ������ �ʱ�ȭ�Ѵ�.
	init_gameOver();
	return S_OK;
}
void Stage::release()
{
	_ui->release();
	_objControl->release();
	delete_gameOverImg();
}
void Stage::update()
{
	if (_objControl->is_ZombiePassByLine() == true) {}
	else
	{
		_ui->update();
		update_clickedUi();
		update_uiToObjControl();
		_objControl->update();
		update_objControlToUi();
	}//else: ���ӿ����� �ƴ϶��
	if (_ui->is_gameWin() == true)
	{
		change_sceneEnding();
		
	}//if: ���ӿ��� �̱�� �������� �Ѿ��.
}
void Stage::render()
{
	_ui->render();
	_objControl->render();
	// ================================================
	// **				���ӿ��� �̹���				 **
	// ================================================
	if (_objControl->is_ZombiePassByLine() == true)
	{
		_gameOverImg->render(getMemDC(),
			_gameOverRect.left, _gameOverRect.top);
	}
}

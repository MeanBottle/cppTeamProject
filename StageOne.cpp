#include "stdafx.h"
#include "StageOne.h"
#include "Player.h"
#include "FlyBug.h"
#include "Crab.h"
HRESULT StageOne::Init()
{
	// StageOne���� ����� ������Ʈ �������ش�.

	//�÷��̾�
	Player* _player = new Player("player", { 45, WINSIZEY / 2 + 100 }, { 100,150 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _player);

	//���ڸ� ����
	//FlyBug* _flybug = new FlyBug("flybug", { WINSIZEX / 2 + 300, 200 }, { 200, 100 }, GameObject::Pivot::Center);
	//���ڸ� ��ü �߰��ϱ�
	//OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _flybug);

	//�� ����
	Crab* _crab = new Crab("crab", { 1060, WINSIZEY / 2 + 175 }, { 100, 150 }, GameObject::Pivot::Center);
	//���ڸ� ��ü �߰��ϱ�
	OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _crab);

	OBJECTMANAGER->Init();
	return S_OK;
}

void StageOne::Release()
{
	OBJECTMANAGER->Release();
}

void StageOne::Update()
{
	OBJECTMANAGER->Update();
}

void StageOne::Render()
{
	OBJECTMANAGER->Render();
}

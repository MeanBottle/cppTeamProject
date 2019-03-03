#include "stdafx.h"
#include "StageOne.h"
#include "Player.h"
#include "FlyBug.h"
#include "Crab.h"
HRESULT StageOne::Init()
{
	// StageOne에서 사용할 오브젝트 생성해준다.

	//플레이어
	Player* _player = new Player("player", { 45, WINSIZEY / 2 + 100 }, { 100,150 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _player);

	//잠자리 생성
	//FlyBug* _flybug = new FlyBug("flybug", { WINSIZEX / 2 + 300, 200 }, { 200, 100 }, GameObject::Pivot::Center);
	//잠자리 객체 추가하기
	//OBJECTMANAGER->AddObject(ObjectType::Enum::Object, _flybug);

	//게 생성
	Crab* _crab = new Crab("crab", { 1060, WINSIZEY / 2 + 175 }, { 100, 150 }, GameObject::Pivot::Center);
	//잠자리 객체 추가하기
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

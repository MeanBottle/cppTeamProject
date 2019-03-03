#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	
};


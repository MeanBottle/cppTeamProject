#include "stdafx.h"
#include "Player.h"

// 자식이 나오기 위해선 부모님이 필요행
// 데리고와야해

Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_name = name;				// 클래스 이름 설정 해준다.
	_position = pos;			// 좌표 초기화 해준다.
	_size = size;				// 사이즈 초기화 해준다.
	_pivot = Pivot::LeftTop;	// 피벗 위치 잡아준다.
	this->UpdateRectByPivot();	// RECT 그려준다.
	_isActive = true;			// 활성화 되어있다. 
	_isLive = true;				// 살아 있다.
}

Player::~Player()
{
}

HRESULT Player::Init()
{
	return S_OK;
}

void Player::Release()
{

}

void Player::Update()
{
	if (KEYMANAGER->isStayKeyDown('A')) {
		_rc.left -= 5;
		_rc.right -= 5;
	}

	if (KEYMANAGER->isStayKeyDown('D')) {
		_rc.left += 5;
		_rc.right += 5;
	}
	
	//this->UpdateRectByPivot();	// RECT 그려준다.

}

void Player::Render()
{
	Rectangle(getMemDC(), _rc);
}

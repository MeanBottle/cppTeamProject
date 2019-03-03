#include "stdafx.h"
#include "Player.h"

// �ڽ��� ������ ���ؼ� �θ���� �ʿ���
// ������;���

Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_name = name;				// Ŭ���� �̸� ���� ���ش�.
	_position = pos;			// ��ǥ �ʱ�ȭ ���ش�.
	_size = size;				// ������ �ʱ�ȭ ���ش�.
	_pivot = Pivot::LeftTop;	// �ǹ� ��ġ ����ش�.
	this->UpdateRectByPivot();	// RECT �׷��ش�.
	_isActive = true;			// Ȱ��ȭ �Ǿ��ִ�. 
	_isLive = true;				// ��� �ִ�.
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
	
	//this->UpdateRectByPivot();	// RECT �׷��ش�.

}

void Player::Render()
{
	Rectangle(getMemDC(), _rc);
}

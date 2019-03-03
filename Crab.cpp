#include "stdafx.h"
#include "crab.h"
#include "Player.h"

Crab::Crab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

Crab::~Crab()
{
}

HRESULT Crab::Init()
{
	//���� �ʱ�ȭ
	_state = state::IDLE;

	//���� ó���� ���� ����
	_gauge = 1;
	_angle = 0.f;
	_isAttack = false;
	_isAttackFinish = false;
	//�� ��üó�� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//���� ó���� ���� ����
	_deathTimer = 0;

	//�� ī�޶� ��Ʈ(�׻� �� �߾��� ����ٴѴ�.)
	_camera.pt = { _position.x, _position.y };
	_camera.rc = RectMakeCenter(_camera.pt.x, _camera.pt.y, _size.x * 18.f, _size.y);
	_camera.isCrush = false;

	//�� �浹 ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x, _position.y };
	}
	_col[0].rc = RectMakeCenter(_col[0].pt.x, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	_col[1].rc = RectMakeCenter(_col[1].pt.x, _col[1].pt.y + _size.y / 3 + 10, _size.x - 30, _size.y / 5);
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//�� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x, _position.y };
	}
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 3, _att[0].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 3, _att[1].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);

	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = (Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::Object, "player");

	//�÷��̾���� ���� �ʱ�ȭ
	_angle = GetAngle(_position.x, _position.y
		, _player->GetRect().left + (_player->GetRect().right - _player->GetRect().left) / 2
		, _player->GetRect().top + (_player->GetRect().bottom - _player->GetRect().top) / 2);

	return S_OK;
}

void Crab::Release()
{
}

void Crab::Update()
{
	//���콺 ��ǥ ���
	_pt.x = _ptMouse.x;
	_pt.y = _ptMouse.y;

	//�̵� �׽�Ʈ
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_position.x -= 5.f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_position.x += 5.f;
	}

	//�� ��Ʈ
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//�� ��üó�� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//�� ī�޶� ��Ʈ(�׻� �� �߾��� ����ٴѴ�.)
	_camera.pt = { _position.x, _position.y };
	_camera.rc = RectMakeCenter(_camera.pt.x, _camera.pt.y, _size.x * 18.f, _size.y);
	
	//�� �浹 ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x, _position.y };
	}
	_col[0].rc = RectMakeCenter(_col[0].pt.x, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	_col[1].rc = RectMakeCenter(_col[1].pt.x, _col[1].pt.y + _size.y / 3 + 10, _size.x - 30, _size.y / 5);
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//�� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x, _position.y };
	}
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 3, _att[0].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 3, _att[1].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);

	//�÷��̾�� ���� üũ
	_angle = GetAngle(_position.x, _position.y
		, _player->GetRect().left + (_player->GetRect().right - _player->GetRect().left) / 2
		, _player->GetRect().top + (_player->GetRect().bottom - _player->GetRect().top) / 2);

	//�÷��̾�� �Ÿ� üũ
	_dist = GetDistance(_position.x, _position.y
		, _player->GetRect().left + (_player->GetRect().right - _player->GetRect().left) / 2
		, _player->GetRect().top + (_player->GetRect().bottom - _player->GetRect().top) / 2);

	//ī�޶�� �浹�� �ƴ� ��� ��� ����
	if (!_camera.isCrush)
	{
		_state = state::IDLE;
	}

	//�÷��̾� ������ ���� ī�޶�� �浹 ó��
	RECT rcCam;
	if (IntersectRect(&rcCam, &_camera.rc, &_player->GetRect()))
	{
		_camera.isCrush = true;
	}

	//ī�޶�� �浹�� ��� ������ ���� ������ ����
	if (_camera.isCrush)
	{
		if (_angle == PI)
		{
			_state = state::L_MOVE;
		}

		if (_angle == 0.f)
		{
			_state = state::R_MOVE;
		}
	}

	//�÷��̾���� �Ÿ��� 300.f���� ������ ������ ���� �̵� ���·� ����
	if (_dist <= 300.f)
	{
		if (_angle == PI)
		{
			_state = state::L_ATTACK_MOVE;
		}

		if (_angle == 0.f)
		{
			_state = state::R_ATTACK_MOVE;
		}
	}

	//�÷��̾���� �������� �� ���� ����
	if (_dist <= _player->GetSize().x / 2 + _size.x / 2)
	{
		_isAttack = true;
	}

	//���� ������ �������� �� ���� ��ٸ� �� ���ݷ�Ʈ�� ������
	if (_isAttack)
	{
		_gauge++;

		if (_angle == PI)
		{
			_state = state::L_ATTACK;
		}
		if (_angle == 0.f)
		{
			_state = state::R_ATTACK;
		}

		if (_gauge % 50 == 0)
		{
			_isAttack = false;
			_isAttackFinish = true;
		}
	}

	//������ ������ �ڷ� ���� ó��
	if (_isAttackFinish)
	{
		if (_angle == PI)
		{
			_state = state::L_ATTACK_FINISH;
		}

		if (_angle == 0.f)
		{
			_state = state::R_ATTACK_FINISH;
		}
	}

	//���¿� ���� ������ ó��
	switch (_state)
	{
	case state::L_MOVE:
		if (_dist > 300.f)
		{
			_position.x -= 5.f;
		}
		break;
	case state::R_MOVE:
		if (_dist > 300.f)
		{
			_position.x += 5.f;
		}
		break;
	case state::L_ATTACK_MOVE:
		if (_dist > _player->GetSize().x / 2 + _size.x / 2)
		{
			_position.x -= 5.f;
		}
		break;
	case state::R_ATTACK_MOVE:
		if (_dist > _player->GetSize().x / 2 + _size.x / 2)
		{
			_position.x += 5.f;
		}
		break;
	case state::L_ATTACK:
		_att[0].rc.left -= _size.x / 4;
		_att[0].rc.right -= _size.x / 4;
		break;
	case state::R_ATTACK:
		_att[1].rc.left += _size.x / 4;
		_att[1].rc.right += _size.x / 4;
		break;
	case state::L_ATTACK_FINISH:
		if (_dist < 300.f)
		{
			_position.x += 5.f;
		}
		if (_dist >= 300.f)
		{
			_isAttackFinish = false;
		}
		break;
	case state::R_ATTACK_FINISH:
		if (_dist < 300.f)
		{
			_position.x -= 5.f;
		}
		if (_dist >= 300.f)
		{
			_isAttackFinish = false;
		}
		break;
	}

}

void Crab::Render()
{
	//ī�޶� ��Ʈ �׸���
	//Rectangle(getMemDC(), _camera.rc);

	//��Ʈ �׸���
	Rectangle(getMemDC(), _rc);

	//�浹��Ʈ �׸���
	for (int i = 0; i < 4; i++)
	{
		//Rectangle(getMemDC(), _col[i].rc);
	}

	//��üó����Ʈ �׸���
	for (int i = 0; i < 3; i++)
	{
		//Rectangle(getMemDC(), _part[i].rc);
	}

	//����ó����Ʈ �׸���
	for (int i = 0; i < 2; i++)
	{
		Rectangle(getMemDC(), _att[i].rc);
	}

	//�ؽ�Ʈ ���
	sprintf(msg1, "x : %d, y : %d", _pt.x, _pt.y);
	TextOut(getMemDC(), 50, 50, msg1, strlen(msg1));
}
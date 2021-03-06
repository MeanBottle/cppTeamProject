#include "stdafx.h"
#include "FlyBug.h"
#include "Player.h"

FlyBug::FlyBug(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

FlyBug::~FlyBug()
{
}

HRESULT FlyBug::Init()
{
	//상태 초기화
	_state = state::IDLE;
	//상하 움직임 처리를 위한 변수 초기화
	_move = 0;
	_isUp = false;
	//공격 처리를 위한 변수
	_gauge = 1;
	_angle = 0.f;
	_isAttack = false;
	//잠자리 시체처리 렉트
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}
	//죽음 처리를 위한 변수
	_deathTimer = 0;
	//잠자리 카메라 렉트(항상 몸 중앙을 따라 다닌다.)
	_camera.pt = { _position.x, _position.y };
	_camera.rc = RectMakeCenter(_camera.pt.x, _camera.pt.y, _size.x * 3.f, _size.y * 2.f);
	//플레이어 클래스 초기화
	_player = (Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::Object, "player");
	//플레이어와의 각도 초기화
	_angle = GetAngle(_position.x, _position.y
					, _player->GetRect().left + (_player->GetRect().right - _player->GetRect().left)/2
					, _player->GetRect().top + (_player->GetRect().bottom - _player->GetRect().top)/2 );
	//잠자리 충돌 렉트(항상 몸 중앙을 따라 다닌다.)
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_col.pt.x + _size.y / 2, _col.pt.y, _size.x, _size.y / 2);

	return S_OK;
}

void FlyBug::Release()
{
}

void FlyBug::Update()
{
	//마우스 좌표 담기
	_pt.x = _ptMouse.x; 
	_pt.y = _ptMouse.y;

	//잠자리 렉트
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//잠자리 시체처리 렉트
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//잠자리 카메라 렉트(항상 몸 중앙을 따라다닌다.)
	_camera.pt = { _position.x, _position.y };
	_camera.rc = RectMakeCenter(_camera.pt.x, _camera.pt.y, _size.x * 2.f, _size.y);

	//잠자리 충돌 렉트(항상 몸을 따라 다닌다.)
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_col.pt.x, _col.pt.y, _size.x, _size.y);

	//플레이어와 각도 체크
	_angle = GetAngle(_position.x, _position.y
		, _player->GetRect().left + (_player->GetRect().right - _player->GetRect().left) / 2
		, _player->GetRect().top + (_player->GetRect().bottom - _player->GetRect().top) / 2);

	if (_camera.rc.left <= 50 || _camera.rc.right >= WINSIZEX - 50)
	{
		_state = state::IDLE;
	}

	//270도보다 크면 왼쪽으로 이동
	if (_angle > PI / 180 * 270 && _camera.rc.left > 50)
	{
		_state = state::L_MOVE;
	}
	//270도 보다 작으면 오른쪽으로 이동
	else if (_angle < PI / 180 * 270 && _camera.rc.right < WINSIZEX - 50)
	{
		_state = state::R_MOVE;
	}

	//공격 게이지 10번 모으면 그때 공격 상태로 변경
	if (_gauge % 10 == 0)
	{
		_state = state::ATTACK;
	}

	//플레이어와 충돌 체크
	if (GetDistance(_position.x, _position.y
					, _player->GetRect().left + (_player->GetRect().right - _player->GetRect().left) / 2
					, _player->GetRect().top + (_player->GetRect().bottom - _player->GetRect().top) / 2)
					< _size.x / 2 + (_player->GetRect().right - _player->GetRect().left) / 2 )
	{
		_isAttack = true;
	}
	
	//플레이어 총알과 충돌 체크
	if (KEYMANAGER->isToggleKey('R'))
	{
		_state = state::DEATH;
	}

	//이동 테스트
	/*if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_position.x -= 5.f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_position.x += 5.f;
	}*/
	//상태 따른 움직임 처리
	switch (_state)
	{
	//대기 상태
	case state::IDLE:	
		//아래로 이동
		if (!_isUp)
		{
			//_position.x += 2.f;
			_position.y += 4.f;
			_move += 1;
		}
		//위로 이동
		else
		{
			//_position.x -= 2.f;
			_position.y -= 4.f;
			_move += 1;
		}

		//25 이동시 반대로 이동
		if (_move > 25)
		{
			_move = 0;
			_isUp = !_isUp;
			_gauge++;
		}
		break;
	//공격 상태
	case state::ATTACK:
		if (!_isAttack)
		{
			//플레이어를 공격 할 각도 설정
			_attackAngle = GetAngle(_position.x, _position.y
				, _player->GetRect().left + (_player->GetRect().right - _player->GetRect().left) / 2
				, _player->GetRect().top + (_player->GetRect().bottom - _player->GetRect().top) / 2);

			_position.x += cosf(_attackAngle) * 5.f;
			_position.y += -sinf(_attackAngle) * 5.f;
		}

		//플레이어와 충돌 처리 되면 다시 원위치
		if (_isAttack)
		{
			_attackAngle = GetAngle(_position.x, _position.y, _tempPt.x, _tempPt.y);
			_position.x += cosf(_attackAngle) * 5.f;
			_position.y += -sinf(_attackAngle) * 5.f;
			_gauge = 1;
			_isAttack = false;
		}

		break;
	//왼쪽으로 이동 상태
	case state::L_MOVE:
		//270도보다 크면 왼쪽으로 이동
		if (_camera.rc.left > 50)
		{
			_position.x -= 12.f;
		}

		if (_camera.rc.top > 150)
		{
			_position.y -= 5.f;
		}

		//다시 돌아갈 위치 설정
		_tempPt = { _position.x, _position.y };

		break;
	//오른쪽으로 이동 상태
	case state::R_MOVE:
		//270도 보다 작으면 오른쪽으로 이동
		if (_camera.rc.right < WINSIZEX - 50)
		{
			_position.x += 12.f;
		}

		if (_camera.rc.top > 150)
		{
			_position.y -= 5.f;
		}

		//다시 돌아갈 위치 설정
		_tempPt = { _position.x, _position.y };

		break;
	//죽음 상태
	case state::DEATH:
		//충돌 렉트 없애기
		_col.rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);

		if (_position.y + _size.y / 2 < WINSIZEY)
		{
			//시체 부분 떨어뜨리기
			_position.y += 5.f;
		}
		//땅에 도착했을 때
		if (_position.y + _size.y / 2 >= WINSIZEY)
		{
			_deathTimer++;

			if (_deathTimer % 100 == 0)
			{
				OBJECTMANAGER->RemoveObject(ObjectType::Object, OBJECTMANAGER->FindObject(ObjectType::Object, "flybug"));
			}
		}

		break;
	}
	
}

void FlyBug::Render()
{
	//카메라 렉트 그리기
	Rectangle(getMemDC(), _camera.rc);
	//렉트 그리기
	Rectangle(getMemDC(), _rc);
	//충돌렉트 그리기
	Rectangle(getMemDC(), _col.rc);
	//시체처리렉트 그리기
	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), _part[i].rc);
	}
	//텍스트 출력
	sprintf(msg1, "x : %d, y : %d", _pt.x, _pt.y);
	TextOut(getMemDC(), 50, 50, msg1, strlen(msg1));
}

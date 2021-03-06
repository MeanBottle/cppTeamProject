#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

class Crab : public GameObject
{
private:
	//상태
	STATE _state;
	//상하 움직임 처리를 위한 변수
	int _move;
	bool _isUp;
	//공격 처리를 위한 변수
	int _gauge;
	float _attackAngle;
	bool _isAttack;
	bool _isAttackFinish;
	POINTFLOAT _tempPt;
	//죽음 처리를 위한 변수
	int _deathTimer;
	//카메라 구조체
	CAMERA _camera;	//플레이어를 감지하는 범위 중심점으로 부터 900
					//왔다갔다 공격하는 범위 중심점으로 부터 300
	//충돌 구조체
	COL _col[4];	//0 : top, 1: bottom, 2 : left, 3: right
	//시체처리 구조체
	PART _part[3];	//0 : left, 1 : center, 2 : right 
	//공격처리 구조체
	ATTACK _att[2];	//0 : left, 1 : right
	//플레이어와의 각도
	float _angle;
	//플레이어와의 거리
	float _dist;
	//마우스 좌표 텍스트
	char msg1[128];
	POINT _pt;
	//플레이어 클래스
	class Player* _player;
public:
	Crab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Crab();

	//충돌여부 get
	bool getIsCrush(int i) { return _col[i].isCrush; }
	//충돌여부 set
	void setIsCrush(int i, bool crush) { _col[i].isCrush = crush; }
	//플레이어 죽임여부 get
	bool getIsKill(int i) { return _col[i].isKill; }

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};


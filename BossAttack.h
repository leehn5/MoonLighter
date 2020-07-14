#pragma once
#include "BossState.h"
#include "Boss.h"

	//���� ���� �⺻ Ʋ
class BossAttack : public BossState
{
protected:
	//���⿡ �� ����.......
	int _count;
	float _timer;
	float _angle;

	Object* _area;

public:
	BossAttack(Boss* boss) : BossState(boss) {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};


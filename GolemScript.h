#pragma once
#include "Collider.h"

class GolemScript : public Collider
{
	virtual void CollisionBegin(void* obj);
	//�浹��
	virtual void CollisionPreSolve(void* obj);
	//�浹 ���� ����
	virtual void CollisionEnd(void* obj);
};


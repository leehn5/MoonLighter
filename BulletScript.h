#pragma once
#include "Collider.h"

class BulletScript : public Collider
{
public:
	//�浹�� ����
	virtual void CollisionBegin(void* obj);
	//�浹��
	virtual void CollisionPreSolve(void* obj);
	//�浹 ���� ����
	virtual void CollisionEnd(void* obj);
};


#pragma once
#include "Collider.h"
class ItemScript :	public Collider
{
public:

	//�浹�� ����
	virtual void CollisionBegin(void* obj);
	virtual void CollisionPreSolve(void* obj);
};


#pragma once
#include "Object.h"
#include "Sprite.h"

class ShopDoor :public Object
{
private:

	Sprite* _sprite;

//��� Npc�� ���̶� ��Ҵ��� �˷������
//������ ���� ���� �����Ŀ� �ٽ� �ݾ���� ��
//�ٵ� �������� ������ �����Ŀ� ������ �ȵǴϱ�
//�浹���� NPC�� ������ ����, ������ �ݰ� �̷������� �ؾߵɵ�

	//�浹�� NpcManager���� �ҰŴϱ�
	//NpcManager�� include�ؾ��ϳ�?

	//�ƴϸ� �׳� NpcManager����
	//�浹�� ����ٰ� �������ִ°� SetDoor�ص� �ɵ�

public:
	virtual void Init() override;
	virtual void Update() override;

};


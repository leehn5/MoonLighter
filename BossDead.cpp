#include "stdafx.h"
#include "BossDead.h"

void BossDead::Enter()
{
	_Bstate = "Dead";

	//�״� �̹����� �ΰ��� ������ ����....��� ����?
	//�ι�° �״� �̵̹� 41������
	_boss->GetSprite()->SetImgName("deadBoss1");
	_boss->GetSprite()->SetMaxFrameX(41);
	_boss->GetSprite()->SetFrameX(0);
	_boss->GetSprite()->SetFPS(1.0f);
	_boss->GetSprite()->SetIsLoop(false); //true �����൵ �ǰ���..?
	_boss->GetSprite()->SetPosition(_boss->GetTrans()->GetPos());

	//if (setmaxframex�� �������̸�
	// _boss->GetSprite()->SetImgName(deadBoss2);
	// �̷��� �ɱ�...?
}

void BossDead::Update()
{
}

void BossDead::Exit()
{
}

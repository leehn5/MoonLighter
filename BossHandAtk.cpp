#include "stdafx.h"
//#include "BossHandAtk.h"
//#include "BossIdle.h"
//#include "Player.h"
//
//void BossHandAtk::Enter()
//{
//	_Bstate = "Attack";
//	_obj = _boss->GetHand();
//	//_state = HANDSTATE::SHADOW;
//	_player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Will");
//	_obj = Object::CreateObject<BossHand>();
//	_obj->GetTrans()->SetPos(_player->GetTrans()->GetPos());
//}
//
//void BossHandAtk::Update()
//{
//
////	if ()
//	timer += TIMEMANAGER->getElapsedTime();
//
//	if (timer >= 0.1f)
//	{
//		switch (_state)
//		{
//		case HANDSTATE::SHADOW:
//			//player ����ٴ�
//			//�̤Ӥ����� �׸�����
//			//physic flase�λ���
//			break;
//		case HANDSTATE::HAND:
//			//img �ٲ��ֱ� ������ 
//			//physic true�λ���
//			break;
//		case HANDSTATE::END:
//			//physic flase�λ���
//			//���̵�� �ٲٱ�
//			break;
//		}
//		timer = 0;
//		_count++;
//	}
//
//	//if (_count == rocks.size() && _state == ROCKATK::END)
//	//	_boss->SetState(new BossIdle(_boss));
//}
//
//void BossHandAtk::Exit()
//{
//}

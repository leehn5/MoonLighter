#include "stdafx.h"
#include "BossHand.h"
#include "BossAttack.h"
#include "BossIdle.h"
#include "Player.h"
#include "RockCollider.h"
BossHand::BossHand()
{
}

BossHand::~BossHand()
{
}

void BossHand::Init()
{
	Object::Init();

	//_tag = "boss";
	_name = "BossHand";

	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_sprite->SetImgName("Shadow");
	_sprite->SetPosition(_trans->GetPos());
	_sprite->SetAlpha(0.3f);

	_trans->SetScale(Vector2(100,
		40));
	_trans->SetPos(_player->GetTrans()->GetPos());
	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.0f);
	_physics->GetBody()->SetFixedRotation(true);
	_physics->SetBodyActive(false);
	AddComponent<RockCollider>();
	_count = timer = 0;

	_state = HANDSTATE::SHADOW;
}

void BossHand::Update()
{
	Object::Update();

	Attack();
}

void BossHand::Render()
{
	Object::Render();
}

void BossHand::Release()
{
	SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(_physics->GetBody());
	Object::Release();

}

void BossHand::Attack()
{

	//�� ����..���� ����? 
	timer += TIMEMANAGER->getElapsedTime();

	switch (_state)
	{
	case HANDSTATE::SHADOW:
	{
		if (timer >= 5)
		{
			Vector2::GetAngle(_trans->GetPos(), _target);
			timer = 0;
		}
		else
		{
			float angle = Vector2::GetAngle(_trans->GetPos(), _player->GetTrans()->GetPos());
			Vector2 anlgePos(cosf(angle), -sinf(angle));
			
			_trans->SetPos(_trans->GetPos() + anlgePos * 70 * TIMEMANAGER->getElapsedTime());
		}
	}
	break;

	case HANDSTATE::HAND:
	{
		if (timer >= 1.f)
		{
			_physics->SetBodyActive(true);
			timer = 0;
		}
	}
	break;
	case HANDSTATE::END:
	{
		if (timer >= 2.f)
		{
			_physics->SetBodyActive(false);
			timer = 0;
		}
	}

	break;
	}
	if (timer == 0)
	{
		switch (_state)
		{
		case HANDSTATE::SHADOW:
		{
			_sprite->SetImgName("Hand");
			_sprite->SetAlpha(1.f);
			_state = HANDSTATE::HAND;

		}
			break;
		case HANDSTATE::HAND:
		{
			_state = HANDSTATE::END;

		}
			break;
		case HANDSTATE::END:
		{
			_state = HANDSTATE::SHADOW;
			_sprite->SetImgName("Shadow");
			_sprite->SetAlpha(0.3f);

		}
			break;
		}
	}
	_physics->SetBodyPosition();
	_sprite->SetPosition(_trans->GetPos());
}


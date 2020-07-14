#include "stdafx.h"
#include "Boss.h"
#include "Ability.h"
#include "SlimeEnemy.h"
#include "BossState.h"
#include "BossIdle.h"
#include "BossHand.h"
#include "RockCollider.h"

Boss::Boss()
{

}

Boss::~Boss()
{
}

void Boss::Init(Vector2 pos, vector<Tile*> tiles)
{
	Object::Init();

	_tag = "boss";
	_name = "Boss";
	_aStar = new Astar;
	_aStar->Init(tiles, Bossroom_X, Bossroom_Y);
	_ability = new Ability(100, 100, 10); //�� ũ�� ��� �ϳ�?

	//maxFrameX = 0;
	//frameY = 0;
	_sprite = AddComponent<Sprite>();
	_sprite->Init(true, true);
	_sprite->SetImgName("Open_Boss");
	_sprite->SetPosition(_trans->GetPos());
//	_sprite->SetRectColor(ColorF::Cornsilk);
	_trans->SetPos(pos);
	_trans->SetScale(Vector2(_sprite->GetGraphic()->GetFrameWidth(),
		_sprite->GetGraphic()->GetFrameHeight()));
	//_trans->SetScale(Vector2(100, 100)); //���� ����


	_physics = AddComponent<PhysicsBody>();
	_physics->Init(BodyType::DYNAMIC, 1.0f, 10.0f);
	////���󼼰��� ��Ʈ ��Ʋ���°� ����
	_physics->GetBody()->SetFixedRotation(true);

	//cout << "state ����" << endl;
	_player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Will");
	_Bstate = new BossIdle(this);
	_Bstate->Enter();
	_hand = Object::CreateObject<BossHand>(this);
	_hand->SetPlayer(_player);
	_hand->Init();
	//_hand->SetTarget(_player->GetTrans()->GetPos());
	//_hand->GetTrans()->SetPos(_player->GetTrans()->GetPos());

#pragma region ����


	//1
	Object* rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(759, 533);
	auto s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock0");
	auto p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);

	//1-2
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(583, 601);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock1");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);

	//1-3
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(411, 687);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock2");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);
	
	//2
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(896, 642);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock1");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);


	//2-2
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(791, 773);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock2");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);


	//2-3
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(651, 917);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock3");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);

	//2-4
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(511, 1037);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock3");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);

	//3
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1050, 742);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock2");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);


	//3-2
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1050, 917);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock3");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);

	//3-3

	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1050, 1076);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock0");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);



	//3-4
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1050, 1251);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock0");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);

	//4
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1195, 642);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock3");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);


	//4-2
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1317, 751);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock0");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);


	//4-3
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1449, 896);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock1");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);



	//4-4
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1589, 1026);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock1");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);

	//5
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1367, 547);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock0");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);





	//5-2
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1539, 633);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock1");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);




	//5-3
	rock = Object::CreateObject<Object>(this);
	rock->GetTrans()->SetScale(100, 109);
	rock->GetTrans()->SetPos(1723, 719);
	s = rock->AddComponent<Sprite>();
	s->Init();
	s->SetImgName("Boss_Rock2");
	p = rock->AddComponent<PhysicsBody>();
	p->Init(BodyType::STATIC, 1, 1);
	p->SetBodyPosition();
	_rocks.push_back(rock);







	

#pragma endregion

	for (Object* r : _rocks)
	{
		r->GetComponent<PhysicsBody>()->SetBodyActive(false);
		r->SetIsActive(false);
		r->AddComponent<RockCollider>();
	}

}

void Boss::Update()
{
	Object::Update();
	_physics->SetBodyPosition();
	_Bstate->Update();

	//�̰� ���� ������Ʈ ���� ���ƾ� ���� �Ʒ��� ���ƾ� ���� �𸣰����ϱ� ������ ���� �÷��ּ��� ������ A��Ÿ �ִ°ſ���
	//�׸��� �̰� ���� ���������� �����°ǵ� �������� �����ϱ� Ȥ�� ������ �ؿ� ���� �Ųٷ� ���°� ���ּ���
	//cout << _ability->GetCurrentHP() << endl;
	for (int i = 0; i<_enemys.size();i++)
	{
		if (!_enemys[i]->GetIsActive())
		{
			SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(_enemys[i]->GetComponent<PhysicsBody>()->GetBody());
			_enemys[i]->Release();
			_enemys.erase(_enemys.begin() + i);
			break;
		}
		if (_enemys[i]->GetMove())
		{
			_enemys[i]->SetPath(_aStar->pathFinder(_enemys[i]->GetTrans()->GetPos(), _player->GetTrans()->GetPos()));
		}
		
	}
	//for (int i = _enemys.size(); i <= 0; i--)
	//{
	//	if (!_enemys[i]->GetIsActive())
	//	{
	//		SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(_enemys[i]->GetComponent<PhysicsBody>()->GetBody());
	//		_enemys[i]->Release();
	//		_enemys.erase(_enemys.begin() + i);
	//		break;
	//	}
	//	if (_enemys[i]->GetMove())
	//	{
	//		_enemys[i]->SetPath(_aStar->pathFinder(_enemys[i]->GetTrans()->GetPos(), _player->GetTrans()->GetPos()));
	//	}
	//}



	_hand->Update();
	//_sprite->GetCurrentFrameX();
}

void Boss::Render()
{
	Object::Render();

	//_hp->Render(Vector2(170, 30), Vector2((hpMaxX + 60) / (player->GetAbility()->GetMaxHP() / player->GetAbility()->GetCurrentHP()), hpMaxY), 0, false, 0.7f, PIVOT::LEFT_TOP, false);
	
}

void Boss::Release()
{
	for (Object* r : _rocks)
		SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(r->GetComponent<PhysicsBody>()->GetBody());
	
	for (Object* e : _enemys)
		SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(e->GetComponent<PhysicsBody>()->GetBody());
	
	_hand->Release();

	Object::Release();

}

void Boss::Attack()
{
	switch (_phase)
	{
	case PHASE::ROCK:
		break;
	case PHASE::HAND:
		break;
	case PHASE::SLIME:
		break;
	}
}

void Boss::SetState(BossState* state)
{
	_Bstate->Exit();
	delete _Bstate;
	_Bstate = state;
	_Bstate->Enter();
}

//void Boss::SetHand(BossHand* hand)
//{
//	hand->Init();
//	delete hand;
//}


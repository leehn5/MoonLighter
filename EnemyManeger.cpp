#include "stdafx.h"
#include "EnemyManeger.h"
//#include "Bullet.h"

EnemyManeger::EnemyManeger()
{

	GRAPHICMANAGER->AddFrameImage("Ebullet", L"resource/img/Enemy/enemy_bullet.png", 6, 1);
	GRAPHICMANAGER->AddFrameImage("Ebullet_C", L"resource/img/Enemy/bullet_collision.png", 5, 1);
	_BobjPool = new BulletObjPool;
	_BobjPool->Init(100, "Ebullet", "bullet", "Ebullet", _room, 5);
}

void EnemyManeger::Init(Dungeon* room)
{
	//�Ѿ�

	//�ش� �������� �����ֱ�
	
	_astar = new Astar;
	_astar->Init(room->GetTiles(), Dungeon_X, Dungeon_Y);

	//��������ȯ���� �÷��̾� ��������
	_player = (Player*) SCENEMANAGER->GetNowScene()->GetChildFromName("Will");
	_room = room;
	SetEnemy();

	//Bullet* _bullet = new Bullet;
	//_bullet->Init("Ebullet","bullet", "Ebullet");
	
	
}

void EnemyManeger::Update()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (!_vEnemy[i]->GetIsActive())
		{
			SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(_vEnemy[i]->GetPhysics()->GetBody());
			_vEnemy[i]->Release();
			_vEnemy.erase(_vEnemy.begin() + i);
			break;
		}
		if (_vEnemy[i]->GetMove())
		{
			if(Vector2::Distance(_player->GetTrans()->GetPos(), _vEnemy[i]->GetTrans()->GetPos()) > 80 &&
				Vector2::Distance(_player->GetTrans()->GetPos(), _vEnemy[i]->GetTrans()->GetPos()) < 600)
				_vEnemy[i]->SetPath(_astar->pathFinder(_vEnemy[i]->GetTrans()->GetPos() - _room->GetTrans()->GetPos(), _player->GetTrans()->GetPos() - _room->GetTrans()->GetPos()));
		}
		if (dynamic_cast<GolemEnemy*>(_vEnemy[i]))
		{
			if (Vector2::Distance(_player->GetTrans()->GetPos(), _vEnemy[i]->GetTrans()->GetPos()) <= GolemEnemy::GetAtkRange() && !dynamic_cast<EnemyAttack*>(_vEnemy[i]->GetState()))
			{ 
				_vEnemy[i]->SetAtk(true);
			}
		}
	}
	
	for (int i = 0; i < _BobjPool->GetActivePoolSize(); i++)
	{
		if (_BobjPool->GetActivePool()[i]->GetCollision())
		{
			_BobjPool->GetActivePool()[i]->SetCollision(false);
			_BobjPool->InssertPool(i);
			break;
		}
	}
	Fire();
}

void EnemyManeger::Release()
{
	for (int i = 0; i < _BobjPool->GetActivePoolSize(); i++)
	{
		_BobjPool->InssertPool(i);
	}

	for (Enemy* e : _vEnemy)
	{
		SCENEMANAGER->GetNowScene()->GetWorld()->DestroyBody(e->GetComponent<PhysicsBody>()->GetBody());
	
		e->Release();
	}
	_vEnemy.clear();

	

}

void EnemyManeger::Render()
{
	for (Object* a : _BobjPool->GetActivePool()) a->Render();

	
}

void EnemyManeger::SetEnemy()
{
	int rand = RND->getFromIntTo(2,10);
	//int rand = 1;
	for (int i = 0; i < rand; i++)
	{
		//int Ernad =2;
		int Ernad = RND->getInt(3);
		switch (Ernad)
		{
		case 0:
		{
			int size = RND->getFromIntTo(2, 5);
			for (int i = 0; i < size; i++)
			{
				SlimeEnemy* enemy = Object::CreateObject<SlimeEnemy>();
				Vector2 start(_room->GetTrans()->GetPos() + Vector2(160, 104));
				Vector2 end(_room->GetTrans()->GetPos() + Vector2(TILEWIDTH * Dungeon_X, TILEHEIGHT * Dungeon_Y) - Vector2(160, 104));
				Vector2 ePos(RND->getFromFloatTo(start.x, end.x), RND->getFromFloatTo(start.y, end.y));
				enemy->Init(ePos);
				_vEnemy.push_back(enemy);
			}
		}
		break;

		case 1:
		{
				GolemEnemy* enemy = Object::CreateObject<GolemEnemy>();
				Vector2 start(_room->GetTrans()->GetPos() + Vector2(160, 104));
				Vector2 end(_room->GetTrans()->GetPos() + Vector2(TILEWIDTH * Dungeon_X, TILEHEIGHT * Dungeon_Y) - Vector2(160, 104));
				Vector2 ePos(RND->getFromFloatTo(start.x, end.x), RND->getFromFloatTo(start.y, end.y));
				enemy->Init(ePos);
				_vEnemy.push_back(enemy);

		}
			
		break;

		case 2:
		{
			MintPotEnemy* enemy = Object::CreateObject<MintPotEnemy>();
			Vector2 start(_room->GetTrans()->GetPos() + Vector2(160, 104));
			Vector2 end(_room->GetTrans()->GetPos() + Vector2(TILEWIDTH * Dungeon_X, TILEHEIGHT * Dungeon_Y) - Vector2(160, 104));
			Vector2 ePos(RND->getFromFloatTo(start.x, end.x), RND->getFromFloatTo(start.y, end.y));
			enemy->Init(ePos);
			_vEnemy.push_back(enemy);
		}
		break;

		}
	}
}

void EnemyManeger::Fire()
{
	if (_BobjPool->GetPool().size())
	{
		for (Enemy* e : _vEnemy)
		{
			if (e->GetName() == "Pot")
			{
				MintPotEnemy* pot = (MintPotEnemy*)e;
				if (pot->GetAtk())
				{
					if (_BobjPool->GetPool().size())
					{ 
						_BobjPool->GetPoolObject()->Fire(Vector2(pot->GetTrans()->GetPos().x,
							pot->GetTrans()->GetPos().y), (int)pot->GetDir()*90*DegToRad, 200);
						_BobjPool->InssertActiveObject();
					}
				}
			}
		}
	}
	for (int i = 0; i < _BobjPool->GetActivePoolSize(); i++)
	{
		if (!_BobjPool->GetActivePool()[i]->GetIsActive())
		{
			_BobjPool->GetActivePool()[i]->GetComponent<PhysicsBody>()->GetBody()->SetActive(false);
			_BobjPool->InssertPool(i);
		}
	}
}


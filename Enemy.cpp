#include "stdafx.h"
#include "Enemy.h"
#include "Ability.h"
#include "Bullet.h"
#include "Item.h"
#include "EnemyScript.h"
#include "ETCS.h"
#include "Player.h"
#include "Inventory.h"
//#include "Player.h"
//���漱�� ���� ��...?



EnemyIdle* EnemyIdle::instance;
EnemyMove* EnemyMove::instance;
EnemyAttack* EnemyAttack::instance;
EnemyHit* EnemyHit::instance;
EnemyDead* EnemyDead::instance;


Enemy::Enemy()
{

	SetState(EnemyIdle::GetInstance());

	//cout << "�����ںκ� ���̵�" << endl;
	
}

Enemy::~Enemy()
{
}
//ó�� ���ʹ� ���� ���úκ� ���� Enemy::Init()���� ���� ������
void Enemy::SetState(EnemyBasic* state)
{

	state->Init(this);
	if (dynamic_cast<EnemyMove*>(this->state) || dynamic_cast<EnemyAttack*>(this->state)) delete this->state;
	this->state = state;
}

void Enemy::Init()
{
	Object::Init();

	_tag = "enemy";
	maxFrameX = 0;
	frameY = 0;
	_sprite = AddComponent<Sprite>();
	_sprite->SetMaxFrameX(maxFrameX);
	_sprite->SetFrameY(frameY);
	_player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Will");

	AddComponent<EnemyScript>();
}

void Enemy::Update()
{
	Object::Update();
	
	 //�̹����� �ٲ��ִµ� ��...currentimg(y) �̷���?
	 //if (angle > (3 * PI) / 4 && angle < (5 * PI) / 4) _dir = DIRECTION::LEFT;
	 //if (angle > (4 * PI) / 4 && angle < (7 * PI) / 4) _dir = DIRECTION::RIGHT;
	 //if (angle > PI / 4 && angle < (3 * PI) / 4) _dir = DIRECTION::TOP;
	 //if (angle > PI / 4 && angle < (7 * PI) / 4) _dir = DIRECTION::BOTTOM;

	//���� Update �ɾ���
	state->Update(this);

	if (_angle >= 45 * DegToRad && _angle < 135 * DegToRad)_dir = DIRECTION::TOP;
	else if (_angle >= 135 * DegToRad && _angle < 180 * DegToRad)_dir = DIRECTION::LEFT;
	else if (_angle <= -135 * DegToRad && _angle > -180 * DegToRad)_dir = DIRECTION::LEFT;

	else if (_angle <= -45 * DegToRad && _angle > -135 * DegToRad)_dir = DIRECTION::BOTTOM;

	else if (_angle <= 0 * DegToRad && _angle > -45 * DegToRad)_dir = DIRECTION::RIGHT;
	else if (_angle >= 0 * DegToRad && _angle < 45 * DegToRad)_dir = DIRECTION::RIGHT;


	if (!dynamic_cast<EnemyAttack*>(state))
	{
		if (GetPath().size())
		{
			if (_changePos)
			{
				_changePos = false;
				_angle = (int)  Vector2::GetAngle(_trans->GetPos(), *_path.begin());
			}
			Vector2 dir = *_path.begin() - _trans->GetPos();
			Vector2 pos = _trans->GetPos();
			_trans->SetPos(pos + dir.Nomalized() * _speed * TIMEMANAGER->getElapsedTime());

			if (Vector2::Distance(*_path.begin(), _trans->GetPos()) <= 15.5f)
			{
				_changePos = true;
				_path.erase(_path.begin());
			}
		}
		switch (_dir)
		{
		case DIRECTION::LEFT:
			_sprite->SetFrameY(0);
			break;
		case DIRECTION::RIGHT:
			_sprite->SetFrameY(1);
			break;
		case DIRECTION::TOP:
			_sprite->SetFrameY(2);
			break;
		case DIRECTION::BOTTOM:
			_sprite->SetFrameY(3);
			break;
		}
	}
	_physics->SetBodyPosition();


	if (GetHP()->IsDead())
	{
		SetState(EnemyDead::GetInstance());
	}

}

void Enemy::Render()
{
	Object::Render();
	
}

void Enemy::SetPath(list<Vector2> _path)
{
	this->_path.clear();
	this->_path = _path;
}




#include "SlimeEnemy.h"
#include "GolemEnemy.h"
#include "MintPotEnemy.h"

void EnemyBasic::Update(Enemy* _sEnemy)
{
	/*if (_sEnemy->GetHP()->IsDead())
	{
		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
	}*/
	if (_sEnemy->GetAtk()) SetEnemyState(_sEnemy, EnemyAttack::GetInstance());
}

//������������� Idle ���������������
EnemyIdle* EnemyIdle::GetInstance()
{

	//instance�� null�̸� 
	if (instance == nullptr)
	{
		//enemy���´� idle
		instance = new EnemyIdle();
	}
	//instance = new EnemyIdle(); ��� �������ϱ� EnemyIdle�� ��
	//���� state->Update(this); �ɾ������ϱ� Idle instance�� ������
	return instance;
}

void EnemyIdle::Init(Enemy* _sEnemy)
{
	//cout << "�� �ȵ���?" << endl;
}

void EnemyIdle::Update(Enemy* _sEnemy)
{
	EnemyBasic::Update(_sEnemy);
	Release(_sEnemy);
	//cout << "������?" << endl;
}
void EnemyIdle::Release(Enemy* _sEnemy)
{
	//  ü���� 0 �̸� �׾��
	SetEnemyState(_sEnemy, EnemyMove::GetInstance());
}
//������������� Move ��������������
EnemyMove* EnemyMove::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EnemyMove();
	}

	return new EnemyMove();
}

void EnemyMove::Init(Enemy* _sEnemy)
{
	//cout << "move ����?" << endl;
	_sEnemy->SetMove(true);
	timer = 0;
}

void EnemyMove::Update(Enemy* _sEnemy)
{
	EnemyBasic::Update(_sEnemy);


	switch (_sEnemy->GetDir())
	{
	case DIRECTION::LEFT:
		_sEnemy->GetSprite()->SetFrameY(0);
		break;
	case DIRECTION::RIGHT:
		_sEnemy->GetSprite()->SetFrameY(1);
		break;
	case DIRECTION::TOP:
		_sEnemy->GetSprite()->SetFrameY(2);
		break;
	case DIRECTION::BOTTOM:
		_sEnemy->GetSprite()->SetFrameY(3);
		break;
	}
	_sEnemy->SetMove(false);

	timer += TIMEMANAGER->getElapsedTime();

	if (timer >0.5f) {
		_sEnemy->SetMove(true);
		timer = 0;
	}

}

void EnemyMove::Release(Enemy* _sEnemy)
{
	SetEnemyState(_sEnemy, EnemyIdle::GetInstance());
}
//������������ Attack �������������
EnemyAttack* EnemyAttack::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EnemyAttack();
	}

	return new EnemyAttack();
}

void EnemyAttack::Init(Enemy* _sEnemy)
{
	//cout << "���� ���Դ�?" << endl;
}

void EnemyAttack::Update(Enemy* _sEnemy)
{
	
	if (_sEnemy->GetAtk())
	{
		_sEnemy->Attack();
		_sEnemy->SetAtk(false);
	}
	_sEnemy->SetAngle(Vector2::GetAngle(_sEnemy->GetTrans()->GetPos(), _sEnemy->GetPlayer()->GetTrans()->GetPos()));
	//cout << "����� ����!" << endl;
	if (_sEnemy->GetName() == "Golem")
	{
		if (_sEnemy->GetSprite()->GetCurrentFrameX() == 6) _sEnemy->Attack();
		if(_sEnemy->GetSprite()->GetCurrentFrameX() >= _sEnemy->GetSprite()->GetMaxFrameX())
			Release(_sEnemy);
	}
	//���⼭ ��Ʈ�׾Ƹ� ����
	else if (_sEnemy->GetName() == "Pot")
	{
		if(_sEnemy->GetSprite()->GetCurrentFrameX() >= _sEnemy->GetSprite()->GetMaxFrameX())
			Release(_sEnemy);
	}
}

void EnemyAttack::Release(Enemy* _sEnemy)
{
	_sEnemy->AttackEnd();
	//if �÷��̾����� ������ �´� ���·� ����
	SetEnemyState(_sEnemy, EnemyIdle::GetInstance());
	if (_sEnemy->GetName() == "Golem")
	{
		_sEnemy->GetSprite()->SetImgName("Golem");
	}
	if (_sEnemy->GetName() == "Pot")
	{
		_sEnemy->GetSprite()->SetImgName("enemyPot");
	}
}
//������������� Hit ��������������

EnemyHit* EnemyHit::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EnemyHit();
	}

	return instance;
}

void EnemyHit::Init(Enemy* _sEnemy)
{
	//cout << "����� �¾Ҵٰ� �ϴ� �κ�" << endl;
}

void EnemyHit::Update(Enemy* _sEnemy)
{
	EnemyBasic::Update(_sEnemy);
	//cout << "�÷��̾����� �¾ҳ�?" << endl;
	Release(_sEnemy);
}

void EnemyHit::Release(Enemy* _sEnemy)
{
	// if �¾����� idle�� ����
	// else if �ȸ¾����� �ٽ� ������
	// else if ü���� 0 �̸� �׾��!
	

}
//������������� Dead �������������

EnemyDead* EnemyDead::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EnemyDead();
	}

	return instance;
}

void EnemyDead::Init(Enemy* _sEnemy)
{

	
	//cout << "����� ���� ����" << endl;
}

void EnemyDead::Update(Enemy* _sEnemy)
{
	//	cout << "�׾���?" << endl;
	Release(_sEnemy);
}

void EnemyDead::Release(Enemy* _sEnemy)
{
	

	//if (_sEnemy->GetHP()->IsDead())
	//cout << "�׾��� �Ф�" << endl;
	_sEnemy->SetIsActive(false);
	if (SCENEMANAGER->GetNowScene()->GetName() == "BossRoom")return;
	Player* player = (Player*)SCENEMANAGER->GetNowScene()->GetChildFromName("Will");
	if (player->GetInventory()->GetInventorySize()>=20)return;

	int some = RND->getInt(3);
	//int some = 1;

	for (int i = 0; i < some; i++)
	{
		int rand =  RND->getInt(10);
		switch (rand)
		{
		case 0: Item::CreateItem<Vine>(_sEnemy->GetTrans()->GetPos()); break;
		case 1: Item::CreateItem<Crystal_Energy>(_sEnemy->GetTrans()->GetPos()); break;
		case 2: Item::CreateItem<amulet_ring>(_sEnemy->GetTrans()->GetPos()); break;
		case 3: Item::CreateItem<Treated_Wood>(_sEnemy->GetTrans()->GetPos()); break;
		case 4: Item::CreateItem<Broken_Sword>(_sEnemy->GetTrans()->GetPos()); break;
		case 5: Item::CreateItem<Energy_Crystal>(_sEnemy->GetTrans()->GetPos()); break;
		case 6: Item::CreateItem<Naja_Note>(_sEnemy->GetTrans()->GetPos()); break;
		case 7: Item::CreateItem<Reinforced_Steel_G>(_sEnemy->GetTrans()->GetPos()); break;
		case 8: Item::CreateItem<Golem_Core>(_sEnemy->GetTrans()->GetPos()); break;
		case 9: Item::CreateItem<Familiar_Egg>(_sEnemy->GetTrans()->GetPos()); break;
		case 10: Item::CreateItem<Reinforced_Steel_Y>(_sEnemy->GetTrans()->GetPos()); break;
		}
	}
}

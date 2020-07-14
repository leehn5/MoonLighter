#include "stdafx.h"
#include "EnemyState.h"
//#include "Hp.h"
//#include "SlimeEnemy.h"
//#include "GolemEnemy.h"
//#include "MintPotEnemy.h"
//#include "Boss.h"
//
//
//
//EnemyIdle* EnemyIdle::instance;
//EnemyMove* EnemyMove::instance;
//EnemyAttack* EnemyAttack::instance;
//EnemyHit* EnemyHit::instance;
//EnemyDead* EnemyDead::instance;
//
////hp�� 0�̸� �׾��
//
//
//void EnemyBasic::Update(Enemy* _sEnemy)
//{
//	if (_sEnemy->GetHP()->IsDead())
//	{
//		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	}
//	if (_sEnemy->GetAtk()) SetEnemyState(_sEnemy, EnemyAttack::GetInstance());
//}
//
////������������� Idle ���������������
//EnemyIdle* EnemyIdle::GetInstance()
//{
//
//	//instance�� null�̸� 
//	if (instance == nullptr)
//	{
//		//enemy���´� idle
//		instance = new EnemyIdle();
//	}
//	//instance = new EnemyIdle(); ��� �������ϱ� EnemyIdle�� ��
//	//���� state->Update(this); �ɾ������ϱ� Idle instance�� ������
//	return instance;
//}
//
//void EnemyIdle::Init(Enemy* _sEnemy)
//{
//	//sprite ����?
//	cout << "�� �ȵ���?" << endl;
//}
//
//void EnemyIdle::Update(Enemy* _sEnemy)
//{
//	//if (KEYMANAGER->isOnceKeyDown('0'))
//		//hp �� 0�̸�
//	EnemyBasic::Update(_sEnemy);
//	Release(_sEnemy);
//	cout << "������?" << endl;
//
//}
//void EnemyIdle::Release(Enemy* _sEnemy)
//{
//	cout << "move�� ��!!!" << endl;
//
//	//if �÷��̾ ������
//	// else if ü���� 0 �̸� �׾��!
//	if (_sEnemy->GetHP()->IsDead())
//	{
//		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	}
//	else
//		SetEnemyState(_sEnemy, EnemyMove::GetInstance());
//}
////������������� Move ��������������
//EnemyMove* EnemyMove::GetInstance()
//{
//	if (instance == nullptr)
//	{
//		instance = new EnemyMove();
//	}
//
//	return new EnemyMove();
//}
//
//void EnemyMove::Init(Enemy* _sEnemy)
//{
//	cout << "move ����?" << endl;
//	//a*? bool������.?
//	_sEnemy->SetMove(true);
//	timer = 0;
//}
//
//void EnemyMove::Update(Enemy* _sEnemy)
//{
//	EnemyBasic::Update(_sEnemy);
//
//	if (_sEnemy->GetMove())
//		_sEnemy->SetMove(false);
//	if (_sEnemy->GetPath().size())
//	{
//		Vector2 dir = *_sEnemy->GetPath().begin() - _sEnemy->GetTrans()->GetPos();
//		Vector2 pos = _sEnemy->GetTrans()->GetPos();
//		_sEnemy->SetAngle(Vector2::GetAngle(pos, *_sEnemy->GetPath().begin()));
//		_sEnemy->GetTrans()->SetPos(pos + dir.Nomalized() * _sEnemy->GetSpeed() * TIMEMANAGER->getElapsedTime());
//	}
//	_sEnemy->GetPhysics()->SetBodyPosition();
//	//cout << "����� ���� ���� �ε�ĩ" << endl;
//	//loat a = RND->getFloat(10000000);
//	//if(a<30)
//	timer += TIMEMANAGER->getElapsedTime();
//	if (timer > 3)
//		Release(_sEnemy);
//
//}
//
//void EnemyMove::Release(Enemy* _sEnemy)
//{
//
//	//if ������ �÷��̾ ������ �����ϰ�
//	//SetEnemyState(_sEnemy, EnemyAttack::GetInstance());
//	// else if ������ �÷��̾ ������ �ٽ� ����
//	//SetEnemyState(_sEnemy, EnemyMove::GetInstance());
//	cout << "�ٽ� ����?" << endl;
//	SetEnemyState(_sEnemy, EnemyIdle::GetInstance());
//	// else if ü���� 0 �̸� �׾��!
//
//	//if (_sEnemy->GetHP()->IsDead())
//	//{
//	//	SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	//}
//	//else SetEnemyState(_sEnemy, EnemyAttack::GetInstance());
//}
////������������ Attack �������������
//EnemyAttack* EnemyAttack::GetInstance()
//{
//	if (instance == nullptr)
//	{
//		instance = new EnemyAttack();
//	}
//
//	return instance;
//}
//
//void EnemyAttack::Init(Enemy* _sEnemy)
//{
//
//	//cout << "���� ���Դ�?" << endl;
//}
//
//void EnemyAttack::Update(Enemy* _sEnemy)
//{
//	if (_sEnemy->GetHP()->IsDead())
//	{
//		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	}
//	_sEnemy->Attack();
//	//cout << "����� ����!" << endl;
//
//	Release(_sEnemy);
//}
//
//void EnemyAttack::Release(Enemy* _sEnemy)
//{
//	_sEnemy->SetAtk(false);
//	//if �÷��̾����� ������ �´� ���·� ����
//	SetEnemyState(_sEnemy, EnemyHit::GetInstance());
//	// else if �ƴϸ� idle�� ����
//	//SetEnemyState(_sEnemy, EnemyIdle::GetInstance());
//	// else if ü���� 0 �̸� �׾��!
//	if (_sEnemy->GetHP()->IsDead())
//	{
//		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	}
//}
////������������� Hit ��������������
//
//EnemyHit* EnemyHit::GetInstance()
//{
//	if (instance == nullptr)
//	{
//		instance = new EnemyHit();
//	}
//
//	return instance;
//}
//
//void EnemyHit::Init(Enemy* _sEnemy)
//{
//	//cout << "����� �¾Ҵٰ� �ϴ� �κ�" << endl;
//}
//
//void EnemyHit::Update(Enemy* _sEnemy)
//{
//	EnemyBasic::Update(_sEnemy);
//	//cout << "�÷��̾����� �¾ҳ�?" << endl;
//	Release(_sEnemy);
//}
//
//void EnemyHit::Release(Enemy* _sEnemy)
//{
//	// if �¾����� idle�� ����
//	// else if �ȸ¾����� �ٽ� ������
//	// else if ü���� 0 �̸� �׾��!
//	if (_sEnemy->GetHP()->IsDead())
//	{
//		SetEnemyState(_sEnemy, EnemyDead::GetInstance());
//	}
//
//}
////������������� Dead �������������
//
//EnemyDead* EnemyDead::GetInstance()
//{
//	if (instance == nullptr)
//	{
//		instance = new EnemyDead();
//	}
//
//	return instance;
//}
//
//void EnemyDead::Init(Enemy* _sEnemy)
//{
//	//Item::CreateItem(_sEnemy->GetTrans()->GetPos());
//	//cout << "����� ���� ����" << endl;
//}
//
//void EnemyDead::Update(Enemy* _sEnemy)
//{
//	//	cout << "�׾���?" << endl;
//	Release(_sEnemy);
//}
//
//void EnemyDead::Release(Enemy* _sEnemy)
//{
//	//if (_sEnemy->GetHP()->IsDead())
//	//cout << "�׾��� �Ф�" << endl;
////	_sEnemy->Release();
//}

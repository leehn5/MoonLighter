#pragma once
#include "Object.h"
#include "Player.h"
//#include "Player.h" //h����? cpp����?

enum class DIRECTION
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

//���������� ���� ���漱��
class EnemyBasic;
class EnemyIdle;
class EnemyMove;
class EnemyAttack;
class EnemyHit;
class EnemyDead;

//hp, bullet
class Ability;
//class Bullet;

class Enemy : public Object
{
protected:
	Sprite* _sprite;
	PhysicsBody* _physics;
	Player* _player;
	//�������� �������� Ʋ�� �Ǵ� EnemyBasic�� Enemy���� �˷��� ��������
	EnemyBasic* state;
	DIRECTION _dir;	//����
	float _speed;
	Ability* _ability;
	int _angle;
	list<Vector2> _path;

	bool move;
	bool _isAtk;

	bool _changePos = true;

public:
	Enemy();
	virtual~Enemy(); //���
	
	
	int maxFrameX;
	int frameY;
	
	//���������� ���� Enemy���� �˷��ֱ� ���� �Լ�
	void SetState(EnemyBasic* state);
	virtual void Init();
	virtual void Update();	
	virtual void Render();
	virtual void Attack() {};
	virtual void AttackEnd() {};
//get,set�Լ� ������ ��
	Ability* GetHP() { return _ability; }
	PhysicsBody* GetPhysics() { return _physics; }
	DIRECTION GetDir() { return _dir; }
	Sprite* GetSprite() { return _sprite; }
	float GetAngle() { return _angle; }
	void SetAngle(float angle) { _angle = angle; }
	float GetSpeed() { return _speed; }
	EnemyBasic* GetState() { return state; }
	Player* GetPlayer() { return _player; }

//A*
	void SetPath(list<Vector2> _path);
	list<Vector2> GetPath() { return _path; }
	void SetMove(bool active) { move = active; }
	bool GetMove() { return move; }
	bool GetAtk() { return _isAtk; }
	void SetAtk(bool active) { _isAtk = active; }
//������ ���� ���� ��������

};



//��������������� ���� �����������������
class EnemyBasic
{
protected:
	//�������� ���ο��� ������ ���¸� �Դ� ���� �ϱ� ���� ��.
	void SetEnemyState(Enemy* _sEnemy, EnemyBasic* _EnemyState)
	{
		_sEnemy->SetState(_EnemyState);
	}
public:
	//basic�̶� �� �ʱ�ȭ ���ش�.
	virtual void Init(Enemy* _sEnemy) {};
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy) {};

};
//������������� Idle ���������������
class EnemyIdle : public EnemyBasic
{
	//���¸� ��üȭ ����
	static EnemyIdle* instance;

public:
	//Idle�� �ƴ� �ٸ� ���µ����� ������ �ν��Ͻ�
	static EnemyIdle* GetInstance();

	virtual void Init(Enemy* _sEnemy);
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy);
};
//������������� Move ��������������
class EnemyMove : public EnemyBasic
{
	static EnemyMove* instance;
	float timer;

public:
	static EnemyMove* GetInstance();

	virtual void Init(Enemy* _sEnemy);
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy);
};
//������������ Attack �������������
class EnemyAttack : public EnemyBasic
{
	static EnemyAttack* instance;

public:
	static EnemyAttack* GetInstance();

	virtual void Init(Enemy* _sEnemy);
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy);
};

//������������� Hit ��������������
class EnemyHit : public EnemyBasic
{
	static EnemyHit* instance;

public:
	static EnemyHit* GetInstance();

	virtual void Init(Enemy* _sEnemy);
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy);
};
//������������� Dead �������������

class EnemyDead : public EnemyBasic
{
	static EnemyDead* instance;

public:
	static EnemyDead* GetInstance();

	virtual void Init(Enemy* _sEnemy);
	virtual void Update(Enemy* _sEnemy);
	virtual void Release(Enemy* _sEnemy);
};
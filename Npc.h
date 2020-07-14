#pragma once
#include "Object.h"
//#include "ShopStand.h"
#include "ShopStandManager.h"
#include "CheckStand.h"
#include "Sprite.h"
#define NPDSPEED 70

class ShopStandManager;
class CheckStand;
class NpcShopState;

//���� ���� ���������(destination�̶� �ٸ�)
enum NPCTHOUGHT
{
	WINDOW,//â���� �������
	CHOOSE,
	GOHOME, //�����������
	BUY, //������(�ټ������)
	NOTBUY, //�Ȼ�����
	END
};

//���� ��� �ִ���
enum NPCNOWPOSITION
{
	POS_ENTER,
	POS_WINDOW,
	POS_STAND1,
	POS_STAND2,
	POS_STAND3,
	POS_STAND4,
	POS_CHECKSTAND,
	POS_DOOR,
	POS_END
};

class Npc :	public Object
{
private:
	Sprite* _sprite;

	NPCTHOUGHT _npcThought; //���ؾ�����..
	NPCNOWPOSITION _npcNowPosition;

	float _timer;

	//float _speed;
	bool _isShopSOn;	//���Ǵ�� �浹������
	bool _isCheckSOn;	//����� �浹������

	bool _isAstarOn;	//astar �޾ƾ��ϴ� ��������

	NpcShopState* _npcShopState;

	//ShopStand* _shopStand; //���ĵ带 �����ߵ��� �Ŵ����� �����ߵ��� �𸣰���
	ShopStandManager* _shopStandMgr;
	CheckStand* _checkStand;

	list<Vector2> _lPath; //�����ϴ� ��

public:
	Npc() {};
	~Npc() {};

	virtual void Init(string imgkey, Vector2 pos);
	virtual void Update() override;
	virtual void Render() override;

	void SetPath(list<Vector2> lpath);
	void Move();

	NpcShopState* GetNpcState() { return _npcShopState; }

	
	//���� ���ǿ�
	void ChangeState(NpcShopState* state);

	//����/�ǸŴ� ��ũ��
	void SetCheckStandLink(CheckStand* checkstand) { _checkStand = checkstand; }
	CheckStand* GetCheckStand() { return _checkStand; }
	void SetShopStandLink(ShopStandManager* shopstand) { _shopStandMgr = shopstand; }
	ShopStandManager* GetShopStandMgr() { return _shopStandMgr; }

	//����� ���Ǵ�� �浹��ING���� üũ�� bool
	void SetIsShopSOn(bool shop) { _isShopSOn = shop; }
	bool GetIsShopSOn() { return _isShopSOn; }
	void SetIsCheckSOn(bool check) { _isCheckSOn = check; }
	bool GetIsCheckSOn() { return _isCheckSOn; }
	void SetIsAstarOn(bool ast) { _isAstarOn = ast; }
	bool GetIsAstarOn() { return _isAstarOn; }

	//NPC ���� ���ϰ���� ��������..
	void SetNpcThought(NPCTHOUGHT npcthought) { _npcThought = npcthought; }
	NPCTHOUGHT GetNpcThought() { return _npcThought; }
	//��ġ ����
	void SetNpcNowPosition(NPCNOWPOSITION npcnowposition) { _npcNowPosition = npcnowposition; }
	NPCNOWPOSITION GetNpcNowPosition() { return _npcNowPosition; }

	NpcShopState* GetStatePointer() { return _npcShopState; }
	list<Vector2>* GetPath() { return &_lPath; }


};
#pragma once
#include "Npc.h"
#include "Astar.h"
#include "ShopScene.h"

class ShopStandManager;
class CheckStand;
class ShopScene;

enum DESTINATION
{
	DES_WINDOW,
	DES_STAND1,
	DES_STAND2,
	DES_STAND3,
	DES_STAND4,
	DES_CHECKSTAND,
	DES_DOOR,
	DES_END
};
class NpcManager
{
private:
	Npc* _npc;
	vector<Npc*> _vNpc;
	ShopStandManager* _shopStandMgr;
	CheckStand* _checkStand;

	Vector2 _positions[DESTINATION::DES_END];

	Astar* _ast;

	int _counter; //�� �ð���ŭ �帥 �� ���ο� ���Ǿ� ������
	int _timer;

	int _counter2;
public:
	void Init(ShopScene* parent);
	void Update();
	void Release();
	

	void MakeNpc();
	void SetAstar(); //������ �����ִ°���
	void AstarFunction(int i, int asttar); //astar ���ư��� ��

	void CheckStandCollision(); //����� �浹
	void ShopStandCollision(); //���Ǵ�� �浹

	void SetCheckStandLink(CheckStand* checkstand) { _checkStand = checkstand; }
	void SetShopStandMgrLink(ShopStandManager* shopstsandmgr) { _shopStandMgr = shopstsandmgr; }
	vector<Npc*> GetNpcVector() { return _vNpc; }

};


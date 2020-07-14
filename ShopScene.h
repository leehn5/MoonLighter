#pragma once
#include "Scene.h"
#include "Player.h"
#include "NpcManager.h"
#include "CheckStand.h"
#include "NpcShopState.h"
#include "ShopStandManager.h"
#include "Maptool.h"
#include "ShopDoor.h"
#include "UiManager.h"

#define SHOPTILEMAXX 22
#define SHOPTILEMAXY 28

class NpcManager;

class ShopScene : public Scene
{
private:
	typedef enum PlayerPosition : byte
	{
		Up,
		Down,
	}PP;

private:
	Player* _player;
	NpcManager* _npcMgr;			 //npc �Ŵ���
	CheckStand* _checkStand;		 //����
	NpcShopState* _npcShopState;	 //Npc ����
	ShopStandManager* _shopStandMgr; //���Ǵ� �Ŵ���
	ShopDoor* _shopDoor;			 //���� ���Թ�
	vector<Tile*> _tiles;
	tagTile _tagTiles[SHOPTILEMAXX * SHOPTILEMAXY];
	PP _pp;
	UiManager* UI;
	float _fadeAlpha;

public:
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render()override;
	void SetUp();
	void FadeOut();

	vector<Tile*>GetTiles() { return _tiles; }
	
};


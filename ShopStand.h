#pragma once
#include "Object.h"
#include "Item.h"
#include"Maptool.h"
#include"Inventory.h"
class ShopStand :public Object
{
private:
	Vector2 _itemPos; //������ �̹��� ������ ��ǥ
	string _item; //�ö� ������ �̹��� ����
	//bool _isActive; //�θ� ���, �̹��� �ö󰡸� true ����
	Tile* _tiles[TILENUMX * TILENUMY];
	tagTile _tagTiles[TILENUMX * TILENUMY];
	//Item* _item;
	tagItemInfo item;
	bool _isItemOn;

	bool _isInUse; //npc�� �浹�ؼ� ������̸� �������

public:

	virtual void Init(Vector2 pos, Vector2 scale);
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render()override;

	//�̹��� ������ �κ��丮���� ��� �� �� ����..
	void BuyItem();

	bool GetIsInUse() { return _isInUse; }
	void SetIsInUse(bool isinuse) { _isInUse = isinuse; }

	bool GetIsItemOn() { return _isItemOn; }
	Vector2 GetItemPos() { return _itemPos; }

	void SetItemInfo(tagItemInfo item);
	tagItemInfo GetItem() { return item; }
};


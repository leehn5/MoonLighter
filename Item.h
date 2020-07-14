#pragma once
#include "Object.h"

enum class EItemType
{
	useable,
	etc
};

class Item : public Object
{

protected:

	typedef Object super;

	//�������� �Ҹ�ǰ���� �׿� �ٸ� ���������� ���Ѵ�.
	EItemType _type;

	//����, �������� ������ ��Ÿ����.
	int _price, _maxCount;

	//�������� ����� �̹����� ����
	Sprite* _image;

	//�������� �����ȿ��� �����Ѵٸ� �ÿ��̾ ���󰡾���
	bool _isDungeon = true;

	//���������� ���� ����
	float _followingMovement;

	PhysicsBody* _physics;

public:
	Item();
	~Item() {}

	virtual void Init();
	virtual void Init(Vector2 pos) {};
	virtual void Update();
	virtual void Render();
	virtual void Release();

	//���� �������� �������� ������
	void FollowPlayer(Vector2 playerPos);

	//Get Something
	int GetMaxCount() { return _maxCount; }
	int GetPrice() { return _price; }
	Vector2 GetPos() { return _trans->GetPos(); }
	EItemType GetType() { return _type; }

	//Set Something
	//void SetItemCount(int count) {
	//	_MaxCount += count;
	//}

	void SetPrice(int price) {
		_price = price;
	}

	void SetPos(Vector2 pos) { _trans->SetPos(pos); }
	void SetInDG(bool _isTrue) { _isDungeon = _isTrue; }

	template <typename T>
	static T* CreateItem(Vector2 pos);
	PhysicsBody* GetPhysics() { return _physics; }
};

#include"Item.hpp"
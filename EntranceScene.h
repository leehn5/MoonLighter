#pragma once
#include "Scene.h"
#include "Player.h"
#include "Maptool.h"
#include "UiManager.h"

class EntranceScene : public Scene
{
private:
	vector<Tile*> tiles;
	tagTile _tagTiles[TILENUMX * TILENUMY];
	
	Player* _player;
	UiManager* UI;

	float _fadeAlpha;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	void SetUp();
};


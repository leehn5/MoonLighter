#include "stdafx.h"
#include "TownScene.h"
#include"Inventory.h"
#include "NpcShopState.h"

void TownScene::Init()
{
	Scene::Init();

#pragma region SetTilePage1
	GRAPHICMANAGER->AddImage("build_fountain", L"resource/img/Object/build_fountain.png");
	GRAPHICMANAGER->AddImage("build_Retaile", L"resource/img/Object/build_Retaile.png");
	GRAPHICMANAGER->AddImage("build_Shop", L"resource/img/Object/build_Shop.png");
	GRAPHICMANAGER->AddImage("build_Top1", L"resource/img/Object/build_Top1.png");
	GRAPHICMANAGER->AddImage("build_Well", L"resource/img/Object/build_Well.png");

	GRAPHICMANAGER->AddFrameImage("door", L"resource/img/Object/door.png", 5, 1);
	GRAPHICMANAGER->AddFrameImage("doordown", L"resource/img/Object/doordown.png", 5, 1);

	GRAPHICMANAGER->AddImage("dgLobbyEntry", L"resource/img/Object/dgLobbyEntry.png");
	GRAPHICMANAGER->AddImage("dgLobbyLeft", L"resource/img/Object/dgLobbyLeft.png");
	GRAPHICMANAGER->AddImage("dgLobbyRight", L"resource/img/Object/dgLobbyRight.png");
	GRAPHICMANAGER->AddImage("build_Bottom3", L"resource/img/Object/build_Bottom3.png");
	GRAPHICMANAGER->AddImage("bench", L"resource/img/Object/bench.png");
	GRAPHICMANAGER->AddImage("buildBoard", L"resource/img/Object/buildBoard.png");
	GRAPHICMANAGER->AddImage("build_Bottom1", L"resource/img/Object/build_Bottom1.png");
	GRAPHICMANAGER->AddImage("build_Bottom2", L"resource/img/Object/build_Bottom2.png");
	GRAPHICMANAGER->AddImage("VillageLamps1", L"resource/img/Object/VillageLamps1.png");
	GRAPHICMANAGER->AddImage("build_Enchant", L"resource/img/Object/build_Enchant.png");
	GRAPHICMANAGER->AddImage("VillageLamps2", L"resource/img/Object/VillageLamps2.png");

	GRAPHICMANAGER->AddFrameImage("tree", L"resource/img/Object/tree.png", 4, 1);

	GRAPHICMANAGER->AddImage("build_Forge", L"resource/img/Object/build_Forge.png");
	GRAPHICMANAGER->AddImage("dungeonRock", L"resource/img/Object/dungeonRock.png");
	GRAPHICMANAGER->AddImage("forgeBoard", L"resource/img/Object/forgeBoard.png");
	GRAPHICMANAGER->AddImage("potionBoard", L"resource/img/Object/potionBoard.png");
	GRAPHICMANAGER->AddImage("empty", L"resource/img/empty.png");
#pragma endregion

	GRAPHICMANAGER->AddFrameImage("Girl1", L"resource/img/Smithy/Girl.png", 9, 4);
	GRAPHICMANAGER->AddFrameImage("Guy1", L"resource/img/Smithy/Guy.png", 9, 4);
	GRAPHICMANAGER->AddFrameImage("Kid1", L"resource/img/Smithy/Kids.png", 6, 4);
	GRAPHICMANAGER->AddFrameImage("Lunk1", L"resource/img/Smithy/Lunk.png", 9, 4);

	GRAPHICMANAGER->AddImage("town_map", L"resource/img/Map/map.png");

	GRAPHICMANAGER->AddFrameImage("set_tile", L"set_tile3.png", 4, 6);
	GRAPHICMANAGER->AddFrameImage("set_tile_dungeon", L"set_tile_dungeon.png", 4, 6);

	_smith = GRAPHICMANAGER->AddFrameImage("Smith", L"resource/img/Smithy/Smith_Dott.png", 4, 1);

	_j = GRAPHICMANAGER->AddImage("j", L"resource/img/Smithy/J.png");



	_frameCount = _frameX = 0;


	_name = "Town";

	_player = Object::CreateObject<Player>();
	_player->Init();

	std::ifstream file("PlayerInfo.json");
	string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	json j = json::parse(content);
	
	string prevScene = j["Position"]["curScene"];
	_prevScene = prevScene;

	if (_prevScene == "Shop")
	{
		_player->GetTrans()->SetPos(Vector2(1969, 528));
	}
	else if (_prevScene == "Entrance")
	{
		//_player->GetTrans()->SetPos(Vector2(1893, 385));
		_player->GetTrans()->SetPos(Vector2(2746, 752));
	}
	else
	{
		_player->GetTrans()->SetPos(Vector2(100, 600) + Vector2(0, -14));
	}

	_player->GetPhysics()->SetBodyPosition();

	_player->GetSprite()->SetPosition(_player->GetTrans()->GetPos() + Vector2(0,-14));

	_smithy = new Smithy;
	_smithy->Init(_player->GetInventory());


	CreateNPC();
	SetDest();

	_fadeAlpha = 1.0f;

	SetUp();


	_aStar = new Astar;
	_aStar->Init(this->_tiles, TILENUMX, TILENUMY);

	UI = new UiManager;
	UI->Init();

	//_smithy->SetSmithPos(_smith->GetTrans()->GetPos());
}

void TownScene::Update()
{

	_smithy->Update();

	_frameCount++;
	if (_frameCount >= 5)
	{
		_frameX++;
		//_frameCount = 0;

		if (_frameX >= 4)
			_frameX = 0;
	}
	CAMERA->SetPosition(_player->GetTrans()->GetPos(), "town_map");

	
	if (_fadeAlpha >= 0.0f)
	{
		_fadeAlpha -= 0.7f * TIMEMANAGER->getElapsedTime();
		if (_fadeAlpha < 0.0f)
		{
			_fadeAlpha = 0.0f;
		}
	}

	if (_player->GetTrans()->GetPos().x >= 1930.0f && _player->GetTrans()->GetPos().x <= 2000 &&
		_player->GetTrans()->GetPos().y >= 490 && _player->GetTrans()->GetPos().y <= 540)
	{
		_player->SetIsInteraction(true);
	}

	if (_player->GetIsInteraction() && _player->GetTrans()->GetPos().x >= 1930.0f && _player->GetTrans()->GetPos().x <= 2000 &&
		_player->GetTrans()->GetPos().y >= 490 && _player->GetTrans()->GetPos().y <= 540)
	{
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			SCENEMANAGER->changeScene("Shop");
			return;
		}
	}

	if (_player->GetTrans()->GetPos().x >= 3000.0f &&
		_player->GetTrans()->GetPos().y >= 719 && _player->GetTrans()->GetPos().y <= 854)
	{
		SCENEMANAGER->changeScene("Entrance");
	}

	MoveNPC();

	CheckPos();


	Scene::Update();
}

void TownScene::Release()
{
	_player->Release();

	 
	for (int i = _tiles.size(); i <= 0; i--)
		_tiles[i]->Release();

	_tiles.clear();

	for (Npc* n :_vNpc)
		n->Release();
	_vNpc.clear();

	_destination.clear();
	_destCount.clear();
	_waitCount.clear();

	_smithy->Release();


	Scene::Release();
}

/*void TownScene::Update()
{
	if((_player->GetTrans()->GetPos().x >= 1955 - 100 && _player->GetTrans()->GetPos().y >= 500
		&& _player->GetTrans()->GetPos().x <= 1955 + 100 && _player->GetTrans()->GetPos().y <= 500 + 20))
	{
		//cout << "h" << endl;
		//smithy->SetShow(false);
		SCENEMANAGER->changeScene("Shop");
	}
	 

	CAMERA->SetPosition(Vector2(_player->GetTrans()->GetPos()), "town_map");

	MoveNPC();

	CheckPos();


	Scene::Update();
}*/

void TownScene::SetUp()
{
	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			int index = j + TILENUMX * i;

			Tile* tile = Object::CreateObject<Tile>();
			tile->Init(j, i);
			tile->AddComponent<Sprite>();
			tile->SetAttribute("None");
			tile->SetAllowsRender(false);
			tile->SetIsActive(false);
			_tiles.push_back(tile);

			_tagTiles[index].attribute = "None";
			_tagTiles[index].imgKey = "None";
			_tagTiles[index].isFrame = false;
			_tagTiles[index].pivot = PIVOT::CENTER;
		}
	}


	HANDLE file;
	DWORD read;

	//string str = titleLoad;
	//str += ".map";
	string str = "Town.map";

	//file = CreateFile(titleLoad, GENERIC_READ, 0, NULL,
	file = CreateFile(str.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file != INVALID_HANDLE_VALUE)
	{
		//MessageBox(_hWnd, "load วัดู", str.c_str(), MB_OK);

		ReadFile(file, _tagTiles, sizeof(tagTile) * TILENUMX * TILENUMY, &read, NULL);
		CloseHandle(file);

		for (int i = 0; i < TILENUMX * TILENUMY; i++)
		{
			// _tiles[] initialization
			_tiles[i]->SetImgName("None");
			_tiles[i]->SetAttribute("None");
			_tiles[i]->SetIsFrame(false);
			_tiles[i]->SetPivot(PIVOT::CENTER);

			if (_tiles[i]->GetChildren().size() > 0) _tiles[i]->RemoveChild(_tiles[i]->GetChildren()[0]);


			// value setting
			_tiles[i]->SetAttribute(_tagTiles[i].attribute);
			_tiles[i]->SetImgName(_tagTiles[i].imgKey);
			_tiles[i]->SetIsFrame(_tagTiles[i].isFrame);
			_tiles[i]->SetPivot(_tagTiles[i].pivot);


			if (_tiles[i]->GetImgName() != "None")
			{
				_tiles[i]->SetIsActive(true);
				_tiles[i]->AddChild(Object::CreateObject<Object>());

				_tiles[i]->GetChildren()[0]->GetTrans()->SetPos(_tiles[i]->GetTrans()->GetPos() + Vector2(0, TILEHEIGHT / 2));
				if (_tiles[i]->GetPivot() == RIGHT_BOTTOM) _tiles[i]->GetChildren()[0]->GetTrans()->SetPos(_tiles[i]->GetTrans()->GetPos() + Vector2(TILEWIDTH / 2, TILEHEIGHT / 2));

				_tiles[i]->GetChildren()[0]->GetTrans()->SetScale(GRAPHICMANAGER->FindImage(_tiles[i]->GetImgName())->GetFrameWidth(), GRAPHICMANAGER->FindImage(_tiles[i]->GetImgName())->GetFrameHeight());
				_tiles[i]->GetChildren()[0]->GetTrans()->SetRect();

				if (_tiles[i]->GetIsFrame())
				{
					_tiles[i]->GetChildren()[0]->AddComponent<Sprite>()->Init(true, true);
					_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetImgName(_tiles[i]->GetImgName());
					_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetFPS(0.5f);
					_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPivot(_tiles[i]->GetPivot());
				}
				else
				{
					_tiles[i]->GetChildren()[0]->AddComponent<Sprite>()->SetImgName(_tiles[i]->GetImgName());
					_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPivot(_tiles[i]->GetPivot());
				}
				_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetPosition(_tiles[i]->GetChildren()[0]->GetTrans()->GetPos());
				_tiles[i]->GetChildren()[0]->GetComponent<Sprite>()->SetSize(_tiles[i]->GetChildren()[0]->GetTrans()->GetScale());
			}
			if (_tiles[i]->GetAttribute() == "Wall")
			{
				auto p = _tiles[i]->AddComponent<PhysicsBody>();
				p->Init(BodyType::STATIC, 1, 1);
				p->SetBodyPosition();
			}
		}
	}
	else MessageBox(_hWnd, "can not found the file.", str.c_str(), MB_OK);
}

void TownScene::Render()
{
	GRAPHICMANAGER->DrawImage("town_map", Vector2(0, 0), 1.0f, LEFT_TOP, true);


	Scene::Render();

	_player->GetInventory()->Render();


	if (!_smithy->GetSmithy())
	{
		_smith->FrameRender(Vector2(2470, 1080), _frameX, 1, PIVOT::CENTER);

		if (ShowJ())
		{
			_j->Render(Vector2(2520, 1040), 1.f, PIVOT::CENTER, true);
		}
	}

	if (_smithy->GetSmithy())
	{
		if (!(_player->GetTrans()->GetPos().x > 2470 - 200 && _player->GetTrans()->GetPos().y >= 1080
			&& _player->GetTrans()->GetPos().x < 2470 + 200 && _player->GetTrans()->GetPos().y <= 1080 + 200))
		{
			_smithy->SetShow(false);
		}
	}

	UI->Render();
	_smithy->Render();

	//wchar_t buffer[128];
	//swprintf(buffer, 128, L"x: %1.f, y:%1.f", _player->GetTrans()->GetPos().x, _player->GetTrans()->GetPos().y);
	//GRAPHICMANAGER->Text(Vector2(WINSIZEX / 2, WINSIZEY / 2), buffer, 20, 500, 300, ColorF::White);

	GRAPHICMANAGER->DrawFillRect(Vector2(WINSIZEX / 2 + CAMERA->GetPosition().x, WINSIZEY / 2 + CAMERA->GetPosition().y),
		Vector2(WINSIZEX, WINSIZEY), 0.0f, ColorF::Black, _fadeAlpha, PIVOT::CENTER, true);
}

bool TownScene::ShowJ()
{
	if (_player->GetTrans()->GetPos().x > 2470 - 200 && _player->GetTrans()->GetPos().y >= 1080
		&& _player->GetTrans()->GetPos().x < 2470 + 200 && _player->GetTrans()->GetPos().y <= 1080 + 250)
	{
		_smithy->SetIn(true);
		_player->SetIsInteraction(true);
		return true;
	}
	else
	{
		_smithy->SetIn(false);
		_player->SetIsInteraction(false);
		return false;
	}
}

void TownScene::CreateNPC()
{
	Npc* npc;

	for (int i = 0; i < NPCCOUNT; i++)
	{
		npc = Object::CreateObject<Npc>();
		npc->SetIsCheckSOn(false);
		npc->SetIsAstarOn(true);

		int a = RND->getInt(4);

		if (a == 0)
		{
			npc->Init("Girl1", Vector2(632, 980));
			npc->SetName("girl");
			_vNpc.push_back(npc);
		}
		if (a == 1)
		{
			npc->Init("Guy1", Vector2(2208, 1447));
			npc->SetName("guy");
			_vNpc.push_back(npc);
		}
		if (a == 2)
		{
			npc->Init("Kid1", Vector2(1300, 800));
			npc->SetName("kid");
			_vNpc.push_back(npc);
		}
		if (a == 3)
		{
			npc->Init("Lunk1", Vector2(1490, 2100));
			npc->SetName("lunk");
			_vNpc.push_back(npc);
		}
	}
}

void TownScene::FoundWay(Npc* npc, int i)
{
	if (npc->GetIsAstarOn())
	{
		npc->SetPath(_aStar->pathFinder(npc->GetTrans()->GetPos(), ReturnDest(i)));

		npc->SetIsAstarOn(false);
	}
}

void TownScene::SetDest()
{
	_destination.push_back(Vector2(2517, 809));
	_destination.push_back(Vector2(1679,1295));
	_destination.push_back(Vector2(1912,2092));
	_destination.push_back(Vector2(418,2083));
	_destination.push_back(Vector2(618,957));
	_destination.push_back(Vector2(435,734));
	_destination.push_back(Vector2(801,293));

	for (int i = 0; i < NPCCOUNT; i++)
	{
		_destCount.push_back(-1);
		_waitCount.push_back(0);
	}
}

Vector2 TownScene::ReturnDest(int i)
{
	if(_destCount[i] == -1)
		_destCount[i] = RND->getInt(7);

	return _destination[_destCount[i]];
}

void TownScene::MoveNPC()
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		//if(_vNpc[i]->GetNpcState() == Np cIdle)
		FoundWay(_vNpc[i], i);
	}
}

void TownScene::CheckPos()
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		if (_vNpc[i]->GetTrans()->GetPos().x <= _destination[_destCount[i]].x + 100
			&& _vNpc[i]->GetTrans()->GetPos().x >= _destination[_destCount[i]].x - 100
			&& _vNpc[i]->GetTrans()->GetPos().y <= _destination[_destCount[i]].y + 100
			&& _vNpc[i]->GetTrans()->GetPos().y >= _destination[_destCount[i]].y - 100)
		{
			_waitCount[i]++;

			if (_waitCount[i] >= 20)
			{
				_destCount[i] = RND->getInt(7);
				_waitCount[i] = 0;
			}
		}
	}
}

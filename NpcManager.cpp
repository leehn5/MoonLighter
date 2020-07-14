#include "stdafx.h"
#include "NpcManager.h"
#include "ShopStandManager.h"
void NpcManager::Init(ShopScene* parent)
{
	_counter = 0;
	_timer = RND->getFromIntTo(30, 100);

	_ast = new Astar;
	_ast->Init(parent->GetTiles(), SHOPTILEMAXX, SHOPTILEMAXY);
	//int a;

	//실제로 가야하는 곳
	//_positions[DESTINATION::WINDOW] = Vector2(523, 615);  
	//_positions[DESTINATION::STAND1] = Vector2(287, 525); 
	//_positions[DESTINATION::STAND2] = Vector2(190, 525); 
	//_positions[DESTINATION::STAND3] = Vector2(226, 675); 
	//_positions[DESTINATION::STAND4] = Vector2(316, 616); 
	//_positions[DESTINATION::CHECKSTAND] = Vector2(430, 600);
	//_positions[DESTINATION::DOOR] = Vector2(406, 734); 

	_positions[DESTINATION::DES_WINDOW] = Vector2(515, 550); //창문앞
	_positions[DESTINATION::DES_STAND1] = Vector2(320, 510); //1번(1사분면)
	_positions[DESTINATION::DES_STAND2] = Vector2(160, 510); //2번
	_positions[DESTINATION::DES_STAND3] = Vector2(160, 560); //3번
	_positions[DESTINATION::DES_STAND4] = Vector2(320, 560); //4번
	_positions[DESTINATION::DES_CHECKSTAND] = Vector2(430, 610); //계산대
	_positions[DESTINATION::DES_DOOR] = Vector2(400, 640); //문앞

}
void NpcManager::Update()
{
	//NPC가 4명 미만이면 더 넣어줘라	
	if (_vNpc.size() < 4)
	{
		_counter++;
		if (_counter == _timer)
		{
			MakeNpc();
			_counter = 0;
			_timer = RND->getFromIntTo(30, 100);
		}
	}

	//if (KEYMANAGER->isOnceKeyDown('L')) MakeNpc();


	//집에가면 지우기

	//충돌
	//CheckStandCollision(); //계산대
	//ShopStandCollision(); //가판대

	//Astar
	SetAstar();
	//AstarFunction(); //이건 일단 치워..



	//if (_vNpc.size())
	//{
	//	cout << "ASTAR ON : " << _vNpc[0]->GetIsAstarOn() << endl;
	//	if (_vNpc[0]->GetPath().size())
	//	{
	//		cout << "Path size : " << _vNpc[0]->GetPath().size() << endl;
	//	}
	//}
}

void NpcManager::Release()
{
	//isactive가 false인 npc벡터를 찾아서
	//false인 애가 있으면 지워버려
}

void NpcManager::MakeNpc()
{
	_npc = Object::CreateObject<Npc>();
	_npc->SetCheckStandLink(_checkStand);
	_npc->SetIsCheckSOn(false);
	_npc->SetIsShopSOn(false);
	_npc->SetIsAstarOn(true); //ast 받을지말지
	//_npc->SetDestination(Vector2(392, 700)); //시작하면 문으로 들어가라고
	//_npc->Move(); //astar 일단 여기다가 담아놓음
	cout << _vNpc.size() << endl;
	if (_vNpc.size() < 4)
	{
		int a = RND->getInt(4);

		if (a == 0)
		{
			_npc->Init("Girl", Vector2(400, 700));
			_npc->SetName("girl");
			_vNpc.push_back(_npc);
			return;
		}
		if (a == 1)
		{
			_npc->Init("Guy", Vector2(400, 700));
			_npc->SetName("guy");
			_vNpc.push_back(_npc);
			return;
		}
		if (a == 2)
		{
			_npc->Init("Kid", Vector2(400, 700));
			_npc->SetName("kid");
			_vNpc.push_back(_npc);
			return;
		}
		if (a == 3)
		{
			_npc->Init("Lunk", Vector2(400, 700));
			_npc->SetName("lunk");
			_vNpc.push_back(_npc);
			return;
		}
	}

	else
	{
		for (int i = 0; i < _vNpc.size(); i++)
		{
			if (_vNpc[i]->GetName() != "girl")
			{
				_npc->Init("Girl", Vector2(400, 700));
				_npc->SetName("girl");
				_vNpc.push_back(_npc);
				return;
			}
			else if (_vNpc[i]->GetName() != "guy")
			{
				_npc->Init("Guy", Vector2(400, 700));
				_npc->SetName("guy");
				_vNpc.push_back(_npc);
				return;
			}
			else if (_vNpc[i]->GetName() != "kid")
			{
				_npc->Init("Kid", Vector2(400, 700));
				_npc->SetName("kid");
				_vNpc.push_back(_npc);
				return;
			}
			else if (_vNpc[i]->GetName() != "lunk")
			{
				_npc->Init("Lunk", Vector2(400, 700));
				_npc->SetName("lunk");
				_vNpc.push_back(_npc);
				return;
			}
		}
	}
}

//
////계산대랑 충돌
//void NpcManager::CheckStandCollision()
//{
//	for (int i = 0; i < _vNpc.size(); i++)
//	{
//		int D = getDistance(
//			_vNpc[i]->GetTrans()->GetPos().x, //엔피씨 위치랑
//			_vNpc[i]->GetTrans()->GetPos().y,
//			_checkStand->GetTrans()->GetPos().x,// 계산대 위치
//			_checkStand->GetTrans()->GetPos().y);
//		//거리가 반지름 더한거보다 작아야 충돌임
//		if (D < _vNpc[i]->GetTrans()->GetScale().x / 2 + _checkStand->GetTrans()->GetScale().x / 2)
//		{
//			_vNpc[i]->SetIsCheckSOn(true); //NPC가 계산대랑 충돌중 On!!!!!!!!!
//			_checkStand->SetStandisInUse(true); //계산대가 사용중 ON!!!!!!!!!
//		}
//	}
//}
//
////가판대랑 충돌
//void NpcManager::ShopStandCollision()
//{
//	for (int i = 0; i < _vNpc.size(); i++)
//	{
//		for (int j = 0; j < _shopStandMgr->GetShopStandVector().size(); j++)
//		{
//			int D = getDistance(
//				_vNpc[i]->GetTrans()->GetPos().x, //엔피씨 위치랑
//				_vNpc[i]->GetTrans()->GetPos().y,
//				_shopStandMgr->GetShopStandVector()[j]->GetTrans()->GetPos().x, //테이블위치
//				_shopStandMgr->GetShopStandVector()[j]->GetTrans()->GetPos().y);
//			//거리가 반지름 더한거보다 작아야 충돌임
//			if (D < _vNpc[i]->GetTrans()->GetScale().x / 2 + _shopStandMgr->GetShopStandVector()[j]->GetTrans()->GetScale().x / 2)
//			{
//				_vNpc[i]->SetIsShopSOn(true); //NPC가 가판대랑 충돌중 On!!!!!!!!!
//				_shopStandMgr->GetShopStandVector()[j]->SetIsInUse(true); //가판대가 사용중 ON!!!!!!!!!
//
//				cout << "가판대!!!" << endl;
//			}
//		}
//	}
//}

//상태 조건을 여기다가 걸어줘서 위치를 옮겨줘야함
void NpcManager::SetAstar()
{
	//얘가 뭘하려고 여기있는지 매니저에서 다 체크하고 해줘야함
	for (int i = 0; i < _vNpc.size(); i++) //npc숫자만큼 검사한다
	{


		int a = RND->getInt(3); //랜덤값 받을 변수
		if (_vNpc[i]->GetNpcThought() != NPCTHOUGHT::BUY)
		{
			switch (a)
			{
			case 0:
			{
				_vNpc[i]->SetNpcThought(NPCTHOUGHT::GOHOME);
				AstarFunction(i, DESTINATION::DES_DOOR);
			}
			break;
			case 1:
			{
				_vNpc[i]->SetNpcThought(NPCTHOUGHT::WINDOW);
				AstarFunction(i, DESTINATION::DES_WINDOW);
			}
			break;
			case 2:
			{
				_vNpc[i]->SetNpcThought(NPCTHOUGHT::CHOOSE);
				int randChoose = RND->getInt(4);
				switch (randChoose)
				{
				case 0:
					AstarFunction(i, DESTINATION::DES_STAND1);
					break;
				case 1:
					AstarFunction(i, DESTINATION::DES_STAND2);
					break;
				case 2:
					AstarFunction(i, DESTINATION::DES_STAND3);
					break;
				case 3:
					AstarFunction(i, DESTINATION::DES_STAND4);
					break;
				}
			}
			break;

			}
		}

		//계산대 앞에 있음(바로 집에 갈거임)
		if (Vector2::Distance(_vNpc[i]->GetTrans()->GetPos(), Vector2(430, 540)) < 80)
		{
			_vNpc[i]->SetNpcNowPosition(NPCNOWPOSITION::POS_CHECKSTAND);
			if(_vNpc[i]->GetNpcThought() == NPCTHOUGHT::BUY)
				AstarFunction(i, DESTINATION::DES_DOOR);
		}
		//문앞에 있음(집에 가야하는 상태)
		if (_vNpc[i]->GetTrans()->GetPos().x > 401 && _vNpc[i]->GetTrans()->GetPos().x < 411 &&
			_vNpc[i]->GetTrans()->GetPos().y > 729 && _vNpc[i]->GetTrans()->GetPos().y < 739)
		{
			//_vNpc[i]->SetNpcThought(NPCTHOUGHT::GOHOME); //창문앞에서 셋팅 해주긴 해줌..
			_vNpc[i]->SetNpcNowPosition(NPCNOWPOSITION::POS_DOOR);
			if (_vNpc[i]->GetNpcThought() == NPCTHOUGHT::BUY)
			{

				_vNpc[i]->SetIsActive(false);
			}
			//어디로 가라고 명령은 안함 갈데없음
			//npcstate가 이 위치인지 체크해서 isactive=false; 해줄거임
		}
		//창문앞에 있음
		if (_vNpc[i]->GetTrans()->GetPos().x > 518 && _vNpc[i]->GetTrans()->GetPos().x < 528 &&
			_vNpc[i]->GetTrans()->GetPos().y > 610 && _vNpc[i]->GetTrans()->GetPos().y < 620 && _vNpc[i]->GetNpcThought() != NPCTHOUGHT::BUY)
		{
			_vNpc[i]->SetNpcNowPosition(NPCNOWPOSITION::POS_WINDOW); //창문앞임
		}
		//계산대
		for (int j = 0; j < _shopStandMgr->GetShopStandVector().size(); j++)//가판대체크
		{
			//조건이 채워졌으면
			if (_shopStandMgr->GetShopStandVector()[j]->GetIsInUse() == false && //아무도없음
				_shopStandMgr->GetShopStandVector()[j]->GetIsItemOn() == true) //아이템 있음
			{
				//판매대 앞에 도착했음
				if (Vector2::Distance(_vNpc[i]->GetTrans()->GetPos(), _shopStandMgr->GetShopStandVector()[j]->GetTrans()->GetPos()) < 80)
				{
					switch (j)
					{
					case 0:
						_vNpc[i]->SetNpcNowPosition(NPCNOWPOSITION::POS_STAND1);
						break;
					case 1:
						_vNpc[i]->SetNpcNowPosition(NPCNOWPOSITION::POS_STAND2);
						break;
					case 2:
						_vNpc[i]->SetNpcNowPosition(NPCNOWPOSITION::POS_STAND3);
						break;
					case 3:
						_vNpc[i]->SetNpcNowPosition(NPCNOWPOSITION::POS_STAND4);
						break;
					}
					//도착했으면 누가 쓰고있나 다시 체크해..
					//쓰고있으면 for문 빠져나가서 가판대 번호에 ++해
					if (_shopStandMgr->GetShopStandVector()[j]->GetIsInUse()&& _vNpc[i]->GetNpcThought()!= NPCTHOUGHT::BUY)
					{
						int buyRand = RND->getInt(2);
						switch (buyRand)
						{
						case 0:
						{
							_vNpc[i]->SetNpcThought(NPCTHOUGHT::GOHOME);
							AstarFunction(i, DESTINATION::DES_DOOR);
						}
							break;
						case 1:
						{
							_vNpc[i]->SetNpcThought(NPCTHOUGHT::WINDOW);
							AstarFunction(i, DESTINATION::DES_WINDOW);
						}
							break;
						}
						
					}
					else
					{
						_shopStandMgr->GetShopStandVector()[j]->SetIsInUse(true);

						int buyRand = RND->getInt(2);
						if (buyRand&& _vNpc[i]->GetNpcThought() != NPCTHOUGHT::BUY)
						{
							_shopStandMgr->GetShopStandVector()[j]->BuyItem();
							_vNpc[i]->SetNpcThought(NPCTHOUGHT::BUY);
							//AstarFunction(i, DESTINATION::DES_CHECKSTAND);
							_vNpc[i]->SetIsActive(false);
							break;
						}
						else if(_vNpc[i]->GetNpcThought() != NPCTHOUGHT::BUY)
						{
							_shopStandMgr->GetShopStandVector()[j]->SetIsInUse(false);

							int buyRand = RND->getInt(2);
							switch (buyRand)
							{
							case 0:
							{
								_vNpc[i]->SetNpcThought(NPCTHOUGHT::GOHOME);
								AstarFunction(i, DESTINATION::DES_DOOR);
							}
							break;
							case 1:
							{
								_vNpc[i]->SetNpcThought(NPCTHOUGHT::WINDOW);
								AstarFunction(i, DESTINATION::DES_WINDOW);
							}
							break;
							}


						}
					}
				}
			}
			if (!_shopStandMgr->GetShopStandVector()[j]->GetIsItemOn()&& _vNpc[i]->GetNpcThought() != NPCTHOUGHT::BUY)
			{
				int buyRand = RND->getInt(2);
				switch (buyRand)
				{
				case 0:
				{
					_vNpc[i]->SetNpcThought(NPCTHOUGHT::GOHOME);
					AstarFunction(i, DESTINATION::DES_DOOR);
				}
				break;
				case 1:
				{
					_vNpc[i]->SetNpcThought(NPCTHOUGHT::WINDOW);
					AstarFunction(i, DESTINATION::DES_WINDOW);
				}
				break;
				}

			}
		}
		if (!_vNpc[i]->GetIsActive())
		{
			_vNpc[i]->Release();
			_vNpc.erase(_vNpc.begin() + i);
			break;
		}

	}

}
void NpcManager::AstarFunction(int i, int asttar)
{
	if (_vNpc[i]->GetIsAstarOn())
	{
		_vNpc[i]->SetPath(_ast->pathFinder( //길찾기 함수를 부른다 //여기까지 들어옴 
			_vNpc[i]->GetTrans()->GetPos(), //NPC의 위치를 찾고 //여기서 터지는거같음
			_positions[asttar])); //가야할 위치를 받아옴 //이 숫자 일단 랜덤넣어둠

		_vNpc[i]->SetIsAstarOn(false);
	}

}




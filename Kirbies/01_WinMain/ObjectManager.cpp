#include "pch.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Bottom.h"
#include "Image.h"

ObjectManager::ObjectManager()
{
	//ObjectLayer 별로 벡터 하나씩 맵에 집어 넣는다.
	for (int i = 0; i < (int)ObjectLayer::End; ++i)
	{
		vector<GameObject*> emptyVector;
		mObjectList.insert(make_pair((ObjectLayer)i, emptyVector));
	}
}
void ObjectManager::Init()
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Init();
		}
	}
}

void ObjectManager::Release()
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Release();
			SafeDelete(iter->second[i]);
		}
	}
}



void ObjectManager::Update()
{
	//bottom
	Bottom* bottom = (Bottom*)FindObject(ObjectLayer::Bottom, "Bottom");
	//player
	Player* player = (Player*)FindObject(ObjectLayer::Player, "1");
	//enemy-여러게 불러와야한다.

	//player-bottom 판정
	if (player != nullptr)
	{
		int x = player->GetX();
		for (int y = player->GetY() - 10; y < player->GetY() + 20; y++)
		{
			//int y = mY + mSizeY / 2;
			COLORREF pixelColor1 = GetPixel(bottom->GetImage()->GetHDC(),
				x, y);
			if (pixelColor1 != RGB(255, 0, 255))
			{
				player->SetY(player->GetY() - player->GetSizeY() / 2);
				//mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
				break;
			}
		}
		int xleft = player->GetX() - player->GetSizeX() / 2;
		for (int y = player->GetY() - 50; y < player->GetY(); y++)
		{
			COLORREF pixelColor = GetPixel(bottom->GetImage()->GetHDC(),
				xleft, y);

			if (pixelColor != RGB(255, 0, 255))
			{
				player->SetX(xleft + player->GetSizeX() / 2);
				//mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
				break;
			}

		}
	}

	////player distroy
	//if (player->GetHp()<=0)
	//{
	//	player->SetIsDestroy(true);
	//}
	//내일 할일 player mHp 만들기 enemy mHp,mDamage만들기 Get, Set포함

	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			//DISTROY
			if (iter->second[i]->GetIsDestroy() == true)
			{
				iter->second[i]->Release();
				SafeDelete(iter->second[i]);
				iter->second.erase(iter->second.begin() + i);
				--i;
				continue;
			}
			//ACTIVE
			if (iter->second[i]->GetIsActive() == true)
			{
				iter->second[i]->Update();
			}
		}
	}
}

void ObjectManager::Render(HDC hdc)
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetIsActive() == true)
			{
				iter->second[i]->Render(hdc);
			}
		}
	}
}

void ObjectManager::AddObject(ObjectLayer layer, GameObject* object)
{
	//map도 배열연산자가 정의되어 있다. 
	//단, 실제 배열처럼 동작하는게 아니라.[]연산자 내부에 find함수를 써서 동작함
	//그래서 결국 find쓰는거랑 비슷한데, 다른점이라고 한다면 해당 키값의 데이터가 
	//없으면 새로 생성해버림. 주의해야함
	mObjectList[layer].push_back(object);
}

//해당 이름의 오브젝트 찾아오기
GameObject* ObjectManager::FindObject(const string& name)
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetName() == name)
			{
				return iter->second[i];
			}
		}
	}
	return nullptr;
}

//해당 이름의 오브젝트 찾기
GameObject* ObjectManager::FindObject(ObjectLayer layer, const string& name)
{
	ObjectIter iter = mObjectList.find(layer);
	for (int i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == name)
		{
			return iter->second[i];
		}
	}
	return nullptr;
}

vector<class GameObject*> ObjectManager::FindObjects(const string& name)
{
	vector<GameObject*> result;

	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetName() == name)
			{
				result.push_back(iter->second[i]);
			}
		}
	}

	return result;
}

vector<class GameObject*> ObjectManager::FindObjects(ObjectLayer layer, const string& name)
{
	vector<GameObject*> result;
	ObjectIter iter = mObjectList.find(layer);
	for (int i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == name)
		{
			result.push_back(iter->second[i]);
		}
	}
	return result;
}

vector<class GameObject*> ObjectManager::GetObjectList(ObjectLayer layer)
{
	return mObjectList[layer];
}

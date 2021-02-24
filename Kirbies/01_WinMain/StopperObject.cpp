#include "pch.h"
#include "StopperObject.h"
#include "Player.h"

StopperObject::StopperObject(float x, float y,float sizeX,float sizeY)
	
{
	mX = x;
	mY = y;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}
void StopperObject::Init()
{
}

void StopperObject::Release()
{
}

void StopperObject::Update()
{
	mIsDestroy = true;
	vector<GameObject*> playerList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player);
	for (int i = 0; i < playerList.size(); ++i)
	{
		Player* player = (Player*)playerList[i];
		if (player->GetPlayerState() == PlayerState::StopperState)
		{
			RECT temp;
			RECT playerRect = player->GetRect();
			if (IntersectRect(&temp, &mRect, &playerRect))
			{
				mIsDestroy = false;
				break;
			}
		}
	}
}

void StopperObject::Render(HDC hdc)
{
	//������Ʈ �����ִ°� �մ��� ����! control������ ����
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 255, 0);
	}
}

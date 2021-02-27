#include "pch.h"
#include "Trap.h"
Trap::Trap(const string & name, float x, float y, float sizeX, float sizeY, PlayerState state) : GameObject(name)
{
	mX = x;
	mY = y;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mState = state;
}

void Trap::Init()
{
	mRect = RectMake(mX, mY, mSizeX, mSizeY);

}

void Trap::Update()
{
	vector<GameObject*> player = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player);

	for (int i = 0; i < player.size(); i++)
	{

		Player* tempPlayer = (Player*)player[i];
		RECT tempRc;
		RECT playerRc = tempPlayer->GetRect();
		if (IntersectRect(&tempRc, &mRect, &playerRc)) { //trap 의 렉트와 플레이어 렉트가 충돌하면 플레이어의 상태를 바꿔준다
			//한번 만 받게 수정!
			if (tempPlayer->GetIsTrap() == false)
			{
				tempPlayer->SetPlayerState(mState);
				tempPlayer->SetIsChange(true);
				tempPlayer->SetIsTrap(true);
			}
				
				
		}
	}
}

void Trap::Release()
{
}

void Trap::Render(HDC hdc)
{
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 200, 100, 100);
	}
}

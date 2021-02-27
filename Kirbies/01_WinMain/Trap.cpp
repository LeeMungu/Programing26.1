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
		if (IntersectRect(&tempRc, &mRect, &playerRc)) { //trap �� ��Ʈ�� �÷��̾� ��Ʈ�� �浹�ϸ� �÷��̾��� ���¸� �ٲ��ش�
			//�ѹ� �� �ް� ����!
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

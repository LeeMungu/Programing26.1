#include "pch.h"
#include "Goal.h"
#include "Camera.h"
#include "Image.h"
#include "Player.h"
Goal::Goal(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Goal::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Goal");
	mSizeX = mImage->GetWidth()/2;
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	
}

void Goal::Release()
{

}

void Goal::Update()
{

	vector<GameObject*> player = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player);
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	for (int i = 0; i < player.size(); i++)
	{
		RECT temp;
		RECT playerRect = player[i]->GetRect();
		//골인 판정을 위한 렉트 수정 
		if (IntersectRect(&temp, &playerRect, &mRect))
		{
			Player* tempPlayer = (Player*)player[i];
			if (tempPlayer->GetIsDoor() == false)
			{
				SoundPlayer::GetInstance()->Play(L"GoalEffectSound", 0.3 *SoundPlayer::GetInstance()->GetEffectVolum());
				tempPlayer->SetIsGoal(true);
				tempPlayer->SetIsDoor(true);
			}
		}
	}

	

}

void Goal::Render(HDC hdc)
{
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 100, 100);
	}

	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left-mSizeX, mRect.top, mFrameX, mFrameY);
}

void Goal::mapRender(HDC map)
{
	mImage->Render(map, mX, mY);
}

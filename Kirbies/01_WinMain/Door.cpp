#include "pch.h"
#include "Door.h"
#include "Camera.h"
#include "Image.h"
#include "Player.h"

Door::Door(const string& name, float x, float y, int count)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mStage1Count = count;
}

void Door::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Door");
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mTimer = 0;
	mCount = 0;
	mTimeLimit = 3.f;
}

void Door::Release()
{
}

void Door::Update()
{
	mTimer+=Time::GetInstance()->DeltaTime();

	if (Input::GetInstance()->GetKeyDown('A'))
	{
		if (mTimeLimit < 6)
		{
			mTimeLimit += 0.3f;
		}
	}
	if (Input::GetInstance()->GetKeyDown('S'))
	{
		if (mTimeLimit > 0.9f)
		{
			mTimeLimit -= 0.3f;
		}
	}


	if (mTimer >= mTimeLimit && mCount<mStage1Count)
	{
		mTimer = 0;
		//플레이어 생성
		for (int i = 0; i < 1; i++)
		{
			Player* player = new Player("player" + to_string(mCount), mX, mY);
			player->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player);
		}
		mCount++;
	}
}

void Door::Render(HDC hdc)
{
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 100, 100);
	}

	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top, mFrameX, mFrameY);
}

void Door::mapRender(HDC map)
{
	mImage->Render(map, mX, mY);
}

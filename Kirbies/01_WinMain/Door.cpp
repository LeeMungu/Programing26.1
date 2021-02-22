#include "pch.h"
#include "Door.h"
#include "Camera.h"
#include "Image.h"
#include "Player.h"

Door::Door(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Door::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Door");
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mTimer = 0;
	mCount = 0;
}

void Door::Release()
{
}

void Door::Update()
{
	mTimer = Time::GetInstance()->DeltaTime();

	if (mTimer == 3)
	{
		mTimer = 0;
		//플레이어 생성

		for (int i = 0 ; i < 10; i++)
		{
			Player* player = new Player("player" + to_string(i), mX, mY);
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player);
		}

		
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

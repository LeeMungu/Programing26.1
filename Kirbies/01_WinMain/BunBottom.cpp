#include "pch.h"
#include "BunBottom.h"
#include "Camera.h"
#include "Animation.h"
#include "Image.h"

BunBottom::BunBottom(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void BunBottom::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"BunBottom");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mAnimation = new Animation;
	mAnimation->InitFrameByStartEnd(0, 0, 3, 1, false);
	mAnimation->SetFrameUpdateTime(0.1f);
	mAnimation->SetIsLoop(true);
	mAnimation->Play();
}

void BunBottom::Release()
{
	SafeDelete(mAnimation);
}

void BunBottom::Update()
{
	mAnimation->Update();
}

void BunBottom::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, 0, 0,
			mAnimation->GetNowFrameX(),
			mAnimation->GetNowFrameY());
}


void BunBottom::mapRender(HDC map)
{
	mImage->FrameRender(map, 0, 0, 
		mAnimation->GetNowFrameX(),
		mAnimation->GetNowFrameY());
}

#include "pch.h"
#include "Stopper.h"

#include "Image.h"
#include "Animation.h"
#include "Player.h"
#include "GameObject.h"
#include "StopperObject.h"
#include "Camera.h"
#include "Bottom.h"

Stopper::Stopper()
	:mIsPlay(false), mIsLoop(false), mCurrentFrameIndex(0),
	mCurrentFrameTime(0.f), mFrameUpdateTime(0.f), mCallbackFunc(nullptr) {}

void Stopper::Init()
{

	mImage = IMAGEMANAGER->FindImage(L"Stopper");
	mStopperAnimation = new Animation();
	mStopperAnimation->InitFrameByReverseLoop(0, 0, 4, 0);
	mStopperAnimation->SetIsLoop(true);
	mStopperAnimation->SetFrameUpdateTime(0.1f);
	mCurrentAnimation = mStopperAnimation;
	mCurrentAnimation->Play();

	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());
	mX = mPlayer->GetX();
	mY = mPlayer->GetY();
	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	mIsObject = false;
}

void Stopper::Release()
{
	SafeDelete(mImage);
	SafeDelete(mStopperAnimation);
	SafeDelete(mCurrentAnimation);
}

void Stopper::Update()
{
	//for (int y = mY; y < mY + mPlayer->GetSizeY(); y++)
	//{
	//	COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(), mX, mY);

	//	if (pixelColor == RGB(255, 0, 255))
	//	{
	//		mPlayer->SetY(mPlayer->GetY() + mPlayer->GetGravity() * Time::GetInstance()->DeltaTime());
	//		break;
	//	}
	//	if (pixelColor != RGB(255,0,255) && mPlayer->GetSpeed() != 0)
	//	{
	//		mPlayer->SetSpeed(0);
	//		StopperObject* stopperObject = new StopperObject(mPlayer->GetX(), mPlayer->GetY(), mPlayer->GetSizeX(), mPlayer->GetSizeY());
	//		stopperObject->Init();
	//		ObjectManager::GetInstance()->AddObject(ObjectLayer::StopperObject, stopperObject);
	//		mCurrentAnimation = mStopperAnimation;
	//	}
	//}
	//mCurrentAnimation->Update();

	
	if (mPlayer->GetSpeed() != 0)
	{
		mPlayer->SetSpeed(0);
	}

	if(mIsObject ==false)
	{
		mIsObject = true;
		StopperObject* stopperObject = new StopperObject(mPlayer->GetX(),mPlayer->GetY(), mPlayer->GetSizeX(), mPlayer->GetSizeY());
		stopperObject->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::StopperObject, stopperObject);
		mCurrentAnimation = mStopperAnimation;
	}

	mCurrentAnimation->Update();
}

void Stopper::mapRender(HDC map)
{
	mImage->FrameRender(map, mX, mY, mCurrentAnimation->GetNowFrameX(),	mCurrentAnimation->GetNowFrameY());
}

void Stopper::Render(HDC hdc)
{	
		CameraManager::GetInstance()->GetMainCamera()
			->FrameRender(hdc, mImage, mPlayer->GetX() - mImage->GetFrameWidth() / 2, mPlayer->GetRect().top,
				mCurrentAnimation->GetNowFrameX(),
				mCurrentAnimation->GetNowFrameY());
}

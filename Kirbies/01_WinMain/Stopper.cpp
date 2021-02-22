#include "pch.h"
#include "Stopper.h"

#include "Image.h"
#include "Animation.h"
#include "Player.h"
#include "GameObject.h"
#include "StopperObject.h"
#include "Camera.h"

Stopper::Stopper()
	:mIsPlay(false), mIsLoop(false), mCurrentFrameIndex(0),
	mCurrentFrameTime(0.f), mFrameUpdateTime(0.f), mCallbackFunc(nullptr) {}

void Stopper::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Stopper", Resources(L"stopper.bmp"), 110, 24, 5, 1, true);
	mImage = IMAGEMANAGER->FindImage(L"Stopper");



	mStopperAnimation = new Animation();
	mStopperAnimation->InitFrameByStartEnd(0, 0, 4, 0, true);
	mStopperAnimation->SetIsLoop(true);
	mStopperAnimation->SetFrameUpdateTime(0.2f);
	mCurrentAnimation = mStopperAnimation;
	mCurrentAnimation->Play();

	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());
}

void Stopper::Release()
{
	SafeDelete(mImage);
	SafeDelete(mStopperAnimation);
	SafeDelete(mCurrentAnimation);
}

void Stopper::Update()
{

	if (mPlayer->GetSpeed() != 0)
	{
		mPlayer->SetSpeed(0);
		StopperObject* stopperObject = new StopperObject(mPlayer->GetX(),mPlayer->GetY(), mPlayer->GetSizeX(), mPlayer->GetSizeY());
		stopperObject->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::StopperObject, stopperObject);
		mCurrentAnimation = mStopperAnimation;
	}
	mCurrentAnimation->Update();

}


void Stopper::Render(HDC hdc)
{	
		CameraManager::GetInstance()->GetMainCamera()
			->FrameRender(hdc, mImage, mPlayer->GetX() - mImage->GetFrameWidth() / 2, mPlayer->GetRect().top,
				mCurrentAnimation->GetNowFrameX(),
				mCurrentAnimation->GetNowFrameY());
}

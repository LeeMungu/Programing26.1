#include "pch.h"
#include "Umbrella.h"

#include "Animation.h"
#include "GameObject.h"
#include "Player.h"
#include "State.h"
#include "Image.h"
#include "Camera.h"

void Umbrella::Init()
{

	mImage = IMAGEMANAGER->FindImage(L"Umbrella");

	mRightStartAnimation = new Animation();
	mRightStartAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightStartAnimation->SetCallbackFunc([]() {SoundPlayer::GetInstance()->Play(L"UmbrellaEffectSound", 0.8); });
	mRightStartAnimation->SetIsLoop(false);
	mRightStartAnimation->SetFrameUpdateTime(0.1f);	


	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByStartEnd(4, 0, 22, 0, false);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.1f);
	

	mLeftStartAnimation = new Animation();
	mLeftStartAnimation->InitFrameByStartEnd(0, 1, 1, 1, true);
	mLeftStartAnimation->SetCallbackFunc([]() {SoundPlayer::GetInstance()->Play(L"UmbrellaEffectSound", 0.8); });
	mLeftStartAnimation->SetIsLoop(false);
	mLeftStartAnimation->SetFrameUpdateTime(0.1f);
	

	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByEndStart(22, 1, 4, 1, true);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.1f);



	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	if (mPlayer->GetIntMotionRL() == 0)
	{
		mCurrentAnimation = mRightStartAnimation;
	}


	else if (mPlayer->GetIntMotionRL() == 1)
	{
		mCurrentAnimation = mLeftStartAnimation;
	}

	mPlayer->SetGravity(25.f);
	mCurrentAnimation->Play();

	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());
}

void Umbrella::Release()
{
	SafeDelete(mImage);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mCurrentAnimation);
}

void Umbrella::Update()
{
	if (mCurrentAnimation == mRightStartAnimation)
	{
		if (mCurrentAnimation->GetIsPlay() == false)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightAnimation;
			mCurrentAnimation->Play();
		}
	}
	else if (mCurrentAnimation == mLeftStartAnimation)
	{
		if (mCurrentAnimation->GetIsPlay() == false)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftAnimation;
			mCurrentAnimation->Play();
		}
	}

	mPlayer->SetY(mPlayer->GetY() + mPlayer->GetGravity()*Time::GetInstance()->DeltaTime());
	mCurrentAnimation->Update();


}

void Umbrella::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mPlayer->GetX() - mImage->GetFrameWidth() / 2, mPlayer->GetRect().top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());
}

void Umbrella::mapRender(HDC map)
{
	mImage->FrameRender(map, mPlayer->GetX(), mPlayer->GetY(), mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
}

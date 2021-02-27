#include "pch.h"
#include "Run.h"

#include "GameObject.h"
#include "Animation.h"
#include "State.h"
#include "Boom.h"
#include "Camera.h"
#include "Bottom.h"
#include "StopperObject.h"
#include "Image.h"
#include "ObjectManager.h"


void Run::Init()
{
	IsCrash = false;

	mRunKirby = IMAGEMANAGER->FindImage(L"Run");
	mGoalKirby = IMAGEMANAGER->FindImage(L"GoalKirby");
	//좌측 애니메이션
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByEndStart(9, 1, 0, 1, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.1f);

	//우측 애니메이션
	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByStartEnd(0, 0, 9, 0, false);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.1f);

	//골인 애니메이션
	mGoalKirbyAnimation = new Animation();
	mGoalKirbyAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mGoalKirbyAnimation->SetIsLoop(false);
	mGoalKirbyAnimation->SetFrameUpdateTime(0.1f);
	mGoalKirbyAnimation->SetCallbackFunc([this]() {mPlayer->SetIsDestroy(true); });
	//mGoalKirbyAnimation->Stop();
	//mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Bottom,"Bottom");

	//좌우 판정
	if (mPlayer->GetIntMotionRL() == 0)
	{
		mCurrentAnimation = mRightAnimation;
	}
	else if (mPlayer->GetIntMotionRL() == 1)
	{
		mCurrentAnimation = mLeftAnimation;

	}

	mCurrentAnimation->Play();
	// Run 커비가 골과 충돌했다면

	//작성해야함

	mFrameCount = 0;

	mPlayer->SetSizeX(mRunKirby->GetFrameWidth());
	mPlayer->SetSizeY(mRunKirby->GetFrameHeight());

	mIsDestroyed = false;
	mScaleValue =1.f;
}

void Run::Release()
{
	SafeDelete(mRunKirby);
	SafeDelete(mGoalKirby);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mGoalKirbyAnimation);
	//SafeDelete(mCurrentAnimation);
}

void Run::Update()
{
	
	if (mPlayer->GetIntMotionRL() == 0 && mCurrentAnimation == mLeftAnimation)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightAnimation;
		mCurrentAnimation->Play();
	}
	else if (mPlayer->GetIntMotionRL() == 1 && mCurrentAnimation == mRightAnimation)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftAnimation;
		mCurrentAnimation->Play();

	}

	//COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
	//	mX, mY);
	//if (pixelColor != RGB(255, 0, 255))
	//{
	//	mPlayer->SetY(mPlayer->GetY() - mPlayer->GetSizeY() / 2);
	//}


	mFrameCount++;
	if (mFrameCount > 6)
	{
		mFrameCount = 0;
		if (mCurrentAnimation == mRightAnimation && 
			(mCurrentAnimation->GetNowFrameX()==2||
				mCurrentAnimation->GetNowFrameX() == 6))
		{
			SoundPlayer::GetInstance()->Play(L"RunEffectSound", 0.3 *SoundPlayer::GetInstance()->GetEffectVolum());
		}
		else if (mCurrentAnimation == mLeftAnimation &&
			(mCurrentAnimation->GetNowFrameX()==9-2 ||
				mCurrentAnimation->GetNowFrameX()==9-6))
		{
			SoundPlayer::GetInstance()->Play(L"RunEffectSound", 0.3 *SoundPlayer::GetInstance()->GetEffectVolum());
		}
	}


	if (mCurrentAnimation == mLeftAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed() * Time::GetInstance()->DeltaTime());
	}
	if (mCurrentAnimation == mRightAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() + mPlayer->GetSpeed() * Time::GetInstance()->DeltaTime());
	}
	

	//if (IsCrash == true)
	//{
	//	if (mCurrentAnimation == mLeftAnimation)
	//	{
	//		mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
	//		mLeftAnimation->Stop();
	//		mCurrentAnimation = mRightAnimation;
	//		mRightAnimation->Play();
	//	}
	//	if (mCurrentAnimation == mRightAnimation)
	//	{
	//		mPlayer->SetX(mPlayer->GetX() + mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
	//		mCurrentAnimation->Stop();
	//		mCurrentAnimation = mLeftAnimation;
	//		mCurrentAnimation->Play();
	//	}
	//	IsCrash = false;
	//}
	// 골인 애니메이션이 트루일 경우
	if (mPlayer->GetIsGoal() == true)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mGoalKirbyAnimation;
		mCurrentAnimation->Play();
		mPlayer->SetIsGoal(false);
	}
	if (mCurrentAnimation == mGoalKirbyAnimation)
	{
		mScaleValue -= 0.005f;
	}
	//들어갔을때
	//if (mCurrentAnimation == mGoalKirbyAnimation &&
	//	mCurrentAnimation->GetIsPlay() == false)
	//{
	//
	//	//mIsDestroyed = true;
	//	mPlayer->SetIsDestroy(true);
	//}

	//if (mCurrentAnimation == mGoalKirbyAnimation)
	//{
	//	if (mCurrentAnimation->GetIsPlay() == false)
	//	{
	//		mPlayer->SetIsDestroy(true);
	//	}
	//}
	mCurrentAnimation->Update();
}

void Run::Render(HDC hdc)
{
	Image* nowImage;
	if (mCurrentAnimation == mLeftAnimation ||
		mCurrentAnimation == mRightAnimation)
	{
		nowImage = mRunKirby;
	}
	else
	{
		nowImage = mGoalKirby;
	}

	if (nowImage == mRunKirby)
	{
		CameraManager::GetInstance()->GetMainCamera()
			->FrameRender(hdc, nowImage, mPlayer->GetX() - mRunKirby->GetFrameWidth() / 2, mPlayer->GetRect().top,
				mCurrentAnimation->GetNowFrameX(),
				mCurrentAnimation->GetNowFrameY());
	}
	else if (nowImage == mGoalKirby)
	{
		CameraManager::GetInstance()->GetMainCamera()
			->ScaleFrameRender(hdc, nowImage, mPlayer->GetX() - mRunKirby->GetFrameWidth() / 2, mPlayer->GetRect().top,
				mCurrentAnimation->GetNowFrameX(),
				mCurrentAnimation->GetNowFrameY(),
				nowImage->GetFrameWidth() * mScaleValue,
				nowImage->GetFrameHeight() * mScaleValue
				);
	}
}

void Run::mapRender(HDC map)
{
	Image* nowImage;
	if (mCurrentAnimation == mLeftAnimation ||
		mCurrentAnimation == mRightAnimation)
	{
		nowImage = mRunKirby;
	}
	else
	{
		nowImage = mGoalKirby;
	}
	if (nowImage == mRunKirby)
	{
		mRunKirby->FrameRender(map, mPlayer->GetX(), mPlayer->GetY(), mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	}
	else if (nowImage == mGoalKirby)
	{
		mGoalKirby->FrameRender(map, mPlayer->GetX(), mPlayer->GetY(), mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	}
}

#include "pch.h"
#include "Fall.h"

#include "Animation.h"
#include "GameObject.h"
#include "Player.h"
#include "State.h"
#include "Image.h"
#include "Camera.h"

void Fall::Init()
{
	
	mIsDeadCheck = false;


	mFallKirby = IMAGEMANAGER->FindImage(L"Fall");
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0, 0, 15, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.1f);

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(15, 1, 0, 1, false);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.1f);

	//추락사 애니메이션 
	mFallDeadKirby = IMAGEMANAGER->FindImage(L"KirbyFallDead");
	mLeftFallDeadAnimation = new Animation();
	mLeftFallDeadAnimation->InitFrameByEndStart(2, 1, 0, 1, false);
	mLeftFallDeadAnimation->SetIsLoop(false);
	mLeftFallDeadAnimation->SetFrameUpdateTime(0.3f);
	mLeftFallDeadAnimation->SetCallbackFunc([this]() {mPlayer->SetIsDestroy(true); });

	mRightFallDeadAnimation = new Animation();
	mRightFallDeadAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mRightFallDeadAnimation->SetIsLoop(false);
	mRightFallDeadAnimation->SetFrameUpdateTime(0.3f);
	mRightFallDeadAnimation->SetCallbackFunc([this]() {mPlayer->SetIsDestroy(true); });

	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	if (mPlayer->GetIntMotionRL() == 0)
	{
		mCurrentAnimation = mRightAnimation;
	}
	else if (mPlayer->GetIntMotionRL() == 1)
	{
		mCurrentAnimation = mLeftAnimation;
	}
	mCurrentAnimation->Play();

	//방향전환
	if (mCurrentAnimation == mLeftAnimation && mPlayer->GetIntMotionRL() == 1)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightAnimation;
		mCurrentAnimation->Play();
	}
	else if (mCurrentAnimation == mRightAnimation && mPlayer->GetIntMotionRL() == 0)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftAnimation;
		mCurrentAnimation->Play();
	}


	mPlayer->SetGravity(100.f);
	mPlayer->SetSizeX(mFallKirby->GetFrameWidth());
	mPlayer->SetSizeY(mFallKirby->GetFrameHeight());

	

	mStartY = mPlayer->GetY();

	//COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
	//	mX, mY);
	//if (pixelColor != RGB(255, 0, 255))
	//{
	//	mPlayer->SetY(mPlayer->GetY() - mPlayer->GetSizeY() / 2);
	//}

	mIsDeadCheck = false;

}

void Fall::Release()
{
	SafeDelete(mFallKirby);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mLeftFallDeadAnimation);
	SafeDelete(mRightFallDeadAnimation);
	SafeDelete(mCurrentAnimation);
}

void Fall::Update()
{
	


	if (mPlayer->GetIsFallDead() == false)
	{
		mPlayer->SetY(mPlayer->GetY() + mPlayer->GetGravity()*Time::GetInstance()->DeltaTime());
	}
	else if (mPlayer->GetIsFallDead() == true && mIsDeadCheck==false)
	{
		mCurrentAnimation->Stop();
		if (mPlayer->GetIntMotionRL() == 0)
		{
			mCurrentAnimation = mRightFallDeadAnimation;
		}
		else if (mPlayer->GetIntMotionRL() == 1)
		{
			mCurrentAnimation = mLeftFallDeadAnimation;
		}
		mCurrentAnimation->Play();

		mIsDeadCheck = true;
	}
	
	mCurrentAnimation->Update();


}

void Fall::Render(HDC hdc)
{
	if (mPlayer->GetIsFallDead() == false)
	{
		CameraManager::GetInstance()->GetMainCamera()
			->FrameRender(hdc, mFallKirby, mPlayer->GetX() - mFallKirby->GetFrameWidth() / 2, mPlayer->GetRect().top,
				mCurrentAnimation->GetNowFrameX(),
				mCurrentAnimation->GetNowFrameY());
	}
	else if (mPlayer->GetIsFallDead() == true)
	{
		CameraManager::GetInstance()->GetMainCamera()
			->FrameRender(hdc, mFallDeadKirby, mPlayer->GetX() - mFallDeadKirby->GetFrameWidth() / 2, mPlayer->GetRect().top,
				mCurrentAnimation->GetNowFrameX(),
				mCurrentAnimation->GetNowFrameY());
	}
}

void Fall::mapRender(HDC map)
{
	mFallKirby->FrameRender(map, mPlayer->GetX(), mPlayer->GetY(), mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	//mFallDeadKirby->FrameRender(map, mPlayer->GetX(), mPlayer->GetY(), mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
}


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
	
	mFallKirby = IMAGEMANAGER->FindImage(L"Fall");
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0, 0, 15, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.1f);

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(15, 1, 0, 1, false);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.1f);

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

	mPlayer->SetGravity(100.f);
	mPlayer->SetSizeX(mFallKirby->GetFrameWidth());
	mPlayer->SetSizeY(mFallKirby->GetFrameHeight());

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

	//COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
	//	mX, mY);
	//if (pixelColor != RGB(255, 0, 255))
	//{
	//	mPlayer->SetY(mPlayer->GetY() - mPlayer->GetSizeY() / 2);
	//}



}

void Fall::Release()
{
	SafeDelete(mFallKirby);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mCurrentAnimation);
}

void Fall::Update()
{
	mPlayer->SetY(mPlayer->GetY() + mPlayer->GetGravity()*Time::GetInstance()->DeltaTime());
	mCurrentAnimation->Update();
}

void Fall::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mFallKirby, mPlayer->GetX() - mFallKirby->GetFrameWidth() / 2, mPlayer->GetRect().top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());

}

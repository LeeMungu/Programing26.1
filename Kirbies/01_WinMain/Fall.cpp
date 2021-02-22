#include "pch.h"
#include "Fall.h"

#include "Animation.h"
#include "GameObject.h"
#include "Player.h"
#include "State.h"

void Fall::Init()
{
	
	mFallKirby = IMAGEMANAGER->FindImage(L"Fall");
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0, 0, 15, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.3f);

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(15, 1, 0, 1, false);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.3f);

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

	mPlayer->SetGravity(0.5f);


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
	mPlayer->SetY(mPlayer->GetY() - mPlayer->GetGravity()*Time::GetInstance()->DeltaTime());
	if (mCurrentAnimation == mLeftAnimation && mPlayer->GetIntMotionRL() == 0)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightAnimation;
		mCurrentAnimation->Play();
	}
	else if (mCurrentAnimation == mRightAnimation && mPlayer->GetIntMotionRL() == 1)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftAnimation;
		mCurrentAnimation->Play();
	}
}

void Fall::Render(HDC hdc)
{
	mCurrentAnimation->GetNowFrameX();
	mCurrentAnimation->GetNowFrameY();

}

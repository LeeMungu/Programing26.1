#include "pch.h"
#include "Fall.h"

#include "Animation.h"
#include "GameObject.h"
#include "Player.h"
#include "State.h"

void Fall::Init()
{
	IMAGEMANAGER -> LoadFromFile(L"Fall", Resources(L"Fall.bmp"), 400, 40, 16, 2, true);
	mFallKirby = IMAGEMANAGER->FindImage(L"Fall");
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByEndStart(0, 0, 15, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.3f);

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(0, 1, 15, 1, true);
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


}

void Fall::Release()
{
	SafeDelete(mFallKirby);
}

void Fall::Update()
{
	if (mCurrentAnimation == mLeftAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
	}
	if (mCurrentAnimation == mRightAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
	}

}

void Fall::Render(HDC hdc)
{
	mCurrentAnimation->GetNowFrameX();
	mCurrentAnimation->GetNowFrameY();

}

#include "pch.h"
#include "Run.h"

#include "GameObject.h"
#include "Animation.h"
#include "State.h"
#include "Boom.h"
#include "Camera.h"
#include "StopperObject.h"


void Run::Init()
{

	IsCrash = false;

	mRunKirby = IMAGEMANAGER->FindImage(L"Run");
	//좌측 애니메이션
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByEndStart(0, 0, 9, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.3f);

	//우측 애니메이션
	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(0, 1, 9, 1, true);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.3f);

	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	if (mPlayer->GetIntMotionRL() == 0)
	{
		mCurrentAnimation=mRightAnimation;
	}
	else if (mPlayer->GetIntMotionRL() == 1)
	{
		mCurrentAnimation = mLeftAnimation;

	}
	mCurrentAnimation->Play();


	// 벽, 스토퍼 충돌 구현해야함

	


}

void Run::Release()
{
	SafeDelete(mRunKirby);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mCurrentAnimation);
}

void Run::Update()
{
	if (IsCrash == false)
	{
		if (mCurrentAnimation == mLeftAnimation)
		{
			mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
			mCurrentAnimation->Stop();
			mCurrentAnimation->Play();
		}
		if (mCurrentAnimation == mRightAnimation)
		{
			mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
			mCurrentAnimation->Stop();
			mCurrentAnimation->Play();
		}
	}
	else
	{

	}

}

void Run::Render(HDC hdc)
{
	mCurrentAnimation->GetNowFrameX();
	mCurrentAnimation->GetNowFrameY();

}

#include "pch.h"
#include "Run.h"

#include "GameObject.h"
#include "Animation.h"
#include "State.h"
#include "Boom.h"
#include "Camera.h"
#include "Bottom.h"
#include "StopperObject.h"


void Run::Init()
{
	IsCrash = false;

	mRunKirby = IMAGEMANAGER->FindImage(L"Run");
	mGoalKirby = IMAGEMANAGER->FindImage(L"GoalKirby");
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

	//골인 애니메이션
	mGoalKirbyAnimation = new Animation();
	mGoalKirbyAnimation->InitFrameByEndStart(0, 0, 5, 0, true);
	mGoalKirbyAnimation->SetIsLoop(true);
	mGoalKirbyAnimation->SetFrameUpdateTime(0.3f);

	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	//좌우 판정
	if (mPlayer->GetIntMotionRL() == 0)
	{
		mCurrentAnimation = mRightAnimation;
	}
	else if (mPlayer->GetIntMotionRL() == 1)
	{
		mCurrentAnimation = mLeftAnimation;

	}
	// Run 커비가 골과 충돌했다면

	//작성해야함

	//스토퍼커비와 충돌한 런커비
	RECT Temp;
	mRunKirbyRect = mPlayer->GetRect();
	RECT mStopKirby = mStopperObject->GetRect();
	if (IntersectRect(&Temp, &mRunKirbyRect, &mStopKirby))
	{
		IsCrash = true;
	}
	mCurrentAnimation->Play();

}

void Run::Release()
{
	SafeDelete(mRunKirby);
	SafeDelete(mGoalKirby);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mGoalKirbyAnimation);
	SafeDelete(mCurrentAnimation);
}

void Run::Update()
{

	COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
		mX, mY);




	if (mCurrentAnimation == mLeftAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
	}
	if (mCurrentAnimation == mRightAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() + mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
	}
	//스토퍼커비와 충돌한 런커비
	RECT Temp;
	RECT mRunKirbyRect = mRunKirbyRect;
	RECT mStopKirby = mStopperObject->GetRect();
	if (IntersectRect(&Temp, &mRunKirbyRect, &mStopKirby))
	{
		IsCrash = true;
	}

	if (IsCrash == true)
	{
		if (mCurrentAnimation == mLeftAnimation)
		{
			mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
			mLeftAnimation->Stop();
			mCurrentAnimation = mRightAnimation;
			mRightAnimation->Play();
		}
		if (mCurrentAnimation == mRightAnimation)
		{
			mPlayer->SetX(mPlayer->GetX() + mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftAnimation;
			mCurrentAnimation->Play();
		}
		IsCrash = false;
	}
	// 골인 애니메이션이 트루일 경우
	if (mPlayer->GetIsGoal() == true);
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mGoalKirbyAnimation;
		mCurrentAnimation->Play();
	}
}

void Run::Render(HDC hdc)
{
	mCurrentAnimation->GetNowFrameX();
	mCurrentAnimation->GetNowFrameY();

}

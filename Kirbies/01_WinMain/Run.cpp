#include "pch.h"
#include "Run.h"

#include "GameObject.h"
#include "Animation.h"
#include "State.h"
#include "Boom.h"
#include "Camera.h"


void Run::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Run", Resources(L"Walk.bmp"), 420, 76, 10, 2, true);
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
}

void Run::Release()
{
	SafeDelete(mRunKirby);
}

void Run::Update()
{
	if (mCurrentAnimation == mLeftAnimation)
	{
		mPlayer->SetX(mPlayer->GetX()-mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
	}
	if (mCurrentAnimation == mRightAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
	}


}

void Run::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mRunKirby, mPlayer->SetX(mPlayer->GetX()-m)


}

#include "pch.h"
#include "Run.h"

#include "GameObject.h"
#include "Animation.h"
#include "State.h"
#include "Boom.h"


void Run::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Run", Resources(L"Walk.bmp"), 420, 76, 10, 2, true);
	mRunKirby = IMAGEMANAGER->FindImage(L"Run");
	mPlayer->GetRect = RectMakeCenter(mPlayer->GetRect.GetX, mPlayer->GetRect.GetY, mPlayer->GetSizeX, mPlayer->GetSizeY);
	//좌측 애니메이션
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByEndStart(0, 0, 0, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.3f);

	//우측 애니메이션
	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(0, 1, 0, 1, false);
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




}

void Run::Render(HDC hdc)
{
}

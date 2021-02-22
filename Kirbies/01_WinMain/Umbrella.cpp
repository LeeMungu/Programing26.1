#include "pch.h"
#include "Umbrella.h"

#include "Image.h"
#include "Animation.h"
#include "GameObject.h"
#include "Player.h"
#include "State.h"
#include "Bottom.h"

void Umbrella::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Umbrella");
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0, 0, 23, 0, false);
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

void Umbrella::Release()
{
}

void Umbrella::Update()
{
}

void Umbrella::Render(HDC hdc)
{
}

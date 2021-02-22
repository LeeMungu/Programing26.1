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
	mLeftAnimation->InitFrameByStartEnd(3, 0, 23, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.3f);

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(24, 1, 3, 1, false);
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
	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());
	mPlayer->SetGravity(0.3f);

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

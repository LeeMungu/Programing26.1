#include "pch.h"
#include "Umbrella.h"

#include "Animation.h"
#include "GameObject.h"
#include "Player.h"
#include "State.h"
#include "Image.h"
#include "Camera.h"

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

	mPlayer->SetGravity(5.f);
	mCurrentAnimation->Play();

	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());
}

void Umbrella::Release()
{
	SafeDelete(mImage);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mCurrentAnimation);
}

void Umbrella::Update()
{

	mCurrentAnimation->Update();
}

void Umbrella::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mPlayer->GetX() - mImage->GetFrameWidth() / 2, mPlayer->GetRect().top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());
}

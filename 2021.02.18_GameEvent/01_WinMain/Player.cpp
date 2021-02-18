#include "pch.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Camera.h"
Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Player", Resources(L"kirbyFinal.bmp"), 1148, 396, 14, 4,true);
	mImage = IMAGEMANAGER->FindImage(L"Player");


	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 1, 0,false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(0.3f);
	mIdleAnimation->Play();

	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 1, 1, 1, false);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.3f);
	mLeftIdleAnimation->Play();

	mRunAnimation = new Animation();
	mRunAnimation->InitFrameByStartEnd(2, 0, 11, 0, false);
	mRunAnimation->SetIsLoop(true);
	mRunAnimation->SetFrameUpdateTime(0.1f);

	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(2, 1, 11, 1, true);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.1f);

	mAttackAnimation = new Animation();
	mAttackAnimation->InitFrameByStartEnd(0, 2, 13, 2, false);
	mAttackAnimation->SetIsLoop(true);
	mAttackAnimation->SetFrameUpdateTime(0.05f);

	mLeftAttackAnimation = new Animation();
	mLeftAttackAnimation->InitFrameByStartEnd(2, 3, 13, 3, true);
	mLeftAttackAnimation->SetIsLoop(true);
	mLeftAttackAnimation->SetFrameUpdateTime(0.05f);

	mCurrentAnimation = mIdleAnimation;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Release()
{
	SafeDelete(mIdleAnimation);
}

void Player::Update()
{
	// 플레이어 우측이동
	if (Input::GetInstance()->GetKeyDown('D'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRunAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp('D'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mIdleAnimation;
		mCurrentAnimation->Play();
	}
	//플레이어 좌측이동
	if (Input::GetInstance()->GetKeyDown('A'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftRunAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp('A'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftIdleAnimation;
		mCurrentAnimation->Play();
	}
	//플레이어 공격
	if (Input::GetInstance()->GetKeyDown('E'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mAttackAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp('E'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mIdleAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyDown('Q'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftAttackAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp('Q'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftIdleAnimation;
		mCurrentAnimation->Play();
	}


	mCurrentAnimation->Update();
}

void Player::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());

	//mImage->FrameRender(hdc,mRect.left,mRect.top, mCurrentAnimation->GetNowFrameX(),
	//	mCurrentAnimation->GetNowFrameY());
}

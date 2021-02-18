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
	IMAGEMANAGER->LoadFromFile(L"Player", Resources(L"kirbyMoveFinal.bmp"), 1020, 198, 10, 2,true);
	IMAGEMANAGER->LoadFromFile(L"PlayerAttack", Resources(L"kirbyAttack_Final.bmp"), 1020, 198, 14, 2, true);
	mImage = IMAGEMANAGER->FindImage(L"Player");
	mAttackImage = IMAGEMANAGER->FindImage(L"PlayerAttack");


	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 1, 0,false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(0.3f);
	mIdleAnimation->Play();

	mRunAnimation = new Animation();
	mRunAnimation->InitFrameByStartEnd(0, 0, 9, 0, false);
	mRunAnimation->SetIsLoop(true);
	mRunAnimation->SetFrameUpdateTime(0.1f);

	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(0, 1, 9, 1, true);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.1f);

	mAttackAnimation = new Animation();
	mAttackAnimation->InitFrameByStartEnd(0, 0, 13, 0, false);
	mAttackAnimation->SetIsLoop(true);
	mAttackAnimation->SetFrameUpdateTime(0.1f);

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
		mCurrentAnimation = mLeftRunAnimation;
		mCurrentAnimation->Play();
	}
	//플레이어 공격
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mAttackAnimation;
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

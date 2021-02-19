#include "pch.h"
#include "Enemy.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Player.h"


Enemy::Enemy(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Enemy::Init()
{
	IMAGEMANAGER->LoadFromFile(L"enemy", Resources(L"elep.bmp"), 496, 124, 8, 2, true);
	mImage = IMAGEMANAGER->FindImage(L"enemy");

	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(0.3f);
	mIdleAnimation->Play();

	mRunAnimation = new Animation();
	mRunAnimation->InitFrameByStartEnd(2, 0, 7, 0, false);
	mRunAnimation->SetIsLoop(true);
	mRunAnimation->SetFrameUpdateTime(0.1f);

	mAttackAnimation = new Animation();
	mAttackAnimation->InitFrameByStartEnd(0, 1, 7, 1, false);
	mAttackAnimation->SetIsLoop(true);
	mAttackAnimation->SetFrameUpdateTime(0.1f);

	mCurrentAnimation = mIdleAnimation;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mSpeed = 0.5f;
	mHpPoint = 10;
	mDamage = 10;
	mIsFollow = false;
}

void Enemy::Release()
{
	SafeDelete(mIdleAnimation);
	SafeDelete(mRunAnimation);
	SafeDelete(mAttackAnimation);
}

void Enemy::Update()
{
	mCurrentAnimation->Update();

	mDistance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY());
	float angel = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());

	if (mIsFollow == true)
	{
		mX += cosf(angel) * mSpeed;
		mY += -sinf(angel)*mSpeed;
	}

	if (mDistance > 70 && mIsFollow == false)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRunAnimation;
		mCurrentAnimation->Play();
		mIsFollow = true;
	}
	else if (mDistance < 70 && mIsFollow == true)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mAttackAnimation;
		mCurrentAnimation->Play();
		mIsFollow = false;
	}

	RECT temp;
	RECT PlayerRect = mPlayer->GetRect();
	if (IntersectRect(&temp, &mRect, &PlayerRect))
	{
		mPlayer->SetHpPoint(mDamage);
		if (mX > mPlayer->GetX())
		{
			mPlayer->GetXPosition(-20);
		}
		else
		{
			mPlayer->GetXPosition(20);
		}
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Enemy::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());

	//RenderRect(hdc, mRect);

}

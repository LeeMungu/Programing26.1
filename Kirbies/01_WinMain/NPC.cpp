#include "pch.h"
#include "NPC.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

NPC::NPC(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void NPC::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"dedede");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	
	mLeftIdleAnimation = new Animation;
	mLeftIdleAnimation->InitFrameByEndStart(3,0,0,0,false);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.1f);

	mRightIdleAnimation = new Animation;
	mRightIdleAnimation->InitFrameByStartEnd(0, 2, 3, 2, false);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->SetFrameUpdateTime(0.1f);

	mLeftRunAnimation = new Animation;
	mLeftRunAnimation->InitFrameByEndStart(3, 1, 0, 1, false);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.1f);
	
	mRightRunAnimation = new Animation;
	mRightRunAnimation->InitFrameByEndStart(0, 3, 3, 3, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.1f);

	mCurrentAnimation = mLeftIdleAnimation;
	mCurrentAnimation->Play();

	mNpcState = NPC::NPCState::LeftIdle;
	mIsMotionRL = 1;
	mIsGo = false;
}

void NPC::Update()
{
	if (mIsGo == false)
	{
		if(mIsMotionRL==0 && mCurrentAnimation!=mLeftIdleAnimation)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftIdleAnimation;
			mCurrentAnimation->Play();
		}
		else if (mIsMotionRL == 1 && mCurrentAnimation != mRightIdleAnimation)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightIdleAnimation;
			mCurrentAnimation->Play();
		}
	}
	else if (mIsGo == true)
	{
		if (mIsMotionRL == 0 && mCurrentAnimation != mLeftRunAnimation)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftRunAnimation;
			mCurrentAnimation->Play();
		}
		else if (mIsMotionRL == 1 && mCurrentAnimation != mRightRunAnimation)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightRunAnimation;
			mCurrentAnimation->Play();
		}
	}
	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void NPC::Release()
{
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftRunAnimation);
	SafeDelete(mRightRunAnimation);
}

void NPC::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->
		FrameRender(hdc, mImage, mRect.left, mRect.top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());
}

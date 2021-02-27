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
	mLeftIdleAnimation->SetFrameUpdateTime(0.3f);

	mRightIdleAnimation = new Animation;
	mRightIdleAnimation->InitFrameByStartEnd(0, 2, 3, 2, false);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->SetFrameUpdateTime(0.3f);

	mLeftRunAnimation = new Animation;
	mLeftRunAnimation->InitFrameByEndStart(3, 1, 0, 1, false);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.3f);
	
	mRightRunAnimation = new Animation;
	mRightRunAnimation->InitFrameByStartEnd(0, 3, 3, 3, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.3f);

	mCurrentAnimation = mLeftIdleAnimation;
	mCurrentAnimation->Play();

	mNpcState = NPC::NPCState::LeftIdle;
	mIsMotionRL = 1;
	mIsGo = false;

}

void NPC::Update()
{
	if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Goal, "goal") != NULL)
	{
		RECT temp;
		RECT gameRect = ObjectManager::GetInstance()->FindObject(ObjectLayer::Goal, "goal")->GetRect();
		if (IntersectRect(&temp, &gameRect, &mRect) == true && mIsActive == true)
		{
			mIsActive = false;
		}
	}

	if (mIsGo == false)
	{
		if(mIsMotionRL==1 && mCurrentAnimation!=mLeftIdleAnimation)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftIdleAnimation;
			mCurrentAnimation->Play();
		}
		else if (mIsMotionRL == 0 && mCurrentAnimation != mRightIdleAnimation)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightIdleAnimation;
			mCurrentAnimation->Play();
		}
	}
	else if (mIsGo == true)
	{
		//이동
		if (mIsMotionRL == 1)
		{
			mX -= 2;
		}
		else if (mIsMotionRL == 0)
		{
			mX += 2;
		}

		//왼쪽
		if (mIsMotionRL == 1 && mCurrentAnimation != mLeftRunAnimation)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftRunAnimation;
			mCurrentAnimation->Play();

		}
		else if (mIsMotionRL == 0 && mCurrentAnimation != mRightRunAnimation)
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
	//플레이어 판정렉트 보여주는것 손대지 말것! control누르면 나옴
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 255, 255, 0);
	}
		CameraManager::GetInstance()->GetMainCamera()->
			FrameRender(hdc, mImage, mRect.left, mRect.top,
				mCurrentAnimation->GetNowFrameX(),
				mCurrentAnimation->GetNowFrameY());
}

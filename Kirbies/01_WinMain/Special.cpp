#include "pch.h"
#include "Special.h"
#include "Animation.h"
#include "Image.h"
#include "Camera.h"
#include "SpecialApearEffect.h"
#include "SpecialAttackEffect.h"

Special::Special(const string& name, float x, float y)
{
	mName = name;
	mX = x;
	mY = y;
}

void Special::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"SpecialAppear");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mApearAnimation = new Animation();
	mApearAnimation->InitFrameByStartEnd(0, 0, 7, 2, false);
	mApearAnimation->SetIsLoop(false);
	mApearAnimation->SetFrameUpdateTime(0.15f);
	mApearAnimation->Play();

	mAttackAnimation = new Animation();
	mAttackAnimation->InitFrameByStartEnd(1, 0, 8, 3, false);
	mAttackAnimation->SetIsLoop(false);
	mAttackAnimation->SetFrameUpdateTime(0.16f);

	mEndAnimation = new Animation();
	mEndAnimation->InitFrameByStartEnd(0, 0, 9, 4, false);
	mEndAnimation->SetIsLoop(false);
	mEndAnimation->SetFrameUpdateTime(0.20f);

	mCurrantAnimation = mApearAnimation;
	mIsAnimationChange = false;
	mIsEffect = false;
	mIsEnd = false;
}

void Special::Release()
{
	SafeDelete(mApearAnimation);
	SafeDelete(mAttackAnimation);
	SafeDelete(mEndAnimation);
	//SafeDelete(mCurrantAnimation);
}

void Special::Update()
{
	
	if (mCurrantAnimation == mApearAnimation && 
		mCurrantAnimation->GetNowFrameY() == 2 &&
		mCurrantAnimation->GetNowFrameX() == 6 &&
		mIsAnimationChange==false)
	{
		mCurrantAnimation->Stop();
		mImage = IMAGEMANAGER->FindImage(L"SpecialAttack");
		mSizeX = mImage->GetFrameWidth();
		mSizeY = mImage->GetFrameHeight();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		mCurrantAnimation = mAttackAnimation;
		mCurrantAnimation->Play();
		mIsAnimationChange == true;
	}
	else if (mCurrantAnimation == mAttackAnimation&&
		mCurrantAnimation->GetNowFrameY() == 0 &&
		mCurrantAnimation->GetNowFrameX() == 3 &&
		mIsEffect==false)
	{
		SpecialAttackEffect* effect = new SpecialAttackEffect("AttackEffect", mX, mY, L"SpecialAttackEffect1");
		effect->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::SpecialEffect, effect);

		Camera* prevCamera = (Camera*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Camera, "Camera");
		prevCamera->SetTarget(effect);
		mIsEffect = true;
	}
	else if (mCurrantAnimation == mAttackAnimation &&
		mCurrantAnimation->GetIsPlay() == false)
	{
		mCurrantAnimation->Stop();
		mImage = IMAGEMANAGER->FindImage(L"SpecialEnd");
		mSizeX = mImage->GetFrameWidth();
		mSizeY = mImage->GetFrameHeight();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		mCurrantAnimation = mEndAnimation;
		mCurrantAnimation->Play();
	}
	else if (mCurrantAnimation == mEndAnimation &&
		mCurrantAnimation->GetNowFrameY() == 4 &&
		mCurrantAnimation->GetNowFrameX() == 2 &&
		mIsEnd==false)
	{
		//사라질때 이팩트
		SpecialApearEffect* effect = new SpecialApearEffect("ApearEffect", mX, mY-100, L"SpecialAppearEffect", 9, 3);
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, effect);
		mIsEnd = true;
		//Camera* prevCamera = (Camera*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Camera, "Camera");
		//prevCamera->SetTarget(effect);
	}
	else if (mCurrantAnimation == mEndAnimation &&
		mCurrantAnimation->GetNowFrameY() == 4 &&
		mCurrantAnimation->GetNowFrameX() == 6)
	{
		mCurrantAnimation->Pause();
		//제거될때
		mIsDestroy = true;
	}

	mCurrantAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Special::Render(HDC hdc)
{
	//박스표시
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		RECT rect = RectMakeCenter(mX, mY, mSizeX*1.5, mSizeY*1.5);
		ColorLender::GetInstance()->ColorRectRender(hdc, rect, 100, 100, 0);
	}

	CameraManager::GetInstance()->GetMainCamera()
		->ScaleFrameRender(hdc, mImage, mX - mImage->GetFrameWidth() / 2, mRect.top,
			mCurrantAnimation->GetNowFrameX(),
			mCurrantAnimation->GetNowFrameY(),
			mSizeX*1.5f,mSizeY*1.5f);
}

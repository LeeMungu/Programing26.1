#include "pch.h"
#include "SpecialAttackEffect.h"
#include "Animation.h"
#include "Image.h"
#include "Camera.h"

SpecialAttackEffect::SpecialAttackEffect(string name, float x, float y, wstring imagekey)
	:Effect(name, x, y, imagekey)
{

}

void SpecialAttackEffect::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"SpecialAttackEffect1");
	mAttackEffect1 = new Animation();
	mAttackEffect1->InitFrameByStartEnd(0, 0, 9, 1, false);
	mAttackEffect1->SetIsLoop(true);
	mAttackEffect1->SetFrameUpdateTime(0.2f);
	mAttackEffect1->Play();
	mCurrentAnimation = mAttackEffect1;

	mAttackEffect2 = new Animation();
	mAttackEffect2->InitFrameByStartEnd(0, 0, 4, 4, false);
	mAttackEffect2->SetIsLoop(false);
	mAttackEffect2->SetFrameUpdateTime(0.15f);

	mAttackEffect3 = new Animation();
	mAttackEffect3->InitFrameByStartEnd(0, 0, 9, 0, false);
	mAttackEffect3->SetIsLoop(false);
	mAttackEffect3->SetFrameUpdateTime(0.3f);

}

void SpecialAttackEffect::Release()
{
	SafeDelete(mAttackEffect1);
	SafeDelete(mAttackEffect2);
	SafeDelete(mAttackEffect3);
}

void SpecialAttackEffect::Update()
{
	if (mCurrentAnimation == mAttackEffect1)
	{
		if (mY > WINSIZEY/3)
		{
			mCurrentAnimation->Pause();
			mImage = IMAGEMANAGER->FindImage(L"SpecialAttackEffect2");
			mSizeX = mImage->GetFrameWidth();
			mSizeY = mImage->GetFrameHeight();
			mRect = RectMakeCenter(mX, mY, mSizeX,mSizeY);
			mCurrentAnimation = mAttackEffect2;
			mCurrentAnimation->Play();
		}
		else
		{
			mX += 2.7f;
			mY += 2.2f;
		}
	}
	else if (mCurrentAnimation == mAttackEffect2)
	{
		if (mCurrentAnimation->GetIsPlay() == false)
		{
			mCurrentAnimation->Pause();
			mImage = IMAGEMANAGER->FindImage(L"SpecialAttackEffect3");
			mSizeX = mImage->GetFrameWidth();
			mSizeY = mImage->GetFrameHeight();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			mCurrentAnimation = mAttackEffect3;
			mCurrentAnimation->Play();
		}
	}
	else if (mCurrentAnimation == mAttackEffect3 &&
		mCurrentAnimation->GetIsPlay() == false)
	{
		mCurrentAnimation->Pause();
		mIsDestroy = true;
	}

	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void SpecialAttackEffect::Render(HDC hdc)
{
	if (mCurrentAnimation == mAttackEffect1)
	{
		CameraManager::GetInstance()->GetMainCamera()
			->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top,
				mCurrentAnimation->GetNowFrameX(),
				mCurrentAnimation->GetNowFrameY(),
				mSizeX * 1.5f, mSizeY * 1.5f);
	}
	else if (mCurrentAnimation == mAttackEffect2)
	{
		CameraManager::GetInstance()->GetMainCamera()
			->ScaleFrameRender(hdc, mImage, 
				CameraManager::GetInstance()->GetMainCamera()->GetRect().left, 
				CameraManager::GetInstance()->GetMainCamera()->GetRect().top,
				mCurrentAnimation->GetNowFrameX(),
				mCurrentAnimation->GetNowFrameY(),
				WINSIZEX, WINSIZEY);
	}
	else if (mCurrentAnimation == mAttackEffect3)
	{
		CameraManager::GetInstance()->GetMainCamera()
			->ScaleFrameRender(hdc, mImage, 
				CameraManager::GetInstance()->GetMainCamera()->GetRect().left,
				CameraManager::GetInstance()->GetMainCamera()->GetRect().top,
				mCurrentAnimation->GetNowFrameX(),
				mCurrentAnimation->GetNowFrameY(),
				WINSIZEX, WINSIZEY);
	}
}

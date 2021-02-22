#include "pch.h"
#include "Run.h"

#include "GameObject.h"
#include "Animation.h"
#include "State.h"
#include "Boom.h"
#include "Camera.h"
#include "Bottom.h"
#include "StopperObject.h"
#include "Image.h"
#include "ObjectManager.h"


void Run::Init()
{
	IsCrash = false;

	mRunKirby = IMAGEMANAGER->FindImage(L"Run");
	mGoalKirby = IMAGEMANAGER->FindImage(L"GoalKirby");
	//���� �ִϸ��̼�
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0, 0, 9, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.3f);

	//���� �ִϸ��̼�
	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(9, 1, 0, 1, true);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.3f);

	//���� �ִϸ��̼�
	mGoalKirbyAnimation = new Animation();
	mGoalKirbyAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mGoalKirbyAnimation->SetIsLoop(false);
	mGoalKirbyAnimation->SetFrameUpdateTime(0.3f);

	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	//�¿� ����
	if (mPlayer->GetIntMotionRL() == 0)
	{
		mCurrentAnimation = mRightAnimation;
	}
	else if (mPlayer->GetIntMotionRL() == 1)
	{
		mCurrentAnimation = mLeftAnimation;

	}
	// Run Ŀ�� ��� �浹�ߴٸ�

	//�ۼ��ؾ���

	
	mPlayer->SetSizeX(mRunKirby->GetFrameWidth());
	mPlayer->SetSizeY(mRunKirby->GetFrameHeight());



}

void Run::Release()
{
	SafeDelete(mRunKirby);
	SafeDelete(mGoalKirby);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mGoalKirbyAnimation);
	//SafeDelete(mCurrentAnimation);
}

void Run::Update()
{
	COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
		mX, mY);
	if (pixelColor != RGB(255, 0, 255))
	{
		mPlayer->SetY(mPlayer->GetY() - mPlayer->GetSizeY() / 2);
	}



	if (mCurrentAnimation == mLeftAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed() * 5);//Time::GetInstance()->DeltaTime());
	}
	if (mCurrentAnimation == mRightAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() + mPlayer->GetSpeed() * 5);//Time::GetInstance()->DeltaTime());
	}
	//������Ŀ��� �浹�� ��Ŀ��
	//RECT Temp;
	//mRunKirbyRect = mPlayer->GetRect();
	//RECT mStopKirby = mStopperObject->GetRect();
	//if (IntersectRect(&Temp, &mRunKirbyRect, &mStopKirby))
	//{
	//	IsCrash = true;
	//}

	if (IsCrash == true)
	{
		if (mCurrentAnimation == mLeftAnimation)
		{
			mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
			mLeftAnimation->Stop();
			mCurrentAnimation = mRightAnimation;
			mRightAnimation->Play();
		}
		if (mCurrentAnimation == mRightAnimation)
		{
			mPlayer->SetX(mPlayer->GetX() + mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftAnimation;
			mCurrentAnimation->Play();
		}
		IsCrash = false;
	}
	// ���� �ִϸ��̼��� Ʈ���� ���
	if (mPlayer->GetIsGoal() == true);
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mGoalKirbyAnimation;
		mCurrentAnimation->Play();
		mPlayer->SetIsGoal(false);
	}

	if (mCurrentAnimation == mGoalKirbyAnimation)
	{
		if (mCurrentAnimation->GetIsPlay() == false)
		{
			mPlayer->SetIsDestroy(true);
		}
	}
	
}

void Run::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mRunKirby, mPlayer->GetX() - mRunKirby->GetFrameWidth() / 2, mPlayer->GetRect().top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());

}

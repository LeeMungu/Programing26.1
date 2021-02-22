#include "pch.h"
#include "Run.h"

#include "GameObject.h"
#include "Animation.h"
#include "State.h"
#include "Boom.h"
#include "Camera.h"
#include "Bottom.h"
#include "StopperObject.h"


void Run::Init()
{
	IsCrash = false;

	mRunKirby = IMAGEMANAGER->FindImage(L"Run");
	mGoalKirby = IMAGEMANAGER->FindImage(L"GoalKirby");
	//���� �ִϸ��̼�
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByEndStart(0, 0, 9, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.3f);

	//���� �ִϸ��̼�
	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(0, 1, 9, 1, true);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.3f);

	//���� �ִϸ��̼�
	mGoalKirbyAnimation = new Animation();
	mGoalKirbyAnimation->InitFrameByEndStart(0, 0, 5, 0, true);
	mGoalKirbyAnimation->SetIsLoop(true);
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

	//������Ŀ��� �浹�� ��Ŀ��
	RECT Temp;
	mRunKirbyRect = mPlayer->GetRect();
	RECT mStopKirby = mStopperObject->GetRect();
	if (IntersectRect(&Temp, &mRunKirbyRect, &mStopKirby))
	{
		IsCrash = true;
	}
	mCurrentAnimation->Play();

}

void Run::Release()
{
	SafeDelete(mRunKirby);
	SafeDelete(mGoalKirby);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mGoalKirbyAnimation);
	SafeDelete(mCurrentAnimation);
}

void Run::Update()
{

	COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
		mX, mY);




	if (mCurrentAnimation == mLeftAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
	}
	if (mCurrentAnimation == mRightAnimation)
	{
		mPlayer->SetX(mPlayer->GetX() + mPlayer->GetSpeed()*Time::GetInstance()->DeltaTime());
	}
	//������Ŀ��� �浹�� ��Ŀ��
	RECT Temp;
	RECT mRunKirbyRect = mRunKirbyRect;
	RECT mStopKirby = mStopperObject->GetRect();
	if (IntersectRect(&Temp, &mRunKirbyRect, &mStopKirby))
	{
		IsCrash = true;
	}

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
	}
}

void Run::Render(HDC hdc)
{
	mCurrentAnimation->GetNowFrameX();
	mCurrentAnimation->GetNowFrameY();

}

#include "pch.h"
#include "Run.h"

#include "GameObject.h"
#include "Animation.h"
#include "State.h"


void Run::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Run", Resources(L"Walk.bmp"), 420, 76, 10, 2, true);
	mRunKirby = IMAGEMANAGER->FindImage(L"Run");

	//���� �ִϸ��̼�
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByEndStart(0, 0, 0, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.3f);
	mLeftAnimation->Play();

	//���� �ִϸ��̼�
	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(0, 1, 0, 1, false);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.3f);
	mRightAnimation->Play();

	mLeftRunState = LeftRunState::LeftMove;
	mRightRunState = RightRunState::RightMove;

	mPlayer->SetX(mPlayer->GetX());
	mPlayer->SetY(mPlayer->GetY());

}

void Run::Release()
{
}

void Run::Update()
{
}

void Run::Render(HDC hdc)
{
}

#include "pch.h"
#include "Run.h"

#include "GameObject.h"
#include "Animation.h"
#include "State.h"
#include "Boom.h"


void Run::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Run", Resources(L"Walk.bmp"), 420, 76, 10, 2, true);
	mRunKirby = IMAGEMANAGER->FindImage(L"Run");

	//좌측 애니메이션
	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByEndStart(0, 0, 0, 0, false);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.3f);
	mLeftAnimation->Play();

	//우측 애니메이션
	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByEndStart(0, 1, 0, 1, false);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.3f);
	mRightAnimation->Play();

	mLeftRunState = LeftRunState::LeftMove;
	mRightRunState = RightRunState::RightMove;

	mPlayer->SetX(mPlayer->GetX());
	mPlayer->SetY(mPlayer->GetY());
	mPlayer->SetSpeed(mPlayer->GetSpeed());
	mBottom->SetX(mBottom->GetX());
	mBottom->SetY(mBottom->GetY());

}

void Run::Release()
{
	SafeDelete(mRunKirby);
}

void Run::Update()
{


}

void Run::Render(HDC hdc)
{
}

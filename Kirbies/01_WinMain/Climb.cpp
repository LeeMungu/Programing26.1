#include "pch.h"
#include "Climb.h"
#include "Player.h"
#include "Animation.h"
#include "Bottom.h"
#include "Image.h"
#include "Camera.h"
void Climb::Init() {
	IMAGEMANAGER->LoadFromFile(L"Climb", Resources(L"climb.bmp"), 240, 52, 8, 2, true);
	mImage = IMAGEMANAGER->FindImage(L"Run");

	mAnimation = new Animation();
	//맨처음에는 run 상태 ?
	if (mPlayer->GetIntMotionRL() == 0) { //오른쪽
		mAnimation->InitFrameByStartEnd(0, 0, 9, 0, false);
		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.3f);
	}
	else { //왼쪽
		mAnimation->InitFrameByStartEnd(0, 1, 9, 1, false);
		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.3f);
	}

	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	mX = mPlayer->GetX();
	mY = mPlayer->GetY();

	mIsWallCheck = true;
	mIsWalkCheck = true;


	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());
}

void Climb::Update()
{
	mX = mPlayer->GetX();
	mY = mPlayer->GetY();

	if (mPlayer->GetIntMotionRL() == 0) //오른쪽
	{ 
		COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
			mX + 10, mY - 10);
		if (pixelColor != RGB(255, 0, 255))
		{
			mPlayer->SetY(mY--);
			ClimbAnim();
		}
		else
		{
			WalkAnim();
			mPlayer->SetX(mX++);
			//런으로 변경
		}
	}
	else  //왼쪽
	{
		COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
			mX - 10, mY - 10);
		if (pixelColor != RGB(255, 0, 255))
		{
			mPlayer->SetY(mY--);
			ClimbAnim();
		}
		else
		{
			WalkAnim();
			mPlayer->SetX(mX--);
			//런으로 변경
		}
	}
	mAnimation->Update();

}

void Climb::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mPlayer->GetX() - mImage->GetFrameWidth() / 2, mPlayer->GetRect().top,
			mAnimation->GetNowFrameX(),
			mAnimation->GetNowFrameY());

}

void Climb::ClimbAnim()
{
	if (mIsWallCheck)
	{
		mAnimation->Stop();
		mImage = IMAGEMANAGER->FindImage(L"Climb");
		if (mPlayer->GetIntMotionRL() == 0)
		{
			mAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
		}
		else
		{
			mAnimation->InitFrameByStartEnd(0, 1, 7, 1, false);
		}

		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.3f);
		mAnimation->Play();
		mIsWallCheck = false;
	}

	mIsWalkCheck = true;
}

void Climb::WalkAnim()
{
	if (mIsWalkCheck)
	{
		mAnimation->Stop();
		mImage = IMAGEMANAGER->FindImage(L"Run");
		if (mPlayer->GetIntMotionRL() == 0)
		{
			mAnimation->InitFrameByStartEnd(0, 0, 9, 0, false);
		}
		else
		{
			mAnimation->InitFrameByStartEnd(0, 1, 9, 1, false);
		}
		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.3f);
		mAnimation->Play();
		mIsWalkCheck = false;
	}

	mIsWallCheck = true;
}

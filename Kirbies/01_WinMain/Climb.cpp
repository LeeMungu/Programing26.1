#include "pch.h"
#include "Climb.h"
#include "Player.h"
#include "Animation.h"
#include "Bottom.h"
#include "Image.h"
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

}

void Climb::Update()
{
	mX = mPlayer->GetX();
	mY = mPlayer->GetY();

	if (mPlayer->GetIntMotionRL() == 0) { //오른쪽
		for (int i = mX; i < mX + 30; i++) {
			COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(), mX, mY);

			if (pixelColor != RGB(255, 0, 255))
			{
				mImage = IMAGEMANAGER->FindImage(L"Climb");

				mPlayer->SetY(mY--);
				mAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
				mAnimation->SetIsLoop(true);
				mAnimation->SetFrameUpdateTime(0.3f);

			}
			else
			{
				mPlayer->SetX(mX++);
			}

		}
		
	}
	else { //왼쪽
		mAnimation->InitFrameByStartEnd(1, 0, 7, 1, false);
		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.3f);
	}

}

void Climb::Render(HDC hdc)
{
}

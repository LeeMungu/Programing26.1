#include "pch.h"
#include "Dig.h"
#include "Animation.h"
#include "Bottom.h"
#include "Camera.h"
#include "Player.h"
#include "Image.h"
#include "DigPoint.h"

void Dig::Update()
{
	if (mIsStateStart == false)
	{
		//이미지 불러오기
		IMAGEMANAGER->LoadFromFile(L"Dig", Resources(L"dig.bmp"), 574, 82, 14, 2, true);
		mImage = IMAGEMANAGER->FindImage(L"Dig");

		//애니메이션 설정
		mAnimation = new Animation();
		if (mPlayer->GetIntMotionRL() == 0)
		{
			mAnimation->InitFrameByStartEnd(0, 0, 13, 0, false);
		}
		else if (mPlayer->GetIntMotionRL() == 1)
		{
			mAnimation->InitFrameByStartEnd(0, 1, 13, 1, true);
		}
		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.3f);
		mAnimation->Play();

		//맵
		mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");


		mIsStateStart = true;
	}
	float x = mPlayer->GetX();
	float y = mPlayer->GetRect().bottom;

	for (int i = y - 100; i < y + 100; i++)
	{
		COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(), x, y);


		if (pixelColor != RGB(255, 0, 255))
		{
			mTime++;
			//프레임마다 동작 (추후 수정)
			if (mTime == 50)
			{
				mTime = 0;

				HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
				HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
				HBRUSH oldBrush = (HBRUSH)SelectObject(mBottom->GetImage()->GetHDC(), brush);
				HPEN oldPen = (HPEN)SelectObject(mBottom->GetImage()->GetHDC(), pen);

				//RenderEllipse(mBottom->GetImage()->GetHDC(), x, y, 10);
				DigPoint* digpoint = new DigPoint(mBottom->GetImage()->GetHDC(), x, y, 10);
				ObjectManager::GetInstance()->AddObject(ObjectLayer::DigObject, digpoint);

				SelectObject(mBottom->GetImage()->GetHDC(), oldPen);
				SelectObject(mBottom->GetImage()->GetHDC(), oldBrush);
				DeleteObject(pen);
				DeleteObject(brush);

				y = i;
				break;
			}

		}
		else
		{
			//마젠타면 떨어지는 상태로 변경...인데 플레이어가 체크할것인가?
		}
	}




}

void Dig::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mPlayer->GetX() - mImage->GetFrameWidth() / 2, mPlayer->GetRect().top,
			mAnimation->GetNowFrameX(),
			mAnimation->GetNowFrameY());
}
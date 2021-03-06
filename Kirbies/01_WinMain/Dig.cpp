#include "pch.h"
#include "Dig.h"
#include "Animation.h"
#include "Bottom.h"
#include "Camera.h"
#include "Player.h"
#include "Image.h"
#include "DigPoint.h"
#include "Effect.h"
#include "KirbyEffect.h"
void Dig::Init()
{
	//이미지 불러오기
	
	mImage = IMAGEMANAGER->FindImage(L"Dig");
	Image* temp = IMAGEMANAGER->FindImage(L"Fall");
	IMAGEMANAGER->LoadFromFile(L"DigEffect", Resources(L"DigEffect.bmp"), 144, 46, 4, 1, true);

	//애니메이션 설정
	mAnimation = new Animation();
	if (mPlayer->GetIntMotionRL() == 0)
	{
		mAnimation->InitFrameByStartEnd(0, 0, 13, 0, false);
	}
	else if (mPlayer->GetIntMotionRL() == 1)
	{
		mAnimation->InitFrameByEndStart(13, 1, 0, 1, false);
	}
	mAnimation->SetIsLoop(true);
	mAnimation->SetFrameUpdateTime(0.1f);
	mAnimation->Play();

	//맵
	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	//플레이어 세팅
	mX = mPlayer->GetX();
	mY = mPlayer->GetY();

	mPlayer->SetSizeX(temp->GetFrameWidth());
	mPlayer->SetSizeY(temp->GetFrameHeight());

	mSizeX = mPlayer->GetSizeX()/41*21;
	mSizeY = mPlayer->GetSizeY()/41*19;

	//mDigRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	//mPlayer->SetRect(mDigRect);
	//셋함수 만들어서 넣어두면되나? 상의필요

	mIsFallCheck = false;
	mIsDigCheck = false;
	mRadius = 30;
	mIsDig = false;
}

void Dig::Update()
{

	float x = mPlayer->GetX();
	float y = mPlayer->GetRect().bottom;



	for (int i = y-100; i < y + 100; i++)
	{
		COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(), x, y);


		if (pixelColor != RGB(255, 0, 255))
		{
			DigAnimation();
			if (mPlayer->GetIntMotionRL() == 0)
			{

				if (mAnimation->GetNowFrameX() == 5 && mIsDig==false)
				{
					HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
					HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
					HBRUSH oldBrush = (HBRUSH)SelectObject(mBottom->GetImage()->GetHDC(), brush);
					HPEN oldPen = (HPEN)SelectObject(mBottom->GetImage()->GetHDC(), pen);

					//DigPoint* digpoint = new DigPoint(mBottom->GetImage()->GetHDC(), x, y, 10);
					//digpoint->Render(mBottom->GetImage()->GetHDC());
					//ObjectManager::GetInstance()->AddObject(ObjectLayer::DigObject, digpoint);
					RenderEllipse(mBottom->GetImage()->GetHDC(), x, y, mRadius);
					mEffect = new KirbyEffect("DigEffect", x, y, L"DigEffect", 4, 1);
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, mEffect);

					SelectObject(mBottom->GetImage()->GetHDC(), oldPen);
					SelectObject(mBottom->GetImage()->GetHDC(), oldBrush);
					DeleteObject(pen);
					DeleteObject(brush);
					SoundPlayer::GetInstance()->Play(L"DigEffectSound", 5.f * SoundPlayer::GetInstance()->GetEffectVolum());
					mPlayer->SetY(mPlayer->GetY()+mRadius);
					mIsDig = true;
					break;
				}
				if (mAnimation->GetNowFrameX() != 5)
				{
					mIsDig = false;
				}
			}
			else if (mPlayer->GetIntMotionRL() == 1)
			{
				if (mAnimation->GetNowFrameX() == 8 && mIsDig == false)
				{
					HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
					HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
					HBRUSH oldBrush = (HBRUSH)SelectObject(mBottom->GetImage()->GetHDC(), brush);
					HPEN oldPen = (HPEN)SelectObject(mBottom->GetImage()->GetHDC(), pen);

					//DigPoint* digpoint = new DigPoint(mBottom->GetImage()->GetHDC(), x, y, 10);
					//digpoint->Render(mBottom->GetImage()->GetHDC());
					//ObjectManager::GetInstance()->AddObject(ObjectLayer::DigObject, digpoint);
					RenderEllipse(mBottom->GetImage()->GetHDC(), x, y, mRadius);
					mEffect = new KirbyEffect("DigEffect", x, y, L"DigEffect", 4, 1);
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, mEffect);

					SelectObject(mBottom->GetImage()->GetHDC(), oldPen);
					SelectObject(mBottom->GetImage()->GetHDC(), oldBrush);
					DeleteObject(pen);
					DeleteObject(brush);
					SoundPlayer::GetInstance()->Play(L"DigEffectSound", 5.f * SoundPlayer::GetInstance()->GetEffectVolum());
					mPlayer->SetY(mPlayer->GetY() + mRadius);
					mIsDig = true;
					break;
				}
				if (mAnimation->GetNowFrameX() != 8)
				{
					mIsDig = false;
				}
			}


		}
		else
		{
			mPlayer->SetY(mPlayer->GetY() + 0.5f * Time::GetInstance()->DeltaTime());
			FallAnimation();
			//마젠타면 떨어지는 상태로 변경...인데 플레이어가 체크할것인가?
		}
	}

	mAnimation->Update();
}

void Dig::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mPlayer->GetX() - mImage->GetFrameWidth() / 2,
			mPlayer->GetY() - mImage->GetFrameWidth() + mSizeY / 2 +10, mAnimation->GetNowFrameX(),
			mAnimation->GetNowFrameY());
}

void Dig::mapRender(HDC map)
{
	mImage->FrameRender(map, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}

void Dig::FallAnimation()
{
	if (mIsFallCheck == false)
	{
		mAnimation->Stop();
		mImage = IMAGEMANAGER->FindImage(L"Fall");
		if (mPlayer->GetIntMotionRL() == 0)
		{
			mAnimation->InitFrameByStartEnd(0, 0, 9, 0, false);
		}
		else
		{
			mAnimation->InitFrameByStartEnd(0, 1, 9, 1, false);
		}
		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.1f);
		mAnimation->Play();

		mIsFallCheck = true;
	}
	mIsDigCheck = false;

}

void Dig::DigAnimation()
{
	if (mIsDigCheck == false)
	{
		mAnimation->Stop();
		mImage = IMAGEMANAGER->FindImage(L"Dig");
		if (mPlayer->GetIntMotionRL() == 0)
		{
			mAnimation->InitFrameByStartEnd(0, 0, 13, 0, false);
		}
		else
		{
			mAnimation->InitFrameByEndStart(13, 1, 0, 1, false);
		}
		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.1f);
		mAnimation->Play();
		mIsDigCheck = true;
	}
	mIsFallCheck = false;

}

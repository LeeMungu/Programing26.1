#include "pch.h"
#include "Dig.h"
#include "Animation.h"
#include "Bottom.h"
#include "Camera.h"
#include "Player.h"
#include "Image.h"
#include "DigPoint.h"

void Dig::Init()
{
	//�̹��� �ҷ�����
	
	mImage = IMAGEMANAGER->FindImage(L"Dig");
	Image* temp = IMAGEMANAGER->FindImage(L"Fall");
	//�ִϸ��̼� ����
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
	SoundPlayer::GetInstance()->Play(L"DigEffectSound", 0.8);
	mAnimation->SetFrameUpdateTime(0.1f);
	mAnimation->Play();

	//��
	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	//�÷��̾� ����
	mX = mPlayer->GetX();
	mY = mPlayer->GetY();

	mPlayer->SetSizeX(temp->GetFrameWidth());
	mPlayer->SetSizeY(temp->GetFrameHeight());

	mSizeX = mPlayer->GetSizeX()/41*21;
	mSizeY = mPlayer->GetSizeY()/41*19;

	//mDigRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	//mPlayer->SetRect(mDigRect);
	//���Լ� ���� �־�θ�ǳ�? �����ʿ�

	mIsFallCheck = false;
	mIsDigCheck = false;
	mRadius = 30;
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

				if (mAnimation->GetNowFrameX() == 5)
				{
					HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
					HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
					HBRUSH oldBrush = (HBRUSH)SelectObject(mBottom->GetImage()->GetHDC(), brush);
					HPEN oldPen = (HPEN)SelectObject(mBottom->GetImage()->GetHDC(), pen);

					//DigPoint* digpoint = new DigPoint(mBottom->GetImage()->GetHDC(), x, y, 10);
					//digpoint->Render(mBottom->GetImage()->GetHDC());
					//ObjectManager::GetInstance()->AddObject(ObjectLayer::DigObject, digpoint);
					RenderEllipse(mBottom->GetImage()->GetHDC(), x, y, mRadius);

					SelectObject(mBottom->GetImage()->GetHDC(), oldPen);
					SelectObject(mBottom->GetImage()->GetHDC(), oldBrush);
					DeleteObject(pen);
					DeleteObject(brush);

					mPlayer->SetY(mPlayer->GetY()+mRadius/2);
					break;
				}
			}
			else if (mPlayer->GetIntMotionRL() == 1)
			{
				if (mAnimation->GetNowFrameX() == 8)
				{
					HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
					HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
					HBRUSH oldBrush = (HBRUSH)SelectObject(mBottom->GetImage()->GetHDC(), brush);
					HPEN oldPen = (HPEN)SelectObject(mBottom->GetImage()->GetHDC(), pen);

					//DigPoint* digpoint = new DigPoint(mBottom->GetImage()->GetHDC(), x, y, 10);
					//digpoint->Render(mBottom->GetImage()->GetHDC());
					//ObjectManager::GetInstance()->AddObject(ObjectLayer::DigObject, digpoint);
					RenderEllipse(mBottom->GetImage()->GetHDC(), x, y, mRadius);

					SelectObject(mBottom->GetImage()->GetHDC(), oldPen);
					SelectObject(mBottom->GetImage()->GetHDC(), oldBrush);
					DeleteObject(pen);
					DeleteObject(brush);

					mPlayer->SetY(mPlayer->GetY() + mRadius/2);
					break;
				}
			}


		}
		else
		{
			mPlayer->SetY(mPlayer->GetY() + 0.5f * Time::GetInstance()->DeltaTime());
			FallAnimation();
			//����Ÿ�� �������� ���·� ����...�ε� �÷��̾ üũ�Ұ��ΰ�?
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

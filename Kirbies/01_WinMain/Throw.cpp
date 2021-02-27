#include "pch.h"
#include "Throw.h"
#include "Image.h"
#include "Player.h"
#include "Camera.h"
#include "Animation.h"
#include "Bottom.h"
void Throw::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Fall");
	mX = mPlayer->GetX();
	mY = mPlayer->GetY();

	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());

	mSizeX = mPlayer->GetSizeX();
	mSizeY = mPlayer->GetSizeY();

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, 0, 15, 0, false);
	mAnimation->SetIsLoop(true);
	mAnimation->SetFrameUpdateTime(0.1f);
	mAnimation->Play();
	misTrigger = false;
}

void Throw::Release()
{
	SafeDelete(mAnimation);
}

void Throw::Update()
{
	mPlayer->SetXPosition(cosf(1.1) * 16);
	mPlayer->SetYPosition(-sinf(1.1) * 16 + mThrowGravity);
	mThrowGravity += 0.2f;
	mTimer += Time::GetInstance()->DeltaTime();

	if (mTimer > 1.7 && misTrigger == false)
	{
		mTimer = 0;
		misTrigger = true;
		mPlayer->SetPlayerState(PlayerState::FallState);
		mPlayer->SetIsChange(true);
	}




	mAnimation->Update();
}

void Throw::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mPlayer->GetX() - mImage->GetFrameWidth() / 2,
			mPlayer->GetY() - mImage->GetFrameWidth() + mSizeY / 2 + 10, mAnimation->GetNowFrameX(),
			mAnimation->GetNowFrameY());
}

void Throw::mapRender(HDC map)
{
	mImage->FrameRender(map, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}

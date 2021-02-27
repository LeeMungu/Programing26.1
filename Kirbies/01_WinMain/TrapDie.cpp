#include "pch.h"
#include "TrapDie.h"
#include "Animation.h"
#include "Player.h"
#include "Image.h"
#include "BoomRectManager.h"
#include "Camera.h"
void TrapDie::Init()
{
	mFallDeadKirby = IMAGEMANAGER->FindImage(L"KirbyFallDead");

	mAnimation = new Animation();
	if (mPlayer->GetIntMotionRL() == 0)
	{
		mAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);

	}
	else if (mPlayer->GetIntMotionRL() == 1)
	{
		mAnimation->InitFrameByEndStart(2, 1, 0, 1, false);

	}
	mAnimation->SetIsLoop(false);
	mAnimation->SetFrameUpdateTime(0.3f);
	mAnimation->Play();

	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	mAnimation->SetCallbackFunc([this]() {
		BoomRectManager* boomRcManager = new BoomRectManager(mPlayer->GetX() + 10, mPlayer->GetY() + 15);
		boomRcManager->Init();

		mPlayer->SetIsDestroy(true);
		});

}

void TrapDie::Release()
{
}

void TrapDie::Update()
{
	mAnimation->Update();
}

void TrapDie::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mFallDeadKirby, mPlayer->GetX(), mPlayer->GetY() + 10, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}

void TrapDie::mapRender(HDC map)
{
}

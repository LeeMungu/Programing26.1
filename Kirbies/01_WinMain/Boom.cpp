#include "pch.h"
#include "Boom.h"
#include "Animation.h"
#include "Bottom.h"
#include "Image.h"
#include "Player.h"
#include "Effect.h"
#include "Camera.h"
#include "KirbyEffect.h"
#include "BoomRectManager.h"

void Boom::Init() {
	
	mImage = IMAGEMANAGER->FindImage(L"Boom");


	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
	mAnimation->SetIsLoop(true);
	mAnimation->SetFrameUpdateTime(0.15f);
	mAnimation->SetCallbackFunc([this]() {
		SoundPlayer::GetInstance()->Stop(L"FuseEffectSound");
		SoundPlayer::GetInstance()->Play(L"BunEffectSound", 0.8 *SoundPlayer::GetInstance()->GetEffectVolum());
		BoomRectManager* boomRcManager = new BoomRectManager(mPlayer->GetX(), mPlayer->GetY());
		boomRcManager->Init();
		
		mPlayer->SetIsDestroy(true);
	});
	mAnimation->Play();

	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	mX = mPlayer->GetX();
	mY = mPlayer->GetY();
	mPlayerRect = mPlayer->GetRect();

	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());

	mTimer = 0;

	
	//mEffect = new Effect("BoomEffect", mX, mY, L"BoomEffect");
}
// Ŀ�� ������ -> ī��Ʈ�ٿ�(5��) -> (���⼭�� ī��Ʈ�ٿ� ���� �ൿ ���α׷���)
// Ŀ�� �����鼭 ������� -> ����Ʈ�� �Բ� Ŀ�� �ִ� �ڸ��� ���� ���δ�
void Boom::Update() {
	
	//���� �پ����� ���� ����
	for (int i = mPlayer->GetRect().bottom; i < mPlayer->GetRect().bottom + 100; i++)
	{
		COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(), mX, mPlayer->GetRect().bottom - 5);


		if (pixelColor != RGB(255, 0, 255))
		{
			if (mAnimation->GetNowFrameX() == 7){
				//�� �ı�
				HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
				HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
				HBRUSH oldBrush = (HBRUSH)SelectObject(mBottom->GetImage()->GetHDC(), brush);
				HPEN oldPen = (HPEN)SelectObject(mBottom->GetImage()->GetHDC(), pen);

				RenderEllipse(mBottom->GetImage()->GetHDC(), mX - 10, mPlayer->GetRect().bottom, 30);
				RenderEllipse(mBottom->GetImage()->GetHDC(), mX + 10, mPlayer->GetRect().bottom + 20, 50);
				SoundPlayer::GetInstance()->Play(L"FuseEffectSound", 0.8 *SoundPlayer::GetInstance()->GetEffectVolum());
			
				SelectObject(mBottom->GetImage()->GetHDC(), oldPen);
				SelectObject(mBottom->GetImage()->GetHDC(), oldBrush);
				DeleteObject(pen);
				DeleteObject(brush);

				mTimer = 0;

				mEffect = new KirbyEffect("BoomEffect", mX - 15, mY - 40, L"BoomEffect", 9, 1);
				ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, mEffect);
				//�ִϸ��̼� �÷��� �� �÷��̾� ����
			}

		}
		else {
			mY += 1.5f;
			mPlayer->SetY(mY);
			break;
		}
	}
	mAnimation->Update();
}

void Boom::Render(HDC hdc) {
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mPlayer->GetRect().left, mPlayer->GetRect().top, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());

}

void Boom::mapRender(HDC map)
{
	mImage->FrameRender(map, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}

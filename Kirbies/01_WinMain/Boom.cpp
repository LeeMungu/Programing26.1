#include "pch.h"
#include "Boom.h"
#include "Animation.h"
#include "Bottom.h"
#include "Image.h"
#include "Player.h"
#include "Effect.h"
#include "Camera.h"
void Boom::Init() {
	IMAGEMANAGER->LoadFromFile(L"Boom", Resources(L"boom.bmp"), 280, 32, 8, 1, true);
	mImage = IMAGEMANAGER->FindImage(L"Boom");

	IMAGEMANAGER->LoadFromFile(L"BoomEffect", Resources(L"boom_Effect.bmp"), 288, 48, 8, 1, true);

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
	mAnimation->SetIsLoop(false);
	mAnimation->SetFrameUpdateTime(0.3f);
	mAnimation->Play();

	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	mX = mPlayer->GetX();
	mY = mPlayer->GetY();
	mPlayerRect = mPlayer->GetRect();

	mEffect = new Effect("BoomEffect", mX, mY, L"BoomEffect");


	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());
}
// 커비 핵폭발 -> 카운트다운(5초) -> (여기서는 카운트다운 다음 행동 프로그래밍)
// 커비 죽으면서 사라진다 -> 이펙트와 함께 커비 있던 자리에 땅도 파인다
void Boom::Update() {
	//mTimeTemp += Time::GetInstance()->DeltaTime();

	if (mAnimation->GetIsPlay() == false) { //불타는 애니메이션 동작 끝났으면
		//연기 이펙트 발생
		

		//맵 파괴
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBottom->GetImage()->GetHDC(), brush);
		HPEN oldPen = (HPEN)SelectObject(mBottom->GetImage()->GetHDC(), pen);

		RenderEllipse(mBottom->GetImage()->GetHDC(), mX, mY, 50);

		SelectObject(mBottom->GetImage()->GetHDC(), oldPen);
		SelectObject(mBottom->GetImage()->GetHDC(), oldBrush);
		DeleteObject(pen);
		DeleteObject(brush);


		//애니메이션 플레이 후 플레이어 제거
		SafeDelete(mPlayer);

	}
}

void Boom::Render(HDC hdc) {
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
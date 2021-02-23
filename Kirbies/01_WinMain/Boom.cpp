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
	mAnimation->SetIsLoop(true);
	mAnimation->SetFrameUpdateTime(0.15f);
	mAnimation->Play();

	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	mX = mPlayer->GetX();
	mY = mPlayer->GetY();
	mPlayerRect = mPlayer->GetRect();

	mEffect = new Effect("BoomEffect", mX, mY, L"BoomEffect");


	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());

	mTimer = 0;
}
// Ŀ�� ������ -> ī��Ʈ�ٿ�(5��) -> (���⼭�� ī��Ʈ�ٿ� ���� �ൿ ���α׷���)
// Ŀ�� �����鼭 ������� -> ����Ʈ�� �Բ� Ŀ�� �ִ� �ڸ��� ���� ���δ�
void Boom::Update() {
	mTimer += Time::GetInstance()->DeltaTime();

	if (mTimer >= 3) {
		//�� �ı�
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBottom->GetImage()->GetHDC(), brush);
		HPEN oldPen = (HPEN)SelectObject(mBottom->GetImage()->GetHDC(), pen);

		RenderEllipse(mBottom->GetImage()->GetHDC(), mX, mY, 30);

		SelectObject(mBottom->GetImage()->GetHDC(), oldPen);
		SelectObject(mBottom->GetImage()->GetHDC(), oldBrush);
		DeleteObject(pen);
		DeleteObject(brush);


		//�ִϸ��̼� �÷��� �� �÷��̾� ����
		mPlayer->SetIsDestroy(true);
	}

	//}
	mAnimation->Update();
}

void Boom::Render(HDC hdc) {
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mX-20, mY-20, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}
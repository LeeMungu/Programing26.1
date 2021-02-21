#include "pch.h"
#include "Boom.h"
#include "Animation.h"
// Ŀ�� ������ -> ī��Ʈ�ٿ�(5��) -> (���⼭�� ī��Ʈ�ٿ� ���� �ൿ ���α׷���)
// Ŀ�� �����鼭 ������� -> ����Ʈ�� �Բ� Ŀ�� �ִ� �ڸ��� ���� ���δ�
void Boom::Update() {
	//mTimeTemp += Time::GetInstance()->DeltaTime();

	if (mIsFirstUpdate == false) {
		IMAGEMANAGER->LoadFromFile(L"Boom", Resources(L"boom.bmp"), 280, 32, 8, 1, true);
		mImage = IMAGEMANAGER->FindImage(L"Boom");

		mAnimation = new Animation();
		mAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
		mAnimation->SetIsLoop(false);
		mAnimation->SetFrameUpdateTime(0.3f);
		mAnimation->Play();

		mIsFirstUpdate = true;
	}
	if (mAnimation->GetIsPlay() == false) {
		//�ִϸ��̼� �÷��� �� �÷��̾� ����
		SafeDelete(mPlayer);
	}
}

void Boom::Render(HDC hdc) {

}
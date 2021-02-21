#include "pch.h"
#include "Boom.h"
#include "Animation.h"
// 커비 핵폭발 -> 카운트다운(5초) -> (여기서는 카운트다운 다음 행동 프로그래밍)
// 커비 죽으면서 사라진다 -> 이펙트와 함께 커비 있던 자리에 땅도 파인다
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
		//애니메이션 플레이 후 플레이어 제거
		SafeDelete(mPlayer);
	}
}

void Boom::Render(HDC hdc) {

}
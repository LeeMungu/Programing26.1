#include "pch.h"
#include "Npc.h"

#include "Image.h"
#include "Animation.h"
#include "Camera.h"
Npc::Npc(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Npc::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Npc", Resources(L"Dedede.bmp"), 256, 122, 4, 2, true);
	mImage = IMAGEMANAGER->FindImage(L"Npc");

	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 0, 4, false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(0.3f);
	mIdleAnimation->Play();

	mRunAnimation = new Animation();
	mRunAnimation->InitFrameByStartEnd(0, 1, 4, 1, false);
	mRunAnimation->SetIsLoop(true);
	mRunAnimation->SetFrameUpdateTime(0.1f);

	mCurrentAnimation = mRunAnimation;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Npc::Release()
{
	SafeDelete(mIdleAnimation);
}

void Npc::Update()
{
	if (mIsWin == true && mIsPlaced == false) { //�̰�����
		 mX -= 3.f * Time::GetInstance()->DeltaTime(); //�������� �̵�
		
		 if (mX <= 400) mIsPlaced = true; //���ϴ� ��ġ ����
	}
	else {
		mCurrentAnimation->Stop();
		mCurrentAnimation = mIdleAnimation;
		mCurrentAnimation->Play();

		if (mIsPlaced == true) {
			//��ȭ ��¼��
		}
	}

	mCurrentAnimation->Update();
}

void Npc::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());

}
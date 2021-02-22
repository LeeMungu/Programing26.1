#include "pch.h"
#include "Ui.h"
#include "Image.h"
#include "State.h"
#include "Camera.h"
#include "Player.h"
//��ҿ��� ����̹��� -> ���콺 �ø��� �����̹���
//������ ������ ���� -> 0�� �ƴ� ���� �̿� ���� -> �����ϸ� state �ٲ��ش�(���콺���� �ϴ°�?)
Ui::Ui(PlayerState state, float x, float y, int count) {
	mState = state;
	mX = x;
	mY = y;
	mCountNum = count;

	mImage = IMAGEMANAGER->FindImage(L"ButtonUI");

	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
	 
	//state�� ���� �׷��� �̹��� ��ġ �ٸ� 	mFrameX = ;
	if (mState == PlayerState::BoomState)		mFrameX = 2;
	else if (mState == PlayerState::ClimbState)	mFrameX = 4;
	else if (mState == PlayerState::DigState)	mFrameX = 1;
	else if (mState == PlayerState::UmbrellaState) mFrameX = 0;
	else if (mState == PlayerState::StopperState)  mFrameX = 3;
	mFrameY = 1;

	mIsClicked = false;
}
void Ui::Init()
{

}

void Ui::Release()
{
}

void Ui::Update()
{

	if (PtInRect(&mRect, _mousePosition)) {
		mFrameY = 0;
		if (Input::GetInstance()->GetKeyDown(VK_LEFT)) {
			if (mCountNum != 0) {
				mCountNum--;
				mPlayer->SetPlayerState(mState);

				mIsClicked = true;
			}
		}
		else {
			mIsClicked = false;
		}
	}
	else {
		mFrameY = 1;
	}
}

void Ui::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mX, mY, mFrameX, mFrameY);
}

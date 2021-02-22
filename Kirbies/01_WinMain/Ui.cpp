#include "pch.h"
#include "Ui.h"
#include "Image.h"
#include "State.h"
#include "Camera.h"
#include "Player.h"
#include "Mouse.h"
//��ҿ��� ����̹��� -> ���콺 �ø��� �����̹���
//������ ������ ���� -> 0�� �ƴ� ���� �̿� ���� -> �����ϸ� state �ٲ��ش�(���콺���� �ϴ°�?)
Ui::Ui(PlayerState state, float x, float y, int count) {
	mState = state;
	mX = x;
	mY = y;
	mCountNum = count;

	mImage = IMAGEMANAGER->FindImage(L"Button");

	mCountUI = IMAGEMANAGER->FindImage(L"UICount");
	mCountTens = IMAGEMANAGER->FindImage(L"Numbers");
	mCountUnits = IMAGEMANAGER->FindImage(L"Numbers");

	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());

	//state�� ���� �׷��� �̹��� ��ġ �ٸ� 	mFrameX = ;
	if (mState == PlayerState::BoomState)		mFrameX = 2;
	else if (mState == PlayerState::ClimbState)	mFrameX = 4;
	else if (mState == PlayerState::DigState)	mFrameX = 1;
	else if (mState == PlayerState::UmbrellaState) mFrameX = 0;
	else if (mState == PlayerState::StopperState)  mFrameX = 3;
	mFrameY = 1;

	mIsClicked = false;
	//mMouse = (Mouse*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Mouse,"Mouse");
}
void Ui::Init()
{

}

void Ui::Release()
{
}

void Ui::Update()
{
	mTensNum = (mCountNum / 10) % 10;
	mUnitsNum = mCountNum % 10;

	if (PtInRect(&mRect, _mousePosition)) {
		mFrameY = 0;
		if (Input::GetInstance()->GetKeyDown(MK_LBUTTON)) {
			if (mCountNum != 0) {
				mCountNum--;
				//mMouse->SetPlayerState(mState);

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
	mImage->FrameRender(hdc, mRect.left, mRect.top, mFrameX, mFrameY);

	mCountUI->Render(hdc, mRect.left - 5, mRect.top - 5);

	mCountTens->FrameRender(hdc, mRect.left + 4, mRect.top + 7, mTensNum, 0);
	mCountUnits->FrameRender(hdc, mRect.left + mCountTens->GetFrameWidth() + 5, mRect.top + 7, mUnitsNum, 0);
}

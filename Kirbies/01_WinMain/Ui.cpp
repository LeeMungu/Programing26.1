#include "pch.h"
#include "Ui.h"
#include "Image.h"
#include "State.h"
#include "Camera.h"
#include "Player.h"
#include "Mouse.h"
//평소에는 흑백이미지 -> 마우스 올리면 색깔이미지
//정해진 개수가 있음 -> 0이 아닐 때만 이용 가능 -> 선택하면 state 바꿔준다(마우스에서 하는거?)
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

	//state에 따라 그려줄 이미지 위치 다름 	mFrameX = ;
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

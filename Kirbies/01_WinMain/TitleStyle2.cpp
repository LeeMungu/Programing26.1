#include "pch.h"
#include "TitleStyle2.h"
#include "Image.h"

TitleStyle2::TitleStyle2(wstring key)
	:Title(key)
{
}

void TitleStyle2::Init()
{
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mUpLimit = -WINSIZEY;
	mX = WINSIZEX / 2;
	mY = -WINSIZEY / 2 + 100;
	mState = State::Down;
	mUpLimit = -WINSIZEY / 2 + 300;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void TitleStyle2::Release()
{
}

void TitleStyle2::Update()
{
		//mY > WINSIZEY/2-50 && mY < WINSIZEY/2+50)
	//if (mUpLimit > WINSIZEY / 2 && mY >= WINSIZEY / 2)
	//{
	//	mState = TitleStyle1::State::Stop;
	//}
	//if (mState == TitleStyle1::State::Up)
	//{
	//	mY -= 400 * Time::GetInstance()->DeltaTime();
	//	if (mY < mUpLimit)
	//	{
	//		mState = TitleStyle1::State::Down;
	//		mUpLimit += 300;
	//	}
	//}
	//else if (mState == TitleStyle1::State::Down)
	//{
	//	mY += 500 * Time::GetInstance()->DeltaTime();
	//	if (mY > WINSIZEY / 2)
	//	{
	//		mState = TitleStyle1::State::Up;
	//	}
	//}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void TitleStyle2::Render(HDC hdc)
{
	mImage->ScaleRender(hdc, mRect.left, mRect.top, mSizeX, mSizeY*);
}
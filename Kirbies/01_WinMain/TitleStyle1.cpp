#include "pch.h"
#include "TitleStyle1.h"
#include "Image.h"

TitleStyle1::TitleStyle1(wstring key)
	:Title(key)
{
}

void TitleStyle1::Init()
{
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mUpLimit = -WINSIZEY;
	mX = WINSIZEX / 2;
	mY = -WINSIZEY / 2 + 100;
	mState = State::Down;
	mUpLimit = -WINSIZEY/2 +300;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void TitleStyle1::Release()
{
}

void TitleStyle1::Update()
{
	if (mUpLimit > WINSIZEY/2 && mY >= WINSIZEY/2)
		//mY > WINSIZEY/2-50 && mY < WINSIZEY/2+50)
	{
		mState = TitleStyle1::State::Stop;
	}
	if (mState == TitleStyle1::State::Up)
	{
		mY -= 400 * Time::GetInstance()->DeltaTime();
		if (mY < mUpLimit)
		{
			mState = TitleStyle1::State::Down;
			mUpLimit += 300;
		}
	}
	else if (mState == TitleStyle1::State::Down)
	{
		mY += 500 * Time::GetInstance()->DeltaTime();
		if (mY > WINSIZEY / 2)
		{
			mState = TitleStyle1::State::Up;
		}
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

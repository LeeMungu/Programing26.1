#include "pch.h"
#include "TitleStyle4.h"
#include "Image.h"

TitleStyle4::TitleStyle4(wstring key, TitleStyle4::State state)
	:Title(key)
{
	mName = "TitleFinal";
	mState = state;
}

void TitleStyle4::Init()
{
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mLeftLimit = WINSIZEX / 3 * 2;
	mRightLimit = WINSIZEX / 2 - WINSIZEX / 90;
	if (mState == State::RightToLeft)
	{
		mX = WINSIZEX * 2;
	}
	else
	{
		mX = -WINSIZEX;
	}
	mY = WINSIZEY / 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mIsEndAnimation = false;
}

void TitleStyle4::Release()
{
}

void TitleStyle4::Update()
{
	if (mState == State::RightToLeft)
	{
		mX -= 20;
		if (mX < mRightLimit)
		{
			mX = WINSIZEX / 2;
			mState = State::Stop;
			mIsEndAnimation = true;
		}
	}
	else if (mState == State::LeftToRight)
	{
		mX += 20;
		if (mX > WINSIZEX/2)
		{
			mX = WINSIZEX / 2;
			mState = State::Stop;
			mIsEndAnimation = true;
		}
	}
	else if (mState == State::Stop && mIsEndAnimation == true)
	{
		//다음타자 생성
		mIsEndAnimation = false;
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

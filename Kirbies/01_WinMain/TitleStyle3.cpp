#include "pch.h"
#include "TitleStyle3.h"
#include "TitleStyle4.h"
#include "Image.h"


TitleStyle3::TitleStyle3(wstring key)
	:Title(key)
{
}

void TitleStyle3::Init()
{
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mLeftLimit = WINSIZEX / 3 * 2;
	mRightLimit = WINSIZEX/2 - WINSIZEX/90;
	mX = WINSIZEX/3*2;
	mY = WINSIZEY/2;
	mState = State::RightToLeft;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mIsEndAnimation = false;
}

void TitleStyle3::Release()
{

}

void TitleStyle3::Update()
{
	if (mState == State::RightToLeft)
	{
		mX -= 20;
		if (mX < mRightLimit)
		{
			mState = State::LeftToRight;
			//mRightLimit += 10;
			//if (mRightLimit > WINSIZEX/2 && mX < WINSIZEX/2)
			//{
				mX = WINSIZEX / 2;
				mState = State::Stop;
				mIsEndAnimation = true;
			//}
		}
	}
	//else if (mState == State::LeftToRight)
	//{
	//	mX += 20;
	//	if (mX > WINSIZEX/2)
	//	{
	//		mState = State::LeftToRight;
	//		mLeftLimit -= 10;
	//		if (mLeftLimit < WINSIZEX / 2 && mX>WINSIZEX/2)
	//		{
	//			mX = WINSIZEX / 2;
	//			mState = State::Stop;
	//			mIsEndAnimation = true;
	//		}
	//	}
	//}
	else if (mState == State::Stop && mIsEndAnimation == true)
	{
		//다음타자 생성
		mIsEndAnimation = false;
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

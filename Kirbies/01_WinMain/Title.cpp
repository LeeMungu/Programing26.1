#include "pch.h"
#include "Title.h"
#include "Image.h"

Title::Title(type type, wstring key)
{
	mType = type;
	mImage = IMAGEMANAGER->FindImage(key);
}

void Title::Init()
{
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	switch (mType)
	{
	case type::UpAndDown:
		mUpLimit = -WINSIZEY;
		mX = WINSIZEX / 2;
		mY = -WINSIZEY / 2 + 100;
		mState = State::Down;
		break;
	case type::Size:
		
		break;
	case type::S:
		
		break;
	case type::RightToLeft:
		
		break;
	case type::LeftToRight:
		
		break;
	}

	mUpLimit = -WINSIZEY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Title::Release()
{
}

void Title::Update()
{
	switch (mType)
	{
	case type::UpAndDown:
		if (mUpLimit > 0)
		{
			mState == Title::State::Stop;
		}
		if (mState == Title::State::Up)
		{
			mY -= 5 * Time::GetInstance()->DeltaTime();
			if (mY < mUpLimit)
			{
				mState = Title::State::Down;
				mUpLimit += 50;
			}
		}
		else if (mState == Title::State::Down)
		{
			mY += 5 * Time::GetInstance()->DeltaTime();
			if (mY > WINSIZEY / 2)
			{
				mState = Title::State::Up;
			}
		}


		break;
	
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Title::Render(HDC hdc)
{
	mImage->Render(hdc, mRect.left, mRect.top);
}

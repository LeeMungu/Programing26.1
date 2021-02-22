#include "pch.h"
#include "TitleStyle2.h"
#include "TitleStyle3.h"
#include "Image.h"

TitleStyle2::TitleStyle2(wstring key)
	:Title(key)
{
}

void TitleStyle2::Init()
{
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mSizeLimit = WINSIZEY*6;
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mState = State::SizeDown;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mIsEndAnimation = false;
}

void TitleStyle2::Release()
{
}

void TitleStyle2::Update()
{
	if (mState == State::SizeDown)
	{
		mSizeLimit -= 100;
		if (mSizeLimit <= WINSIZEY)
		{
			mSizeLimit = WINSIZEY;
			mState = State::Stop;
			mIsEndAnimation = true;
		}
	}

	if (mState==State::Stop && mIsEndAnimation == true)
	{
		TitleStyle3* mainText2 = new TitleStyle3(L"MainTitle2");
		mainText2->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, mainText2);
		mIsEndAnimation = false;
	}
	
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void TitleStyle2::Render(HDC hdc)
{
	mImage->ScaleRender(hdc, mRect.left, 
		-(mSizeLimit/2 - WINSIZEY/2),
		mSizeX, mSizeLimit);
}
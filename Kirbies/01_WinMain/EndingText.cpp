#include "pch.h"
#include "EndingText.h"
#include "Image.h"

EndingText::EndingText(int indexY)
{
	mIndexY = indexY;
}

void EndingText::Init()
{
	
	mImage = IMAGEMANAGER->FindImage(L"EndingCredit");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mX = WINSIZEX / 2;
	mY = WINSIZEY + mSizeY/2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mSpeed = 5.f;
	mReduseSizeX = 2.8f;
	mReduseSizeY = mReduseSizeX/mSizeX*mSizeY;
}

void EndingText::Release()
{
}

void EndingText::Update()
{
	if (mRect.bottom < 0)
	{
		mIsDestroy = true;
	}
	mY -= mSpeed;
	if (mSpeed > 0)
	{
		mSpeed -= 0.015f;
	}
	mSizeX -= mReduseSizeX;
	mSizeY -= mReduseSizeY;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void EndingText::Render(HDC hdc)
{
	//HPEN newPen = CreatePen(PS_SOLID, 5, RGB(100, 0, 100));
	//HPEN prevPen = (HPEN)SelectObject(hdc, newPen);
	//RenderRect(hdc, mRect);
	//SelectObject(hdc, prevPen);
	//DeleteObject(newPen);
	
	mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, 0, mIndexY, mSizeX, mSizeY);
}

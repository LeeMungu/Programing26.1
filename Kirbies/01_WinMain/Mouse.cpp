#include "pch.h"
#include "Mouse.h"
#include "Image.h"


void Mouse::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Mouns");
	mX = _mousePosition.x;
	mY = _mousePosition.y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Mouse::Release()
{

}

void Mouse::Update()
{
	//이동
	mX = _mousePosition.x;
	mY = _mousePosition.y;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Mouse::Render(HDC hdc)
{
	
	//마우스 랙트 표시 지우지 말것
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 0, 255);
	}
}

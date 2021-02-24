#include "pch.h"
#include "StopperObject.h"


StopperObject::StopperObject(float x, float y,float sizeX,float sizeY)
	
{
	mX = x;
	mY = y;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}
void StopperObject::Init()
{
}

void StopperObject::Release()
{
}

void StopperObject::Update()
{
}

void StopperObject::Render(HDC hdc)
{
	//판정렉트 보여주는것 손대지 말것! control누르면 나옴
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 255, 0);
	}
}

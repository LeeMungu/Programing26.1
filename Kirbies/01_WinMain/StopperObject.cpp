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
	//������Ʈ �����ִ°� �մ��� ����! control������ ����
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 255, 0);
	}
}

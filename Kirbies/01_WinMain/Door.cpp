#include "pch.h"
#include "Door.h"
#include "Camera.h"
#include "Image.h"

Door::Door(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Door::Init()
{
}

void Door::Release()
{
}

void Door::Update()
{
}

void Door::Render(HDC hdc)
{
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 100, 100);
	}

	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top, mFrameX, mFrameY);
}

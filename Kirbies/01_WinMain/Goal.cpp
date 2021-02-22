#include "pch.h"
#include "Goal.h"
#include "Camera.h"
#include "Image.h"
#include "Player.h"
Goal::Goal(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Goal::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Goal");
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Goal::Release()
{

}

void Goal::Update()
{
}

void Goal::Render(HDC hdc)
{
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 100, 100);
	}

	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top, mFrameX, mFrameY);
}

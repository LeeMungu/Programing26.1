#include "pch.h"
#include "Bottom.h"
#include "Image.h"
#include "Camera.h"

Bottom::Bottom(const string& name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
}

void Bottom::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Bottom");
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Bottom::Release()
{
}

void Bottom::Update()
{
}

void Bottom::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->ScaleRender(hdc, mImage, 0, 0, WINSIZEX, WINSIZEY);
}

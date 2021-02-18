#include "pch.h"
#include "BackGround.h"
#include "Image.h"
#include "Camera.h"
BackGround::BackGround(const string& name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
}

void BackGround::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Background");
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void BackGround::Release()
{
}

void BackGround::Update()
{
}

void BackGround::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->ScaleRender(hdc, mImage, 0, 0,WINSIZEX,WINSIZEY);
}

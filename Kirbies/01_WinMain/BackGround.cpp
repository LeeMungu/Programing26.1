#include "pch.h"
#include "BackGround.h"
#include "Image.h"
#include "Camera.h"


BackGround::BackGround(const string& name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
	wstring temp;
	temp.assign(name.begin(), name.end());
	mImage = IMAGEMANAGER->FindImage(temp);
}

BackGround::BackGround(const string& name, float x, float y, wstring key)
	: GameObject(name)
{
	mX = x;
	mY = y;
	mImage = IMAGEMANAGER->FindImage(key);
}

void BackGround::Init()
{
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
	mImage->ScaleRender(hdc, 0, 0,WINSIZEX,WINSIZEY);
}

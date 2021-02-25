#include "pch.h"
#include "BoomRect.h"
#include "Camera.h"

BoomRect::BoomRect(float x, float y)
{
	mX = x;
	mY = y;
	mSizeX = 3;
	mSizeY = 3;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mAngle = PI *(Random::GetInstance()->RandomInt(30, 150))/180;
	mSpeed = (Random::GetInstance()->RandomInt(1, 100)) / 100;
	mGravity = (Random::GetInstance()->RandomInt(20, 100))/20.f;

}

void BoomRect::Init()
{

}

void BoomRect::Update()
{
	mX += cos(mAngle);
	mY -= sin(mAngle);

	mY -= mGravity;
	mGravity -= 0.1f;

	if (mY > WINSIZEY*2)
		mIsDestroy = true;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void BoomRect::Release()
{
}

void BoomRect::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect);
}

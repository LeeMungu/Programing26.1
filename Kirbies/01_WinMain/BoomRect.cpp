#include "pch.h"
#include "BoomRect.h"

BoomRect::BoomRect(float x, float y)
{
	mX = x;
	mY = y;
	mSizeX = 1;
	mSizeY = 1;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mAngle = PI *(Random::GetInstance()->RandomInt(0, 180))/180;
	mSpeed = 0.01f;
	mGravity = 1.f;

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

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void BoomRect::Release()
{
}

void BoomRect::Render(HDC hdc)
{
	RenderRect(hdc, mRect);
}

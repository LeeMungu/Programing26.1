#include "pch.h"
#include "Effect.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Special.h"

Effect::Effect(string name, float x, float y, wstring imagekey)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mImage = IMAGEMANAGER->FindImage(imagekey);
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

}

void Effect::Init()
{
	
}

void Effect::Release()
{
	SafeDelete(mCurrentAnimation);
}

void Effect::Update()
{
	
}

void Effect::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY(),
			mSizeX*1.5f, mSizeY*1.5f);
}

#include "pch.h"
#include "ThrowBtn.h"
#include "Image.h"
#include "Camera.h"
#include "Bottom.h"
ThrowBtn::ThrowBtn(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void ThrowBtn::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"PowerBtn");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mFrameX = 0;
	mIsBtnOn = false;
	mIsBtnTrigger = false;
}

void ThrowBtn::Release()
{
}

void ThrowBtn::Update()
{
	vector<GameObject*> player = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player);

	for (int i = 0; i < player.size(); i++)
	{
		RECT temp;
		RECT playerRect = player[i]->GetRect();
		if (IntersectRect(&temp, &mRect, &playerRect) && mIsBtnTrigger == false)
		{
			mIsBtnOn = true;
			mIsBtnTrigger = true;
			mFrameX++;
		}

	}
}

void ThrowBtn::Render(HDC hdc)
{
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 100, 100);
	}

	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top, mFrameX, 0);
}

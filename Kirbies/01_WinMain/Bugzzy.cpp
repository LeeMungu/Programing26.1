#include "pch.h"
#include "Bugzzy.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"
#include "Player.h"
Bugzzy::Bugzzy(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Bugzzy::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Bugzzy");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mFrameX = 0;

	mAnimation = new Animation();

	mAnimation->InitFrameByStartEnd(0, 0, 10, 0, false);
	mAnimation->SetIsLoop(false);
	mAnimation->SetFrameUpdateTime(0.03f);
	//mAnimation->Play();

	mFireTrigger = false;
}

void Bugzzy::Release()
{
	SafeDelete(mAnimation);
}

void Bugzzy::Update()
{
	vector<GameObject*> player = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player);
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	for (int i = 0; i < player.size(); i++)
	{
		RECT temp;
		RECT playerRect = player[i]->GetRect();

		if (IntersectRect(&temp, &playerRect, &mRect))
		{

			Player* tempPlayer = (Player*)player[i];
			mAnimation->Play();
			tempPlayer->SetPlayerState(PlayerState::ThrowState);
			tempPlayer->SetIsChange(true);
		}

	}
	if (mAnimation->GetNowFrameX() == 10)
	{
		mAnimation->SetCurrentFrameIndex(0);
		mAnimation->Stop();
	}
	mAnimation->Update();
}

void Bugzzy::Render(HDC hdc)
{
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 100, 100);
	}

	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}

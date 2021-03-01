#include "pch.h"
#include "Plate.h"
#include "Image.h"
#include "Camera.h"
#include "Player.h"

Plate::Plate(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Plate::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"plate");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Plate::Release()
{
}

void Plate::Update()
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
			tempPlayer->SetX(tempPlayer->GetX() + 1.5f);
			tempPlayer->SetY(mRect.top-10);
			//tempPlayer->SetGravity(0);
		}
		//else
		//{
		//	Player* tempPlayer = (Player*)player[i];
		//	mTimer += Time::GetInstance()->DeltaTime();
		//}
	}

	//if (mTimer > 10)
	//{
	//	mTimer = 0;
	//	for (int i = 0; i < player.size(); i++)
	//	{
	//		Player* tempPlayer = (Player*)player[i];
	//		//tempPlayer->SetGravity(100);
	//	}
	//}
}

void Plate::Render(HDC hdc)
{

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 100, 100);
	}

	CameraManager::GetInstance()->GetMainCamera()
		->Render(hdc, mImage, mRect.left, mRect.top);
}

void Plate::mapRender(HDC map)
{
	mImage->Render(map, mX, mY);
}

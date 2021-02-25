#include "pch.h"
#include "BoomRectManager.h"
#include "BoomRect.h"

BoomRectManager::BoomRectManager(float x, float y)
{
	mX = x;
	mY = y;	
}

void BoomRectManager::Init()
{
	for (int i = 0; i < 200; ++i)
	{
		int tempX = Random::GetInstance()->RandomInt(mX - 20, mX + 20);
		int tempY = Random::GetInstance()->RandomInt(mY - 20, mY + 20);
		BoomRect* boomRect = new BoomRect(tempX, tempY);
		boomRect->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, boomRect);
	}
}

void BoomRectManager::Updata()
{
}

void BoomRectManager::Release()
{
}

void BoomRectManager::Render(HDC hdc)
{
}

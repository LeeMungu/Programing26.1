#include "pch.h"
#include "BoomRectManager.h"

BoomRectManager::BoomRectManager(float x, float y)
{
	mX = x;
	mY = y;
	for (int i = 0; i < 1000; ++i)
	{

		BoomRect* boomRect = new BoomRect();
	}
}

void BoomRectManager::Init()
{
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

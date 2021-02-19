#include "pch.h"
#include "Weapon.h"
#include "Animation.h"
#include "Player.h"
#include "Scene1.h"



Weapon::Weapon(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;

	mIdleAnimation;
	mRunAnimation;
	mCurrentAnimation;
}



void Weapon::Init()
{
	mRect = RectMake(mPlayer->GetRect().right, mPlayer->GetRect().top, 30, 30);
}

void Weapon::Release()
{
}

void Weapon::Update()
{
}

void Weapon::Render(HDC hdc)
{
}

void Weapon::Attack(float mX, float mY, float sizeX, float sizeY)
{
	mRect = RectMakeCenter(mX, mY, sizeX, sizeY);
}


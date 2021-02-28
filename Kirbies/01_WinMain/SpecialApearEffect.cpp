#include "pch.h"
#include "SpecialApearEffect.h"
#include "Animation.h"
#include "Special.h"
#include "Camera.h"
#include "Image.h"

SpecialApearEffect::SpecialApearEffect(string name, float x, float y, wstring imagekey, float frameX, int frameY)
	:Effect(name, x, y, imagekey)
{
	mCurrentAnimation = new Animation();
	mCurrentAnimation->InitFrameByStartEnd(0, 0, frameX - 1, frameY - 1, false);
	mCurrentAnimation->SetIsLoop(false);
	mCurrentAnimation->SetFrameUpdateTime(0.1f);
	mCurrentAnimation->Play();
}

void SpecialApearEffect::Init()
{
	mCurrentAnimation->SetCallbackFunc([this]()
	{
		Special* special = new Special("Special", mX, mY+100);
		special->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Special, special);

		Camera* prevCamera = (Camera*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Camera, "Camera");
		prevCamera->SetTarget(special);
	});
}

void SpecialApearEffect::Update()
{
	if (mCurrentAnimation->GetIsPlay() == false)
	{
		mIsDestroy = true;
	}
	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}


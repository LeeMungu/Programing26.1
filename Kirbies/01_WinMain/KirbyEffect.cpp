#include "pch.h"
#include "KirbyEffect.h"
#include "Animation.h"
KirbyEffect::KirbyEffect(string name, float x, float y, wstring imagekey, float frameX, int frameY)
		: Effect(name, x, y, imagekey)
{
	mCurrentAnimation = new Animation();
	mCurrentAnimation->InitFrameByStartEnd(0, 0, frameX - 1, frameY - 1, false);
	mCurrentAnimation->SetIsLoop(false);
	mCurrentAnimation->SetFrameUpdateTime(0.1f);
	mCurrentAnimation->Play();
}

void KirbyEffect::Init()
{
}

void KirbyEffect::Update()
{
	if (mCurrentAnimation->GetIsPlay() == false)
	{
		mIsDestroy = true;
	}
	mCurrentAnimation->Update();
}

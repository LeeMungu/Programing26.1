#include "pch.h"
#include "CountNumEffect.h"
#include "Animation.h"
#include "Ui.h"
CountNumEffect::CountNumEffect(string name, float x, float y, wstring imagekey)
	: Effect(name, x, y, imagekey)
{
	mCurrentAnimation = new Animation();
	mCurrentAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mCurrentAnimation->SetIsLoop(false);
	mCurrentAnimation->SetFrameUpdateTime(0.1f);
	mCurrentAnimation->Play();

}

void CountNumEffect::Init()
{
	mCurrentAnimation->SetCallbackFunc([this]()
		{
			mPlayer->SetPlayerState(PlayerState::BoomState);
			
		});
}

void CountNumEffect::Update()
{
	if (mCurrentAnimation->GetIsPlay() == false)
	{
		mIsDestroy = true;
	}
	mCurrentAnimation->Update();
}

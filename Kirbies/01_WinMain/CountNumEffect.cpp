#include "pch.h"
#include "CountNumEffect.h"
#include "Animation.h"
#include "Ui.h"
#include "Camera.h"
CountNumEffect::CountNumEffect(string name, float x, float y, wstring imagekey)
	: Effect(name, x, y, imagekey)
{
	mCurrentAnimation = new Animation();
	mCurrentAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mCurrentAnimation->SetIsLoop(false);
	mCurrentAnimation->SetFrameUpdateTime(0.5f);
	mCurrentAnimation->Play();

}

void CountNumEffect::Init()
{
	
	mCurrentAnimation->SetCallbackFunc([this]()
		{
			mPlayer->SetPlayerState(PlayerState::BoomState);
			mPlayer->SetIsChange(true);
		});
}

void CountNumEffect::Update()
{	
	mX = mPlayer->GetX() - 10;
	mY = mPlayer->GetY() - 60;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	if (mCurrentAnimation->GetIsPlay() == false)
	{
		mIsDestroy = true;
	}
	mCurrentAnimation->Update();
}
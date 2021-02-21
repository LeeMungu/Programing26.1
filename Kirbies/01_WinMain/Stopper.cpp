#include "pch.h"
#include "Stopper.h"

#include "Image.h"
#include "Animation.h"

Stopper::Stopper()
	:mIsPlay(false), mIsLoop(false), mCurrentFrameIndex(0),
	mCurrentFrameTime(0.f), mFrameUpdateTime(0.f), mCallbackFunc(nullptr) {}

void Stopper::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Stopper", Resources(L"stopper.bmp"), 110, 24, 5, 1, true);
	mImage = IMAGEMANAGER->FindImage(L"Stopper");

	mStopperAnimation = new Animation();
	mStopperAnimation->InitFrameByStartEnd(0, 0, 4, 0, true);
	mStopperAnimation->SetIsLoop(true);
	mStopperAnimation->SetFrameUpdateTime(0.2f);
	mStopperAnimation->Play();

	mSpeed

}

void Stopper::Update()
{
}

void Stopper::Play()
{
}

void Stopper::Stop()
{
}

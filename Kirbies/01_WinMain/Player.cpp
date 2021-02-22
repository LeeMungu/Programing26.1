﻿#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "GameObject.h"

#include "State.h"
#include "Boom.h"
#include "Climb.h"
#include "Fall.h"
#include "Run.h"
#include "Stopper.h"
#include "Umbrella.h"
#include "Dig.h"

Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{
	//mImage = IMAGEMANAGER->FindImage(L"Player");
	mIsMotionRL = 0;
	mSizeX = 200;//mImage->GetFrameWidth();
	mSizeY = 200; //mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	//mBoomState = new Boom;
	//mBoomState->SetPlayerPtr(this);
	//mClimbState = new Climb;
	//mClimbState->SetPlayerPtr(this);
	//mStopperState = new Stopper;
	//mStopperState->SetPlayerPtr(this);
	//mUmbrellaState = new Umbrella;
	//mUmbrellaState->SetPlayerPtr(this);
	//mDigState = new Dig;
	//mDigState->SetPlayerPtr(this);
	//mFallState = new Fall;
	//mFallState->SetPlayerPtr(this);
	//mRunState = new Run;
	//mRunState->SetPlayerPtr(this);
	
	mCurrentState = new Fall();
	mCurrentState->SetPlayerPtr(this);
	mCurrentState->Init();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mIsChange = false;
	mIsGoal = false;
	mIsDoor = false;
	mSpeed = 50;
}

void Player::Release()
{
	SafeDelete(mCurrentState);
}

void Player::Update()
{
	if (mIsChange)
	{
		SafeDelete(mCurrentState);
		switch (mPlayerState)
		{
		case PlayerState::BoomState:
			mCurrentState = new Boom;
			break;
		case PlayerState::ClimbState:
			mCurrentState = new Climb;
			break;
		case PlayerState::DigState:
			mCurrentState = new Dig;
			break;
		case PlayerState::FallState:
			mCurrentState = new Fall;
			break;
		case PlayerState::RunState:
			mCurrentState = new Run;
			break;
		case PlayerState::StopperState:
			mCurrentState = new Stopper;
			break;
		case PlayerState::UmbrellaState:
			mCurrentState = new Umbrella;
			break;
		}
		mCurrentState->SetPlayerPtr(this);
		mIsChange = false;
		mCurrentState->Init();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	//for (int y = this->GetY() ; y < this->GetY()+this->GetSizeY()+15; y++)
	//{
	//	Bottom* tempB = (Bottom*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Bottom, "Bottom");
	//	COLORREF pixelColor = GetPixel(tempB->GetImage()->GetHDC(), this->GetX(), y);
	//	if (pixelColor != RGB(255, 0, 255))
	//	{
	//		this->SetY(y-this->GetSizeY());
	//	}
	//}

		for (float y = mY; y < mY + mSizeY / 2 + 25 ; y++)
		{
			Bottom* tempB = (Bottom*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Bottom, "Bottom");
			COLORREF pixelColor = GetPixel(tempB->GetImage()->GetHDC(), mX, y);
			if (pixelColor != RGB(255, 0, 255) && mPlayerState != PlayerState::RunState && mPlayerState == PlayerState::FallState)
			{
				mY = y - mSizeY / 2;
				mIsChange = true;
				mPlayerState = PlayerState::RunState;
				break;
			}
			else if (pixelColor == RGB(255, 0, 255) && mPlayerState != PlayerState::FallState)
			{
				mIsChange = true;
				mPlayerState = PlayerState::FallState;
			}
		}

	//if (mPlayerState == PlayerState::RunState)
	//{
	//	for (int y = mY; y < mY + mSizeY; y++)
	//	{
	//		Bottom* tempB = (Bottom*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Bottom, "Bottom");
	//		COLORREF pixelColor = GetPixel(tempB->GetImage()->GetHDC(), mX, y);
	//		if (pixelColor != RGB(255, 0, 255))
	//		{
	//			mIsChange = true;
	//			mPlayerState = PlayerState::FallState;
	//		}
	//	}
	//}


	mCurrentState->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Render(HDC hdc)
{
	//플레이어 판정렉트 보여주는것 손대지 말것! control누르면 나옴
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 255, 0, 0);
	}

	mCurrentState->Render(hdc);
}

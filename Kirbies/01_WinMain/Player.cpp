#include "pch.h"
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
#include "TrapDie.h"

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
	mPlayerState = PlayerState::FallState;
	
	mGravity = 100.f;
	mIsChange = false;
	mIsGoal = false;
	mIsDoor = false;
	mSpeed = 50;

	mIsCrash = false;
	mIsClimb = false;
	mIsBoom = false;
	mIsStopper = false;
	mIsFallDead = false;
	mIsDig = false;
	mIsTrap = false;
}

void Player::Release()
{
	SafeDelete(mCurrentState);
}

void Player::Update()
{
	if (mIsChange)
	{
		if (mPlayerState == PlayerState::BoomState)
		{
			mIsBoom = false;
			SafeDelete(mCurrentState);
			mCurrentState = new Boom;
			mCurrentState->SetPlayerPtr(this);
			mIsChange = false;
			mCurrentState->Init();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		else if (mPlayerState == PlayerState::ClimbState)
		{
			mIsCrash = false;
			SafeDelete(mCurrentState);
			mCurrentState = new Climb;
			mCurrentState->SetPlayerPtr(this);
			mIsChange = false;
			mCurrentState->Init();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		else if (mPlayerState == PlayerState::DigState)
		{
			SafeDelete(mCurrentState);
			mCurrentState = new Dig;
			mCurrentState->SetPlayerPtr(this);
			mIsChange = false;
			mCurrentState->Init();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

		}
		else if (mPlayerState == PlayerState::FallState)
		{
			SafeDelete(mCurrentState);
			mCurrentState = new Fall;
			mCurrentState->SetPlayerPtr(this);
			mIsChange = false;
			mCurrentState->Init();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		else if (mPlayerState == PlayerState::RunState)
		{
			SafeDelete(mCurrentState);
			mCurrentState = new Run;
			mCurrentState->SetPlayerPtr(this);
			mIsChange = false;
			mCurrentState->Init();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		else if (mPlayerState == PlayerState::StopperState)
		{
			SafeDelete(mCurrentState);
			mCurrentState = new Stopper;
			mCurrentState->SetPlayerPtr(this);
			mIsChange = false;
			mCurrentState->Init();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		else if (mPlayerState == PlayerState::UmbrellaState)
		{
			SafeDelete(mCurrentState);
			mCurrentState = new Umbrella;
			mCurrentState->SetPlayerPtr(this);
			mIsChange = false;
			mCurrentState->Init();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		else if (mPlayerState == PlayerState::TrapDieState)
		{
			SafeDelete(mCurrentState);
			mCurrentState = new TrapDie;
			mCurrentState->SetPlayerPtr(this);
			mIsChange = false;
			mCurrentState->Init();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
	}

	Bottom* tempB = (Bottom*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Bottom, "Bottom");
	
	//떨어졌을때 바닥보정
	if (mPlayerState == PlayerState::FallState)
	{
		for (float y = mY; y < mY + mSizeY / 2 + 25; y++)
		{
			COLORREF pixelColor = GetPixel(tempB->GetImage()->GetHDC(), mX, y);
			if (pixelColor != RGB(255, 0, 255))
			{
				mY = y - mSizeY / 2;
				//낙사 높이
				if (mY - ((Fall*)mCurrentState)->GetStartY() > WINSIZEY / 3)
				{
					mIsFallDead = true;
					mY += 15; // 바닥과 캐릭터
				}
				else
				{
					mIsChange = true;
					mPlayerState = PlayerState::RunState;
				}
				break;
			}
		}
	}
	if (mPlayerState == PlayerState::UmbrellaState)
	{
		for (float y = mY; y < mY + mSizeY / 2 + 25; y++)
		{
			COLORREF pixelColor = GetPixel(tempB->GetImage()->GetHDC(), mX, y);
			if (pixelColor != RGB(255, 0, 255))
			{
				mY = y - mSizeY / 2;

				mIsChange = true;
				mPlayerState = PlayerState::RunState;
				break;
			}
		}
	}
	//if (mPlayerState == PlayerState::ClimbState)
	//{
	//	for (float y = mY; y < mY + mSizeY / 2 + 25; y++)
	//	{
	//		COLORREF pixelColor = GetPixel(tempB->GetImage()->GetHDC(), mX, y);
	//		if (pixelColor != RGB(255, 0, 255))
	//		{
	//			mY = y - mSizeY / 2;
	//			SafeDelete(mCurrentState);
	//			mCurrentState = new Run;
	//			mCurrentState->SetPlayerPtr(this);
	//			mIsChange = false;
	//			mCurrentState->Init();
	//			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	//			break;
	//		}
	//	}
	//}

	//런 바닥보정
	if (mPlayerState == PlayerState::RunState)
	{
		bool isGround = false;
		for (float y = mY; y < mY + mSizeY / 2 + 50; y++)
		{

			COLORREF pixelColor = GetPixel(tempB->GetImage()->GetHDC(), mX, y);
			if (pixelColor != RGB(255, 0, 255))
			{
				isGround = true;
				mY = y - mSizeY / 2;
				break;
			}
		}		
		if (isGround == false)
		{
			mPlayerState = PlayerState::FallState;
			mIsChange = true;
		}


		//좌우-벽 충돌
		if (mIsMotionRL == 0)
		{
			COLORREF pixelColor = GetPixel(tempB->GetImage()->GetHDC(), mRect.right, mY);
			if (pixelColor != RGB(255, 0, 255))
			{
				if (mIsClimb == false)
				{
					mIsCrash = true;
					mIsMotionRL = 1;
				}
				else if (mIsClimb == true)
				{
					mPlayerState = PlayerState::ClimbState;
					mIsChange = true;
				}
			}
		}
		else if (mIsMotionRL == 1)
		{
			COLORREF pixelColor = GetPixel(tempB->GetImage()->GetHDC(), mRect.left, mY);
			if (pixelColor != RGB(255, 0, 255))
			{
				if (mIsClimb == false)
				{
					mIsCrash = true;
					mIsMotionRL = 0;
				}
				else if (mIsClimb == true)
				{
					mPlayerState = PlayerState::ClimbState;
					mIsChange = true;
				}
			}
		}	

		//스토퍼 전환
		if (mIsStopper == true)
		{
			mIsChange = true;
			mPlayerState = PlayerState::StopperState;
		}

		//스토퍼커비와 충돌한 런커비
		RECT Temp;
		vector<GameObject*> stopperObjectList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::StopperObject);
		for (int i = 0; i < stopperObjectList.size(); ++i)
		{
			RECT mStopKirby = stopperObjectList[i]->GetRect();
			if (IntersectRect(&Temp, &mRect, &mStopKirby))
			{
				if (mIsMotionRL == 0)
				{
					mIsMotionRL = 1;
					mX = mStopKirby.left - mSizeX / 2;
				}
				else if (mIsMotionRL == 1)
				{
					mIsMotionRL = 0;
					mX = mStopKirby.right + mSizeX / 2;
				}
			}
		}
	}

	//땅팠을때 보정
	if (mPlayerState == PlayerState::DigState)
	{
		Dig* tempDig = (Dig*)mCurrentState;
		if (tempDig->GetDigCheck() == true)
		{
			float y = mRect.bottom + mSizeY / 2;
			COLORREF pixelColor = GetPixel(tempB->GetImage()->GetHDC(), mX, y);
			if (pixelColor == RGB(255, 0, 255))
			{
				mIsDig = false;
				mIsChange = true;
				mPlayerState = PlayerState::FallState;
			}
		}
	}
	if (mPlayerState == PlayerState::ClimbState)
	{

	}

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
	wstring str;
	if (mPlayerState == PlayerState::BoomState)
	{
		str = L"Boom";
	}
	else if (mPlayerState == PlayerState::ClimbState)
	{
		str = L"climb";
	}
	else if(mPlayerState == PlayerState::DigState)
	{
		str = L"dig";
	}
	else if (mPlayerState == PlayerState::FallState)
	{
		str = L"fall";
	}
	else if (mPlayerState == PlayerState::RunState)
	{
		str = L"run";
	}
	else if (mPlayerState == PlayerState::StopperState)
	{
		str = L"stop";
	}
	else if (mPlayerState == PlayerState::UmbrellaState)
	{
		str = L"umb";
	}
	else if (mPlayerState == PlayerState::TrapDieState)
	{
		str = L"die";
	}
	POINT playerPoint = CameraManager::GetInstance()->GetMainCamera()->GetPoint(mX,mY);
	TextOut(hdc, playerPoint.x, playerPoint.y-mSizeY, str.c_str(), str.length());

	mCurrentState->Render(hdc);
}

void Player::mapRender(HDC map)
{
	if(mCurrentState!=NULL)
	mCurrentState->mapRender(map);
}

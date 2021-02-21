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

Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Player");
	mIsMotionRL = 0;
	mBoomState = new Boom;
	mClimbState = new Climb;
	mStopperState = new Stopper;
	mUmbrellaState = new Umbrella;
	mDigState = new Dig;
	mFallState = new Fall;
	mRunState = new Run;
	
	mCurrentState = mFallState;
	//mCurrentState->
}

void Player::Release()
{

}

void Player::Update()
{
	//mState->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Render(HDC hdc)
{
	//플레이어 판정렉트 보여주는것 손대지 말것! control누르면 나옴
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 255, 0, 0);
	}


}

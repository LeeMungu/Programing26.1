#include "pch.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Weapon.h"
#include "Enemy.h"
#include "GameObject.h"

Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Player", Resources(L"kirbyFinal4.bmp"), 1520, 318, 14, 4,true);
	mImage = IMAGEMANAGER->FindImage(L"Player");


	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 1, 0,false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(0.3f);
	mIdleAnimation->Play();

	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 1, 1, 1, false);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.3f);
	mLeftIdleAnimation->Play();

	mRunAnimation = new Animation();
	mRunAnimation->InitFrameByStartEnd(2, 0, 11, 0, false);
	mRunAnimation->SetIsLoop(true);
	mRunAnimation->SetFrameUpdateTime(0.05f);

	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(2, 1, 11, 1, true);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.05f);

	mAttackAnimation = new Animation();
	mAttackAnimation->InitFrameByStartEnd(0, 2, 13, 2, false);
	mAttackAnimation->SetIsLoop(true);
	mAttackAnimation->SetFrameUpdateTime(0.05f);

	mLeftAttackAnimation = new Animation();
	mLeftAttackAnimation->InitFrameByStartEnd(0, 3, 13, 3, true);
	mLeftAttackAnimation->SetIsLoop(true);
	mLeftAttackAnimation->SetFrameUpdateTime(0.05f);

	mCurrentAnimation = mIdleAnimation;
	mSizeX = mImage->GetFrameWidth()/2;
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);


	mState = CharactorState::RightIdle;

	mHpPoint = 100;
	mSpeed = 10.f;

	mEnemyList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemey);
	mIsStop = false;
}

void Player::Release()
{
	SafeDelete(mIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mAttackAnimation);
	SafeDelete(mLeftAttackAnimation);
	SafeDelete(mRunAnimation);
	SafeDelete(mLeftRunAnimation);
	SafeDelete(mCurrentAnimation);
}

void Player::Update()
{
	if (!mIsStop)
	{
		if (!(mState == CharactorState::LeftAttack || mState == CharactorState::RightAttack))
		{
			// 플레이어 우측이동
			if (mState != CharactorState::RightRun)
			{
				if (Input::GetInstance()->GetKeyDown('D'))
				{
					mState = CharactorState::RightRun;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRunAnimation;
					mCurrentAnimation->Play();
				}
			}
			if (Input::GetInstance()->GetKey('D'))
			{
				if (mState == CharactorState::RightRun)
				{
					mX += 3;
					mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
				}
			}
			if (Input::GetInstance()->GetKeyUp('D'))
			{
				mState = CharactorState::RightIdle;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mIdleAnimation;
				mCurrentAnimation->Play();
			}
			//플레이어 좌측이동
			if (mState != CharactorState::LeftRun)
			{
				if (Input::GetInstance()->GetKeyDown('A'))
				{
					mState = CharactorState::LeftRun;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftRunAnimation;
					mCurrentAnimation->Play();
				}
			}
			if (Input::GetInstance()->GetKey('A'))
			{
				if (mState == CharactorState::LeftRun)
				{
					mX -= 3;
					mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
				}
			}
			if (Input::GetInstance()->GetKeyUp('A'))
			{
				mState = CharactorState::LeftIdle;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftIdleAnimation;
				mCurrentAnimation->Play();
			}
		}
	}
		//플레이어 공격
		if (mState != CharactorState::RightAttack)
		{
			if (Input::GetInstance()->GetKeyDown('E'))
			{
				mState = CharactorState::RightAttack;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mAttackAnimation;
				mCurrentAnimation->Play();
			}
		}
		if (mState == CharactorState::RightAttack &&
			mCurrentAnimation->GetNowFrameX() > 12)
		{
			mState = CharactorState::RightIdle;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mIdleAnimation;
			mCurrentAnimation->Play();
		}

		if (mState != CharactorState::LeftAttack)
		{
			if (Input::GetInstance()->GetKeyDown('Q'))
			{
				mState = CharactorState::LeftAttack;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftAttackAnimation;
				mCurrentAnimation->Play();
			}
		}
		if (mState == CharactorState::LeftAttack &&
			mCurrentAnimation->GetNowFrameX() < 1)
		{
			mState = CharactorState::LeftIdle;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftIdleAnimation;
			mCurrentAnimation->Play();
		}


	if (mState == CharactorState::RightAttack)
	{
		if (mCurrentAnimation->GetNowFrameX() == 3)
		{
			if (mWeapon != nullptr)
			{
				mWeapon->SetIsDestroy(true);
			}
			mWeapon = new Weapon("w", mX, mY);
			mWeapon->SetPlayerPtr(this);
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Weapon, mWeapon);
			mWeapon->Attack(this->GetRect().right, this->GetY(), 50, this->GetSizeY());
		}
		if (mCurrentAnimation->GetNowFrameX() == 10)
		{
			mWeapon->SetIsDestroy(true);
		}
	}
	if (mState == CharactorState::LeftAttack)
	{
		if (mCurrentAnimation->GetNowFrameX() == 10)
		{
			if (mWeapon != nullptr)
			{
				mWeapon->SetIsDestroy(true);

			}
			mWeapon = new Weapon("w", mX, mY);
			mWeapon->SetPlayerPtr(this);
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Weapon, mWeapon);
			mWeapon->Attack(this->GetRect().left, this->GetY(), 50, this->GetSizeY());
		}
		if (mCurrentAnimation->GetNowFrameX() == 3)
		{
			mWeapon->SetIsDestroy(true);
		}
	}


	if (mWeapon != nullptr)
	{
		for (int i = 0; i < mEnemyList.size(); ++i)
		{
			RECT temp;
			RECT enemyRC = mEnemyList[i]->GetRect();
			RECT weaponRC = mWeapon->GetRect();
			if (IntersectRect(&temp, &enemyRC, &weaponRC))
			{
				mEnemyList[i]->SetIsDestroy(true);
			}
		}
	}

	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mX-mImage->GetFrameWidth()/2, mRect.top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());
	if (mWeapon != nullptr)
	{
		//CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mWeapon->GetRect());
	}


	//mImage->FrameRender(hdc,mRect.left,mRect.top, mCurrentAnimation->GetNowFrameX(),
	//	mCurrentAnimation->GetNowFrameY());
}

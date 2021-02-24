#include "pch.h"
#include "Climb.h"
#include "Player.h"
#include "Animation.h"
#include "Bottom.h"
#include "Image.h"
#include "Camera.h"
void Climb::Init() {
	
	mImage = IMAGEMANAGER->FindImage(L"Run");

	mAnimation = new Animation();
	//��ó������ run ���� ?
	if (mPlayer->GetIntMotionRL() == 0) { //������
		mAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.3f);
	}
	else { //����
		mAnimation->InitFrameByStartEnd(0, 1, 7, 1, false);
		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.3f);
	}

	mBottom = (Bottom*)ObjectManager::GetInstance()->FindObject("Bottom");

	mX = mPlayer->GetX();
	mY = mPlayer->GetY();

	mIsWallCheck = true;
	mIsWalkCheck = true;


	mPlayer->SetSizeX(mImage->GetFrameWidth());
	mPlayer->SetSizeY(mImage->GetFrameHeight());

	mClimbCount = 1;
	mState = State::Climb;
}

void Climb::Update()
{
	mX = mPlayer->GetX();
	mY = mPlayer->GetY();

	//��Ż ��
	if (mState == State::Climb)
	{
		if (mPlayer->GetIntMotionRL() == 0) //������
		{
			COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
				mPlayer->GetRect().right, mPlayer->GetRect().bottom);

			if (pixelColor != RGB(255, 0, 255))
			{
				mPlayer->SetY(mPlayer->GetY() - mPlayer->GetSpeed() * Time::GetInstance()->DeltaTime());
				ClimbAnim();
			}
			//COLORREF pixelColor1 = GetPixel(mBottom->GetImage()->GetHDC(),
			//	mPlayer->GetRect().right, mPlayer->GetRect().bottom);
			//if (pixelColor1 != RGB(255, 0, 255))
			//{
			//	mPlayer->SetX(mPlayer->GetX() + mPlayer->GetSpeed() * Time::GetInstance()->DeltaTime());
			//	ClimbAnim();
			//}
		}
		else if (mPlayer->GetIntMotionRL() == 1)//����
		{
			COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
				mPlayer->GetRect().left, mPlayer->GetRect().bottom);
			if (pixelColor != RGB(255, 0, 255))
			{
				mPlayer->SetY(mPlayer->GetY() - mPlayer->GetSpeed()* Time::GetInstance()->DeltaTime());
				ClimbAnim();
			}
			//COLORREF pixelColor1 = GetPixel(mBottom->GetImage()->GetHDC(),
			//	mPlayer->GetRect().left, mPlayer->GetY());
			//if (pixelColor1 != RGB(255, 0, 255))
			//{
			//	mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSpeed() * Time::GetInstance()->DeltaTime());
			//	ClimbAnim();
			//}
		}
	}

	//��Ÿ���� ���� �߰�
	if (mIsWallCheck == false && mState == State::Climb)//��Ÿ�� ���̴�
	{
		if (mPlayer->GetIntMotionRL() == 0) //������
		{
			COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
				mPlayer->GetRect().right, mPlayer->GetRect().bottom);
			if (pixelColor == RGB(255, 0, 255))
			{
				mPlayer->SetX(mPlayer->GetX()+mPlayer->GetSizeX());
				WalkAnim();
				mState = State::Run;
			}
		}
		else if (mPlayer->GetIntMotionRL() == 1)//����
		{
			COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
				mPlayer->GetRect().left, mPlayer->GetRect().bottom);
			if (pixelColor == RGB(255, 0, 255))
			{
				mPlayer->SetX(mPlayer->GetX() - mPlayer->GetSizeX());
				WalkAnim();
				mState = State::Run;
			}
		}
	}

	//��Ÿ���� õ�忡 �ε���
	if (mIsWallCheck == false && mState == State::Climb)//��Ÿ�� ���̴�
	{
		COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
			mPlayer->GetX(), mPlayer->GetRect().top);
		if (pixelColor != RGB(255, 0, 255))
		{
			mPlayer->SetPlayerState(PlayerState::FallState);
			mPlayer->SetIsChange(true);
			mPlayer->SetIsClimb(false);
		}
	}

	//���� �߰��ؼ� �ȴ� ���̴�
	if (mState == State::Run)
	{
		if (mPlayer->GetIntMotionRL() == 0) //������
		{
			COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
				mX, mPlayer->GetRect().bottom);
			if (pixelColor != RGB(255, 0, 255))
			{
				mPlayer->SetPlayerState(PlayerState::RunState);
				mPlayer->SetIsChange(true);
			}
			else
			{
				mPlayer->SetPlayerState(PlayerState::FallState);
				mPlayer->SetIsChange(true);
			}
		}
		else if (mPlayer->GetIntMotionRL() == 1)//����
		{
			COLORREF pixelColor = GetPixel(mBottom->GetImage()->GetHDC(),
				mX, mPlayer->GetRect().bottom);
			if (pixelColor != RGB(255, 0, 255))
			{
				mPlayer->SetPlayerState(PlayerState::RunState);
				mPlayer->SetIsChange(true);
			}
			else
			{
				mPlayer->SetPlayerState(PlayerState::FallState);
				mPlayer->SetIsChange(true);
			}
		}
		//�̰� ���ϸ� �ѹ��������� �ٽ� �������� ��� ��Ÿ�� ��ȹ�ǵ� ����
		mPlayer->SetIsClimb(false);
	}

	mAnimation->Update();
}

void Climb::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mPlayer->GetX() - mImage->GetFrameWidth() / 2, mPlayer->GetRect().top,
			mAnimation->GetNowFrameX(),
			mAnimation->GetNowFrameY());

}

void Climb::mapRender(HDC map)
{
	mImage->FrameRender(map, mX, mY, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY());
}

void Climb::ClimbAnim()
{
	if (mIsWallCheck)
	{
		mAnimation->Stop();
		mImage = IMAGEMANAGER->FindImage(L"Climb");
		if (mPlayer->GetIntMotionRL() == 0)
		{
			mAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
		}
		else
		{
			mAnimation->InitFrameByStartEnd(0, 1, 7, 1, false);
		}

		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.1f);
		mAnimation->Play();
		mIsWallCheck = false;
	}
	mIsWalkCheck = true;
}

void Climb::WalkAnim()
{
	if (mIsWalkCheck)
	{
		mAnimation->Stop();
		mImage = IMAGEMANAGER->FindImage(L"Run");
		if (mPlayer->GetIntMotionRL() == 0)
		{
			mAnimation->InitFrameByStartEnd(0, 0, 9, 0, false);
		}
		else
		{
			mAnimation->InitFrameByStartEnd(0, 1, 9, 1, false);
		}
		mAnimation->SetIsLoop(true);
		mAnimation->SetFrameUpdateTime(0.3f);
		mAnimation->Play();
		mIsWalkCheck = false;
	}

	mIsWallCheck = true;
}

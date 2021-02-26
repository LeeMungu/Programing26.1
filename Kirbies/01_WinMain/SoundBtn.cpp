#include "pch.h"
#include "SoundBtn.h"
#include "Image.h"
#include "ConfigUi.h"
SoundBtn::SoundBtn(SoundbtnState state, float x, float y)
{
	mSoundbtnState = state;
	mImage = IMAGEMANAGER->FindImage(L"PlusMinus");
	mX = x;
	mY = y;
	mIndexX = 0;
	mIndexY = 0;
	if (mSoundbtnState == SoundbtnState::BgmPlus)
	{
		mIndexY = 0;
	}
	else if (mSoundbtnState == SoundbtnState::BgmMinus)
	{
		mIndexY = 2;
	}
	else if (mSoundbtnState == SoundbtnState::EffPlus)
	{
		mIndexY = 1;
	}
	else if (mSoundbtnState == SoundbtnState::EffMinus)
	{
		mIndexY = 3;
	}
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mScaleX = 17;
	mScaleY = 17;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void SoundBtn::Init()
{

}


void SoundBtn::Release()
{
}

void SoundBtn::Update()
{
	if (PtInRect(&mRect, _mousePosition) && Input::GetInstance()->GetKey(VK_LBUTTON))
	{
		if (mSoundbtnState == SoundbtnState::BgmPlus)
		{
			mScaleX = 15;
			mRect = RectMakeCenter(mX + 1, mY, mSizeX, mSizeY);
		}
		else if (mSoundbtnState == SoundbtnState::BgmMinus)
		{
			mScaleX = 15;
			mRect = RectMakeCenter(mX + 1, mY, mSizeX, mSizeY);
		}
		else if (mSoundbtnState == SoundbtnState::EffPlus)
		{
			mScaleX = 15;
			mRect = RectMakeCenter(mX + 1, mY, mSizeX, mSizeY);
		}
		else if (mSoundbtnState == SoundbtnState::EffMinus)
		{
			mScaleX = 15;
			mRect = RectMakeCenter(mX + 1, mY, mSizeX, mSizeY);
		}
	}
	if (PtInRect(&mRect, _mousePosition) && Input::GetInstance()->GetKeyUp(VK_LBUTTON))
	{
		mScaleX = 17;
		mRect = RectMakeCenter(mX , mY, mSizeX, mSizeY);
		if (mSoundbtnState == SoundbtnState::BgmPlus)
		{
			ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");
			temp->SoundIndexX(L"Bgm");
			if (temp->GetSoundBarScale() < 100)
			{
				temp->SetSoundBarScale(10.f);
			}
			
			SoundPlayer::GetInstance()->SetBgmVolum(0.1);
		}
		else if (mSoundbtnState == SoundbtnState::BgmMinus)
		{
			ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");
			temp->SoundIndexX(L"Bgm");
			if (temp->GetSoundBarScale() > 0)
			{
				temp->SetSoundBarScale(-10.f);
			}
			
			SoundPlayer::GetInstance()->SetBgmVolum(-0.1);
		}
		else if (mSoundbtnState == SoundbtnState::EffPlus)
		{
			ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");
			temp->SoundIndexX(L"EffSound");
			if (temp->GetEffSoundBarScale() < 100)
			{
				temp->SetEffSoundBarScale(10.f);
			}
			
			SoundPlayer::GetInstance()->SetEffectVolum(0.1);
		}
		else if (mSoundbtnState == SoundbtnState::EffMinus)
		{
			ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");
			temp->SoundIndexX(L"EffSound");
			if (temp->GetEffSoundBarScale() > 0)
			{
				temp->SetEffSoundBarScale(-10.f);
			}
			
			SoundPlayer::GetInstance()->SetEffectVolum(-0.1);
		}
	}
}



void SoundBtn::Render(HDC hdc)
{
	mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY, mScaleX, mScaleY);
}

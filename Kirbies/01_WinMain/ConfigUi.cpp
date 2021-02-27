#include "pch.h"
#include "ConfigUi.h"
#include "Image.h"
#include "ButtonUi.h"
#include "SoundBtn.h"
#include "Animation.h"
#include "DataUI.h"

ConfigUi::ConfigUi(const string& name)
	: Ui(name)
{
	mImage = IMAGEMANAGER->FindImage(L"Menu");
	mMenuImage = IMAGEMANAGER->FindImage(L"MenuBtn");
	mSubImage = IMAGEMANAGER->FindImage(L"SubMenu");
	mSoundImage = IMAGEMANAGER->FindImage(L"BgmImage");
	mEffImage = IMAGEMANAGER->FindImage(L"EffsoundImage");
	mBgmBar = IMAGEMANAGER->FindImage(L"SoundBar");
	mEffSoundBar = IMAGEMANAGER->FindImage(L"SoundBar");
	mIndexX = 0;
	msubsizeX = 0;

	mBgmScaleX = SoundPlayer::GetInstance()->GetBgmvolum() * 100;
	mEffScaleX = SoundPlayer::GetInstance()->GetEffectVolum() * 100;
	
}

void ConfigUi::Init()
{
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mMenuEnd = new ButtonUi(BtnState::End, WINSIZEX / 2, WINSIZEY / 2 - 100 + 180);
	mMenuEnd->Init();

	mMenuRecord = new ButtonUi(BtnState::Record, WINSIZEX / 2, WINSIZEY / 2 - 150 + 180);
	mMenuRecord->Init();


	mMenuRestart = new ButtonUi(BtnState::ReStart, WINSIZEX / 2, WINSIZEY / 2 - 200 + 180);
	mMenuRestart->Init();


	mMenuSound = new ButtonUi(BtnState::Sound, WINSIZEX / 2, WINSIZEY / 2 - 250 + 180);
	mMenuSound->Init();

	mBgmPlus = new SoundBtn(SoundbtnState::BgmPlus, WINSIZEX / 2+100+100, WINSIZEY / 2 -50);
	mBgmPlus->Init();
	
	mBgmMinus = new SoundBtn(SoundbtnState::BgmMinus, WINSIZEX / 2+100+50, WINSIZEY / 2-50);
	mBgmMinus->Init();
	
	mEffPlus = new SoundBtn(SoundbtnState::EffPlus, WINSIZEX / 2+200, WINSIZEY / 2+50);
	mEffPlus->Init();
	
	mEffMinus = new SoundBtn(SoundbtnState::EffMinus, WINSIZEX / 2+150, WINSIZEY / 2+50);
	mEffMinus->Init();

	mBgmAnimation = new Animation;
	mBgmAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mBgmAnimation->SetIsLoop(false);
	mBgmAnimation->SetFrameUpdateTime(0.1f);

	mEffAnimaion = new Animation;
	mEffAnimaion->InitFrameByStartEnd(0, 0, 5, 0, false);
	mEffAnimaion->SetIsLoop(false);
	mEffAnimaion->SetFrameUpdateTime(0.1f);
	
}

void ConfigUi::Release()
{
	SafeDelete(mMenuEnd);
	SafeDelete(mMenuRecord);
	SafeDelete(mMenuRestart);
	SafeDelete(mMenuSound);

	SafeDelete(mBgmPlus);
	SafeDelete(mBgmMinus);
	SafeDelete(mEffPlus);
	SafeDelete(mEffMinus);
}

void ConfigUi::Update()
{
	

	if (mBgmScaleX >= 100)
	{
		mBgmScaleX = 100;
	}
	else if (mBgmScaleX <= 0)
	{
		mBgmScaleX = 0;
	}

	if (mEffScaleX >= 100)
	{
		mEffScaleX = 100;
	}
	else if (mEffScaleX <= 0)
	{
		mEffScaleX = 0;
	}


	mMenuEnd->Update();
	mMenuRecord->Update();
	mMenuRestart->Update();
	mMenuSound->Update();

	if (mIsSoundMenuOpen)
	{
		mBgmPlus->Update();
		mBgmMinus->Update();
		mEffPlus->Update();
		mEffMinus->Update();
	}
	//if (mIsRecordMenuOpen)
	//{
	//	DataUI* dataUI = new DataUI("dataUI");
	//	dataUI->Init();
	//	UiManager::GetInstance()->AddUi(UiLayer::DataUI, dataUI);
	//}

	mBgmAnimation->Update();
	mEffAnimaion->Update();
}

void ConfigUi::Render(HDC hdc)
{
	mImage->Render(hdc, mRect.left, mRect.top);
	mMenuEnd->Render(hdc);
	mMenuRecord->Render(hdc);
	mMenuRestart->Render(hdc);
	mMenuSound->Render(hdc);
	mSubImage->ScaleRender(hdc, mRect.right, mRect.top, msubsizeX, 240);

	if (mIsSoundMenuOpen)
	{
		mBgmPlus->Render(hdc);
		mBgmMinus->Render(hdc);
		mEffPlus->Render(hdc);
		mEffMinus->Render(hdc);

		mSoundImage->FrameRender(hdc, mRect.right+40, mRect.top+40, mBgmAnimation->GetNowFrameX(),0);
		mEffImage->FrameRender(hdc, mRect.right+40, mRect.top+135, mEffAnimaion->GetNowFrameX(), 0);
		mBgmBar->ScaleRender(hdc, mRect.right + 100, mRect.top+50, mBgmScaleX, 10);
		mEffSoundBar->ScaleRender(hdc, mRect.right + 100, mRect.top + 150, mEffScaleX, 10);
	}


	



}

void ConfigUi::SoundIndexX(wstring aniName)
{
	wstring str = aniName;
	if (str == L"Bgm")
	{
		mBgmAnimation = new Animation;
		mBgmAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
		mBgmAnimation->SetIsLoop(false);
		mBgmAnimation->SetFrameUpdateTime(0.05f);
		mBgmAnimation->Play();
	}
	else if (str == L"EffSound")
	{
		mEffAnimaion = new Animation;
		mEffAnimaion->InitFrameByStartEnd(0, 0, 5, 0, false);
		mEffAnimaion->SetIsLoop(false);
		mEffAnimaion->SetFrameUpdateTime(0.05f);
		mEffAnimaion->Play();
	}
	
}

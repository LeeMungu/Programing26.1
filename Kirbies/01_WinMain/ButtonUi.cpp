#include "pch.h"
#include "ButtonUi.h"
#include "Image.h"
#include "ConfigUi.h"


ButtonUi::ButtonUi(BtnState state, float x, float y)
{
	mbtnState = state;
	mImage = IMAGEMANAGER->FindImage(L"MenuBtn");
	mX = x;
	mY = y;
	mIndexX = 0;
	mIndexY = 0;
	if (mbtnState == BtnState::End)
	{
		mIndexY = 3;
	}
	else if (mbtnState == BtnState::Record)
	{
		mIndexY = 0;
	}
	else if (mbtnState == BtnState::ReStart)
	{
		mIndexY = 1;
	}
	else if (mbtnState == BtnState::Sound)
	{
		mIndexY = 2;
	}
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mScaleX = 128;
	mScaleY = 32;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}
void ButtonUi::Init()
{

}



void ButtonUi::Update()
{

	if (PtInRect(&mRect, _mousePosition) && Input::GetInstance()->GetKey(VK_LBUTTON))
	{
		if (mbtnState == BtnState::End)
		{
			mScaleX = 120;
			mRect = RectMakeCenter(mX+3, mY, mSizeX, mSizeY);
		}
		else if (mbtnState == BtnState::Record)
		{
			mScaleX = 120;
			mRect = RectMakeCenter(mX + 3, mY, mSizeX, mSizeY);
		}
		else if (mbtnState == BtnState::ReStart)
		{
			mScaleX = 120;
			mRect = RectMakeCenter(mX + 3, mY, mSizeX, mSizeY);
		}
		else if (mbtnState == BtnState::Sound)
		{
			mScaleX = 120;
			mRect = RectMakeCenter(mX + 3, mY, mSizeX, mSizeY);
		}
	}

	if (PtInRect(&mRect, _mousePosition) && Input::GetInstance()->GetKeyUp(VK_LBUTTON))
	{
		mScaleX = 128;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		if (mbtnState == BtnState::End)
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
			SceneManager::GetInstance()->SetIsconfig(false);
			ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");
			temp->SetIsDestroy(true);
		}

		else if (mbtnState == BtnState::Record)
		{
			ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");

			if (temp->GetSubMenu() != 200)
			{
				temp->SetSubMenuOpen(200);
			}
			else if (temp->GetSubMenu() == 200)
			{
				temp->SetSubMenuOpen(0);
			}
		}
		else if (mbtnState == BtnState::ReStart)
		{
			SceneManager::GetInstance()->LoadScene(L"LoadingScene");
			SceneManager::GetInstance()->SetIsconfig(false);
			ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");
			temp->SetIsDestroy(true);
		}
		else if (mbtnState == BtnState::Sound)
		{
			ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");
			if (temp->GetSubMenu() != 200)
			{
				temp->SetSubMenuOpen(200);
				temp->SetIsSoundMenu(true);
			}
			else if (temp->GetSubMenu() == 200)
			{
				temp->SetSubMenuOpen(0);
				temp->SetIsSoundMenu(false);
			}
		}
	}
}

void ButtonUi::Release()
{

}

void ButtonUi::Render(HDC hdc)
{

	//mImage->FrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY);
	mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY, mScaleX, mScaleY);
	//RenderRect(hdc, mRect);

}

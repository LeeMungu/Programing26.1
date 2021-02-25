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
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}
void ButtonUi::Init()
{

}



void ButtonUi::Update()
{
	if (PtInRect(&mRect, _mousePosition) && Input::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		if (mbtnState == BtnState::End)
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
			SceneManager::GetInstance()->SetIsconfig(false);
			ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");
			temp->SetIsDestroy(true);


		}
		else if (mbtnState == BtnState::Record)
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
			SceneManager::GetInstance()->SetIsconfig(false);
		}
		else if (mbtnState == BtnState::ReStart)
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
			SceneManager::GetInstance()->SetIsconfig(false);
		}
		else if (mbtnState == BtnState::Sound)
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
			SceneManager::GetInstance()->SetIsconfig(false);
		}
	}
}

void ButtonUi::Release()
{

}

void ButtonUi::Render(HDC hdc)
{

	mImage->FrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY);
	//RenderRect(hdc, mRect);

}

#include "pch.h"
#include "ButtonUi.h"
#include "Image.h"

ButtonUi::ButtonUi(State state, float x, float y)
{
	mState = state;
	mImage = IMAGEMANAGER->FindImage(L"MenuBtn");
	mX = x;
	mY = y;
	mIndexX = 0;
	mIndexY = 0;
	if (mState == State::End)
	{
		mIndexY = 3;
	}
	else if (mState == State::Record)
	{
		mIndexY = 0;
	}
	else if (mState == State::ReStart)
	{
		mIndexY = 1;
	}
	else if (mState == State::Sound)
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
		if (mState == State::End)
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
			SceneManager::GetInstance()->SetIsconfig(false);
		}
		else if (mState == State::Record)
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
			SceneManager::GetInstance()->SetIsconfig(false);
		}
		else if (mState == State::ReStart)
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
			SceneManager::GetInstance()->SetIsconfig(false);
		}
		else if (mState == State::Sound)
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
	
	mImage->FrameRender(hdc,mRect.left,mRect.top,mIndexX,mIndexY);
	//RenderRect(hdc, mRect);

}

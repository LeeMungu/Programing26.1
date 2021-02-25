#include "pch.h"
#include "ConfigUi.h"
#include "Image.h"
#include "ButtonUi.h"

ConfigUi::ConfigUi(const string& name)
	: Ui(name)
{
	mImage = IMAGEMANAGER->FindImage(L"Menu");
	mMenuImage = IMAGEMANAGER->FindImage(L"MenuBtn");
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


}

void ConfigUi::Release()
{
	SafeDelete(mMenuEnd);
	SafeDelete(mMenuRecord);
	SafeDelete(mMenuRestart);
	SafeDelete(mMenuSound);

}

void ConfigUi::Update()
{
	mMenuEnd->Update();
	mMenuRecord->Update();
	mMenuRestart->Update();
	mMenuSound->Update();
}

void ConfigUi::Render(HDC hdc)
{
	mImage->Render(hdc, mRect.left, mRect.top);
	mMenuEnd->Render(hdc);
	mMenuRecord->Render(hdc);
	mMenuRestart->Render(hdc);
	mMenuSound->Render(hdc);
}

#include "pch.h"
#include "LoadingScene.h"
#include "Image.h"

void LoadingScene::AddLoadFunc(const function<void(void)>& func)
{
	mLoadList.push_back(func);
}

void LoadingScene::Init()
{
	mLoadIndex = 0;
	mIsEndLoading = false;
	for (int i = 0; i < 1000; i++)
	{
		AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"bullet", Resources(L"bullet.bmp"), 21, 21, true); });
	}
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"explosion", Resources(L"explosion.bmp"), 832, 62,26,1, true); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"Moon", Resources(L"MOON.mp3"), true); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"Star", Resources(L"Star.mp3"), true); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"400km", Resources(L"400km.mp3"), true); });

	mLoadingImage = IMAGEMANAGER->FindImage(L"LoadingImage");
	mLoadingBarImage1 = IMAGEMANAGER->FindImage(L"LoadingBar1");
	mLoadingBarImage2 = IMAGEMANAGER->FindImage(L"LoadingBar2");

}

void LoadingScene::Release()
{

}

void LoadingScene::Update()
{
	if (mLoadIndex >= mLoadList.size())
	{
		mIsEndLoading = true;
		return;
	}

	function<void(void)> func = mLoadList[mLoadIndex];
	func();
	
	mLoadIndex++;
}

void LoadingScene::Render(HDC hdc)
{
	mLoadingImage->Render(hdc, 0, 0);
	mLoadingBarImage1->Render(hdc, WINSIZEX / 2 - mLoadingBarImage1->GetWidth() / 2, WINSIZEY / 10 * 9);
	mLoadingBarImage2->Render(hdc, WINSIZEX / 2 - mLoadingBarImage2->GetWidth() / 2, WINSIZEY / 10 * 9,
		0,0,mLoadingBarImage2->GetWidth()*mLoadIndex/mLoadList.size(),mLoadingBarImage2->GetHeight());

	wstring loadingFer = L"LOADING : "+to_wstring(mLoadIndex*100 / mLoadList.size()) + L"%";
	TextOut(hdc, WINSIZEX/2-50, WINSIZEY/10*8, loadingFer.c_str(), loadingFer.length());
	
	if (mIsEndLoading == true)
	{
		wstring strNext = L"PUSH THE SPACE";
		TextOut(hdc, WINSIZEX / 2 - 50, WINSIZEY / 10 * 8, strNext.c_str(), loadingFer.length());
	}
}

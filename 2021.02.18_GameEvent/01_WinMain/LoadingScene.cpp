#include "pch.h"
#include "LoadingScene.h"

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
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Background", Resources(L"backGround2.bmp"), 768, 336, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bottom", Resources(L"bottom.bmp"), 768, 368, true); });
	
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
}

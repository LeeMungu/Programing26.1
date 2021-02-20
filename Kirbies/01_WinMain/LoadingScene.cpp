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
	
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Background", Resources(L"backGround2.bmp"), 768, 336, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bottom", Resources(L"bottom.bmp"), 1280, 614, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Speech", Resources(L"speech.bmp"), 172, 57, 2,1, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Player", Resources(L"kirbyFinal4.bmp"), 1520, 318, 14, 4, true); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"BoomEffectSound", Resources(L"BoomEffectSound.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"OpenDoorSound", Resources(L"OpenDoorSound.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"CloseDoorSound", Resources(L"CloseDoorSound.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"BunEffectSound", Resources(L"BunEffectSound.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"DigEffectSound", Resources(L"DigEffectSound.mp3"), false); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAppear", Resources(L"/sp/appear.bmp"), 1328, 540, 8, 3, true);});
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAppearEffect", Resources(L"/sp/appeareffect.bmp"), 2988, 1536, 9, 3, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAttack", Resources(L"/sp/attack.bmp"), 1494, 720, 9, 4, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAttackEffect1", Resources(L"/sp/attackeffect1.bmp"), 2560, 512, 10, 2, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAttackEffect2", Resources(L"/sp/attackeffect2.bmp"), 1600, 1600, 5, 5, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAttackEffect3", Resources(L"/sp/attackeffect3.bmp"), 2560, 249, 10, 1, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialEnd", Resources(L"/sp/end.bmp"), 1660, 900, 10, 5, true); });

	mLoadingImage = IMAGEMANAGER->FindImage(L"LoadingImage");
	mLoadingBarImage1 = IMAGEMANAGER->FindImage(L"LoadingBar1");
	mLoadingBarImage2 = IMAGEMANAGER->FindImage(L"LoadingBar2");
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
	if (mIsEndLoading == true)
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"Scene1");
		}
	}

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
		0, 0, mLoadingBarImage2->GetWidth() * mLoadIndex / mLoadList.size(), mLoadingBarImage2->GetHeight());

	wstring loadingFer = L"LOADING : " + to_wstring(mLoadIndex * 100 / mLoadList.size()) + L"%";
	TextOut(hdc, WINSIZEX / 2 - 50, WINSIZEY / 10 * 8, loadingFer.c_str(), loadingFer.length());

	if (mIsEndLoading == true)
	{
		wstring strNext = L"PUSH THE SPACE";
		TextOut(hdc, WINSIZEX / 2 - 50, WINSIZEY / 10 * 8, strNext.c_str(), loadingFer.length());
	}

	
}

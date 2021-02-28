#include "pch.h"
#include "MainScene.h"
#include "BackGround.h"
#include "Title.h"
#include "TitleStyle1.h"
#include "TitleStyle2.h"
#include "TitleStyle3.h"
#include "TitleStyle4.h"

#include "Scene.h"

void MainScene::Init()
{
	//오브젝트
	BackGround* background = new BackGround("BackGround", WINSIZEX / 2, WINSIZEY / 2, L"MainBackGround");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);
	TitleStyle1* mainImage = new TitleStyle1(L"MainImage");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, mainImage);

	ObjectManager::GetInstance()->Init();
	//TitleStyle4* mainText3 = new TitleStyle4(L"MainTitle3");				 
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, mainText3);

	//사운드
	SoundPlayer::GetInstance()->Play(L"TitleBGM", 0.5f
		*SoundPlayer::GetInstance()->GetBgmvolum());

	mIsLoadEnd = false;
	mTimeSet = 0.f;
}

void MainScene::Release()
{
	ObjectManager::GetInstance()->Release();
}

void MainScene::Update()
{
	ObjectManager::GetInstance()->Update();

	Title* tempTitle = (Title*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Background, "TitleFinal");
	if (tempTitle != NULL)
	{
		if (tempTitle->GetIsEndAnimation() == true)
		{
			mIsLoadEnd = true;
		}
	}
	if (mIsLoadEnd == true)
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{

			SceneManager::GetInstance()->LoadScene(L"LoadingScene");
			mIsLoadEnd = false;
		}
		mTimeSet += Time::GetInstance()->DeltaTime();
	}
}

void MainScene::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

	if(mIsLoadEnd == true && mTimeSet>0.5f)
	{
		SetBkMode(hdc, 1);
		HFONT hFont, oldFont;
		hFont = CreateFont(60, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("메이플스토리 Bold"));
		oldFont = (HFONT)SelectObject(hdc, hFont);
		wstring strNext = L"PUSH THE SPACE";
		TextOut(hdc, WINSIZEX / 6, WINSIZEY / 2, strNext.c_str(), strNext.length());
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
		if (mTimeSet > 1.f)
		{
			mTimeSet = 0.f;
		}
	}
}

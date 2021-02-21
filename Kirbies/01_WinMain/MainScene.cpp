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
	BackGround* background = new BackGround("BackGround", WINSIZEX / 2, WINSIZEY / 2,L"MainBackGround");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	TitleStyle1* mainImage = new TitleStyle1(L"MainImage");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, mainImage);

	//TitleStyle2* mainText1 = new TitleStyle2(L"MainTitle1");
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, mainText1);
	//																	
	//TitleStyle3* mainText2 = new TitleStyle3(L"MainTitle2");				 
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, mainText2);
	//																	 
	//TitleStyle4* mainText3 = new TitleStyle4(L"MainTitle3");				 
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, mainText3);


	ObjectManager::GetInstance()->Init();

	mIsLoadEnd = false;
}

void MainScene::Release()
{
	ObjectManager::GetInstance()->Release();

}

void MainScene::Update()
{
	if (Input::GetInstance()->GetKey(VK_SPACE) && mIsLoadEnd ==true)
	{
		SceneManager::GetInstance()->LoadScene(L"LoadingScene");
	}
	ObjectManager::GetInstance()->Update();
}

void MainScene::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}

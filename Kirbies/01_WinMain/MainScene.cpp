#include "pch.h"
#include "MainScene.h"
#include "BackGround.h"
#include "Title.h"
#include "Scene.h"

void MainScene::Init()
{
	BackGround* background = new BackGround("BackGround", WINSIZEX / 2, WINSIZEY / 2,L"MainBackGround");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	Title* mainImage = new Title(type::UpAndDown, L"MainImage");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, mainImage);


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
}

void MainScene::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}

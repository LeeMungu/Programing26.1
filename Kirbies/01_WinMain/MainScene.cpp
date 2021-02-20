#include "pch.h"
#include "MainScene.h"
#include "BackGround.h"
#include "Title.h"

void MainScene::Init()
{
	BackGround* background = new BackGround("BackGround", WINSIZEX / 2, WINSIZEY / 2,L"MainBackGround");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, background);

	Title* mainImage = new Title(type::UpAndDown, L"MainImage");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, mainImage);


	ObjectManager::GetInstance()->Init();
}

void MainScene::Release()
{
	ObjectManager::GetInstance()->Release();

}

void MainScene::Update()
{
}

void MainScene::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}

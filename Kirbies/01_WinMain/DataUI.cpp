#include "pch.h"
#include "DataUI.h"
DataUI::DataUI(string name, float x, float y, int stage) : GameObject(name)
{
	mX = x;
	mY = y;
	
	if (stage == 1) mCountingPlayerUI = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene1count");
	if (stage == 2) mCountingPlayerUI = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene2count");
	if (stage == 3) mCountingPlayerUI = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene3count");
	if (stage == 4) mCountingPlayerUI = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene4count");
	if (stage == 5) mCountingPlayerUI = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene5count");
	
}

void DataUI::Init()
{
	
	mTime = 0;
	mGoalPercent = 0;
}

void DataUI::Release()
{
}

void DataUI::Update()
{

}

void DataUI::Render(HDC hdc)
{
}

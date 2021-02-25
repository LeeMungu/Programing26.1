#include "pch.h"
#include "DataUI.h"
#include "GameObject.h"
#include "CountingPlayerUI.h"
DataUI::DataUI(const string& name, int stage) 
	: Ui(name)
{
	if (stage == 1)
	{
		mCountingPlayerUI = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene1count");
		int a = 0;
	}
	else if (stage == 2) mCountingPlayerUI = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene2count");
	else if (stage == 3) mCountingPlayerUI = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene3count");
	else if (stage == 4) mCountingPlayerUI = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene4count");
	else if (stage == 5) mCountingPlayerUI = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene5count");	
}

void DataUI::Init()
{
	mTime = mCountingPlayerUI->GetTimer();
	mGoalPercent = mCountingPlayerUI->GetGoalPercent();
}

void DataUI::Render(HDC hdc)
{
	wstring GoalPlayer = to_wstring((int)mGoalPercent);
	wstring timer = to_wstring((int)(mTime / 60) % 60) + L":"
		+ to_wstring((int)mTime % 60);

	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, GoalPlayer.c_str(), GoalPlayer.length());
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 100 , timer.c_str(), timer.length());
}

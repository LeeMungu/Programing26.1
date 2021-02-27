#include "pch.h"
#include "DataUI.h"
#include "GameObject.h"
#include "CountingPlayerUI.h"
#include "ConfigUi.h"
DataUI::DataUI(const string& name)	: Ui(name)
{
}

void DataUI::Init()
{
	
}

void DataUI::Release()
{
}

void DataUI::Update()
{
	tempCountingUI = UiManager::GetInstance()->GetUiList(UiLayer::CountPlayerUi);
	vector<float>::iterator iterGoal = mGoalPercentList.begin();
	if (tempCountingUI.size() != NULL) {
		mGoalPercentList.clear();
		mTimeList.clear();

		for (int i = 0; i < tempCountingUI.size(); i++) {
			mGoalPercentList.push_back( ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent() );
			mTimeList.push_back( ((CountingPlayerUI*)tempCountingUI[i])->GetTimer() );

		}
	}
	//만약 클리어하고 이전 점수보다 점수가 높으면 점수 세팅해준다.
	/*
	float newScore = mCountingPlayerUI->GetGoalPlayer() * 100 + mTime;
	
	if (newScore > mScore) {
		mTime = mCountingPlayerUI->GetTimer();
		mGoalPercent = mCountingPlayerUI->GetGoalPercent();
	}
	*/

}

void DataUI::Render(HDC hdc)
{

	ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");
	
	if (temp->GetIsRecordMenu() == true)
	{

		if (mGoalPercentList.size() != NULL) {
			for (int i = 0; i < tempCountingUI.size(); i++) {
				wstring goal = to_wstring((int)mGoalPercentList[i]) + L"%";
				wstring timer = to_wstring((int)(mTimeList[i] / 60) % 60) + L":" + to_wstring((int)mTimeList[i] % 60);

				TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 50 * i, goal.c_str(), goal.length());
				TextOut(hdc, WINSIZEX / 2 + 100, WINSIZEY / 2 + 50 * i, timer.c_str(), timer.length());
			}
		}
	}

	//wstring GoalPlayer = to_wstring((int)mGoalPercent);
	//wstring timer = to_wstring((int)(mTime / 60) % 60) + L":"
	//	+ to_wstring((int)mTime % 60);
	//
	//TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, GoalPlayer.c_str(), GoalPlayer.length());
	//TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 100 , timer.c_str(), timer.length());
}

void DataUI::SetData()
{
}

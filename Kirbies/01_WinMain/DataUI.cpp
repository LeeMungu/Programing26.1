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

	if (tempCountingUI.size() != NULL) {
		//mGoalMap.clear(); 
		//mTimeMap.clear();

		for (int i = 0; i < tempCountingUI.size(); i++) {
			string name = ((CountingPlayerUI*)tempCountingUI[i])->GetName();

			if (name == "Scene1count") {
				if (mGoalMap.count("1") == 0) {
					mGoalMap.insert(make_pair("1", ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent()));
					mTimeMap.insert(make_pair("1", ((CountingPlayerUI*)tempCountingUI[i])->GetTimer()));
				}
				else if (mGoalMap.count("1") == 1) {
					mGoalMap["1"] = ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent();
					mTimeMap["1"] = ((CountingPlayerUI*)tempCountingUI[i])->GetTimer();
				}
			} 
			else if (name == "Scene2count") {
				if (mGoalMap.count("2") == 0) {
					mGoalMap.insert(make_pair("2", ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent()));
					mTimeMap.insert(make_pair("2", ((CountingPlayerUI*)tempCountingUI[i])->GetTimer()));
				}
				else if (mGoalMap.count("2") == 1) {
					mGoalMap["2"] = ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent();
					mTimeMap["2"] = ((CountingPlayerUI*)tempCountingUI[i])->GetTimer();
				}
			}
			else if (name == "Scene3count") {
				if (mGoalMap.count("3") == 0) {
					mGoalMap.insert(make_pair("3", ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent()));
					mTimeMap.insert(make_pair("3", ((CountingPlayerUI*)tempCountingUI[i])->GetTimer()));
				}
				else if (mGoalMap.count("3") == 1) {
					mGoalMap["3"] = ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent();
					mTimeMap["3"] = ((CountingPlayerUI*)tempCountingUI[i])->GetTimer();
				}
			}
			else if (name == "Scene4count") {
				if (mGoalMap.count("4") == 0) {
					mGoalMap.insert(make_pair("4", ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent()));
					mTimeMap.insert(make_pair("4", ((CountingPlayerUI*)tempCountingUI[i])->GetTimer()));
				}
				else if (mGoalMap.count("4") == 1) {
					mGoalMap["4"] = ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent();
					mTimeMap["4"] = ((CountingPlayerUI*)tempCountingUI[i])->GetTimer();
				}
			}
			else if (name == "Scene5count") {
				if (mGoalMap.count("5") == 0) {
					mGoalMap.insert(make_pair("5", ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent()));
					mTimeMap.insert(make_pair("5", ((CountingPlayerUI*)tempCountingUI[i])->GetTimer()));
				}
				else if (mGoalMap.count("5") == 1) {
					mGoalMap["5"] = ((CountingPlayerUI*)tempCountingUI[i])->GetGoalPercent();
					mTimeMap["5"] = ((CountingPlayerUI*)tempCountingUI[i])->GetTimer();
				}
			}
		}
	}

}

void DataUI::Render(HDC hdc)
{
	ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi("Menu");

	SetBkMode(hdc, 1);
	HFONT hFont, oldFont;
	hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Edit Undo BRK"));
	oldFont = (HFONT)SelectObject(hdc, hFont);

	wstring str = L"STAGE   IN   TIME";
	TextOut(hdc, WINSIZEX / 2 + 150, WINSIZEY / 2 - 100, str.c_str(), str.length());

	map<string, float>::iterator iter;
	if (temp->GetIsRecordMenu() == true)
	{
		int i = 0;
		int j = 0;
		if (mGoalMap.size() != NULL) {
			for (iter = mGoalMap.begin(); iter != mGoalMap.end(); iter++) {
				wstring stage = to_wstring(i + 1);
				wstring goal = to_wstring((int)iter->second) + L"%";
				TextOut(hdc, WINSIZEX / 2 + 170, WINSIZEY / 2 - 80 + 30 * i, stage.c_str(), stage.length());
				TextOut(hdc, WINSIZEX / 2 + 220, WINSIZEY / 2 - 80 + 30 * i, goal.c_str(), goal.length());

				i++;
			}
		}

		if (mTimeMap.size() != NULL) {
			for (iter = mTimeMap.begin(); iter != mTimeMap.end(); iter++) {
				wstring timer = to_wstring((int)(iter->second / 60) % 60) + L":" + to_wstring((int)iter->second % 60);
				TextOut(hdc, WINSIZEX / 2 + 270, WINSIZEY / 2 - 80 + 30 * j, timer.c_str(), timer.length());
				j++;
			}
		}
	}

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void DataUI::SetData()
{
}

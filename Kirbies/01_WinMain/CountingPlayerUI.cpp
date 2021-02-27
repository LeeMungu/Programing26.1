#include "pch.h"
#include "CountingPlayerUI.h"
#include "Door.h"
#include "Player.h"
#include "Image.h"
//생성된 플레이어 수 / 골 된 플레이어 수(퍼센트) / 시간 을 UI로 보여준다.
CountingPlayerUI::CountingPlayerUI(string name, float x, float y, float timer) : Ui(name)
{
	mX = x;
	mY = y;
	mTimer = timer;

}
void CountingPlayerUI::Init()
{
	Door* tempDoor = (Door*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Door, "Door");
	if (tempDoor != NULL)
	{
		mPlayerCount = tempDoor->GetStageCount();
	}
	mCreatedPlayerCount = 0;
	mGoalPlayerCount = 0;

	mOutImage = IMAGEMANAGER->FindImage(L"OutUI");
	mInImage = IMAGEMANAGER->FindImage(L"OutUI");
	mTimeImage = IMAGEMANAGER->FindImage(L"TimeUI");

	AddFontResourceA("../02_Resources/editundo.ttf");
}

void CountingPlayerUI::Release()
{
}

void CountingPlayerUI::Update()
{
	vector<GameObject*> player = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player);

	for (int i = 0; i < player.size(); i++)
	{
		
			Player* tempPlayer = (Player*)player[i];
			if (tempPlayer->GetIsDoor() == true) {
				if (tempPlayer->GetIsDestroy() == true)
				{
					mGoalPlayerCount++;
				}
			}
	}

	//타이머
	if ((ConfigUi*)UiManager::GetInstance()->FindUi(UiLayer::Object, "Menu") == NULL)
	{
		if (mTimer > 0)
			mTimer -= Time::GetInstance()->DeltaTime();
	}

	//플레이어 갯수 세기
	Door* tempDoor = (Door*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Door, "Door");
	if(tempDoor != NULL)
	{	
	//도어에서 겟해서 넣어주기
	mCreatedPlayerCount = tempDoor->GetPlayerCount();

	mGoalPercent = mGoalPlayerCount * 100 / mPlayerCount;
	}

	//Scene* scene 
	//if (scene->GetIsGameClear() == true) {
	//
	//}
	
}	

void CountingPlayerUI::Render(HDC hdc)
{

	mOutImage->Render(hdc, mX, mY);
	mInImage->Render(hdc, mX + 130, mY);
	mTimeImage->Render(hdc, mX + 260, mY);

	SetBkMode(hdc, 1);
	HFONT hFont, oldFont;
	hFont = CreateFont(27, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Edit Undo BRK"));
	oldFont = (HFONT)SelectObject(hdc, hFont);

	wstring createdPlayer = L"OUT " + to_wstring(mCreatedPlayerCount);
	wstring GoalPlayer = L"IN " + to_wstring((int)mGoalPercent) + L"%";
	wstring timer = L"TIME " + to_wstring((int)(mTimer / 60) % 60) + L":"
		+ to_wstring((int)mTimer % 60);

	TextOut(hdc, mX + 10, mY + 10, createdPlayer.c_str(), createdPlayer.length());
	TextOut(hdc, mX + 140, mY + 10, GoalPlayer.c_str(), GoalPlayer.length());
	TextOut(hdc, mX + 265, mY + 10, timer.c_str(), timer.length());

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

}

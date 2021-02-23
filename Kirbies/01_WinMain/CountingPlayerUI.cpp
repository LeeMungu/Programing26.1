#include "pch.h"
#include "CountingPlayerUI.h"
#include "Door.h"
#include "Player.h"
//생성된 플레이어 수 / 골 된 플레이어 수(퍼센트) / 시간 을 UI로 보여준다.
CountingPlayerUI::CountingPlayerUI(float x, float y, float timer)
{
	mX = x;
	mY = y;
	mTimer = timer;
}
void CountingPlayerUI::Init()
{
	mDoor =	(Door*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Door, "Door");
	mPlayerCount = mDoor->GetStageCount();

	mCreatedPlayerCount = 0;
	mGoalPlayerCount = 0;
}

void CountingPlayerUI::Release()
{
}

void CountingPlayerUI::Update()
{
	if (mTimer > 0) 
		mTimer -= Time::GetInstance()->DeltaTime();

	mCountTimer += Time::GetInstance()->DeltaTime();

	if (mCountTimer >= 3 && mCreatedPlayerCount < mPlayerCount) {
		mCountTimer = 0;
		mCreatedPlayerCount++;
	}

}

void CountingPlayerUI::Render(HDC hdc)
{
	wstring createdPlayer = L"OUT " + to_wstring(mCreatedPlayerCount);
	wstring GoalPlayer = L"IN " + to_wstring(mGoalPlayerCount / mPlayerCount * 100) + L"%";
	wstring timer = L"TIME " + to_wstring((int)(mTimer / 60) % 60) + L":"
		+ to_wstring((int)mTimer % 60);

	TextOut(hdc, mX, mY, createdPlayer.c_str(), createdPlayer.length());
	TextOut(hdc, mX + 100, mY, GoalPlayer.c_str(), GoalPlayer.length());
	TextOut(hdc, mX + 200, mY, timer.c_str(), timer.length());
}

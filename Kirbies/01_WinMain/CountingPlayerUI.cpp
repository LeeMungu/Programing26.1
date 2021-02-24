#include "pch.h"
#include "CountingPlayerUI.h"
#include "Door.h"
#include "Player.h"
#include "Image.h"
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

	mOutImage = IMAGEMANAGER->FindImage(L"OutUI");
	mInImage = IMAGEMANAGER->FindImage(L"InUI");
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
			if (tempPlayer->GetIsGoal() == true) {
				if (tempPlayer->GetIsDestroy() == true)
				{
					mGoalPlayerCount++;
				}
			}
	}


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

	mOutImage->Render(hdc, mX, mY);
	mInImage->Render(hdc, mX + 130, mY);
	mTimeImage->Render(hdc, mX + 260, mY);

	SetBkMode(hdc, 1);
	HFONT hFont, oldFont;
	hFont = CreateFont(27, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Edit Undo BRK"));
	oldFont = (HFONT)SelectObject(hdc, hFont);

	wstring createdPlayer = to_wstring(mCreatedPlayerCount);
	wstring GoalPlayer = to_wstring((int)mGoalPlayerCount * 100 / mPlayerCount );
	wstring timer = to_wstring((int)(mTimer / 60) % 60) + L":"
		+ to_wstring((int)mTimer % 60);

	TextOut(hdc, mX + 80, mY + 10, createdPlayer.c_str(), createdPlayer.length());
	TextOut(hdc, mX + 190, mY + 10, GoalPlayer.c_str(), GoalPlayer.length());
	TextOut(hdc, mX + 347, mY + 10, timer.c_str(), timer.length());

}

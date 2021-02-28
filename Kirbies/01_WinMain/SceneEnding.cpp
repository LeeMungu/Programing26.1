#include "pch.h"
#include "SceneEnding.h"
#include "EndingText.h"

void SceneEnding::Init()
{
	
	mIndexY = 0;
	EndingText* endingText = new EndingText(mIndexY);
	endingText->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, endingText);
	mEndText = endingText;
	mIndexY++;
}
void SceneEnding::Release()
{
	ObjectManager::GetInstance()->Release();
}

void SceneEnding::Update()
{
	if (mEndText->GetRect().bottom < WINSIZEY-10 && mIndexY < 44)
	{
		EndingText* endingText = new EndingText(mIndexY);
		endingText->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, endingText);
		mEndText = endingText;
		mIndexY++;
	}
	ObjectManager::GetInstance()->Update();
}

void SceneEnding::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}

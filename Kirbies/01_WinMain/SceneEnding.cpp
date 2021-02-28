#include "pch.h"
#include "SceneEnding.h"
#include "EndingText.h"
#include "BackGround.h"

void SceneEnding::Init()
{
	BackGround* backGround = new BackGround("EndingBackGound", WINSIZEX/2,WINSIZEY/2);
	backGround->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);

	mIndexY = 0;
	EndingText* endingText = new EndingText(mIndexY);
	endingText->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, endingText);
	mEndText = endingText;
	mIndexY++;
	mStop = false;

	SoundPlayer::GetInstance()->Play(L"EndingBGM", 0.5f);
}
void SceneEnding::Release()
{
	ObjectManager::GetInstance()->Release();
}

void SceneEnding::Update()
{
	if (mStop == false)
	{
		if (mEndText->GetRect().bottom < WINSIZEY - 10 && mIndexY < 44)
		{
			EndingText* endingText = new EndingText(mIndexY);
			endingText->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, endingText);
			mEndText = endingText;
			mIndexY++;
		}
		ObjectManager::GetInstance()->Update();
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			mStop = true;
		}
	}
	else
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			mStop = false;
		}
	}
}

void SceneEnding::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}

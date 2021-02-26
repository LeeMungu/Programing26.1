#include "pch.h"
#include "Scene3.h"
#include "Player.h"
#include "Bottom.h"
#include "BackGround.h"
#include "Camera.h"
#include "GameEvent.h"
#include "Image.h"
#include "Mouse.h"
#include "Door.h"
#include "Goal.h"
#include "Ui.h"
#include "CountingPlayerUI.h"
#include "DataUI.h"
#include "Animation.h"

void Scene3::Init()
{
	mImageGameOver = IMAGEMANAGER->FindImage(L"GameOver");
	mAnimationGameOver = new Animation();
	mAnimationGameOver->InitFrameByStartEnd(0, 0, 8, 0, false);
	mAnimationGameOver->SetIsLoop(true);
	mAnimationGameOver->SetFrameUpdateTime(0.1f);

	Mouse* mouse = new Mouse("Mouse");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);

	BackGround* backGround = new BackGround("Background3", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);


	Bottom* bottom = new Bottom("Bottom", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);

	Door* door = new Door("Door", WINSIZEX / 2, 0, 10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);

	Goal* goal = new Goal("goal", WINSIZEX / 2 + 300, 0);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Goal, goal);


	Ui* ui = new Ui("BoomBtn", PlayerState::BoomState, 100, 100, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);
	Ui* ui2 = new Ui("ClimbBtn", PlayerState::ClimbState, 100, 200, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui2);
	Ui* ui3 = new Ui("DigBtn", PlayerState::DigState, 100, 300, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui3);
	Ui* ui4 = new Ui("StopperBtn", PlayerState::StopperState, 100, 400, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui4);
	Ui* ui5 = new Ui("UmbrellaBtn", PlayerState::UmbrellaState, 100, 500, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui5);

	//Ui
	CountingPlayerUI* countUI = new CountingPlayerUI("Scene3count", 100, WINSIZEY - 100, 300);
	countUI->Init();
	UiManager::GetInstance()->AddUi(UiLayer::CountPlayerUi, countUI);


	//camera
	Camera* camera = new Camera();
	camera->SetX(100);
	camera->SetY(WINSIZEY / 2);
	//camera->SetTarget(player1);
	camera->ChangeMode(Camera::Mode::Free);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Camera, camera);

	ObjectManager::GetInstance()->Init();

	//����
	SoundPlayer::GetInstance()->Play(L"Scene3BGM", SoundPlayer::GetInstance()->GetBgmvolum());
	SoundPlayer::GetInstance()->Stop(L"Scene2BGM");

	mIsSpecial = false;
}

void Scene3::Release()
{
	ObjectManager::GetInstance()->Release();
	SoundPlayer::GetInstance()->Stop(L"Scene3BGM");
	UiManager::GetInstance()->FindUi(UiLayer::CountPlayerUi, "Scene3count")->SetIsActive(false);
}

void Scene3::Update()
{
	//Ŭ���� �� ���� �ε���
	if (mIsGameClear == true)
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"LoadingScene3to4");
		}
	}
	//Ŭ��������
	CountingPlayerUI* tempUi = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene3count");
	if (tempUi != NULL)
	{
		if (tempUi->GetGoalPercent() > 50.f &&
			ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() == NULL)
		{
			mIsGameClear = true;
			Ui* dataUI = new DataUI("DataUI", 3);
			UiManager::GetInstance()->AddUi(UiLayer::DataUI, dataUI);
		}
	}

	//���ӿ��� ����
	mGameOverTimer += Time::GetInstance()->DeltaTime();
	if (mGameOverTimer > 5)
	{
		if (tempUi != NULL && mIsGameOver == false)
		{
			if (tempUi->GetGoalPercent() < 50.f &&
				ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() == NULL)
			{
				mIsGameOver = true;
				mAnimationGameOver->Play();
			}
		}
	}

	mAnimationGameOver->Update();
	

	SoundPlayer::GetInstance()->Stop(L"TitleBGM");
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();
	SpecialFunc();
}

void Scene3::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

	wstring str = L"��������3 �Һҵ���.";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 3, str.c_str(), str.length());

	if (mIsGameClear)
	{
		wstring str1 = L"�������� Ŭ����";
		TextOut(hdc, WINSIZEX / 2, WINSIZEY / 3, str1.c_str(), str1.length());
	}


	if (mIsGameOver == true)
	{
		wstring str2 = L"�ѿ��";
		TextOut(hdc, WINSIZEX / 2, WINSIZEY / 3, str2.c_str(), str2.length());
		mImageGameOver->FrameRender(hdc, 550, WINSIZEY / 2,
			mAnimationGameOver->GetNowFrameX(),
			mAnimationGameOver->GetNowFrameY());
	}
}

void Scene3::mapRender(HDC map)
{
	ObjectManager::GetInstance()->mapRender(map);
}
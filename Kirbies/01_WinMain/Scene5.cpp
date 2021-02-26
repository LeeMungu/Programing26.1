#include "pch.h"
#include "Scene5.h"
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

void Scene5::Init()
{
	mImageGameOver = IMAGEMANAGER->FindImage(L"GameOver");
	mAnimationGameOver = new Animation();
	mAnimationGameOver->InitFrameByStartEnd(0, 0, 8, 0, false);
	mAnimationGameOver->SetIsLoop(true);
	mAnimationGameOver->SetFrameUpdateTime(0.1f);

	Mouse* mouse = new Mouse("Mouse");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);

	BackGround* backGround = new BackGround("Background5", WINSIZEX / 2, WINSIZEY / 2);
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
	CountingPlayerUI* countUI = new CountingPlayerUI("Scene5count", 100, WINSIZEY - 100, 300);
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

	//사운드
	SoundPlayer::GetInstance()->Play(L"Scene5BGM", SoundPlayer::GetInstance()->GetBgmvolum());
	SoundPlayer::GetInstance()->Stop(L"Scene4BGM");

	mIsSpecial = false;
}

void Scene5::Release()
{
	ObjectManager::GetInstance()->Release();
	SoundPlayer::GetInstance()->Stop(L"Scene5BGM");
	UiManager::GetInstance()->FindUi(UiLayer::CountPlayerUi, "Scene5count")->SetIsActive(false);
}

void Scene5::Update()
{
	//클리어 시 변경 로딩씬
	if (mIsGameClear == true)
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
		}
	}
	//클리어조건
	CountingPlayerUI* tempUi = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene5count");
	if (tempUi != NULL)
	{
		if (tempUi->GetGoalPercent() > 50.f &&
			ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() == NULL)
		{
			mIsGameClear = true;
			Ui* dataUI = new DataUI("DataUI", 5);
			UiManager::GetInstance()->AddUi(UiLayer::DataUI, dataUI);
		}
	}

	//게임오버 조건
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

void Scene5::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

	wstring str = L"스테이지5 풀풀동산.";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 3, str.c_str(), str.length());

	if (mIsGameClear)
	{
		wstring str1 = L"스테이지 클리어";
		TextOut(hdc, WINSIZEX / 2, WINSIZEY / 3, str1.c_str(), str1.length());
	}


	if (mIsGameOver == true)
	{
		wstring str2 = L"뿌우웅";
		TextOut(hdc, WINSIZEX / 2, WINSIZEY / 3, str2.c_str(), str2.length());
		mImageGameOver->FrameRender(hdc, 550, WINSIZEY / 2,
			mAnimationGameOver->GetNowFrameX(),
			mAnimationGameOver->GetNowFrameY());
	}
}

void Scene5::mapRender(HDC map)
{
	ObjectManager::GetInstance()->mapRender(map);
}
#include "pch.h"
#include "Scene1.h"
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

void Scene1::Init()
{	

	mImageGameOver = IMAGEMANAGER->FindImage(L"GameOver");
	mAnimationGameOver = new Animation();
	mAnimationGameOver->InitFrameByStartEnd(0, 0, 8, 0, false);
	mAnimationGameOver->SetIsLoop(true);
	mAnimationGameOver->SetFrameUpdateTime(0.1f);
	//mAnimationGameOver->SetCallbackFunc([this]() {mPlayer->SetIsDestroy(true); });

	Mouse* mouse = new Mouse("Mouse");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);

	BackGround* backGround = new BackGround("Background", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);
	

	Bottom* bottom = new Bottom("Bottom", WINSIZEX/2, WINSIZEY/2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);

	Door* door = new Door("Door",WINSIZEX/2,0,10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);

	Goal* goal = new Goal("goal", WINSIZEX / 2+300,200);
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
	CountingPlayerUI* countUI = new CountingPlayerUI("Scene1count",100, WINSIZEY - 100, 300);
	countUI->Init();
	UiManager::GetInstance()->AddUi(UiLayer::CountPlayerUi, countUI);

	//camera
	Camera* camera = new Camera();
	camera->SetX(100);
	camera->SetY(WINSIZEY / 2);
	//camera->SetTarget(player1);
	camera->ChangeMode(Camera::Mode::Free);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Camera,camera);

	ObjectManager::GetInstance()->Init();

	//����
	SoundPlayer::GetInstance()->Play(L"Scene1BGM", 0.5f
		*SoundPlayer::GetInstance()->GetBgmvolum());
	SoundPlayer::GetInstance()->Stop(L"TitleBGM");

	SoundPlayer::GetInstance()->Play(L"Scene1BGM", 0.5f);
	
	mIsSpecial = false;
	mIsGameClear = false;
	mIsGameOver = false;
	mGameOverTimer = 0.f;
}

void Scene1::Release()
{
	ObjectManager::GetInstance()->Release();
	SoundPlayer::GetInstance()->Stop(L"Scene1BGM");
	UiManager::GetInstance()->FindUi(UiLayer::CountPlayerUi, "Scene1count")->SetIsActive(false);
}

void Scene1::Update()
{
	//Ŭ���� �� ���� �ε���
	if (mIsGameClear == true)
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"LoadingScene1to2");
		}
	}
	if (mIsGameOver == true)
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
		}
	}
	//Ŭ��������
	CountingPlayerUI* tempUi = (CountingPlayerUI*)UiManager::GetInstance()->FindUi(UiLayer::CountPlayerUi, "Scene1count");
	if (tempUi != NULL && mIsGameClear == false)
	{
		if (tempUi->GetGoalPercent() > 50.f &&
			ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() == NULL)
		{
			mIsGameClear = true;

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
	

	//���� �����ֱ�
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();

	SpecialFunc();
}

void Scene1::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

	wstring str = L"��������1 ������������.";
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
		mImageGameOver->FrameRender(hdc, WINSIZEX / 3, WINSIZEY / 2,
			mAnimationGameOver->GetNowFrameX(),
				mAnimationGameOver->GetNowFrameY());
	}

}

void Scene1::mapRender(HDC map)
{
	ObjectManager::GetInstance()->mapRender(map);
}


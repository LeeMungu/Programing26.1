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

void Scene5::Init()
{
	Mouse* mouse = new Mouse("Mouse");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);

	BackGround* backGround = new BackGround("BackGround", WINSIZEX / 2, WINSIZEY / 2);
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

	CountingPlayerUI* countUI = new CountingPlayerUI("Scene5count", 100, WINSIZEY - 100, 300);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, countUI);


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
	SoundPlayer::GetInstance()->Play(L"Scene5BGM", 0.5f
		*SoundPlayer::GetInstance()->GetBgmvolum());
	SoundPlayer::GetInstance()->Stop(L"Scene4BGM");

	mIsSpecial = false;
}

void Scene5::Release()
{
	ObjectManager::GetInstance()->Release();
	SoundPlayer::GetInstance()->Stop(L"Scene5BGM");
}

void Scene5::Update()
{
	//Ŭ���� �� ���� �ε���
	if (mIsGameClear == true)
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
		}
	}
	//Ŭ��������
	CountingPlayerUI* tempUi = (CountingPlayerUI*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Scene5count");
	if (tempUi != NULL)
	{
		if (tempUi->GetGoalPercent() > 50.f &&
			ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() == NULL)
		{
			mIsGameClear = true;
		}
	}


	SoundPlayer::GetInstance()->Stop(L"TitleBGM");
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();
	SpecialFunc();
}

void Scene5::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

	wstring str = L"��������5 ǮǮ����.";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 3, str.c_str(), str.length());
}

void Scene5::mapRender(HDC map)
{
	ObjectManager::GetInstance()->mapRender(map);
}
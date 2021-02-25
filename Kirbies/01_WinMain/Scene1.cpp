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
void Scene1::Init()
{
	//player
	//Player* player1 = new Player("1", 200, 631);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player1);
	
	Mouse* mouse = new Mouse("Mouse");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);

	BackGround* backGround = new BackGround("BackGround", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);
	

	Bottom* bottom = new Bottom("Bottom", WINSIZEX/2, WINSIZEY/2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);

	Door* door = new Door("Door",WINSIZEX/2,0,10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);

	Goal* goal = new Goal("goal", WINSIZEX / 2+300,0);
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

	CountingPlayerUI* countUI = new CountingPlayerUI("CountUI",100, WINSIZEY - 100, 300);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, countUI);


	//camera
	Camera* camera = new Camera();
	camera->SetX(100);
	camera->SetY(WINSIZEY / 2);
	//camera->SetTarget(player1);
	camera->ChangeMode(Camera::Mode::Free);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Camera,camera);

	ObjectManager::GetInstance()->Init();

	//사운드
	SoundPlayer::GetInstance()->Play(L"Scene1BGM", 0.5f);

	mIsSpecial = false;
}

void Scene1::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene1::Update()
{
	//클리어되면 씬 넘어가게
	//사운드 멈춰주기
	SoundPlayer::GetInstance()->Stop(L"TitleBGM");
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();

	SpecialFunc();
}

void Scene1::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

	wstring str = L"스테이지1 구름구름동산.";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 3, str.c_str(), str.length());
}

void Scene1::mapRender(HDC map)
{
	ObjectManager::GetInstance()->mapRender(map);
}


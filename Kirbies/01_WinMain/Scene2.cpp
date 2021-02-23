#include "pch.h"
#include "Scene2.h"
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

void Scene2::Init()
{
	//���콺 ���� �޾ƿ���
	Mouse* mouse = new Mouse("Mouse");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
	//��׶��� �޾ƿ���
	BackGround* backGround = new BackGround("BackGround1", WINSIZEX / 2, WINSIZEY / 2, L"Background1");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);
	//�ٴ� �޾ƿ���
	Bottom* bottom = new Bottom("Bottom", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);
	//���۹� �޾ƿ���
	Door* door = new Door("Door", WINSIZEX / 2, 0, 10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);
	//�� �޾ƿ���
	Goal* goal = new Goal("goal", 100, 430);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Goal, goal);
	//UI
	Ui* ui = new Ui(PlayerState::BoomState, 100, 100, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);
	Ui* ui2 = new Ui(PlayerState::ClimbState, 100, 200, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui2);
	Ui* ui3 = new Ui(PlayerState::DigState, 100, 300, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui3);
	Ui* ui4 = new Ui(PlayerState::StopperState, 100, 400, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui4);
	Ui* ui5 = new Ui(PlayerState::UmbrellaState, 100, 500, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui5);

	//camera
	Camera* camera = new Camera();
	camera->SetX(100);
	camera->SetY(WINSIZEY / 2);
	//camera->SetTarget(player1);
	camera->ChangeMode(Camera::Mode::Free);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Camera, camera);

	ObjectManager::GetInstance()->Init();

	mIsSpecial = false;

}

void Scene2::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene2::Update()
{
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();

	SpecialFunc();
}

void Scene2::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}

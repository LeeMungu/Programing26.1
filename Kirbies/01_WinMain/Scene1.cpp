#include "pch.h"
#include "Scene1.h"
#include "Player.h"
#include "Bottom.h"
#include "BackGround.h"
#include "Special.h"
#include "Camera.h"
#include "SpecialApearEffect.h"
#include "GameEvent.h"
#include "Image.h"
#include "Mouse.h"
#include "Door.h"
#include "Goal.h"
void Scene1::Init()
{
	//player
	//Player* player1 = new Player("1", 200, 631);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player1);
	
	Mouse* mouse = new Mouse();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, mouse);

	BackGround* backGround = new BackGround("BackGround", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);
	

	Bottom* bottom = new Bottom("Bottom", WINSIZEX/2, WINSIZEY/2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);

	Door* door = new Door("Door",WINSIZEX/2,10,10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);

	Goal* goal = new Goal("goal",100,10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Goal, goal);

	

	//camera
	Camera* camera = new Camera();
	camera->SetX(100);
	camera->SetY(WINSIZEY / 2);
	//camera->SetTarget(player1);
	camera->ChangeMode(Camera::Mode::Free);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Camera,camera);

	ObjectManager::GetInstance()->Init();

	mIsSpecial = false;
}

void Scene1::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene1::Update()
{
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();

	if (mIsSpecial == false &&
		Input::GetInstance()->GetKeyDown(VK_TAB))
	{
		Camera* prevCamera = (Camera*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Camera, "Camera");
		prevCamera->ChangeMode(Camera::Mode::Follow);

		SpecialApearEffect* effect = new SpecialApearEffect("ApearEffect",0, -100,L"SpecialAppearEffect",9,3);
		effect->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect,effect);
		

		prevCamera->SetTarget(effect);

		mIsSpecial = true;
	}
	if (mIsSpecial == true &&
		ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Special).size() == NULL &&
		ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Effect).size() == NULL)
	{
		mIsSpecial = false;
		Camera* prevCamera = (Camera*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Camera, "Camera");
		prevCamera->ChangeMode(Camera::Mode::Free);
	}
}

void Scene1::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}

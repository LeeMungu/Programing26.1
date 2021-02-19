#include "pch.h"
#include "Scene1.h"
#include "Npc.h"
#include "Player.h"
#include "Bottom.h"
#include "BackGround.h"
#include "Camera.h"
#include "GameEvent.h"
#include "Weapon.h"
#include "Enemy.h"
void Scene1::Init()
{
	//player
	Player* player1 = new Player("1", 100, 631);
	Npc* Npc1 = new Npc("Npc", 200, 580);
	Enemy* enemy1 = new Enemy("enemy", 200, 580);
	enemy1->SetPlayerPtr(player1);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemey, enemy1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player1);
	
	BackGround* backGround = new BackGround("BackGround", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);

	Bottom* bottom = new Bottom("Bottom", WINSIZEX/2, WINSIZEY/2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);


	Weapon* weapon = new Weapon("w", 100, WINSIZEY / 2);
	weapon->SetPlayerPtr(player1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Weapon, weapon);

	//camera
	Camera* camera = new Camera();
	camera->SetX(100);
	camera->SetY(WINSIZEY / 2);
	camera->SetTarget(player1);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player,camera);

	ObjectManager::GetInstance()->Init();

	//GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.0f));
	//GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(player2));
	//GameEventManager::GetInstance()->PushEvent(new IDelayEvent(3.0f));
	//GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(player1));
}

void Scene1::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene1::Update()
{
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();
}

void Scene1::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}

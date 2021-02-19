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
#include "Image.h"
void Scene1::Init()
{
	//player
	Player* player1 = new Player("1", 200, 631);
	
	Enemy* enemy1 = new Enemy("enemy", 1000, 580);
	enemy1->SetPlayerPtr(player1);
	Enemy* enemy2 = new Enemy("enemy", 1000, 700);
	enemy2->SetPlayerPtr(player1);
	Enemy* enemy3 = new Enemy("enemy", 1000, 200);
	enemy3->SetPlayerPtr(player1);
	Enemy* enemy4 = new Enemy("enemy", 1000, 400);
	enemy4->SetPlayerPtr(player1);
	Enemy* enemy5 = new Enemy("enemy", 1000, 0);
	enemy5->SetPlayerPtr(player1);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemey, enemy1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemey, enemy2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemey, enemy3);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemey, enemy4);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemey, enemy5);
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


	mIsEvent = false;


	mTextBox = IMAGEMANAGER->FindImage(L"Speech");

	

}

void Scene1::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene1::Update()
{
	Player* player = (Player*)ObjectManager::GetInstance()->FindObject("1");
	if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemey).size() == NULL
		&& mIsEvent==false )
	{
		Npc* Npc1 = new Npc("2", 1000, 500);
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Npc, Npc1);
		ObjectManager::GetInstance()->FindObject("2")->Init();
		mIsEvent = true;


		if (mIsEvent)
		{
			GameEventManager::GetInstance()->PushEvent(new IDelayEvent(0.5f));
			GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(Npc1));
			GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.0f));
			GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(ObjectManager::GetInstance()->FindObject("1")));

			
			player->SetStop(true);
		}
	}
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();



}

void Scene1::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

	if (mIsEvent && ObjectManager::GetInstance()->FindObject("2") != nullptr)
	{
		//GameObject* temp = ObjectManager::GetInstance()->FindObject("C");
		CameraManager::GetInstance()->GetMainCamera()->FrameRender
		(hdc, mTextBox, ObjectManager::GetInstance()->FindObject("2")->GetX() - 50,
			ObjectManager::GetInstance()->FindObject("2")->GetY() - 80, 0, 0);
	
	}
}

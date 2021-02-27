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
#include "NPC.h"
#include "TextBox.h"

void Scene1::Init()
{	

	mTextBoxDeDeDe = IMAGEMANAGER->FindImage(L"TextBoxDeDeDe");
	mTextBoxKirby = IMAGEMANAGER->FindImage(L"TextBoxKirby");

	mImageGameClear = IMAGEMANAGER->FindImage(L"GameClear");
	mAnimationGameClear = new Animation();
	mAnimationGameClear->InitFrameByReverseLoop(0, 0, 16, 0);
	mAnimationGameClear->SetIsLoop(true);
	mAnimationGameClear->SetFrameUpdateTime(0.1f);

	mImageGameOver = IMAGEMANAGER->FindImage(L"GameOver");
	mAnimationGameOver = new Animation();
	mAnimationGameOver->InitFrameByStartEnd(0, 0, 8, 0, false);
	mAnimationGameOver->SetIsLoop(true);
	mAnimationGameOver->SetFrameUpdateTime(0.1f);
	

	Mouse* mouse = new Mouse("Mouse");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);

	BackGround* backGround = new BackGround("Background", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);
	

	Bottom* bottom = new Bottom("Bottom", WINSIZEX/2, WINSIZEY/2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);

	Door* door = new Door("Door",WINSIZEX/2,0,10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);

	Goal* goal = new Goal("goal", 1200, 1230);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Goal, goal);

	//NPC
	NPC* npc = new NPC("dedede", 1050, 1230);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::NPC, npc);


	Ui* ui = new Ui("BoomBtn", PlayerState::BoomState, 100, 100, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);
	Ui* ui2 = new Ui("ClimbBtn", PlayerState::ClimbState, 100, 200, 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui2);
	Ui* ui3 = new Ui("DigBtn", PlayerState::DigState, 100, 300, 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui3);
	Ui* ui4 = new Ui("StopperBtn", PlayerState::StopperState, 100, 400, 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui4);
	Ui* ui5 = new Ui("UmbrellaBtn", PlayerState::UmbrellaState, 100, 500, 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui5);

	//Ui
	CountingPlayerUI* countUI = new CountingPlayerUI("Scene1count",100, WINSIZEY - 100, 300);
	countUI->Init();
	UiManager::GetInstance()->AddUi(UiLayer::CountPlayerUi, countUI);


	//camera
	Camera* camera = new Camera();
	//camera->SetX(0);
	//camera->SetY(0);
	//camera->SetTarget(player1);//시작 타겟 설정
	//camera->ChangeMode(Camera::Mode::Free);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Camera, camera);

	//textBox
	TextBox* textBox = new TextBox("Text1", L"경찰이다 손들어!!!", 0.3f, TextType::Dedede);
	textBox->SetIsActive(false);
	TextBox* textBox1 = new TextBox("Text2", L"여기까지 온건가!!!", 0.3f, TextType::Kirby);
	textBox1->SetIsActive(false);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox1);


	//오브젝트 Init
	ObjectManager::GetInstance()->Init();

	//사운드
	SoundPlayer::GetInstance()->Play(L"Scene1BGM", SoundPlayer::GetInstance()->GetBgmvolum());
	SoundPlayer::GetInstance()->Stop(L"TitleBGM");

	//이벤트 초기화
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f)); //3초동안의텀
	//GameEventManager::GetInstance()->PushEvent(new IChangeCameraModeEvent(Camera::Mode::Follow));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(npc));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox1));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(5.f));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(door));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.f));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraModeEvent(Camera::Mode::Free));
	GameEventManager::GetInstance()->PushEvent(new IDoorController(door, true));


	//셋 초기화
	mIsGameClear = false;
	mIsGameOver = false;
	mGameOverTimer = 0.f;
}


void Scene1::Update()
{

	Door* door = (Door*)ObjectManager::GetInstance()->FindObject("Door");

	//클리어 시 변경 로딩씬
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
	//클리어조건
	CountingPlayerUI* tempUi = (CountingPlayerUI*)UiManager::GetInstance()->FindUi(UiLayer::CountPlayerUi, "Scene1count");
	if (tempUi != NULL && mIsGameClear == false)
	{
		if (tempUi->GetGoalPercent() > 50.f &&
			ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() == NULL)
		{
			mIsGameClear = true;
			mAnimationGameClear->Play();
		}
	}
	//게임오버 조건
	mGameOverTimer += Time::GetInstance()->DeltaTime();
	if (mGameOverTimer > 5)
	{
		if (tempUi != NULL && mIsGameOver == false && door->GetIsCreatedEnd())
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
	mAnimationGameClear->Update();

	//사운드 멈춰주기
	ObjectManager::GetInstance()->Update();

	GameEventManager::GetInstance()->Update();

	//CameraWalk();
	SpecialFunc();
}

void Scene1::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

	wstring str = L"스테이지1 구름구름동산.";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 3, str.c_str(), str.length());
	if (mIsGameClear == true)
	{
		mImageGameClear->FrameRender(hdc, (WINSIZEX -mImageGameClear->GetFrameWidth())/2, 
			(WINSIZEY-mImageGameClear->GetFrameHeight())/2,
			mAnimationGameClear->GetNowFrameX(),
			mAnimationGameClear->GetNowFrameY());
	}


	if (mIsGameOver == true)
	{
		mImageGameOver->FrameRender(hdc, 550, WINSIZEY / 2,
			mAnimationGameOver->GetNowFrameX(),
				mAnimationGameOver->GetNowFrameY());

		//mTextBoxDeDeDe->Render(hdc, 0, WINSIZEY / 2 + 40);

	}

	

}

void Scene1::mapRender(HDC map)
{
	ObjectManager::GetInstance()->mapRender(map);
}


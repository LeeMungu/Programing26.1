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
#include "NPC.h"
#include "TextBox.h"
#include "PowerBtn.h"
#include "ThrowBtn.h"
#include "Plate.h"
#include "Bugzzy.h"

void Scene5::Init()
{
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

	BackGround* backGround = new BackGround("Background5", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);


	Bottom* bottom = new Bottom("Bottom", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);

	Door* door = new Door("Door", 200, 700, 50);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);

	Goal* goal = new Goal("goal", 2300, 420);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Goal, goal);

	PowerBtn* powerbtn = new PowerBtn("powerbtn", 100, 1015);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, powerbtn);

	ThrowBtn* throwbtn = new ThrowBtn("throwbtn", 280, 1160);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, throwbtn);

	Plate* plate = new Plate("plate", WINSIZEX / 2 + 200, 760);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, plate);
	Plate* plate2 = new Plate("plate2", WINSIZEX / 2 + 200, 760);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, plate2);
	Plate* plate3 = new Plate("plate3", WINSIZEX / 2 + 200, 760);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, plate3);


	//NPC
	NPC* npc = new NPC("dedede", 2100, 440);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::NPC, npc);

	Ui* ui = new Ui("BoomBtn", PlayerState::BoomState, 100, 100, 50);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);
	Ui* ui2 = new Ui("ClimbBtn", PlayerState::ClimbState, 100, 200, 50);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui2);
	Ui* ui3 = new Ui("DigBtn", PlayerState::DigState, 100, 300, 5);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui3);
	Ui* ui4 = new Ui("StopperBtn", PlayerState::StopperState, 100, 400, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui4);
	Ui* ui5 = new Ui("UmbrellaBtn", PlayerState::UmbrellaState, 100, 500, 0);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui5);


	//Ui
	mCountUi = new CountingPlayerUI("Scene5count", 200, 50, 300);
	mCountUi->Init();
	UiManager::GetInstance()->AddUi(UiLayer::CountPlayerUi, mCountUi);


	//camera
	Camera* camera = new Camera();
	//camera->SetX(0);
	//camera->SetY(0);
	//camera->SetTarget(player1);//시작 타겟 설정
	//camera->ChangeMode(Camera::Mode::Free);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Camera, camera);

	//textBox
	TextBox* textBox = new TextBox("Text1", L"막다른 길인가...", 0.05f, TextType::Dedede);
	textBox->SetIsActive(false);
	TextBox* textBox1 = new TextBox("Text2", L"좋은 말로 할 때 해독약 내놔! 디디디 대왕!!!", 0.05f, TextType::Kirby);
	textBox1->SetIsActive(false);
	TextBox* textBox2 = new TextBox("Text3", L"내가 어떻게 이 계획을 만들었는데! 절대 안돼!", 0.05f, TextType::Dedede);
	textBox2->SetIsActive(false);
	TextBox* textBox3 = new TextBox("Text4", L"혹시 50명한테 동시에 맞아본 적 있어?", 0.05f, TextType::Kirby);
	textBox3->SetIsActive(false);
	TextBox* textBox4 = new TextBox("Text5", L"아..아니...", 0.05f, TextType::Dedede);
	textBox4->SetIsActive(false);
	TextBox* textBox5 = new TextBox("Text6", L"그럼 오늘이 그 날이야!!! 딱 기다려!!!", 0.05f, TextType::Kirby);
	textBox5->SetIsActive(false);
	TextBox* textBox6 = new TextBox("Text7", L"그래도 해독약은 못 줘어어어어!!!!!", 0.05f, TextType::Dedede);
	textBox6->SetIsActive(false);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox3);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox4);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox5);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox6);


	GameEventManager::GetInstance()->PushEvent(new IDoorController(door, false));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f)); //3초동안의텀
	//GameEventManager::GetInstance()->PushEvent(new IChangeCameraModeEvent(Camera::Mode::Follow));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(npc));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox1));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox2));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox3));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox4));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox5));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox6));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(3.f));
	GameEventManager::GetInstance()->PushEvent(new INpcController(npc, true, 0));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.f));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(door));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraModeEvent(Camera::Mode::Free));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.f));
	GameEventManager::GetInstance()->PushEvent(new IDoorController(door, true));

	GameEventManager::GetInstance()->PushEvent(new IChangeCameraModeEvent(Camera::Mode::Free));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.f));
	GameEventManager::GetInstance()->PushEvent(new IDoorController(door, true));
	ObjectManager::GetInstance()->Init();

	//사운드
	SoundPlayer::GetInstance()->Play(L"Scene5BGM", SoundPlayer::GetInstance()->GetBgmvolum());
	SoundPlayer::GetInstance()->Stop(L"Scene4BGM");

	//이벤트 업데이트
	GameEventManager::GetInstance()->Update();

	mIsGameClear = false;
	mIsGameOver = false;
	mGameOverTimer = 0.f;

	mIsSpecial = false;
	
}

void Scene5::Release()
{
	ObjectManager::GetInstance()->Release();
	SoundPlayer::GetInstance()->Stop();
	vector<Ui*> temps = UiManager::GetInstance()->GetUiList(UiLayer::CountPlayerUi);
	if (temps.size() != NULL)
	{
		for (int i = 0; i < temps.size(); i++)
		{
			temps[i]->SetIsActive(false);
		}
	}
	SafeDelete(mAnimationGameOver);
	SafeDelete(mAnimationGameClear);
}
void Scene5::Update()
{
	Door* door = (Door*)ObjectManager::GetInstance()->FindObject("Door");

	
	//클리어조건
	//CountingPlayerUI* tempUi = (CountingPlayerUI*)UiManager::GetInstance()->FindUi(UiLayer::CountPlayerUi, "Scene3count");
	if (mCountUi != NULL && mIsGameClear == false)
	{
		if (mCountUi->GetGoalPercent() >= 50.f &&
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
		if (mCountUi != NULL && mIsGameOver == false && door->GetIsCreatedEnd())
		{
			if (mCountUi->GetGoalPercent() < 50.f &&
				ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() == NULL)
			{
				mIsGameOver = true;
				mAnimationGameOver->Play();
			}
		}
	}
	PowerBtn* powerbtntemp = (PowerBtn*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Bottom, "powerbtn");
	if (powerbtntemp->GetIsBtnOn() == true)
	{
		Plate* platetemp = (Plate*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Bottom, "plate");
		platetemp->Init();
		
		Plate* platetemp3 = (Plate*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Bottom, "plate3");
		platetemp3->Init();

		platetemp->SetX(740);
		platetemp3->SetX(940);
	}
	ThrowBtn* thorwbtntemp = (ThrowBtn*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Bottom, "throwbtn");
	if (thorwbtntemp->GetIsBtnOn() == true && mIsTrigger == false)
	{
		Bugzzy* bugzzy = new Bugzzy("Bugzzy", 1400, 870);
		bugzzy->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::NPC, bugzzy);
		mIsTrigger = true;
	}


	mAnimationGameOver->Update();
	mAnimationGameClear->Update();

	SoundPlayer::GetInstance()->Stop(L"TitleBGM");
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();

	//클리어 시 변경 로딩씬
	if (mIsGameClear == true)
	{

		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"EndingScene");
		}
	}
	if (mIsGameOver == true)
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
		}
	}
	SpecialFunc();
	FollowPlayer();
}

void Scene5::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

	if (mIsGameClear == true)
	{
		mImageGameClear->FrameRender(hdc, (WINSIZEX - mImageGameClear->GetFrameWidth()) / 2,
			(WINSIZEY - mImageGameClear->GetFrameHeight()) / 2,
			mAnimationGameClear->GetNowFrameX(),
			mAnimationGameClear->GetNowFrameY());
	}


	if (mIsGameOver == true)
	{
		mImageGameOver->FrameRender(hdc, 550, WINSIZEY / 2,
			mAnimationGameOver->GetNowFrameX(),
			mAnimationGameOver->GetNowFrameY());
	}
}

void Scene5::mapRender(HDC map)
{
	ObjectManager::GetInstance()->mapRender(map);

	//지도 위 렉트
	HPEN newPen = CreatePen(PS_SOLID, 50, RGB(255, 255, 255));
	HPEN prevPen = (HPEN)SelectObject(map, newPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(map, myBrush);
	RenderRect(map, CameraManager::GetInstance()->GetMainCamera()->GetRect());
	SelectObject(map, oldBrush);
	DeleteObject(myBrush);
	SelectObject(map, prevPen);
	DeleteObject(newPen);
}
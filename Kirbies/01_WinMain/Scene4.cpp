#include "pch.h"
#include "Scene4.h"
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
#include "Trap.h"
#include "NPC.h"
#include "TextBox.h"

void Scene4::Init()
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

	BackGround* backGround = new BackGround("Background4", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);


	Bottom* bottom = new Bottom("Bottom", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);

	Door* door = new Door("Door", 2000, 50, 40);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);


	//Goal* goal = new Goal("goal", 2200, 50);
	Goal* goal = new Goal("goal", 480, 1400);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Goal, goal);

	//Trap
	Trap* trap1 = new Trap("trap1", 590, 680, 920, 50, PlayerState::TrapDieState);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, trap1);

	Trap* trap2 = new Trap("trap2", 1820, 340, 600, 50, PlayerState::TrapDieState);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, trap2);

	Trap* trap3 = new Trap("trap3", 0, 1430, WINSIZEX * 2, 100, PlayerState::TrapDieState);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, trap3);
	

	//NPC
	NPC* npc = new NPC("dedede", 490, 1400);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::NPC, npc);

	Ui* ui = new Ui("BoomBtn", PlayerState::BoomState, 100, 100, 10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);
	Ui* ui2 = new Ui("ClimbBtn", PlayerState::ClimbState, 100, 200, 50);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui2);
	Ui* ui3 = new Ui("DigBtn", PlayerState::DigState, 100, 300, 5);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui3);
	Ui* ui4 = new Ui("StopperBtn", PlayerState::StopperState, 100, 400, 10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui4);
	Ui* ui5 = new Ui("UmbrellaBtn", PlayerState::UmbrellaState, 100, 500, 99);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui5);

	//Ui
	mCountUi = new CountingPlayerUI("Scene4count", 200, 50, 300);
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
	TextBox* textBox = new TextBox("Text1", L"헥...헥...더워죽겠다!!!", 0.05f, TextType::Dedede);
	textBox->SetIsActive(false);
	TextBox* textBox1 = new TextBox("Text2", L"그만 쫓아와!!!", 0.05f, TextType::Dedede);
	textBox1->SetIsActive(false);
	TextBox* textBox2 = new TextBox("Text3", L"그거 알아? 디디디 대왕?", 0.05f, TextType::Kirby);
	textBox2->SetIsActive(false);
	TextBox* textBox3 = new TextBox("Text3", L"나는 지금 40배로 더워!!!!!", 0.05f, TextType::Kirby);
	textBox3->SetIsActive(false);
	TextBox* textBox4 = new TextBox("Text3", L".......!!!!!!!!", 0.05f, TextType::Dedede);
	textBox4->SetIsActive(false);
	TextBox* textBox5 = new TextBox("Text3", L"이제 얼마 안 남았다!!! 기다려라!!!", 0.05f, TextType::Kirby);
	textBox5->SetIsActive(false);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox3);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox4);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox5);

	ObjectManager::GetInstance()->Init();

	camera->SetX(2500);
	camera->SetY(WINSIZEY / 2);

	//사운드
	SoundPlayer::GetInstance()->Stop(L"Scene3BGM");
	SoundPlayer::GetInstance()->Play(L"Scene4BGM", SoundPlayer::GetInstance()->GetBgmvolum());

	//이벤트 초기화
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(0.5f)); //3초동안의텀
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
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(3.f));
	GameEventManager::GetInstance()->PushEvent(new INpcController(npc, true, 0));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.f));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(door));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraModeEvent(Camera::Mode::Free));
	//GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.f));
	GameEventManager::GetInstance()->PushEvent(new IDoorController(door, true));

	mIsGameClear = false;
	mIsGameOver = false;
	mGameOverTimer = 0.f;

	mIsSpecial = false;
}

void Scene4::Release()
{
	GameEventManager::GetInstance()->RemoveAllEvent();
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

void Scene4::Update()
{
	Door* door = (Door*)ObjectManager::GetInstance()->FindObject("Door");
	//클리어조건
	//CountingPlayerUI* tempUi = (CountingPlayerUI*)UiManager::GetInstance()->FindUi(UiLayer::CountPlayerUi, "Scene4count");
	if (mCountUi != NULL && mIsGameClear == false)
	{
		if (mCountUi->GetGoalPercent() >= 50.f &&
			ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() == NULL)
		{
			mIsGameClear = true;
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
				
			}
		}
	}

	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();

	//클리어 시 변경 로딩씬
	if (mIsGameClear == true)
	{
		mAnimationGameClear->Play();
		mAnimationGameClear->Update();
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"LoadingScene4to5");
		}
	}
	if (mIsGameOver == true)
	{
		mAnimationGameOver->Play();
		mAnimationGameOver->Update();
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
		}
	}
	SpecialFunc();
	FollowPlayer();
}

void Scene4::Render(HDC hdc)
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
		mImageGameOver->FrameRender(hdc, (WINSIZEX - mImageGameOver->GetFrameWidth()) / 2,
			(WINSIZEY - mImageGameOver->GetFrameHeight()) / 2,
			mAnimationGameOver->GetNowFrameX(),
			mAnimationGameOver->GetNowFrameY());
	}
}

void Scene4::mapRender(HDC map)
{
	ObjectManager::GetInstance()->mapRender(map);

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
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

	Door* door = new Door("Door",WINSIZEX/2,100,10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);

	//Goal* goal = new Goal("goal", WINSIZEX / 2+150, 170);
	Goal* goal = new Goal("goal", 1200, 1230);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Goal, goal);

	//NPC
	NPC* npc = new NPC("dedede", 1050, 1230);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::NPC, npc);


	Ui* ui = new Ui("BoomBtn", PlayerState::BoomState, 100, 100, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);
	Ui* ui2 = new Ui("ClimbBtn", PlayerState::ClimbState, 100, 200, 10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui2);
	Ui* ui3 = new Ui("DigBtn", PlayerState::DigState, 100, 300, 10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui3);
	Ui* ui4 = new Ui("StopperBtn", PlayerState::StopperState, 100, 400, 10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui4);
	Ui* ui5 = new Ui("UmbrellaBtn", PlayerState::UmbrellaState, 100, 500, 10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui5);

	//Ui
	mCountUi = new CountingPlayerUI("Scene1count",200, 50, 300);
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
	TextBox* textBox = new TextBox("Text1", L"의심도 없이 멍청하게 쌍둥이 열매를 먹다니!", 0.05f, TextType::Dedede);
	textBox->SetIsActive(false);
	TextBox* textBox1 = new TextBox("Text2", L"너희는 이제 끝도 없이 증식되어 온 우주가!", 0.05f, TextType::Dedede);
	textBox1->SetIsActive(false);
	TextBox* textBox2 = new TextBox("Text3", L"너희 커비로 가득찰 것이다!!!", 0.05f, TextType::Dedede);
	textBox2->SetIsActive(false);
	TextBox* textBox3 = new TextBox("Text4", L"(10명으로 증식됐나...)", 0.05f, TextType::Kirby);
	textBox3->SetIsActive(false);
	TextBox* textBox4 = new TextBox("Text5", L"거기서라! 디디디 대왕!!! 해독약을 내놔!", 0.05f, TextType::Kirby);
	textBox4->SetIsActive(false);
	TextBox* textBox5 = new TextBox("Text6", L"흥!!! 어림도 없지!!!", 0.05f, TextType::Dedede);
	textBox5->SetIsActive(false);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox3);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox4);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox5);

	//오브젝트 Init
	ObjectManager::GetInstance()->Init();

	//사운드
	SoundPlayer::GetInstance()->Play(L"Scene1BGM", SoundPlayer::GetInstance()->GetBgmvolum());
	SoundPlayer::GetInstance()->Stop(L"TitleBGM");

	//이벤트 초기화
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
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.f));
	GameEventManager::GetInstance()->PushEvent(new IDoorController(door, true));

	GameEventManager::GetInstance()->PushEvent(new IChangeCameraModeEvent(Camera::Mode::Free));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(0.1f));
	GameEventManager::GetInstance()->PushEvent(new IDoorController(door, true));

	//GameEventManager::GetInstance()->PushEvent(new IDelayEvent(5.0f));
	//GameEventManager::GetInstance()->PushEvent(new IDoorController(door, true));


	//셋 초기화

	GameEventManager::GetInstance()->Update();
	ObjectManager::GetInstance()->Update();
	mIsGameClear = false;
	mIsGameOver = false;
	mGameOverTimer = 0.f;

	mIsSpecial = false;
}

void Scene1::Release()
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

void Scene1::Update()
{

	Door* door = (Door*)ObjectManager::GetInstance()->FindObject("Door");

	
	//클리어조건
	//CountingPlayerUI* tempUi = (CountingPlayerUI*)UiManager::GetInstance()->FindUi(UiLayer::CountPlayerUi, "Scene1count");
	if (mCountUi != NULL && mIsGameClear == false)
	{
		if (mCountUi->GetGoalPercent() > 50.f &&
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

	mAnimationGameOver->Update();
	mAnimationGameClear->Update();

	//사운드 멈춰주기
	ObjectManager::GetInstance()->Update();

	GameEventManager::GetInstance()->Update();
	
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
	//CameraWalk();
	SpecialFunc();
	FollowPlayer();
}

void Scene1::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

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


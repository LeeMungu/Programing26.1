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
#include "CountingPlayerUI.h"
#include "DataUI.h"
#include "Animation.h"
#include "NPC.h"
#include "TextBox.h"
#include "Trap.h"

void Scene2::Init()
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

	BackGround* backGround = new BackGround("Background2", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);


	Bottom* bottom = new Bottom("Bottom", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);

	Door* door = new Door("Door", WINSIZEX / 2, 0, 20);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);

	Goal* goal = new Goal("goal", 1480, 1205);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Goal, goal);

	NPC* npc = new NPC("dedede", 1300, 1210);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::NPC, npc);


	Trap* trap2 = new Trap("trap1", 1960, 1050, 600, 50, PlayerState::TrapDieState);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, trap2);

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

	//Ui
	mCountUi = new CountingPlayerUI("Scene2count", 200, 50, 300);
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
	TextBox* textBox = new TextBox("Text1", L"벌써 20명으로 늘어났어!!!", 0.05f, TextType::Kirby);
	textBox->SetIsActive(false);
	TextBox* textBox1 = new TextBox("Text2", L"흥! 이제 곧 머지 않았다!!!", 0.05f, TextType::Dedede);
	textBox1->SetIsActive(false);
	TextBox* textBox2 = new TextBox("Text2", L"열심히 쫓아와보시지!!!", 0.05f, TextType::Dedede);
	textBox2->SetIsActive(false);
	

	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox2);

	ObjectManager::GetInstance()->Init();

	//사운드
	SoundPlayer::GetInstance()->Stop(L"Scene1BGM");
	SoundPlayer::GetInstance()->Play(L"Scene2BGM", SoundPlayer::GetInstance()->GetBgmvolum());

	//이벤트 초기화
	GameEventManager::GetInstance()->PushEvent(new IDoorController(door, false));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f)); //3초동안의텀
	//GameEventManager::GetInstance()->PushEvent(new IChangeCameraModeEvent(Camera::Mode::Follow));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(npc));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox1));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox2));
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

void Scene2::Release()
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

void Scene2::Update()
{
	Door* door = (Door*)ObjectManager::GetInstance()->FindObject("Door");
	
	//클리어조건
	//CountingPlayerUI* tempUi = (CountingPlayerUI*)UiManager::GetInstance()->FindUi(UiLayer::CountPlayerUi, "Scene2count");
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
			SceneManager::GetInstance()->LoadScene(L"LoadingScene2to3");
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

void Scene2::Render(HDC hdc)
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

void Scene2::mapRender(HDC map)
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


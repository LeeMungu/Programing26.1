#include "pch.h"
#include "Scene3.h"
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
#include "BunBottom.h"

void Scene3::Init()
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

	BackGround* backGround = new BackGround("Background3", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);
	

	Bottom* bottom = new Bottom("Bottom", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Bottom, bottom);

	//마그마 바닥
	BunBottom* bunBottom = new BunBottom("BunBottom", WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, bunBottom);



	Door* door = new Door("Door", WINSIZEX / 4, 300, 30);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);
	
	Goal* goal = new Goal("goal", WINSIZEX/2 *3 + 300, WINSIZEY*2 - 120);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Goal, goal);

	//NPC
	NPC* npc = new NPC("dedede", WINSIZEX / 2 * 3 + 300 - 150, WINSIZEY * 2 - 120);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::NPC, npc);
	
	Ui* ui = new Ui("BoomBtn", PlayerState::BoomState, 100, 100, 10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui);
	Ui* ui2 = new Ui("ClimbBtn", PlayerState::ClimbState, 100, 200, 35);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui2);
	Ui* ui3 = new Ui("DigBtn", PlayerState::DigState, 100, 300, 5);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui3);
	Ui* ui4 = new Ui("StopperBtn", PlayerState::StopperState, 100, 400, 5);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui4);
	Ui* ui5 = new Ui("UmbrellaBtn", PlayerState::UmbrellaState, 100, 500, 45);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, ui5);

	//Ui
	mCountUi = new CountingPlayerUI("Scene3count", 200, 50, 300);
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
	TextBox* textBox = new TextBox("Text1", L"설마 해독약이 내 손에 있을거라 생각하는거냐!!!", 0.05f, TextType::Dedede);
	textBox->SetIsActive(false);
	TextBox* textBox1 = new TextBox("Text2", L"앗....없어?", 0.05f, TextType::Kirby);
	textBox1->SetIsActive(false);
	TextBox* textBox2 = new TextBox("Text3", L"당연히 나한테 있지롱!!! 우하하하하하!!!!!", 0.05f, TextType::Dedede);
	textBox2->SetIsActive(false);
	TextBox* textBox3 = new TextBox("Text3", L"...............", 0.05f, TextType::Kirby);
	textBox3->SetIsActive(false);
	TextBox* textBox4 = new TextBox("Text4", L"거기 안 서?!!!!!!", 0.05f, TextType::Kirby);
	textBox4->SetIsActive(false);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox3);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox4);

	ObjectManager::GetInstance()->Init();

	GameEventManager::GetInstance()->PushEvent(new IDoorController(door, false));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f)); //3초동안의텀
	//GameEventManager::GetInstance()->PushEvent(new IChangeCameraModeEvent(Camera::Mode::Follow));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(npc));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox1));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox2));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox3));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(textBox4));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(3.f));
	GameEventManager::GetInstance()->PushEvent(new INpcController(npc, true, 0));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.f));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(door));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraModeEvent(Camera::Mode::Free));
	//GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.f));
	GameEventManager::GetInstance()->PushEvent(new IDoorController(door, true));


	//사운드
	SoundPlayer::GetInstance()->Stop(L"TitleBGM");
	SoundPlayer::GetInstance()->Stop(L"Scene2BGM");
	SoundPlayer::GetInstance()->Play(L"Scene3BGM", SoundPlayer::GetInstance()->GetBgmvolum());

	//셋 초기화
	mIsGameClear = false;
	mIsGameOver = false;
	mGameOverTimer = 0.f;

	mIsSpecial = false;
}

void Scene3::Release()
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
void Scene3::Update()
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
	//이벤트 업데이트
	GameEventManager::GetInstance()->Update();

	//클리어 시 변경 로딩씬
	if (mIsGameClear == true)
	{
		mAnimationGameClear->Play();
		mAnimationGameClear->Update();

		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"LoadingScene3to4");
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

void Scene3::Render(HDC hdc)
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

void Scene3::mapRender(HDC map)
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
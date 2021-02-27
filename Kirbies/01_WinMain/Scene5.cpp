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

	Door* door = new Door("Door", WINSIZEX / 2, 0, 10);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Door, door);

	Goal* goal = new Goal("goal", WINSIZEX / 2 + 300, 0);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Goal, goal);

	//NPC
	NPC* npc = new NPC("dedede", 490, 1400);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::NPC, npc);

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
	CountingPlayerUI* countUI = new CountingPlayerUI("Scene5count", 200, 50, 300);
	countUI->Init();
	UiManager::GetInstance()->AddUi(UiLayer::CountPlayerUi, countUI);


	//camera
	Camera* camera = new Camera();
	//camera->SetX(0);
	//camera->SetY(0);
	//camera->SetTarget(player1);//���� Ÿ�� ����
	//camera->ChangeMode(Camera::Mode::Free);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Camera, camera);

	//textBox
	TextBox* textBox = new TextBox("Text1", L"���ٸ� ���ΰ�...", 0.05f, TextType::Dedede);
	textBox->SetIsActive(false);
	TextBox* textBox1 = new TextBox("Text2", L"���� ���� �� �� �ص��� ���� ���� ���...", 0.05f, TextType::Kirby);
	textBox1->SetIsActive(false);
	TextBox* textBox2 = new TextBox("Text3", L"������� �� �� ������ ����!!!", 0.05f, TextType::Dedede);
	textBox2->SetIsActive(false);
	TextBox* textBox3 = new TextBox("Text4", L"Ȥ�� 50������ ���ÿ� �¾ƺ� �� �־�?", 0.05f, TextType::Kirby);
	textBox3->SetIsActive(false);
	TextBox* textBox4 = new TextBox("Text5", L"��..�ƴ�...", 0.05f, TextType::Dedede);
	textBox4->SetIsActive(false);
	TextBox* textBox5 = new TextBox("Text6", L"�׷� ������ �� ���̾�!!! �� ��ٷ�!!!", 0.05f, TextType::Kirby);
	textBox5->SetIsActive(false);
	TextBox* textBox6 = new TextBox("Text7", L"�׷��� �ص����� �� ������!!!!!", 0.05f, TextType::Dedede);
	textBox6->SetIsActive(false);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox3);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox4);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox5);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, textBox6);

	ObjectManager::GetInstance()->Init();

	//����
	SoundPlayer::GetInstance()->Play(L"Scene5BGM", SoundPlayer::GetInstance()->GetBgmvolum());
	SoundPlayer::GetInstance()->Stop(L"Scene4BGM");

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

	//Ŭ���� �� ���� �ε���
	if (mIsGameClear == true)
	{

		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"LoadingScene3to4");
		}
	}
	if (mIsGameOver == true)
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			SceneManager::GetInstance()->LoadScene(L"MainScene");
		}
	}
	//Ŭ��������
	CountingPlayerUI* tempUi = (CountingPlayerUI*)UiManager::GetInstance()->FindUi(UiLayer::CountPlayerUi, "Scene3count");
	if (tempUi != NULL && mIsGameClear == false)
	{
		if (tempUi->GetGoalPercent() > 50.f &&
			ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() == NULL)
		{
			mIsGameClear = true;
			mAnimationGameClear->Play();
		}
	}
	//���ӿ��� ����
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

	SoundPlayer::GetInstance()->Stop(L"TitleBGM");
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();
	SpecialFunc();
}

void Scene5::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);

	wstring str = L"��������5 ǮǮ����.";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 3, str.c_str(), str.length());

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
}
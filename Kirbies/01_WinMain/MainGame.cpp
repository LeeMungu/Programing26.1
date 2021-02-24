#include "pch.h"
#include "MainGame.h"

#include "Image.h"

#include "Scene1.h"
#include "Scene2.h"
#include "LoadingScene.h"
#include "MainScene.h"
/*
Scene : �������� ������ ���̶�� ��
*/

/*
Initialize : �ʱ�ȭ
������ ������ �����ϱ� ���� �ʱ�ȭ �� ������ ���⼭ ����
���� �����ϱ� ���� �� �ѹ��� ����Ǵ� �Լ�
*/
void MainGame::Init()
{
	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);
	mMapBuffer = new Image();
	mMapBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	//�̹��� �ε�
	//IMAGEMANAGER->LoadFromFile(L"LoadingImage", Resources(L"LoadingImage.bmp"), 1280, 720, true);
	IMAGEMANAGER->LoadFromFile(L"LoadingBar1", Resources(L"LoadingBar1.bmp"), 1116, 66, true);
	IMAGEMANAGER->LoadFromFile(L"LoadingBar2", Resources(L"LoadingBar2.bmp"), 1100, 50, false);
	IMAGEMANAGER->LoadFromFile(L"LoadingBackGround1", Resources(L"loading_background1.bmp"), 1280, 720, false);
	IMAGEMANAGER->LoadFromFile(L"LoadingBackGround2", Resources(L"loading_background2.bmp"), 1280, 720, false);
	IMAGEMANAGER->LoadFromFile(L"LoadingBackGround3", Resources(L"loading_background3.bmp"), 1280, 720, false);
	IMAGEMANAGER->LoadFromFile(L"MainBackGround", Resources(L"MainBackGround.bmp"), 1280, 720,true);
	IMAGEMANAGER->LoadFromFile(L"MainImage", Resources(L"MainImage.bmp"), 1280, 720, true);
	IMAGEMANAGER->LoadFromFile(L"MainTitle1", Resources(L"MainTitle1.bmp"), 1280, 720, true);
	IMAGEMANAGER->LoadFromFile(L"MainTitle2", Resources(L"MainTitle2.bmp"), 1280, 720, true);
	IMAGEMANAGER->LoadFromFile(L"MainTitle3", Resources(L"MainTitle3.bmp"), 1280, 720, true);
	IMAGEMANAGER->LoadFromFile(L"MainTitle4", Resources(L"MainTitle4.bmp"), 1280, 720, true);
	SoundPlayer::GetInstance()->LoadFromFile(L"TitleBGM", Resources(L"KirbysDreamland3SandCanyon1.mp3"), true);

	//���ε�
	SceneManager::GetInstance()->AddScene(L"MainScene", new MainScene);
	SceneManager::GetInstance()->AddScene(L"Scene1", new Scene1);
	SceneManager::GetInstance()->AddScene(L"LoadingScene", new LoadingScene);
	
	//ó���� ����ȭ��
	SceneManager::GetInstance()->LoadScene(L"MainScene");
}

/*
Release : �޸� ������ �� �ҷ��ִ� �Լ�
����Ƽ��� OnDestroy
�ش� Ŭ���� �ν��Ͻ��� �޸� ���� �� �� �� �ѹ� ȣ�����ִ� �༮
*/
void MainGame::Release()
{
	Random::ReleaseInstance();	//�̱��� �ν��Ͻ� ����

	SafeDelete(mBackBuffer);
	SafeDelete(mMapBuffer);

}

/*
Update : �� ������ ����Ǵ� �Լ�, ���⼭ ���� ó�� �Ѵ�.
*/
void MainGame::Update()
{
	SceneManager::GetInstance()->Update();
}

/*
Render : �� ������ ����Ǵ� �Լ�, Update�� ������ Render�� ����ȴ�.
ȭ�鿡 �׷��ִ� �͵��� ���� ���⼭ ó��

�Ű����� hdc : ������ â�� HDC�� ����
*/
void MainGame::Render(HDC hdc)
{
	//������� HDC �����´�
	HDC backDC = mBackBuffer->GetHDC();


	//HDC ������ Ư�� ������ �о������ �༮
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		SceneManager::GetInstance()->Render(backDC);

		RenderTime(backDC);

	}
	//====================================================
	//�ĸ���� ������ ������ â�� ��� ����

	mBackBuffer->Render(hdc, 0, 0);

}

void MainGame::mapRender(HDC map)
{
	//������� HDC �����´�
	HDC mapDC = mMapBuffer->GetHDC();

	//HDC ������ Ư�� ������ �о������ �༮
	PatBlt(mapDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		SceneManager::GetInstance()->mapRender(mapDC);
	}
	//====================================================
	//�ĸ���� ������ ������ â�� ��� ����
	mMapBuffer->ScaleRender(map, WINSIZEX - 100, WINSIZEY - 100, WINSIZEX / 4, WINSIZEY / 4);
}

void MainGame::RenderTime(HDC hdc)
{
	float worldTime = Time::GetInstance()->GetWorldTime();
	float deltaTime = Time::GetInstance()->DeltaTime();
	ULONG fps = Time::GetInstance()->GetmFrameRate();
	wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	wstring strDeltaTime = L"DeltaTime : " + to_wstring(deltaTime);
	wstring strFPS = L"FPS : " + to_wstring(fps);

	TextOut(hdc, 10, 10, strWorldTime.c_str(), strWorldTime.length());
	TextOut(hdc, 10, 25, strDeltaTime.c_str(), strDeltaTime.length());
	TextOut(hdc, 10, 40, strFPS.c_str(), strFPS.length());
}


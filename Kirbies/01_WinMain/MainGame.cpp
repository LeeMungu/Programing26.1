#include "pch.h"
#include "MainGame.h"

#include "Image.h"

#include "Scene1.h"
#include "Scene2.h"
#include "LoadingScene.h"
#include "MainScene.h"
/*
Scene : 스테이지 단위를 씬이라고 함
*/

/*
Initialize : 초기화
앞으로 게임을 시작하기 전에 초기화 및 생성은 여기서 진행
게임 시작하기 전에 딱 한번만 실행되는 함수
*/
void MainGame::Init()
{
	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);
	mMapBuffer = new Image();
	mMapBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	//이미지 로드
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

	//씬로드
	SceneManager::GetInstance()->AddScene(L"MainScene", new MainScene);
	SceneManager::GetInstance()->AddScene(L"Scene1", new Scene1);
	SceneManager::GetInstance()->AddScene(L"LoadingScene", new LoadingScene);
	
	//처음은 메인화면
	SceneManager::GetInstance()->LoadScene(L"MainScene");
}

/*
Release : 메모리 해제할 때 불러주는 함수
유니티라면 OnDestroy
해당 클래스 인스턴스가 메모리 해제 될 때 단 한번 호출해주는 녀석
*/
void MainGame::Release()
{
	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제

	SafeDelete(mBackBuffer);
	SafeDelete(mMapBuffer);

}

/*
Update : 매 프레임 실행되는 함수, 여기서 연산 처리 한다.
*/
void MainGame::Update()
{
	SceneManager::GetInstance()->Update();
}

/*
Render : 매 프레임 실행되는 함수, Update가 끝나고 Render가 실행된다.
화면에 그려주는 것들은 전부 여기서 처리

매개변수 hdc : 윈도우 창의 HDC가 들어옴
*/
void MainGame::Render(HDC hdc)
{
	//백버퍼의 HDC 가져온다
	HDC backDC = mBackBuffer->GetHDC();


	//HDC 영역을 특정 색으로 밀어버리는 녀석
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		SceneManager::GetInstance()->Render(backDC);

		RenderTime(backDC);

	}
	//====================================================
	//후면버퍼 내용을 윈도우 창에 고속 복사

	mBackBuffer->Render(hdc, 0, 0);

}

void MainGame::mapRender(HDC map)
{
	//백버퍼의 HDC 가져온다
	HDC mapDC = mMapBuffer->GetHDC();

	//HDC 영역을 특정 색으로 밀어버리는 녀석
	PatBlt(mapDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		SceneManager::GetInstance()->mapRender(mapDC);
	}
	//====================================================
	//후면버퍼 내용을 윈도우 창에 고속 복사
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


#include "pch.h"
#include "MainGame.h"

#include "Image.h"

#include "Scene1.h"
#include "Scene2.h"
#include "LoadingScene.h"
/*
Scene : 스테이지 단위를 씬이라고 함
*/
//ㄴ릴ㄴ미ㅏㅣㄹㄴ어ㅣㄹ넌리ㅓ

//이 아래 전부 거짓말중입니다.
// 이것은 이지훈의 확인용 주석입니다 ㅋㅋㄹㅃㅃ

// 이지훈의 작업물
// 이지훈의 작업물2

// 이문구의 작업
// 이문구의 작업2
/*
Initialize : 초기화
앞으로 게임을 시작하기 전에 초기화 및 생성은 여기서 진행
게임 시작하기 전에 딱 한번만 실행되는 함수
*/
void MainGame::Init()
{
	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	//이미지 로드
	IMAGEMANAGER->LoadFromFile(L"LoadingImage", Resources(L"LemmingsLoading.bmp"), 1280, 853, true);
	IMAGEMANAGER->LoadFromFile(L"LoadingBar1", Resources(L"LoadingBar1.bmp"), 1100, 50, true);
	IMAGEMANAGER->LoadFromFile(L"LoadingBar2", Resources(L"LoadingBar2.bmp"), 1100, 50, true);

	//씬 로드
	SceneManager::GetInstance()->AddScene(L"LoadingScene", new LoadingScene);
	SceneManager::GetInstance()->AddScene(L"Scene1", new Scene1);
	SceneManager::GetInstance()->AddScene(L"Scene2", new Scene2);

	SceneManager::GetInstance()->LoadScene(L"LoadingScene");
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

}

/*
Update : 매 프레임 실행되는 함수, 여기서 연산 처리 한다.
*/
void MainGame::Update()
{
	SceneManager::GetInstance()->Update();

	if (Input::GetInstance()->GetKeyDown('A'))
	{
		SceneManager::GetInstance()->LoadScene(L"Scene1");
	}
	if (Input::GetInstance()->GetKeyDown('S'))
	{
		SceneManager::GetInstance()->LoadScene(L"Scene2");
	}
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


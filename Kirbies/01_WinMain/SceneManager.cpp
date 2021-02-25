#include "pch.h"
#include "SceneManager.h"

#include "Scene.h"
#include "LoadingScene.h"
#include "ConfigUi.h"
SceneManager::SceneManager()
	:mCurrentScene(nullptr),mLoadingThread(nullptr),mTargetScene(nullptr),mLoadingScene(nullptr),
mIsLoadingEnd(false), mIsConfig(false){}

SceneManager::~SceneManager()
{
	SceneIter iter = mSceneList.begin();
	for (; iter != mSceneList.end(); ++iter)
	{
		//iter->second->Release();
		SafeDelete(iter->second);
	}
}

void SceneManager::Update()
{
	if (mIsConfig == false)
	{
		if (mCurrentScene != nullptr)
			mCurrentScene->Update();

		if (Input::GetInstance()->GetKeyDown(VK_ESCAPE))
		{
			mIsConfig = true;
			//���⼭ ���Ǳ�(�Ŵ�) �����ֱ�
			ConfigUi* Menu = new ConfigUi("Menu");
			Menu->Init();
			UiManager::GetInstance()->AddUi(UiLayer::Object, Menu);
		}
	}
	else if (mIsConfig == true)
	{
		if (Input::GetInstance()->GetKeyDown(VK_ESCAPE))
		{
			mIsConfig = false;
			ConfigUi* temp = (ConfigUi*)UiManager::GetInstance()->FindUi(UiLayer::Object, "Menu");
			temp->SetIsDestroy(true);
		}
	}
}

void SceneManager::Render(HDC hdc)
{
	if (mCurrentScene != nullptr)
		mCurrentScene->Render(hdc);
}

void SceneManager::mapRender(HDC map)
{
	if (mCurrentScene != nullptr)
		mCurrentScene->mapRender(map);
}

void SceneManager::AddScene(const wstring& sceneName,Scene * scene)
{
	SceneIter iter = mSceneList.find(sceneName);
	//�̹� �ش��̸��� �����Ͱ� �ʾȿ� �ִ�
	if (iter != mSceneList.end())
		return;

	mSceneList.insert(make_pair(sceneName, scene));
}

void SceneManager::LoadScene(const wstring & sceneName)
{
	SceneIter iter = mSceneList.find(sceneName);
	//��ã������ return (���ư���)
	if (iter == mSceneList.end())
		return;

	if (mCurrentScene == iter->second)
		return;
	
	Scene* targetScene = iter->second;

	if (mCurrentScene)
		mCurrentScene->Release();

	targetScene->Init();

	mCurrentScene = targetScene;
}

/*
�� �����δ� ���� �츮�� �Ⱦ��� - LMG
*/
//�� �����ؼ� ���. �� �𸣰� ���� ���� ������ �и�
void SceneManager::LoadScene(const wstring & targetSceneName, const wstring & loadingSceneName)
{
	SceneIter iter = mSceneList.find(targetSceneName);
	if (iter != mSceneList.end())
		mTargetScene = iter->second;

	iter = mSceneList.find(loadingSceneName);
	if (iter != mSceneList.end())
		mLoadingScene = iter->second;

	if (mTargetScene == nullptr || mLoadingScene == nullptr ||
		mTargetScene == mCurrentScene || mLoadingScene == mCurrentScene)
	{
		mTargetScene = nullptr;
		mLoadingScene = nullptr;
		return;
	}

	function<void(void)> threadFunc = bind(&SceneManager::LoadingThread, this);
	//������� �޸� �Ҵ����ִ� �������� �ٷ� ���� �����Ѵ�.
	mLoadingThread = new thread(threadFunc);
}


void SceneManager::DeleteMenu()
{
	mIsConfig = false;
}


void SceneManager::LoadingThread()
{
	//����� ����!! ã�ƺ�!

	Scene* prevScene = mCurrentScene;
	
	mCurrentScene = mLoadingScene;
	mCurrentScene->Init();

	prevScene->Release();

	mTargetScene->Init();
	
	mCurrentScene = mTargetScene;


	mLoadingScene->Release();

	mTargetScene = nullptr;
	mLoadingScene = nullptr;
	mIsLoadingEnd = true;
}

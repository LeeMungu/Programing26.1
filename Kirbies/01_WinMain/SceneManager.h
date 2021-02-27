#pragma once
#include <thread>
class Scene;
class ConfigUi;
class SceneManager
{
	Singleton(SceneManager)
private:
	typedef map<wstring, Scene*>::iterator SceneIter;
	map<wstring, Scene*> mSceneList;
	Scene* mCurrentScene;						//���� ��

	class Scene* mTargetScene;
	class Scene* mLoadingScene;
	thread* mLoadingThread;
	bool mIsLoadingEnd;
	//true �϶� �� �Ͻ�����, �Ŵ� ȣ��
	bool mIsConfig;
	bool mIsActive;
	ConfigUi* Menu;
public:
	SceneManager();
	~SceneManager();

	void Update();
	void Render(HDC hdc);
	void mapRender(HDC map);

	void AddScene(const wstring& sceneName,Scene* scene);
	//�ε����� �ε��ϴ� �Լ�
	void LoadScene(const wstring& sceneName);
	void LoadScene(const wstring& targetSceneName, const wstring& loadingSceneName);

	void DeleteMenu();
	void SetIsconfig(bool config) { mIsConfig = config; }

	void SetIsActive(bool active){ mIsActive = active; }
	bool GetIsActive() { return mIsActive; }

private:
	//�����忡 ���� ���� �Լ� : �� ������ �����尡 �۾� ó�� �� �Լ�
	void LoadingThread();
};


#pragma once

/*
씬이 넘어가도 데이터를 가지고 있는 친구
Ui관리 및 ObjectManager 저장

*/

enum class UiLayer : int
{
	Score = 0,
	Stage = 1,
	Time = 2,
	Object =3,
	End
};


class UiManager
{
public:
	//ui메니져==게임의 데이터를 가지고 있는 친구
	static UiManager* GetInstance()
	{
		static UiManager instance;
		return &instance;
	}
private:

	typedef map<ObjectLayer, vector<class GameObject*>>::iterator ObjectIter;
	map<ObjectLayer, vector <class GameObject*>> mObjectList;
	
	typedef map<UiLayer, vector<class Ui*>>::iterator UiIter;
	map<UiLayer, vector<class Ui*>> mUiList;

public:
	UiManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddUi(UiLayer layer, class Ui* object);
	class Ui* FindUi(const string& name);
	class Ui* FindUi(UiLayer layer, const string& name);
	vector<class Ui*> FindUis(const string& name);
	vector<class Ui*> FindUis(UiLayer layer, const string& name);
	vector<class Ui*> GetUiList(UiLayer layer);

	map<ObjectLayer,vector< class GameObject*>> GetObjectList(ObjectLayer layer) { return mObjectList; };
	void SetObjectList(map<ObjectLayer, vector< class GameObject*>> objectManager) 
	{ mObjectList = objectManager; };
};


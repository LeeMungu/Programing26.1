#pragma once

/*
���� �Ѿ�� �����͸� ������ �ִ� ģ��
Ui���� �� ObjectManager ����
������Ʈ�޴����ʹ� �ٸ��� ���� �Ѿ�� ���� ������ ���� �ϰ� �; ���� �༮
*/

enum class UiLayer : int
{
	DataUI = 0,
	Object = 1,
	End
};


class UiManager
{
public:
	//ui�޴���==������ �����͸� ������ �ִ� ģ��
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

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

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


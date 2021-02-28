#pragma once

/*
## ObjectManager ##
GameObject 관리하는 클래스
*/

//enum (열거자) : 정수를 다른 이름으로 표현하는 것
enum class ObjectLayer : int
{
	Background = 0,
	Goal = 1,
	Bottom = 2,
	Door = 3,
	Player = 4,
	UI = 5,
	SpecialEffect = 6,
	Special = 7,
	Effect = 8,
	Camera=9,
	StopperObject = 10,
	DigObject = 11,
	Mouse =12,
	NPC =13,
	TextBox =14,
	End
};

class ObjectManager
{
	Singleton(ObjectManager)
private:
	typedef map<ObjectLayer, vector<class GameObject*>>::iterator ObjectIter;
	map<ObjectLayer, vector<class GameObject*>> mObjectList;
public:
	ObjectManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void mapRender(HDC map);

	void AddObject(ObjectLayer layer, class GameObject* object);
	class GameObject* FindObject(const string& name);
	class GameObject* FindObject(ObjectLayer layer, const string& name);
	vector<class GameObject*> FindObjects(const string& name);
	vector<class GameObject*> FindObjects(ObjectLayer layer, const string& name);
	vector<class GameObject*> GetObjectList(ObjectLayer layer);
};


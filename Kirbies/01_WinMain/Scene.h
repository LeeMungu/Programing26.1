#pragma once
class Scene
{
protected:
	bool mIsSpecial;

public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void mapRender(HDC map) {};

	void SpecialFunc();
};


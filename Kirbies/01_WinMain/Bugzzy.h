#pragma once
#include "GameObject.h"
class Animation;
class Bugzzy : public GameObject
{
	Image* mImage;
	int mFrameX;
	Animation* mAnimation;
	bool mFireTrigger;
public:
	Bugzzy(const string& name, float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;
};


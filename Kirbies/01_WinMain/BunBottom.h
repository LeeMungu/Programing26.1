#pragma once
#include "GameObject.h"
class Image;
class Animation;
class BunBottom : public GameObject
{
	Animation* mAnimation;
	Image* mImage;
public:
	BunBottom(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;

	Image* GetImage()const { return mImage; }
};


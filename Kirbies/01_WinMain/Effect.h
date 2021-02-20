#pragma once
#include "GameObject.h"

class Animation;
class Image;
class Effect : public GameObject
{
protected:
	Image* mImage;
	Animation* mCurrentAnimation;
public:
	Effect(string name, float x, float y, wstring imagekey);
	
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
};


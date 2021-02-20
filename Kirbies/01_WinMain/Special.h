#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Special : public GameObject
{
	Image* mImage;
	Animation* mCurrantAnimation;
	Animation* mApearAnimation;
	Animation* mAttackAnimation;
	Animation* mEndAnimation;
public:
	Special(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};


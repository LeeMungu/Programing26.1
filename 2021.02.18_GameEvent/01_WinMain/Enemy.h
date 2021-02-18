#pragma once
#include "GameObject.h"

class Image;
class Animation;

class Enemy : public GameObject
{
	Image* mImage;
	Animation* mIdleAnimation;
	Animation* mRunAnimation;
	Animation* mAttackAnimation;
	Animation* mCurrentAnimation;


public:
	Enemy(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};


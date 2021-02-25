#pragma once
#include "GameObject.h"
class Image;
class BoomRect : public GameObject
{
	Image* mImage;
	float mAngle;
	float mSpeed;
	float mGravity;

public:
	BoomRect(float x, float y);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};


#pragma once

#include "GameObject.h"

class DigPoint : public GameObject
{
	float mRadius;
public:
	DigPoint(HDC hdc, int x, int y, float radius);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};


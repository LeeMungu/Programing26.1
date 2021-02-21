#pragma once
#include "GameObject.h"

class StopperObject : public GameObject
{
public:
	StopperObject(const float x, float y, float sizeX, float sizeY);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};


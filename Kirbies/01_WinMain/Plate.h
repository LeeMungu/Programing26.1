#pragma once
#include "GameObject.h"
class Plate : public GameObject
{
	Image* mImage;
	float mTimer;
public:
	Plate(const string& name, float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;
};


#pragma once
#include "GameObject.h"

class Bottom : public GameObject
{
	class Image* mImage;
public:
	Bottom(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};


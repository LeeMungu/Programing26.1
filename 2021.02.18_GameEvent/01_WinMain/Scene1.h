#pragma once
#include "Scene.h"
class Scene1 : public Scene
{
	bool mIsEvent;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};


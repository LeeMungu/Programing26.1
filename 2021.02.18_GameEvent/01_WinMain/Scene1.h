#pragma once
#include "Scene.h"
class Scene1 : public Scene
{
	bool mIsEvent;
	Image* mTextBox;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};


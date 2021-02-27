#pragma once
#include "Scene.h"

class Image;
class SceneEnding : public Scene
{
	Image* mImage;
public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
};


#pragma once
#include "Scene.h"

class Image;
class MainScene : public Scene
{
	bool mIsLoadEnd;
	float mTimeSet;
private:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};


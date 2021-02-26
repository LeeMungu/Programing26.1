#pragma once
#include "Scene.h"

class Image;
class Animation;
class Scene4 : public Scene
{

	Image* mImageGameOver;
	Animation* mAnimationGameOver;
	float mGameOverTimer;

public:
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;

	void SetIsSpecial(bool isSpecial) { mIsSpecial = isSpecial; }
};


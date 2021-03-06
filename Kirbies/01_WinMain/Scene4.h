#pragma once
#include "Scene.h"

class Image;
class Animation;
class CountingPlayerUI;
class Scene4 : public Scene
{

	Image* mImageGameClear;
	Image* mImageGameOver;

	Image* mTextBoxDeDeDe;
	Image* mTextBoxKirby;

	Animation* mAnimationGameOver;
	Animation* mAnimationGameClear;
	float mGameOverTimer;
	CountingPlayerUI* mCountUi;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;

	void SetIsSpecial(bool isSpecial) { mIsSpecial = isSpecial; }
};


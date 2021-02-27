#pragma once
#include "Scene.h"

class Image;
class Animation;
class CountingPlayerUI;
class Scene1 : public Scene
{
	Image* mImageGameClear;
	Image* mImageGameOver;
	Animation* mAnimationGameOver;
	Animation* mAnimationGameClear;

	Image* mTextBoxDeDeDe;
	Image* mTextBoxKirby;

	CountingPlayerUI* mCountUi;

	float mGameOverTimer;
	float mGameClearTimer;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;

	void SetIsSpecial(bool isSpecial) { mIsSpecial = isSpecial; }

	
};


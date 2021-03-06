#pragma once
#include "State.h"


class Bottom;
class Image;
class Animation;
class State;
class Umbrella : public State
{
	Bottom* mBottom;
	Image* mImage;
	Animation* mLeftAnimation;
	Animation* mLeftStartAnimation;
	Animation* mRightStartAnimation;
	Animation* mRightAnimation;
	Animation* mCurrentAnimation;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void mapRender(HDC map)override;
};


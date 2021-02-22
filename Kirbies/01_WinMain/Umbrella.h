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
	Animation* mRightAnimation;
	Animation* mCurrentAnimation;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};


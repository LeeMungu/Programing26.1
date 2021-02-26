#pragma once
#include "State.h"

#include "GameObject.h"
#include "Player.h"
#include "Bottom.h"

class State;
class Fall : public State
{
	Bottom* mBottom;
	Image* mFallKirby;
	Image* mFallDeadKirby;
	Animation* mLeftAnimation;
	Animation* mRightAnimation;
	Animation* mLeftFallDeadAnimation;
	Animation* mRightFallDeadAnimation;
	Animation* mCurrentAnimation;



public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void mapRender(HDC map)override;



};


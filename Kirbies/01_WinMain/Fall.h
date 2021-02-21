#pragma once
#include "State.h"

#include "GameObject.h"
#include "Player.h"
#include "Bottom.h"

class State;
class Fall : public State
{
	Player*  mPlayer;
	Bottom* mBottom;
	Image* mFallKirby;
	Animation* mLeftAnimation;
	Animation* mRightAnimation;
	Animation* mCurrentAnimation;

	float gravity;


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);




};


#pragma once
#include "State.h"

#include "GameObject.h"
#include "Player.h"
#include "Bottom.h"

class State;
class Run : public State
{

	Player*  mPlayer;
	Bottom* mBottom;
	Image* mRunKirby;
	Animation* mLeftAnimation;
	Animation* mRightAnimation;
	Animation* mCurrentAnimation;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);


};


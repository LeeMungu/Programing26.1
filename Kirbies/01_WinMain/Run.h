#pragma once
#include "State.h"

#include "GameObject.h"
#include "Player.h"
#include "Bottom.h"

class State;
class Run : public State
{
	enum class LeftRunState
	{
		LeftMove = 0,
		End
	};
	enum class RightRunState
	{
		RightMove = 0,
		End
	};

	Player*  mPlayer;
	Bottom* mBottom;
	Image* mRunKirby;
	Animation* mLeftAnimation;
	Animation* mRightAnimation;
	LeftRunState mLeftRunState;
	RightRunState mRightRunState;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);


};


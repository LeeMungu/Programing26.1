#pragma once
#include "State.h"

#include "GameObject.h"
#include "Player.h"
#include "Bottom.h"
#include "StopperObject.h"

class StopperObject;
class State;
class ObjectManager;
class Run : public State
{
	StopperObject* mStopperObject;
	Bottom* mBottom;
	Image* mRunKirby;
	Image* mGoalKirby;
	Animation* mLeftAnimation;
	Animation* mRightAnimation;
	Animation* mGoalKirbyAnimation;
	Animation* mCurrentAnimation;

	RECT mRunKirbyRect;
	RECT mWall;

	int mFrameCount;
	float mX, mY;

	bool IsCrash;


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);


};


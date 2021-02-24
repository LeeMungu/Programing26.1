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

	float mScaleValue;

	int mFrameCount;
	float mX, mY;

	bool IsCrash;
	bool mIsDestroyed;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void mapRender(HDC map)override;

	bool GetIsDestroyed() { return mIsDestroyed; }
};


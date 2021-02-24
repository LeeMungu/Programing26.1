#pragma once
#include "State.h"

class Climb : public State
{
	enum class State
	{
		Climb,
		Run,
		Fall
	};

	class Bottom* mBottom;

	State mState;

	float mX, mY;

	bool mIsWallCheck;
	bool mIsWalkCheck;
	
	int mClimbCount;

public:
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;

	void ClimbAnim();
	void WalkAnim();
};
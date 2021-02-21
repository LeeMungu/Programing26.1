#pragma once
#include "State.h"

class Climb : public State
{
	
	class Bottom* mBottom;

	float mX, mY;

	bool mIsWallCheck;
	bool mIsWalkCheck;
	

public:
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;

	void ClimbAnim();
	void WalkAnim();
};
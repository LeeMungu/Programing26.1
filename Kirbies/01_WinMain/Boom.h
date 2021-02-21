#pragma once
#include "State.h"
class Boom : public State
{
	//float mTimeTemp = 0;
	//int mCountNum = 5;
	//bool mIsDead = false;

	bool mIsFirstUpdate = false;

public:
	void Update()override;
	void Render(HDC hdc)override;
};
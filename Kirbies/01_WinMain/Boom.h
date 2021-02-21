#pragma once
#include "State.h"
class Boom : public State
{
	//float mTimeTemp = 0;
	//int mCountNum = 5;
	//bool mIsDead = false;

	bool mIsFirstUpdate = false;

public:
	virtual void Update() {}
	virtual void Render(HDC hdc) {}
};
#pragma once
#include "State.h"
class Boom : public State
{
	//float mTimeTemp = 0;
	//int mCountNum = 5;
	//bool mIsDead = false;

	//bool mIsFirstUpdate = false;
	class Bottom* mBottom;
	
	class Effect* mEffect;
	RECT mPlayerRect;
	float mX, mY;
public:
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
};
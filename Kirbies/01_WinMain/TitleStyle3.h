#pragma once
#include "Title.h"

class TitleStyle3 : public Title
{
	enum class State
	{
		LeftToRight,
		RightToLeft,
		Stop
	};
	float mLeftLimit;
	float mRightLimit;
	State mState;
public:
	TitleStyle3(wstring key);
	void Init()override;
	void Release()override;
	void Update()override;
};
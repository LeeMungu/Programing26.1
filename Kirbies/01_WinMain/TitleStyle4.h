#pragma once
#include "Title.h"

class TitleStyle4 : public Title
{
public:
	enum class State
	{
		LeftToRight,
		RightToLeft,
		Stop
	};
private:
	float mLeftLimit;
	float mRightLimit;
	State mState;
public:
	TitleStyle4(wstring key, TitleStyle4::State state);
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
};


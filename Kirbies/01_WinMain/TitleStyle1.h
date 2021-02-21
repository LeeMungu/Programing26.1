#pragma once
#include "Title.h"

class TitleStyle1 : public Title
{
	enum class State
	{
		Up,
		Down,
		Stop
	};
	TitleStyle1::State mState;
	float mUpLimit;
public:
	TitleStyle1(wstring key);
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
};


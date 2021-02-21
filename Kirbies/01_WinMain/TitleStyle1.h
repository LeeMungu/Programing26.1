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
	void Init()override;
	void Release()override;
	void Update()override;
};


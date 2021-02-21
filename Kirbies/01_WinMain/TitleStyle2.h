#pragma once
#include "Title.h"

class TitleStyle2 : public Title
{
	enum class State
	{
		SizeUp,
		SizeDown,
		Stop
	};
	TitleStyle2::State mState;
	
	float mSizeLimit;
public:
	TitleStyle2(wstring key);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};


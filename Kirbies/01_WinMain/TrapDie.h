#pragma once
#include "State.h"
class Image;
class Animation;
class TrapDie : public State
{
	class Bottom* mBottom;

	class Effect* mEffect;
	RECT mPlayerRect;

	Image* mFallDeadKirby;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;
};


#pragma once
#include "State.h"

class Bottom;
class Image;
class DigPoint;

class Dig :public State
{
	bool mIsStateStart = false;

	Bottom* mBottom;

	float mTime = 0;
public:
	void Update()override;
	void Render(HDC hdc)override;
};


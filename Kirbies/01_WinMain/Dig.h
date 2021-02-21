#pragma once
#include "State.h"

class Bottom;
class Image;
class DigPoint;

class Dig :public State
{

	Bottom* mBottom;
	RECT mDigRect;
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;

public:
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
};


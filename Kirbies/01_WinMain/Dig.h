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

	bool mIsFallCheck;
	bool mIsDigCheck;

public:
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;


	void FallAnimation();

	void DigAnimation();
};


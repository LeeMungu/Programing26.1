#pragma once
#include "State.h"

class Bottom;
class Image;
class DigPoint;
class Effect;
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

	float mRadius;
	Effect* mEffect;

public:
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;


	void FallAnimation();

	void DigAnimation();

	float GetRadius() { return mRadius; }
	void SetRadius(float x) { mRadius = x; }

	bool GetDigCheck() { return mIsDigCheck; }
};


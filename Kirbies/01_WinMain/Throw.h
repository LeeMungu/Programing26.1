#pragma once
#include "State.h"

class Bottom;

class Throw : public State
{
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	float mThrowGravity;
	Bottom* mBottom;
	float mTimer;

	bool misTrigger;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;
};


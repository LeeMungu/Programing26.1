#pragma once
#include "State.h"

class Climb : public State
{
	class Player* mPlayer;
	class Bottom* mBottom;

	float mX, mY;

	

public:
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
};
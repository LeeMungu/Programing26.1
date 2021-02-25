#pragma once
#include "GameObject.h"
class Image;

enum class State
{
	ReStart,
	End,
	Sound,
	Record
};

class ButtonUi : public GameObject
{
	
	State mState;
	Image* mImage;
	int mIndexX, mIndexY;

public:
	ButtonUi(State state, float x, float y);
	void Init()override;
	void Update() override;
	void Release() override;
	void Render(HDC hdc) override;
};


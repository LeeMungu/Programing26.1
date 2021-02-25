#pragma once
#include "GameObject.h"
class Image;

enum class BtnState
{
	ReStart,
	End,
	Sound,
	Record
};

class ButtonUi : public GameObject
{

	BtnState mbtnState;
	Image* mImage;
	int mIndexX, mIndexY;
	int mScaleX, mScaleY;

public:
	ButtonUi(BtnState state, float x, float y);
	void Init()override;
	void Update() override;
	void Release() override;
	void Render(HDC hdc) override;


};


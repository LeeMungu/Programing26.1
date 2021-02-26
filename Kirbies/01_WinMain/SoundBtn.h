#pragma once
#include "GameObject.h"

enum class SoundbtnState
{
	BgmPlus,
	BgmMinus,
	EffPlus,
	EffMinus
};

class Image;

class SoundBtn : public GameObject
{

	SoundbtnState mSoundbtnState;
	Image* mImage;
	int mIndexX, mIndexY;
	int mScaleX, mScaleY;



	public:
		SoundBtn(SoundbtnState state, float x, float y);
		void Init()override;
		void Update() override;
		void Release() override;
		void Render(HDC hdc) override;
};


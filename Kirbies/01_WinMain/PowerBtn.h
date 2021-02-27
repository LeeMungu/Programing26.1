#pragma once

#include "GameObject.h"

class Image;
class PowerBtn : public GameObject
{
	Image* mImage;
	int mFrameX;

	bool mIsBtnOn;
	bool mIsBtnTrigger;

public:
	PowerBtn(const string& name, float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	bool GetIsBtnOn() { return mIsBtnOn; }
	void SetIsBtnOn(bool btnon) { mIsBtnOn = btnon; }
};


#pragma once
#include "Effect.h"

class SpecialAttackEffect : public Effect
{
	Animation* mAttackEffect1;
	Animation* mAttackEffect2;
	Animation* mAttackEffect3;
	float mPlayerX;
	float mPlayerY;
public:
	SpecialAttackEffect(string name, float x, float y, wstring imagekey);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};


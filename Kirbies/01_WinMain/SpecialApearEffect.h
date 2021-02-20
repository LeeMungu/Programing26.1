#pragma once
#include "Effect.h"

class SpecialApearEffect : public Effect
{

public:
	SpecialApearEffect(string name, float x, float y, wstring imagekey, float frameX, int frameY);

	void Init()override;
	void Update()override;
};


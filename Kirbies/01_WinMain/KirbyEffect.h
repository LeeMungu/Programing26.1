#pragma once
#include "Effect.h"
class KirbyEffect : public Effect
{
public:
	KirbyEffect(string name, float x, float y, wstring imagekey, float frameX, int frameY);

	void Init()override;
	void Update()override;
};


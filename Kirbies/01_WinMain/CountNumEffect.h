#pragma once
#include "Effect.h"
class Player;

class CountNumEffect : public Effect
{
	Player* mPlayer;

public:
	CountNumEffect(string name, float x, float y, wstring imagekey);

	void Init()override;
	void Update()override;

	void SetPlayerptr(Player* player) { mPlayer = player; }
};

